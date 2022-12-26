#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    this->name = name;
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(handleErrors(QAbstractSocket::SocketError)));
    connect(this->socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(this->socket,SIGNAL(disconnected()),SLOT(deleteLater()));
    socket->connectToHost("127.0.0.1", 5555);
}

void MainWindow::setSocket(QTcpSocket *socket)
{
    this->socket = socket;
}

void MainWindow::sendToServer(QString str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QString message = name + " [" + QTime::currentTime().toString("hh:mm") + "]: " + str;
    out << message;
    socket->write(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}

void MainWindow::readMessage()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok){
        QString str;
        in >> str;
        ui->textBrowser->append(str);
    }
    else{
        qDebug()<<"QDataStream error";
    }
}

void MainWindow::handleErrors(QAbstractSocket::SocketError)
{
    QMessageBox::critical(this,"Ошибка","Не удалось подключиться к серверу, попробуйте позже!\n" + socket->errorString(),QMessageBox::Ok);
    this->close();
}

