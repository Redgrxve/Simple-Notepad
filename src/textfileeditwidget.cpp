#include "textfileeditwidget.h"
#include "ui_textfileeditwidget.h"

#include <QMessageBox>
#include <QFile>
#include <QFileInfo>

TextFileEditWidget::TextFileEditWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextFileEditWidget)
{
    ui->setupUi(this);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

TextFileEditWidget::~TextFileEditWidget()
{
    delete ui;
}

void TextFileEditWidget::readFile(const QString &filePath)
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

void TextFileEditWidget::saveToFile(const QString &filePath)
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

void TextFileEditWidget::setText(const QString& text)
{
    ui->textEdit->setText(text);
}

QString TextFileEditWidget::getText() const
{
    return ui->textEdit->toPlainText();
}

QTextEdit* TextFileEditWidget::textEdit() const
{
    return ui->textEdit;
}

void TextFileEditWidget::onTextChanged()
{
    if (!isSaved) return;

    isSaved = false;
    emit textUnsaved();
}
