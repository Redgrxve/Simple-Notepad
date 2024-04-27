#include "tabwidget.h"
#include "texteditwidget.h"
#include "tabbuttonwidget.h"
#include "ui_tabwidget.h"
#include <QTabBar>

TabWidget::TabWidget(QWidget* parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
{
    ui->setupUi(this);

    TabButtonWidget* tabButton = new TabButtonWidget(ui->starterTab);
    tabBar()->setTabButton(0, QTabBar::RightSide, tabButton);
    connect(tabButton, SIGNAL(closeTabClicked(TabButtonWidget*)), this, SLOT(onCloseTabClicked(TabButtonWidget*)));
    connect(ui->starterTab, SIGNAL(textChanged()), this, SLOT(onTabEdited()));
}

TabWidget::~TabWidget()
{
    delete ui;
}

int TabWidget::addTabWithButton(const QString& tabText)
{
    TextEditWidget* newTab = new TextEditWidget(this);
    TabButtonWidget* tabButton = new TabButtonWidget(newTab);
    int newTabIndex = addTab(newTab, tabText.isEmpty() ? "New file" : tabText);
    tabBar()->setTabButton(newTabIndex, QTabBar::RightSide, tabButton);
    connect(tabButton, SIGNAL(closeTabClicked(TabButtonWidget*)), this, SLOT(onCloseTabClicked(TabButtonWidget*)));
    connect(newTab, SIGNAL(textChanged()), this, SLOT(onTabEdited()));
    setCurrentIndex(newTabIndex);
    return newTabIndex;
}

void TabWidget::setCurrentTabText(const QString& text)
{
    setTabText(currentIndex(), text);
}

QString TabWidget::getCurrentTabText() const
{
    return tabText(currentIndex());
}

void TabWidget::onCloseTabClicked(TabButtonWidget* sender)
{
    if (count() <= 1) return;

    int tabIndex = tabBar()->tabAt(sender->pos());
    removeTab(tabIndex);
    emit tabClosed(tabIndex);
}

void TabWidget::onTabEdited()
{
    emit tabEdited();
}
