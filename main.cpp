#include <QApplication>
#include <QFile>

#include "trayicon.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TrayIcon w;
    w.show();
    return app.exec();
}
