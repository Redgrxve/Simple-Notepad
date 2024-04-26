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

    connect(ui->tabWidget, SIGNAL(closeTabClicked(int)), this, SLOT(onTabClose(int)));
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
    currentFilePath = filePath;
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
    currentFilePath = filePath;
    ui->statusbar->showMessage("The file saved: " + filePath);
}

void MainWindow::onNewTriggered()
{
    QString filePath = Utils::getOpenFileName(this);
    if (filePath.isEmpty()) return;

    ui->tabWidget->addTabWithButton("");
    openFile(filePath);
    filePaths.push_back(filePath);
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

void MainWindow::onTabClose(int tabIndex)
{
    filePaths.removeAt(tabIndex);
}

