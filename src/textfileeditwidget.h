#ifndef TEXTFILEEDITWIDGET_H
#define TEXTFILEEDITWIDGET_H

#include <QWidget>

class QTextEdit;

namespace Ui {
class TextFileEditWidget;
}

class TextFileEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextFileEditWidget(QWidget *parent = nullptr);
    ~TextFileEditWidget();

    void readFile(const QString& filePath);
    void saveToFile(const QString& filePath);

    void setText(const QString& text);
    QString getText() const;
    QString getFilePath() const { return filePath; }
    QTextEdit* textEdit() const;
    bool isUnsaved() const { return !isSaved; }

private:
    Ui::TextFileEditWidget *ui;
    bool isSaved = true;
    QString filePath = "";

signals:
    void textSaved(const QString& filePath);
    void textUnsaved();

private slots:
    void onTextChanged();
};

#endif // TEXTFILEEDITWIDGET_H
