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

private:
    Ui::TabWidget *ui;

private slots:
    void onAddTabClicked();
    void onCloseTabClicked(TabButtonWidget* sender);
};

#endif // TABWIDGET_H
