#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QMessageBox>
#include <QSettings>
#include <QInputDialog>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    m_authenticated(false)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация");
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::authenticate(const QString &password)
{
    QSettings settings("MyCompany", "CipherApp");
    QString savedPassword = settings.value("auth/password").toString();

    if (savedPassword.isEmpty()) {
        savePassword(password);
        return true;
    }

    return (password == savedPassword);
}

void LoginDialog::savePassword(const QString &password)
{
    QSettings settings("MyCompany", "CipherApp");
    settings.setValue("auth/password", password);
}

void LoginDialog::on_loginButton_clicked()
{
    QString password = ui->passwordLineEdit->text();

    if (authenticate(password)) {
        m_authenticated = true;
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный пароль");
        ui->passwordLineEdit->clear();
        ui->passwordLineEdit->setFocus();
    }
}

void LoginDialog::on_changePasswordButton_clicked()
{
    bool ok;
    QString currentPassword = QInputDialog::getText(this, "Смена пароля","Текущий пароль:",QLineEdit::Password,"", &ok);

    if (!ok) return;

    if (!authenticate(currentPassword)) {
        QMessageBox::warning(this, "Ошибка", "Неверный текущий пароль");
        return;
    }

    QString newPassword = QInputDialog::getText(this, "Смена пароля","Новый пароль:",QLineEdit::Password,"", &ok);

    if (!ok) return;

    if (newPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пароль не может быть пустым");
        return;
    }

    savePassword(newPassword);
    QMessageBox::information(this, "Успех", "Пароль успешно изменен");
}
