#ifndef TEXTEDITWIDGET_H
#define TEXTEDITWIDGET_H

#include <QWidget>

class QTextEdit;

namespace Ui {
class TextEditWidget;
}

class TextEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditWidget(QWidget *parent = nullptr);
    ~TextEditWidget();

    void setText(const QString& text);
    QString getText() const;
    QTextEdit* textEdit() const;

private:
    Ui::TextEditWidget *ui;

signals:
    void textChanged();

private slots:
    void onTextChanged();
};

#endif // TEXTEDITWIDGET_H
