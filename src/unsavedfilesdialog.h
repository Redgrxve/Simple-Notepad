#ifndef UNSAVEDFILESDIALOG_H
#define UNSAVEDFILESDIALOG_H

#include <QDialog>

namespace Ui {
class UnsavedFilesDialog;
}

class UnsavedFilesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnsavedFilesDialog(int fileTabIndex, QWidget *parent = nullptr);
    ~UnsavedFilesDialog();

    void setLabel(const QString& text);

private:
    Ui::UnsavedFilesDialog *ui;
    int tabIndex;

signals:
    void saveAccepted(int tabIndex);
    void saveRejected(int tabIndex);

private slots:
    void onYesClicked();
    void onNoClicked();
};

#endif // UNSAVEDFILESDIALOG_H
