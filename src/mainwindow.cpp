#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textfileeditwidget.h"
#include "utils.h"

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

void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
    ui->tabWidget->saveAllUnsavedTabs();
    QMainWindow::closeEvent(closeEvent);
}

void MainWindow::onNewTriggered()
{
    ui->tabWidget->addTabWithButton();
}

void MainWindow::onOpenTriggered()
{
    QString filePath = Utils::getOpenFileName(this);
    if (filePath.isEmpty()) return;

    ui->tabWidget->openFileInNewTab(filePath);
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


