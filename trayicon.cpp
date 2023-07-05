#include "trayicon.h"

#include <QApplication>
#include <QIcon>
#include <QMenu>
#include <QSlider>

TrayIcon::TrayIcon(QWidget *parent)
    : QSystemTrayIcon(QIcon("://icon.png"), parent)
    , menu(new QMenu(nullptr))
{
    initTrayMenu();
    show();
}

TrayIcon::~TrayIcon()
{
    menu->clear();
    delete menu;
}

void TrayIcon::createActions()
{
    auto slider = new QSlider(Qt::Orientation::Vertical, nullptr);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setMinimumHeight(150);

    slider->setStyleSheet(R"(
        QSlider::groove:vertical {
            border: 1px solid #999999;
            width: 10px;
            /* height: 8px;  the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */
            background: #FFFFFF;
            margin: 2px 0;
        }
        
        QSlider::handle:vertical {
            background: #8B7E74;
            border: 1px solid #5c5c5c;
            width: 18px;
            height: 10px;
            /*margin: -2px 0; handle is placed by default on the contents rect of the groove. Expand outside the groove */
            border-radius: 3px;
        }
    )");

    connect(slider, &QAbstractSlider::valueChanged, this, &TrayIcon::brightnessChanged);
    connect(this, &QSystemTrayIcon::activated, this, [this, slider]() {
        slider->setValue(displayController.getCurrentBrightness());
    });

    sliderAction = new QWidgetAction(menu);
    sliderAction->setDefaultWidget(slider);

    quitAction = new QAction(tr("Quit"), menu);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
}

void TrayIcon::initTrayMenu()
{
    createActions();

    menu->addAction(sliderAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    setContextMenu(menu);
}

void TrayIcon::brightnessChanged(int newValue)
{
    displayController.setBrightness(newValue);
}
