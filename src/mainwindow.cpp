#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedialog.h"
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

void MainWindow::openFile(const QString &filePath)
{
    QFile mFile(filePath);
    if (!mFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "File can't be opened");
        ui->statusbar->showMessage("Open the file error");
        return;
    }

    currentFilePath = filePath;
    QTextStream stream(&mFile);
    QString buffer = stream.readAll();
    ui->textEdit->setText(buffer);
    ui->statusbar->showMessage("The file readed: " + filePath);
    mFile.close();
}

void MainWindow::saveFile(const QString &filePath)
{
    QFile mFile(filePath);
    if (!mFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, "Error", "File can't be saved");
        ui->statusbar->showMessage("Save the file error");
        return;
    }

    currentFilePath = filePath;
    QTextStream stream(&mFile);
    stream << ui->textEdit->toPlainText();
    mFile.close();
    ui->statusbar->showMessage("The file saved: " + filePath);
}
