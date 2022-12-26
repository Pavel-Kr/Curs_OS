#include "server.h"
#include <QDataStream>

Server::Server()
{
    qDebug()<<"Hello!";
    listen(QHostAddress::Any,5555);
}

void Server::sendToClient(QString str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out << str;
    for(int i=0;i<sockets.size();i++){
        sockets[i]->write(data);
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(deleteSocket()));
    sockets.push_back(socket);
}

void Server::readMessage()
{
    qDebug()<<"read message";
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);
    if(in.status() == QDataStream::Ok){
        qDebug()<<"ok";
        QString str;
        in >> str;
        sendToClient(str);
    }
    else{
        qDebug()<<"QDataStream error";
    }
}

void Server::deleteSocket()
{
    QTcpSocket *Sender = (QTcpSocket*)sender();
    for(int i=0;i<sockets.size();i++){
        if(sockets[i] == Sender){
            qDebug()<<"Deleted user "<<i;
            sockets.removeAt(i);
            break;
        }
    }
    Sender->deleteLater();
}
