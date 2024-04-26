#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class FileDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString currentFilePath;

    void openFile(const QString& filePath);
    void saveFile(const QString& filePath);

private slots:
    void onOpenTriggered();
    void onSaveTriggered();
    void onSaveAsTriggered();

    void onAddTabClicked();
    void onCloseTabClicked();
};
#endif // MAINWINDOW_H
