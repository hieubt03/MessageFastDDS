#include "SubscriberApp.h"
#include <QtWidgets/QApplication>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubscriberApp w;
    w.show();
    return a.exec();
}
