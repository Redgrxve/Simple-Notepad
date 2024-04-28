#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texteditwidget.h"
#include "utils.h"
#include "unsavedfilesdialog.h"

#include <QtWidgets>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tabWidget, SIGNAL(tabAdded(int)), this, SLOT(onTabAdded()));
    connect(ui->tabWidget, SIGNAL(tabClosed(int)), this, SLOT(onTabClosed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewTriggered()
{
    ui->tabWidget->addTabWithButton();
}

void MainWindow::onOpenTriggered()
{
    if (ui->tabWidget->isCurrentTabUnsaved()) {
        UnsavedFilesDialog* saveDialog = new UnsavedFilesDialog(this);
        QString dialogLabel = "Do you want to save " + ui->tabWidget->getCurrentTabText();
        dialogLabel[dialogLabel.length() - 1] = '?';
        saveDialog->setLabel(dialogLabel);
        connect(saveDialog, SIGNAL(saveAccepted()), this, SLOT(onSaveDialogAccepted()));
        connect(saveDialog, SIGNAL(saveRejected()), this, SLOT(onSaveDialogRejected()));
        saveDialog->exec();
        return;
    }

    QString filePath = Utils::getOpenFileName(this);
    if (filePath.isEmpty()) return;

    ui->tabWidget->openFileInCurrentTab(filePath);
    ui->statusbar->showMessage(tr("The file readed: ") + filePath);
}

void MainWindow::onSaveTriggered()
{
    QString filePath = ui->tabWidget->getCurrentTextEdit()->getFilePath();
    if (filePath.isEmpty()) {
        onSaveAsTriggered();
        return;
    }

    ui->tabWidget->saveCurrentTab(filePath);
    ui->statusbar->showMessage(tr("The file saved: ") + filePath);
}

void MainWindow::onSaveAsTriggered()
{
    QString filePath = Utils::getSaveFileName(this);
    if (filePath.isEmpty()) return;

    ui->tabWidget->saveCurrentTab(filePath);
    ui->statusbar->showMessage(tr("The file saved: ") + filePath);
}

void MainWindow::onTabAdded()
{
    if (ui->tabWidget->count() == 1) {
        ui->actionSave->setEnabled(true);
        ui->actionSave_As->setEnabled(true);
    }
}

void MainWindow::onTabClosed()
{
    if (ui->tabWidget->count() == 0) {
        ui->actionSave->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
    }
}

void MainWindow::onSaveDialogAccepted()
{
    onSaveAsTriggered();
    onOpenTriggered();
}

void MainWindow::onSaveDialogRejected()
{
    QString filePath = Utils::getOpenFileName(this);
    if (filePath.isEmpty()) return;

    ui->tabWidget->openFileInCurrentTab(filePath);
    ui->statusbar->showMessage(tr("The file readed: ") + filePath);
}


