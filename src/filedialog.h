#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = nullptr);
    ~FileDialog();

private:
    Ui::FileDialog *ui;

signals:
    void filePath(const QString& str);

private slots:
    void onAccepted();
    void onToolButtonClicked();
};
#endif // FILEDIALOG_H
