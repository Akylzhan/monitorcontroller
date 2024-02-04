#include "trayicon.h"

#include <QApplication>
#include <QCheckBox>
#include <QSlider>

TrayIcon::TrayIcon(QWidget *parent)
    : QSystemTrayIcon(parent)
    , menu(new QMenu(nullptr))
    , defaultIcon(QIcon("://icon.png"))
    , coffeeIcon(QIcon("://coffee.png"))
{
    setIcon(defaultIcon);

    caffeineSubmenu = new QMenu("Caffeine", menu);
    initTrayMenu();
    show();
}

TrayIcon::~TrayIcon()
{
    menu->clear();
    delete menu;
}

void TrayIcon::initTrayMenu()
{
    createCaffeineActions();
    createActions();

    caffeineSubmenu->addAction(keepDisplayOnAction);
    caffeineSubmenu->addAction(drinkCaffeineAction);

    menu->addAction(sliderAction);
    menu->addSeparator();
    menu->addMenu(caffeineSubmenu);
    menu->addSeparator();
    menu->addAction(quitAction);

    setContextMenu(menu);
}

void TrayIcon::createCaffeineActions()
{
    auto checkBox = new QCheckBox(tr("Keep Display On"), nullptr);
    checkBox->setChecked(caffeine.keepDisplayOn);

    connect(checkBox, &QCheckBox::clicked, this, [this](bool checked) {
        caffeine.keepDisplayOn = checked;
    });

    keepDisplayOnAction = new QWidgetAction(caffeineSubmenu);
    keepDisplayOnAction->setDefaultWidget(checkBox);

    drinkCaffeineAction = new QAction(tr("Start"), caffeineSubmenu);

    connect(drinkCaffeineAction, &QAction::triggered, this, [this](bool checked) {
        if (caffeine.isDrinking) {
            setIcon(defaultIcon);

            drinkCaffeineAction->setText(tr("Start"));
            caffeine.stopDrinking();
        } else {
            setIcon(coffeeIcon);

            drinkCaffeineAction->setText(tr("Stop"));
            caffeine.startDrinking();
        }
    });
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
            border-radius: 3px;
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

    connect(slider, &QAbstractSlider::valueChanged, this, [this](int newValue) {
        monitorController.setBrightness(newValue);
    });

    connect(this, &QSystemTrayIcon::activated, this, [this, slider]() {
        bool found = monitorController.findPrimaryMonitor();
        slider->setEnabled(found);
        caffeineSubmenu->setEnabled(found);
        if (!found) {
            return;
        }
        slider->setValue(monitorController.getCurrentBrightness());
    });

    sliderAction = new QWidgetAction(menu);
    sliderAction->setDefaultWidget(slider);

    quitAction = new QAction(tr("Quit"), menu);
    connect(quitAction, &QAction::triggered, this, &QApplication::quit);
}
