#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texteditwidget.h"
#include <QtWidgets>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::onOpenTriggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select file"),
        QDir::homePath(),
        tr("Text files (*.txt *.bat *.cpp *.vbs *.pro);;All files (*.*);;*.txt;;*.bat;;*.cpp;;*.vbs;;*pro")
    );

    if (!filePath.isEmpty())
        openFile(filePath);
}

void MainWindow::onSaveTriggered()
{
    if (currentFilePath.isEmpty()) {
        onSaveAsTriggered();
        return;
    }

    saveFile(currentFilePath);
}

void MainWindow::onSaveAsTriggered()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Select file",
        QDir::homePath(),
        "*.txt;;*.bat;;*.cpp;;*.vbs;;*.pro"
    );

    if (!filePath.isEmpty())
        saveFile(filePath);
}

