#include "filedialog.h"
#include "ui_filedialog.h"
#include <QFileDialog>

FileDialog::FileDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileDialog)
{
    ui->setupUi(this);
    setFixedHeight(sizeHint().height());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(onToolButtonClicked()));
}


FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::onAccepted()
{
    emit filePath(ui->lineEdit->text());
    close();
}

void FileDialog::onToolButtonClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select file", QDir::homePath());
    ui->lineEdit->setText(filePath);
}
