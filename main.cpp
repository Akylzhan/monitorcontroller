#include <QApplication>
#include <QMessageBox>
#include <QSharedMemory>

#include "trayicon.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSharedMemory shm("memorycontroller/shared");
    if (!shm.create(42)) {
        QMessageBox::warning(nullptr, "Warning!", "Another instance is already running");
        app.exit(0);
        return 0;
    }

    TrayIcon w;
    w.show();
    return app.exec();
}
