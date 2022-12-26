#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString name, QWidget *parent = nullptr);
    void setSocket(QTcpSocket *socket);
    void sendToServer(QString str);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void readMessage();
    void handleErrors(QAbstractSocket::SocketError);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QString name;
    QByteArray data;
};

#endif // MAINWINDOW_H
