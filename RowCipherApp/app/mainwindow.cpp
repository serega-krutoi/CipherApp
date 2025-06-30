#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLibrary>
#include <QDir>
#include <QDebug>
#include <QInputDialog>
#include <QClipboard>

#include <memory>
#include <string>

#include "../include/ICipher.h"
#include "../include/ICipherFactory.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, &QTabWidget::currentChanged,
            this, &MainWindow::on_tabWidget_currentChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0) {
        ui->textInputEdit->clear();
        ui->textOutputEdit->clear();
    } else {
        ui->codeWordEdit->clear();
    }
}


unique_ptr<ICipher> MainWindow::tryLoadCipher(const QString& programName) {
    QString pluginPath;

    if (programName == "Кодовое слово") {
        pluginPath = QDir(QCoreApplication::applicationDirPath()).filePath("plugins/libcodeword.so");
    } else if (programName == "Магический квадрат") {
        pluginPath = QDir(QCoreApplication::applicationDirPath()).filePath("plugins/libmagic.so");
    } else if (programName == "Скитала") {
        pluginPath = QDir(QCoreApplication::applicationDirPath()).filePath("plugins/libskitala.so");
    } else {
        QMessageBox::critical(this, "Ошибка", "Выберите корректный шифр");
        return nullptr;
    }

    if (!QFile::exists(pluginPath)) {
        QMessageBox::critical(this, "Ошибка", "Файл плагина не найден:\n" + pluginPath);
        return nullptr;
    }

    QLibrary lib(pluginPath);
    if (!lib.load()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить плагин:\n" + lib.errorString());
        return nullptr;
    }

    typedef ICipherFactory* (*CreateFactoryFunc)();
    CreateFactoryFunc createFactory = (CreateFactoryFunc) lib.resolve("createFactory");

    if (!createFactory) {
        QMessageBox::critical(this, "Ошибка", "Функция createFactory не найдена в плагине");
        return nullptr;
    }

    unique_ptr<ICipherFactory> factory(createFactory());

    bool isFileTabActive = ui->tabWidget->currentIndex() == 0;

    QString param;
    if (isFileTabActive) {
        param = ui->codeWordEdit->text();
    } else {
        param = ui->codeWordEdit_TextWork->text();
    }

    try {
        if (programName == "Кодовое слово") {
            if (param.isEmpty())
                throw runtime_error("Кодовое слово не может быть пустым");
            factory->setParameter("codeword", param.toStdString());
        } else if (programName == "Магический квадрат") {
            if (param.isEmpty())
                throw runtime_error("Введите размерность квадрата");
            factory->setParameter("n", param.toStdString());
        } else if (programName == "Скитала") {
            if (param.isEmpty())
                throw runtime_error("Введите количество строк");
            factory->setParameter("rows", param.toStdString());
        }
    } catch (const exception& ex) {
        QMessageBox::critical(this, "Ошибка параметров", ex.what());
        return nullptr;
    }



    try {
        unique_ptr<ICipher> cipher(factory->create());
        if (!cipher) {
            QMessageBox::critical(this, "Ошибка", "Не удалось создать объект шифра");
            return nullptr;
        }
        return cipher;
    } catch (const exception& ex) {
        QMessageBox::critical(this, "Ошибка создания шифра", ex.what());
        return nullptr;
    }
}


void MainWindow::on_encryptTextButton_clicked()
{
    QString text = ui->textInputEdit->toPlainText();
    if(text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст для шифрования");
        return;
    }

    QString programName = ui->comboBox_TextWork->currentText();
    unique_ptr<ICipher> loadedCipher = tryLoadCipher(programName);
    if(!loadedCipher) return;

    this->cipher = std::move(loadedCipher);


    QByteArray textData = text.toUtf8();
    textData.append('\0');
    vector<uint8_t> binaryData(textData.begin(), textData.end());
    vector<uint8_t> encryptedData = this->cipher->encrypt(binaryData);
    QByteArray encryptedByteArray(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
    ui->textOutputEdit->setPlainText(encryptedByteArray.toBase64());
}

void MainWindow::on_decryptTextButton_clicked()
{
    QString text = ui->textInputEdit->toPlainText();
    if(text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст для дешифрования");
        return;
    }

    QByteArray encryptedData = QByteArray::fromBase64(text.toUtf8());
    if(encryptedData.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат данных");
        return;
    }

    QString programName = ui->comboBox_TextWork->currentText();
    unique_ptr<ICipher> loadedCipher = tryLoadCipher(programName);
    if(!loadedCipher) return;

    this->cipher = std::move(loadedCipher);
    vector<uint8_t> binaryData(encryptedData.begin(), encryptedData.end());
    vector<uint8_t> decryptedData = this->cipher->decrypt(binaryData);
    QByteArray decryptedByteArray(reinterpret_cast<const char*>(decryptedData.data()), decryptedData.size());
    if(decryptedByteArray.endsWith('\0')) {
        decryptedByteArray.chop(1);
    }

    ui->textOutputEdit->setPlainText(QString::fromUtf8(decryptedByteArray));
}

void MainWindow::on_copyResultButton_clicked()
{
    QApplication::clipboard()->setText(ui->textOutputEdit->toPlainText());
    QMessageBox::information(this, "Успех", "Текст скопирован в буфер обмена");
}



void MainWindow::on_encryptButton_clicked() {
    QString filePath = ui->lineEditPath->text();
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите файл");
        return;
    }

    QString programName = ui->comboBox->currentText();
    QString programm = "encrypt";

    unique_ptr<ICipher> loadedCipher = tryLoadCipher(programName);
    if (!loadedCipher) return;

    this->cipher = std::move(loadedCipher);
    processFile(filePath, programm);
}

