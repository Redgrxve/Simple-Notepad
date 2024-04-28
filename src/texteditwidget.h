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

    void readFile(const QString& filePath);
    void saveToFile(const QString& filePath);

    void setText(const QString& text);
    QString getText() const;
    QString getFilePath() const { return filePath; }
    QTextEdit* textEdit() const;
    bool isUnsaved() const { return !isSaved; }

private:
    Ui::TextEditWidget *ui;
    bool isSaved = true;
    QString filePath = "";

signals:
    void textSaved(const QString& filePath);
    void textUnsaved();

private slots:
    void onTextChanged();
};

#endif // TEXTEDITWIDGET_H
