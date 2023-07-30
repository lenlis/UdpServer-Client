#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QWidget>
#include <QUdpSocket>
#include <QTimer>

class UdpClient : public QWidget
{
    Q_OBJECT

public:
    UdpClient(QWidget *parent = nullptr);
    ~UdpClient();

private:

};


#endif // UDPCLIENT_H


//#pragma pack(push, 1)
//   struct Message1
//   {
//       quint16 header = 0xABCD;
//       quint16 height;
//   };
//   #pragma pack(pop)

//#pragma pack(push, 1)
//   struct Message2
//   {
//       quint16 header = 0x1234;
//   };
//   #pragma pack(pop)
