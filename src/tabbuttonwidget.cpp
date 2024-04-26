#include "tabbuttonwidget.h"
#include "ui_tabbuttonwidget.h"

TabButtonWidget::TabButtonWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TabButtonWidget)
{
    ui->setupUi(this);

    connect(ui->closeTabButton, SIGNAL(clicked(bool)), this, SLOT(onCloseTabClicked()));
}

TabButtonWidget::~TabButtonWidget()
{
    delete ui;
}

void TabButtonWidget::onCloseTabClicked()
{
    emit closeTabClicked(this);
}


