#include "UdpServer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UdpServer w;
    w.show();
    return a.exec();
}
