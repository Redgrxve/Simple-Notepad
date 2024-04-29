#include "tabtextwidget.h"
#include "textfileeditwidget.h"
#include "tabbuttonwidget.h"
#include "ui_tabtextwidget.h"
#include "unsavedfilesdialog.h"

#include <QTabBar>
#include <QMessageBox>

TabTextWidget::TabTextWidget(QWidget* parent)
    : QTabWidget(parent)
    , ui(new Ui::TabTextWidget)
{
    ui->setupUi(this);
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

void TabTextWidget::onCloseTabClicked(const TabButtonWidget* sender)
{
    //ДОДЕЛАТЬ
    // if (isCurrentTabUnsaved()) {
    //     UnsavedFilesDialog* saveDialog = new UnsavedFilesDialog(tabIndex, this);
    //     QString dialogLabel = "Do you want to save " + getCurrentTabText();
    //     dialogLabel[dialogLabel.length() - 1] = '?';
    //     saveDialog->setLabel(dialogLabel);
    //     connect(saveDialog, SIGNAL(saveAccepted(int)), this, SLOT(onSaveDialogAccepted(int)));
    //     connect(saveDialog, SIGNAL(saveRejected(int)), this, SLOT(onSaveDialogRejected(int)));
    //     saveDialog->exec();
    //     return;
    // }

    int tabIndex = tabBar()->tabAt(sender->pos());
    removeTab(tabIndex);
    emit tabClosed(tabIndex);
}

void TabTextWidget::onSaveDialogAccepted(int tabIndex)
{
    //ДОДЕЛАТЬ
}

void TabTextWidget::onSaveDialogRejected(int tabIndex)
{
    //ДОДЕЛАТЬ
}

void TabTextWidget::onTextSaved(const QString& fileName)
{
    setCurrentTabText(fileName);
    emit tabSaved();
}

void TabTextWidget::onTextUnsaved()
{
    setCurrentTabText(getCurrentTabText() + "*");
    emit tabUnsaved();
}

