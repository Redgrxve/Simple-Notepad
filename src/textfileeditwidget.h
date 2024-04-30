#ifndef TEXTFILEEDITWIDGET_H
#define TEXTFILEEDITWIDGET_H

#include <QWidget>
#include <QFileInfo>

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
    QString getFilePath() const { return fileInfo.filePath(); }
    QTextEdit* textEdit() const;
    bool isUnsaved() const { return !isSaved; }

private:
    Ui::TextFileEditWidget *ui;
    bool isSaved = true;
    bool isFileReaded = false;
    QFileInfo fileInfo;

signals:
    void textReaded(const QString& filePath);
    void textSaved(const QString& filePath);
    void textUnsaved();
    void undoAvailable(bool available);

private slots:
    void onTextChanged();
    void onUndoAvailable(bool available);
};

#endif // TEXTFILEEDITWIDGET_H
