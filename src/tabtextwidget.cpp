#include "tabtextwidget.h"
#include "textfileeditwidget.h"
#include "tabbuttonwidget.h"
#include "ui_tabtextwidget.h"
#include "unsavedfilesdialog.h"
#include "utils.h"

#include <QTabBar>
#include <QMessageBox>
#include <QStack>

TabTextWidget::TabTextWidget(QWidget* parent)
    : QTabWidget(parent)
    , ui(new Ui::TabTextWidget)
{
    ui->setupUi(this);

    addTabWithButton();
}

TabTextWidget::~TabTextWidget()
{
    delete ui;
}

void TabTextWidget::openFileInNewTab(const QString &filePath)
{
    addTabWithButton();
    readFile(filePath);
}

void TabTextWidget::openFileInCurrentTab(const QString &filePath)
{
    if (!currentWidget())
        addTabWithButton();

    readFile(filePath);
}

void TabTextWidget::saveCurrentTab(const QString &filePath)
{
    auto textEdit = getCurrentTextEdit();
    if (!textEdit) {
        QMessageBox::information(this, tr("Error"), tr("Save the file error"));
        return;
    }

    textEdit->saveToFile(filePath);
}

void TabTextWidget::saveTab(int tabIndex, const QString &filePath)
{
    auto textEdit = getTextEdit(tabIndex);
    if (!textEdit) {
        QMessageBox::information(this, tr("Error"), tr("Save the file error"));
        return;
    }

    textEdit->saveToFile(filePath);
}

void TabTextWidget::saveAllUnsavedTabs()
{
    std::sort(unsavedTabsIndexes.begin(), unsavedTabsIndexes.end());
    while (unsavedTabsIndexes.size() != 0) {
        int unsevedTabIndex = unsavedTabsIndexes.pop();
        execSaveDialog(unsevedTabIndex);
    }
}

int TabTextWidget::addTabWithButton()
{
    TextFileEditWidget* newTab = new TextFileEditWidget(this);
    TabButtonWidget* tabButton = new TabButtonWidget(newTab);
    int newTabIndex = addTab(newTab, "untitled" + QString::number(++newTabNumber));
    tabBar()->setTabButton(newTabIndex, QTabBar::RightSide, tabButton);
    connect(newTab, SIGNAL(textSaved(const QString&)), this, SLOT(onTextSaved(const QString&)));
    connect(newTab, SIGNAL(textUnsaved()), this, SLOT(onTextUnsaved()));
    connect(tabButton, SIGNAL(clicked(const TabButtonWidget*)), this, SLOT(onCloseTabClicked(const TabButtonWidget*)));
    setCurrentIndex(newTabIndex);
    emit tabAdded(newTabIndex);
    return newTabIndex;
}

TextFileEditWidget *TabTextWidget::getCurrentTextEdit()
{
    return qobject_cast<TextFileEditWidget*>(currentWidget());
}

TextFileEditWidget *TabTextWidget::getTextEdit(int tabIndex)
{
    return qobject_cast<TextFileEditWidget*>(widget(tabIndex));
}

void TabTextWidget::setCurrentTabText(const QString& text)
{
    setTabText(currentIndex(), text);
}

QString TabTextWidget::getCurrentTabText() const
{
    return tabText(currentIndex());
}

bool TabTextWidget::isCurrentTabUnsaved()
{
    auto textEdit = getCurrentTextEdit();
    if (!textEdit) return false;

    return textEdit->isUnsaved();
}

void TabTextWidget::readFile(const QString& filePath)
{
    auto textEdit = getCurrentTextEdit();
    if (!textEdit) {
        QMessageBox::information(this, tr("Error"), tr("Reading the file error"));
        return;
    }

    textEdit->readFile(filePath);
}

void TabTextWidget::execSaveDialog(int unsavedTabIndex)
{
    UnsavedFilesDialog* saveDialog = new UnsavedFilesDialog(unsavedTabIndex, this);
    QString dialogLabel = "Do you want to save " + tabText(unsavedTabIndex);
    dialogLabel[dialogLabel.length() - 1] = '?';
    saveDialog->setLabel(dialogLabel);
    connect(saveDialog, SIGNAL(saveAccepted(int)), this, SLOT(onSaveDialogAccepted(int)));
    connect(saveDialog, SIGNAL(saveRejected(int)), this, SLOT(onSaveDialogRejected(int)));
    saveDialog->exec();
}

void TabTextWidget::onCloseTabClicked(const TabButtonWidget* sender)
{
    int tabIndex = tabBar()->tabAt(sender->pos());

    if (isCurrentTabUnsaved()) {
        execSaveDialog(tabIndex);
        return;
    }

    removeTab(tabIndex);
    if (count() == 0)
        newTabNumber = 0;
    emit tabClosed(tabIndex);
}

void TabTextWidget::onSaveDialogAccepted(int tabIndex)
{
    QString filePath = Utils::getSaveFileName(this);
    if (filePath.isEmpty()) return;

    saveTab(tabIndex, filePath);
    removeTab(tabIndex);
}

void TabTextWidget::onSaveDialogRejected(int tabIndex)
{
    removeTab(tabIndex);
}

void TabTextWidget::onTextSaved(const QString& fileName)
{
    setCurrentTabText(fileName);
    emit tabSaved();
}

void TabTextWidget::onTextUnsaved()
{
    setCurrentTabText(getCurrentTabText() + "*");
    unsavedTabsIndexes.push(currentIndex());
    emit tabUnsaved();
}

