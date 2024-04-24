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

void MainWindow::onOpenTriggered()
{
    FileDialog* window = new FileDialog(this);
    connect(window, SIGNAL(filePath(const QString&)), this, SLOT(openFile(const QString&)));
    window->exec();
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
    FileDialog* window = new FileDialog(this);
    connect(window, SIGNAL(filePath(const QString&)), this, SLOT(saveFile(const QString&)));
    window->exec();
}
