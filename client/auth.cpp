#include "auth.h"
#include "ui_auth.h"
#include "mainwindow.h"
#include <QAbstractSocket>
#include <QIODevice>
#include <QDebug>
#include <QMessageBox>

Auth::Auth(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Auth)
{
    ui->setupUi(this);
}

Auth::~Auth()
{
    delete ui;
}


void Auth::on_loginButton_clicked()
{
    window = new MainWindow(ui->nicknameEdit->text());
    window->show();
    this->close();
}

