#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent* closeEvent) override;

private slots:
    void onNewTriggered();
    void onOpenTriggered();
    void onSaveTriggered();
    void onSaveAsTriggered();

    void onTabAdded();
    void onTabClosed();
};
#endif // MAINWINDOW_H
