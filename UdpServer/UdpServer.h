#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QWidget>
#include <QUdpSocket>
#include <QTimer>
#include <QSlider>
#include <QLabel>


class UdpServer : public QWidget
{
    Q_OBJECT

public:
    UdpServer(QWidget *parent = nullptr);
    void setConnection(bool signal){
        connection = signal;
    }

private:
    bool connection = false;

};

#endif // UDPSERVER_H
