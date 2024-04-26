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

    void setVisibleAddButton(bool visible) const;
    void setVisibleCloseButton(bool visible) const;

private:
    Ui::TabButtonWidget *ui;

signals:
    void addTabClicked();
    void closeTabClicked(TabButtonWidget*);

private slots:
    void onAddTabClicked();
    void onCloseTabClicked();
};

#endif // TABBUTTONWIDGET_H
