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
    QStringList filePaths;

    void openFile(const QString& filePath);
    void saveFile(const QString& filePath);

private slots:
    void onNewTriggered();
    void onOpenTriggered();
    void onSaveTriggered();
    void onSaveAsTriggered();

    void onTabClosed(int tabIndex);
    void onTabMoved(int from, int to);
    void onTabEdited();
};
#endif // MAINWINDOW_H
