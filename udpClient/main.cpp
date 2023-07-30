#include "udpclient.h"
#include "HeightIndicatorWidget.h"
#include "UdpServer.h"

#include <QApplication>
#include <QMetaObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UdpClient w;
    HeightIndicatorWidget p;
    return a.exec();
}
