#ifndef TABBUTTONWIDGET_H
#define TABBUTTONWIDGET_H

#include <QWidget>

namespace Ui {
class TabButtonWidget;
}

class TabButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabButtonWidget(QWidget *parent = nullptr);
    ~TabButtonWidget();

private:
    Ui::TabButtonWidget *ui;

signals:
    void closeTabClicked(TabButtonWidget*);

private slots:
    void onCloseTabClicked();
};

#endif // TABBUTTONWIDGET_H
