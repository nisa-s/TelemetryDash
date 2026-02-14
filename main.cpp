#include "TelemetryDash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelemetryDash w;
    w.show();
    return a.exec();
}