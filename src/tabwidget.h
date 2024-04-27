#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

class TabButtonWidget;

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    ~TabWidget();

    int addTabWithButton(const QString& tabText = "");
    void setCurrentTabText(const QString& text);
    QString getCurrentTabText() const;

private:
    Ui::TabWidget *ui;

signals:
    void tabClosed(int index);
    void tabEdited();

private slots:
    void onCloseTabClicked(TabButtonWidget* sender);
    void onTabEdited();
};

#endif // TABWIDGET_H