void MainWindow::on_decryptButton_clicked() {
    QString filePath = ui->lineEditPath->text();
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите файл");
        return;
    }

    QString programName = ui->comboBox->currentText();
    QString programm = "decrypt";

    unique_ptr<ICipher> loadedCipher = tryLoadCipher(programName);
    if (!loadedCipher) return;

    this->cipher = std::move(loadedCipher);
    processFile(filePath, programm);
}

void MainWindow::processFile(const QString &inputPath, const QString &programm)
{
    if (!cipher) {
        QMessageBox::critical(this, "Ошибка", "Шифр не инициализирован");
        return;
    }

    QFileInfo fileInfo(inputPath);
    QString dirPath = fileInfo.absolutePath();
    QString baseName = fileInfo.completeBaseName();
    QString extension = fileInfo.suffix();

    QString encryptedPath = dirPath + QString("/%1_encrypted.bin").arg(baseName);
    QString decryptedPath = dirPath + QString("/decrypted_%1.%2").arg(baseName).arg(extension);

    if (programm == "encrypt") {
        QFileInfo fileInfo(inputPath);
        QString extension = fileInfo.suffix();

        QFile inFile(inputPath);
        if (!inFile.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть входной файл для чтения");
            return;
        }
        QByteArray inputData = inFile.readAll();
        inFile.close();

        QByteArray extendedData;
        QDataStream stream(&extendedData, QIODevice::WriteOnly);
        stream << extension;
        extendedData.append(inputData);

        vector<uint8_t> inputBytes(reinterpret_cast<const uint8_t*>(extendedData.constData()),
                                        reinterpret_cast<const uint8_t*>(extendedData.constData()) + extendedData.size());

        vector<uint8_t> encryptedBytes;
        try {
            encryptedBytes = cipher->encrypt(inputBytes);
        } catch (const exception& ex) {
            QMessageBox::critical(this, "Ошибка шифрования", ex.what());
            return;
        }

        QFile outEncFile(encryptedPath);
        if (!outEncFile.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи зашифрованных данных");
            return;
        }
        outEncFile.write(reinterpret_cast<const char*>(encryptedBytes.data()), encryptedBytes.size());
        outEncFile.close();

        QMessageBox::information(this, "Готово", QString("Файлы %1 создан").arg(encryptedPath));

    } else if (programm == "decrypt") {
        QFile inEncFile(inputPath);
        if (!inEncFile.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл зашифрованных данных для чтения");
            return;
        }
        QByteArray encryptedData = inEncFile.readAll();
        inEncFile.close();

        vector<uint8_t> encryptedDataBytes(reinterpret_cast<const uint8_t*>(encryptedData.constData()),
                                                reinterpret_cast<const uint8_t*>(encryptedData.constData()) + encryptedData.size());

        vector<uint8_t> decryptedBytes;
        try {
            decryptedBytes = cipher->decrypt(encryptedDataBytes);
        } catch (const exception& ex) {
            QMessageBox::critical(this, "Ошибка дешифрования", ex.what());
            return;
        }

        QByteArray decryptedData(reinterpret_cast<const char*>(decryptedBytes.data()), decryptedBytes.size());
        QDataStream stream(&decryptedData, QIODevice::ReadOnly);
        QString originalExtension;
        stream >> originalExtension;

        QByteArray fileContent = decryptedData.mid(stream.device()->pos());

        QFileInfo fileInfo(inputPath);
        QString baseName = fileInfo.completeBaseName();
        if (baseName.endsWith("_encrypted")) {
            baseName.chop(10);
        }
        QString decryptedPath = fileInfo.absolutePath() + QString("/decrypted_%1.%2").arg(baseName).arg(originalExtension);

        QFile outDecFile(decryptedPath);
        if (!outDecFile.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл для записи расшифрованных данных");
            return;
        }
        outDecFile.write(fileContent);
        outDecFile.close();

        QMessageBox::information(this, "Готово", QString("Файл %1 создан").arg(decryptedPath));
    }

}

void MainWindow::on_comboBox_currentTextChanged(const QString &text)
{
    if (text == "Кодовое слово") {
        ui->codeWordEdit->setPlaceholderText("Введите кодовое слово");
    } else if (text == "Магический квадрат") {
        ui->codeWordEdit->setPlaceholderText("Введите размерность (например, 3)");
    } else if (text == "Скитала") {
        ui->codeWordEdit->setPlaceholderText("Введите количество строк (например, 4)");
    }
}

void MainWindow::on_comboBox_TextWork_currentTextChanged(const QString &text)
{
    if (text == "Кодовое слово") {
        ui->codeWordEdit_TextWork->setPlaceholderText("Введите кодовое слово");
    } else if (text == "Магический квадрат") {
        ui->codeWordEdit_TextWork->setPlaceholderText("Введите размерность (например, 3)");
    } else if (text == "Скитала") {
        ui->codeWordEdit_TextWork->setPlaceholderText("Введите количество строк (например, 4)");
    }
}

void MainWindow::on_lineEditPath_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл");
    if (!fileName.isEmpty()) {
        ui->lineEditPath->setText(fileName);
    }
}
