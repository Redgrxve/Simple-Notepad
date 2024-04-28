#include "texteditwidget.h"
#include "ui_texteditwidget.h"

#include <QMessageBox>
#include <QFile>
#include <QFileInfo>

TextEditWidget::TextEditWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextEditWidget)
{
    ui->setupUi(this);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

TextEditWidget::~TextEditWidget()
{
    delete ui;
}

void TextEditWidget::readFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this, tr("Error"), tr("File can't be opened"));
        return;
    }

    QString buffer = file.readAll();
    file.close();
    setText(buffer);
    isSaved = true;
    this->filePath = filePath;
    emit textSaved(QFileInfo(filePath).fileName());
}

void TextEditWidget::saveToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::information(this, tr("Error"), tr("File can't be opened"));
        return;
    }

    file.write(getText().toUtf8());
    file.close();
    isSaved = true;
    this->filePath = filePath;
    emit textSaved(QFileInfo(filePath).fileName());
}

void TextEditWidget::setText(const QString& text)
{
    ui->textEdit->setText(text);
}

QString TextEditWidget::getText() const
{
    return ui->textEdit->toPlainText();
}

QTextEdit* TextEditWidget::textEdit() const
{
    return ui->textEdit;
}

void TextEditWidget::onTextChanged()
{
    if (!isSaved) return;

    isSaved = false;
    emit textUnsaved();
}
