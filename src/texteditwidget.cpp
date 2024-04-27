#include "texteditwidget.h"
#include "ui_texteditwidget.h"

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
    emit textChanged();
}
