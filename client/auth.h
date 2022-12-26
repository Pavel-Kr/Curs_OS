#ifndef AUTH_H
#define AUTH_H

#include <QMainWindow>
#include <QTcpSocket>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Auth; }
QT_END_NAMESPACE

class Auth : public QMainWindow
{
    Q_OBJECT

public:
    Auth(QWidget *parent = nullptr);
    ~Auth();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Auth *ui;
    QTcpSocket *socket;
    MainWindow *window;
};
#endif // AUTH_H
