#ifndef TRAYICON_H
#define TRAYICON_H

#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QWidgetAction>

#include "monitorcontroller.h"

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon(QWidget *parent = nullptr);
    ~TrayIcon();

private slots:
    void brightnessChanged(int newValue);

private:
    void createActions();
    void initTrayMenu();

    QWidgetAction *sliderAction;
    QAction *quitAction;
    QMenu *menu;
    
    MonitorController displayController;
};
#endif // TRAYICON_H
