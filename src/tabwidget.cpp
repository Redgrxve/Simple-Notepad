#include "tabwidget.h"
#include "texteditwidget.h"
#include "tabbuttonwidget.h"
#include "ui_tabwidget.h"

#include <QTabBar>
#include <QMessageBox>

TabWidget::TabWidget(QWidget* parent)
    : QTabWidget(parent)
    , ui(new Ui::TabWidget)
{
    ui->setupUi(this);
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::openFileInCurrentTab(const QString &filePath)
{
    if (!currentWidget())
        addTabWithButton();

    auto textEdit = getCurrentTextEdit();
    if (!textEdit) {
        QMessageBox::information(this, tr("Error"), tr("Opening the file error"));
        return;
    }

    textEdit->readFile(filePath);
}

void TabWidget::saveCurrentTab(const QString &filePath)
{
    auto textEdit = getCurrentTextEdit();
    if (!textEdit) {
        QMessageBox::information(this, tr("Error"), tr("Save the file error"));
        return;
    }

    textEdit->saveToFile(filePath);
}

int TabWidget::addTabWithButton(const QString& tabText)
{
    TextEditWidget* newTab = new TextEditWidget(this);
    TabButtonWidget* tabButton = new TabButtonWidget(newTab);
    QString newTabText = tabText.isEmpty() ? "NewFile" + QString::number(count() + 1) : tabText;
    int newTabIndex = addTab(newTab, newTabText);
    tabBar()->setTabButton(newTabIndex, QTabBar::RightSide, tabButton);
    connect(tabButton, SIGNAL(closeTabClicked(TabButtonWidget*)), this, SLOT(onCloseTabClicked(TabButtonWidget*)));
    connect(newTab, SIGNAL(textSaved(const QString&)), this, SLOT(onTextSaved(const QString&)));
    connect(newTab, SIGNAL(textUnsaved()), this, SLOT(onTextUnsaved()));
    setCurrentIndex(newTabIndex);
    emit tabAdded(newTabIndex);
    return newTabIndex;
}

TextEditWidget *TabWidget::getCurrentTextEdit()
{
    return qobject_cast<TextEditWidget*>(currentWidget());
}

void TabWidget::setCurrentTabText(const QString& text)
{
    setTabText(currentIndex(), text);
}

QString TabWidget::getCurrentTabText() const
{
    return tabText(currentIndex());
}

bool TabWidget::isCurrentTabUnsaved()
{
    auto textEdit = getCurrentTextEdit();
    if (!textEdit) return false;

    return textEdit->isUnsaved();
}

void TabWidget::onCloseTabClicked(TabButtonWidget* sender)
{
    int tabIndex = tabBar()->tabAt(sender->pos());
    removeTab(tabIndex);
    emit tabClosed(tabIndex);
}

void TabWidget::onTextSaved(const QString& fileName)
{
    setCurrentTabText(fileName);
}

void TabWidget::onTextUnsaved()
{
    setCurrentTabText(getCurrentTabText() + "*");
    emit tabUnsaved();
}

