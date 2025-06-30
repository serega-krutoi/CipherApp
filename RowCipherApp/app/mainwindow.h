#pragma once

#include <QMainWindow>
#include <memory>
#include <QMessageBox>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ICipher;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_encryptButton_clicked();
    void on_comboBox_currentTextChanged(const QString &text);
    void on_lineEditPath_clicked();

    void on_comboBox_TextWork_currentTextChanged(const QString &text);

    void on_decryptButton_clicked();

    void on_encryptTextButton_clicked();
    void on_decryptTextButton_clicked();
    void on_copyResultButton_clicked();
    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ICipher> cipher;
    std::unique_ptr<ICipher> tryLoadCipher(const QString& programName);

    void processFile(const QString &inputPath, const QString &programm);
};
