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
    void clicked(const TabButtonWidget* sender);

private slots:
    void onClicked();
};

#endif // TABBUTTONWIDGET_H
