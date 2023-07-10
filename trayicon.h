#ifndef TRAYICON_H
#define TRAYICON_H

#include <QIcon>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>
#include <QWidgetAction>

#include "caffeine.h"
#include "monitorcontroller.h"

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    TrayIcon(QWidget *parent = nullptr);
    ~TrayIcon();

private:
    void initTrayMenu();
    void createCaffeineActions();
    void createActions();

    QWidgetAction *sliderAction;
    QWidgetAction *keepDisplayOnAction; // maybe set QAction checkable?
    QAction *drinkCaffeineAction;
    QAction *quitAction;

    QMenu *caffeineSubmenu;
    QMenu *menu;

    Caffeine caffeine;

    MonitorController displayController;

    QIcon defaultIcon;
    QIcon coffeeIcon;
};
#endif // TRAYICON_H
