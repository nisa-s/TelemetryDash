#include "TelemetryDash.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelemetryDash w;
    w.show();
    return a.exec();
}