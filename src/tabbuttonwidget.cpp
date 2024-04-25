#include "tabbuttonwidget.h"
#include "ui_tabbuttonwidget.h"

TabButtonWidget::TabButtonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabButtonWidget)
{
    ui->setupUi(this);
}

TabButtonWidget::~TabButtonWidget()
{
    delete ui;
}
