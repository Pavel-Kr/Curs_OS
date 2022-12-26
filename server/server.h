#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    void sendToClient(QString str);
private slots:
    void incomingConnection(qintptr socketDescriptor);
    void readMessage();
    void deleteSocket();
private:
    QTcpSocket *socket;
    QVector<QTcpSocket*> sockets;
    QByteArray data;
};

#endif // SERVER_H
