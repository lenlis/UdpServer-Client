#include "UdpServer.h"


UdpServer::UdpServer(QWidget *parent)
    : QWidget(parent)

{
    auto timer = new QTimer(this);
    timer->setInterval(20);
    timer->start();
    auto socket = new QUdpSocket(this);
    auto sendSocket = new QUdpSocket(this);
    int port = 65001;

    socket->bind(65002, QUdpSocket::ShareAddress);

    auto slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setSingleStep(1);

    slider->setGeometry(20,60,500,20);
    slider->setRange(0,9999);
    slider->show();

    QLabel *text = new QLabel(this);
    text->setText("Связь с клиентом: ");
    text->setGeometry(20,10,120,20);

    QLabel *con = new QLabel(this);
    con->setGeometry(120,10,30,20);
    auto conTimer = new QTimer(this);
    conTimer->setInterval(2000);
    conTimer->start();
    if(this->connection){
        con->setText("Да");
    }
    else{
        con->setText("Нет");
    }
    connect(conTimer, &QTimer::timeout, this, [this,con](){
        if(this->connection){
            con->setText("Да");
        }
        else{
            con->setText("Нет");
        }
    });



    connect(timer, &QTimer::timeout, this, [this, sendSocket, slider, port](){
        if(this->connection){
         QByteArray data;
         QDataStream out(&data, QIODevice::WriteOnly);
         out << quint16(0xABCD);
         out << quint16(slider->value());
         sendSocket->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, port);
        }
    });

    connect(socket, &QUdpSocket::readyRead, this, [this, socket](){
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());

        QDataStream in(&datagram, QIODevice::ReadOnly);
        quint16 header = 0;
         in >> header;
         qDebug()<<"header";
         if(header == 0x1234){

                this->setConnection(true);
         }
         else{
             this->setConnection(false);
         }
    });


}
