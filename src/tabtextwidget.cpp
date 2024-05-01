#include "tabtextwidget.h"
#include "textfileeditwidget.h"
#include "tabbuttonwidget.h"
#include "ui_tabtextwidget.h"
#include "unsavedfilesdialog.h"
#include "utils.h"

#include <QTabBar>
#include <QMessageBox>
#include <QFileInfo>

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
    for (int i = 0; i < count(); ++i) {
        if (QFileInfo(filePath) == QFileInfo(getTextEdit(i)->getFilePath())) {
            setCurrentIndex(i);
            return;
        }
    }

    addTabWithButton();
    readFile(filePath);
}

void TabTextWidget::openFileInCurrentTab(const QString &filePath)
{
    for (int i = 0; i < count(); ++i) {
        if (QFileInfo(filePath) == QFileInfo(getTextEdit(i)->getFilePath())) {
            setCurrentIndex(i);
            return;
        }
    }

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
    unsavedTabsIndexes.remove(currentIndex());
}

void TabTextWidget::saveTab(int tabIndex, const QString &filePath)
{
    auto textEdit = getTextEdit(tabIndex);
    if (!textEdit) {
        QMessageBox::information(this, tr("Error"), tr("Save the file error"));
        return;
    }

    textEdit->saveToFile(filePath);
    unsavedTabsIndexes.remove(tabIndex);
}

void TabTextWidget::saveAllUnsavedTabs(bool enableSaveDialog)
{
    while (unsavedTabsIndexes.size() != 0) {
        int unsavedTabIndex = unsavedTabsIndexes.last();
        setCurrentIndex(unsavedTabIndex);

        if (enableSaveDialog) {
            execSaveDialog(unsavedTabIndex);
        } else {
            onSaveDialogAccepted(unsavedTabIndex);
        }
    }
}

int TabTextWidget::addTabWithButton()
{
    TextFileEditWidget* newTab = new TextFileEditWidget(this);
    TabButtonWidget* tabButton = new TabButtonWidget(newTab);
    int newTabIndex = addTab(newTab, "untitled" + QString::number(++newTabNumber));
    tabBar()->setTabButton(newTabIndex, QTabBar::RightSide, tabButton);
    connect(newTab, SIGNAL(textReaded(QString)), this, SLOT(onTextReaded(QString)));
    connect(newTab, SIGNAL(textSaved(QString)), this, SLOT(onTextSaved(QString)));
    connect(newTab, SIGNAL(textUnsaved()), this, SLOT(onTextUnsaved()));
    connect(newTab, SIGNAL(undoAvailable(bool)), this, SLOT(onUndoAvailable(bool)));
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
    QString filePath = getTextEdit(tabIndex)->getFilePath();
    if (!filePath.isEmpty()) {
        saveTab(tabIndex, filePath);
        removeTab(tabIndex);
        return;
    }

    filePath = Utils::getSaveFileName(this);
    if (filePath.isEmpty()) return;

    saveTab(tabIndex, filePath);
    removeTab(tabIndex);
}

void TabTextWidget::onSaveDialogRejected(int tabIndex)
{
    removeTab(tabIndex);
    unsavedTabsIndexes.remove(tabIndex);
}

void TabTextWidget::onTextReaded(const QString &fileName)
{
    setCurrentTabText(fileName);
}

void TabTextWidget::onTextSaved(const QString& fileName)
{
    setCurrentTabText(fileName);
    emit tabSaved();
}

void TabTextWidget::onTextUnsaved()
{
    setCurrentTabText(getCurrentTabText() + "*");
    if (!unsavedTabsIndexes.contains(currentIndex()))
        unsavedTabsIndexes[currentIndex()] = currentIndex();
    emit tabUnsaved();
}

void TabTextWidget::onUndoAvailable(bool available)
{
    if (!available) {
        unsavedTabsIndexes.remove(currentIndex());
        QString tabText = getCurrentTabText();
        tabText.removeLast();
        setCurrentTabText(tabText);
    }
}

