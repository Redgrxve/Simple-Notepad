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
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), this, SLOT(onUndoAvailable(bool)));
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
    isSaved = false;
    setText(buffer);
    isSaved = true;
    fileInfo = QFileInfo(filePath);
    emit textReaded(fileInfo.fileName());
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
    fileInfo = QFileInfo(filePath);
    emit textSaved(fileInfo.fileName());
}

void TextFileEditWidget::setText(const QString& text)
{
    ui->textEdit->setText(text);
}

QString TextFileEditWidget::getText() const
{
    return ui->textEdit->toPlainText();
}

QString TextFileEditWidget::getFilePath() const
{
    return fileInfo.filePath();
}

QTextEdit* TextFileEditWidget::textEdit() const
{
    return ui->textEdit;
}

bool TextFileEditWidget::isUnsaved() const
{
    return !isSaved;
}

bool TextFileEditWidget::isWrapEnabled() const
{
    return wrapEnabled;
}

void TextFileEditWidget::setLineWrap(bool wrap)
{
    if (wrap) {
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
        wrapEnabled = true;
    } else {
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
        wrapEnabled = false;
    }
}

void TextFileEditWidget::onTextChanged()
{
    if (!isSaved) return;

    isSaved = false;
    emit textUnsaved();
}

void TextFileEditWidget::onUndoAvailable(bool available)
{
    if (!available)
        isSaved = true;
    emit undoAvailable(available);
}
