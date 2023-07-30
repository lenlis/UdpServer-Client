#include "udpclient.h"
#include "HeightIndicatorWidget.h"


UdpClient::UdpClient(QWidget *parent)
    : QWidget(parent)

{
    auto timer = new QTimer(this);
    timer->setInterval(200);
    timer->start();
    auto paint = new HeightIndicatorWidget();
    paint->show();
    auto socket = new QUdpSocket(this);
    auto sendSocket = new QUdpSocket(this);
    int port = 65001;

    socket->bind(port, QUdpSocket::ShareAddress);
    connect(socket, &QUdpSocket::channelReadyRead, this, [this, socket, paint](){
         QByteArray datagram;
         datagram.resize(socket->pendingDatagramSize());
         socket->readDatagram(datagram.data(), datagram.size());

         QDataStream in(&datagram, QIODevice::ReadOnly);
         quint16 header = 0;
         in >> header;
         if(header == 0xABCD){
             quint16 height = 0;
             in >> height;
             paint->setHeight(height);
             paint->repaint();

         }
    });
    connect(timer, &QTimer::timeout, this, [this, sendSocket](){
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << quint16(0x1234);
        sendSocket->writeDatagram(data.data(), data.size(),QHostAddress::Broadcast, 65002);
    });


}

UdpClient::~UdpClient(){

}



