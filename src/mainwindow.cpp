#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texteditwidget.h"
#include "utils.h"
#include <QtWidgets>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tabWidget, SIGNAL(tabClosed(int)), this, SLOT(onTabClosed(int)));
    connect(ui->tabWidget->tabBar(), SIGNAL(tabMoved(int,int)), this, SLOT(onTabMoved(int, int)));
    connect(ui->tabWidget, SIGNAL(tabEdited()), this, SLOT(onTabEdited()));
    filePaths.push_back("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "File can't be opened");
        ui->statusbar->showMessage("Open the file error");
        return;
    }

    auto textEditWidget = qobject_cast<TextEditWidget*>(ui->tabWidget->currentWidget());
    if (!textEditWidget) {
        file.close();
        QMessageBox::information(this, tr("Error"), tr("Opening the file error"));
        ui->statusbar->showMessage(tr("Opening the file error"));
        return;
    }

    QTextStream stream(&file);
    QString buffer = stream.readAll();
    file.close();
    textEditWidget->setText(buffer);
    ui->statusbar->showMessage("The file readed: " + filePath);
    ui->tabWidget->setCurrentTabText(QFileInfo(filePath).fileName());
}

void MainWindow::saveFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, tr("Error"), tr("File can't be saved"));
        ui->statusbar->showMessage(tr("Save the file error"));
        return;
    }

    auto textEditWidget = qobject_cast<TextEditWidget*>(ui->tabWidget->currentWidget());
    if (!textEditWidget) {
        file.close();
        QMessageBox::information(this, tr("Error"), tr("File can't be saved"));
        ui->statusbar->showMessage(tr("Save the file error"));
        return;
    }

    QTextStream stream(&file);
    stream << textEditWidget->getText();
    file.close();
    ui->statusbar->showMessage("The file saved: " + filePath);
}

void MainWindow::onNewTriggered()
{
    ui->tabWidget->addTabWithButton();
    filePaths.push_back("");
}

void MainWindow::onOpenTriggered()
{
    QString filePath = Utils::getOpenFileName(this);
    if (filePath.isEmpty()) return;

    openFile(filePath);
    filePaths[ui->tabWidget->currentIndex()] = filePath;
}

void MainWindow::onSaveTriggered()
{
    QString currentFilePath = filePaths[ui->tabWidget->currentIndex()];
    if (currentFilePath.isEmpty()) {
        onSaveAsTriggered();
        return;
    }

    saveFile(currentFilePath);
}

void MainWindow::onSaveAsTriggered()
{
    QString filePath = Utils::getSaveFileName(this);
    if (filePath.isEmpty()) return;

    saveFile(filePath);
    openFile(filePath);
    filePaths[ui->tabWidget->currentIndex()] = filePath;
}

void MainWindow::onTabClosed(int tabIndex)
{
    filePaths.removeAt(tabIndex);
}

void MainWindow::onTabMoved(int from, int to)
{
    filePaths.swapItemsAt(from, to);
}

void MainWindow::onTabEdited()
{
    // if (ui->tabWidget->currentTabChanged()) return;

    // QString currentTabText = ui->tabWidget->getCurrentTabText();
    // ui->tabWidget->setCurrentTabText(currentTabText + "*");
}

