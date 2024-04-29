#include "unsavedfilesdialog.h"
#include "ui_unsavedfilesdialog.h"

UnsavedFilesDialog::UnsavedFilesDialog(int fileTabIndex, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UnsavedFilesDialog)
    , tabIndex(fileTabIndex)
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
    emit saveAccepted(tabIndex);
}

void UnsavedFilesDialog::onNoClicked()
{
    close();
    emit saveRejected(tabIndex);
}
