#include "unsavedfilesdialog.h"
#include "ui_unsavedfilesdialog.h"

UnsavedFilesDialog::UnsavedFilesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UnsavedFilesDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onYesClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(onNoClicked()));
}

UnsavedFilesDialog::~UnsavedFilesDialog()
{
    delete ui;
}

void UnsavedFilesDialog::setLabel(const QString &text)
{
    ui->label->setText(text);
    setFixedSize(sizeHint().width(), sizeHint().height());
}

void UnsavedFilesDialog::onYesClicked()
{
    close();
    emit saveAccepted();
}

void UnsavedFilesDialog::onNoClicked()
{
    close();
    emit saveRejected();
}
