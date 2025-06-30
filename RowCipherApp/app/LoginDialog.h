#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    bool isAuthenticated() const { return m_authenticated; }

private slots:
    void on_loginButton_clicked();
    void on_changePasswordButton_clicked();

private:
    Ui::LoginDialog *ui;
    bool m_authenticated = false;
    bool authenticate(const QString &password);
    void savePassword(const QString &password);
};

#endif
