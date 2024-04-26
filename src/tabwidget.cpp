#include "tabwidget.h"
#include "texteditwidget.h"
#include "tabbuttonwidget.h"
#include "ui_tabwidget.h"
#include <QTabBar>

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
{
    ui->setupUi(this);

    TabButtonWidget* tabButton = new TabButtonWidget(ui->starterTab);
    tabBar()->setTabButton(0, QTabBar::RightSide, tabButton);
    connect(tabButton, SIGNAL(addTabClicked()), this, SLOT(onAddTabClicked()));
    connect(tabButton, SIGNAL(closeTabClicked(TabButtonWidget*)), this, SLOT(onCloseTabClicked(TabButtonWidget*)));
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::onAddTabClicked()
{
    TextEditWidget* newTab = new TextEditWidget(this);
    int newTabIndex = addTab(newTab, "New file");

    TabButtonWidget* tabButton = new TabButtonWidget(newTab);
    tabBar()->setTabButton(newTabIndex, QTabBar::RightSide, tabButton);
    connect(tabButton, SIGNAL(addTabClicked()), this, SLOT(onAddTabClicked()));
    connect(tabButton, SIGNAL(closeTabClicked(TabButtonWidget*)), this, SLOT(onCloseTabClicked(TabButtonWidget*)));

    setCurrentIndex(newTabIndex);
}

void TabWidget::onCloseTabClicked(TabButtonWidget* sender)
{
    if (count() <= 1) return;

    removeTab(tabBar()->tabAt(sender->pos()));

    if (count() == 1) {
        auto tabButtonWidget = qobject_cast<TabButtonWidget*>(tabBar()->tabButton(0, QTabBar::RightSide));
        if (tabButtonWidget)
            tabButtonWidget->setVisibleAddButton(true);
    }
}
