#include "planname.h"

#include <QPainter>

PlanName::PlanName(QWidget *parent) : QWidget(parent)
{
//    this->setStyleSheet("background-color:#1a448c;");

    //    this->resize(200, 1000);

    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(10, 10, 10, 10);
    spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout_->addItem(spacer_);
}

void PlanName::Init(int row, int planHeight)
{
    QString name("文字%1");
    for (int i=0; i<row; ++i)
    {
        QLabel *label = new  QLabel(this);
        label->setMinimumSize(QSize(200, planHeight));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setStyleSheet("background-color:#1a448c;");
        label->setText(name.arg(i));

        int count = layout_->count();
        layout_->insertWidget(count-1, label);

        plan_names_.push_back(label);
    }
}

void PlanName::SetRowName(int row, QString name)
{
    if(row > (plan_names_.count() - 1))
    {
        return;
    }

    plan_names_[row]->setText(name);
}

void PlanName::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#1a4400"));
    p.drawRect(rect());

}
