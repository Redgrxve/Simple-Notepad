#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QFileDialog>

class Utils
{
public:
    static QString getOpenFileName(QWidget* parent)
    {
        QString filePath = QFileDialog::getOpenFileName(
            parent,
            "Select file",
            QDir::homePath(),
            "Text files (*.txt *.bat *.cpp *.vbs *.pro);;All files (*.*);;*.txt;;*.bat;;*.cpp;;*.vbs;;*pro"
        );

        return filePath;
    }

    static QString getSaveFileName(QWidget* parent)
    {
        QString filePath = QFileDialog::getSaveFileName(
            parent,
            "Select file",
            QDir::homePath(),
            "*.txt;;*.bat;;*.cpp;;*.vbs;;*.pro"
        );

        return filePath;
    }
};

#endif // UTILS_H
