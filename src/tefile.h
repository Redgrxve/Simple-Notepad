#ifndef TEFILE_H
#define TEFILE_H

#include <QString>
#include <QFile>

class TEFile
{
public:
    TEFile(const QString& filePath);
    ~TEFile();

private:
    QFile file;
    QString path;
    QString name;
};

#endif // TEFILE_H
