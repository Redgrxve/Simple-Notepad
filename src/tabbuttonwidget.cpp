#include "tabbuttonwidget.h"
#include "ui_tabbuttonwidget.h"

TabButtonWidget::TabButtonWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TabButtonWidget)
{
    ui->setupUi(this);

    connect(ui->addTabButton, SIGNAL(clicked(bool)), this, SLOT(onAddTabClicked()));
    connect(ui->closeTabButton, SIGNAL(clicked(bool)), this, SLOT(onCloseTabClicked()));
}

TabButtonWidget::~TabButtonWidget()
{
    delete ui;
}

void TabButtonWidget::setVisibleAddButton(bool visible) const
{
    ui->addTabButton->setVisible(visible);
}

void TabButtonWidget::setVisibleCloseButton(bool visible) const
{
    ui->closeTabButton->setVisible(visible);
}

void TabButtonWidget::onAddTabClicked()
{
    emit addTabClicked();
    ui->addTabButton->hide();
}

void TabButtonWidget::onCloseTabClicked()
{
    emit closeTabClicked(this);
}


