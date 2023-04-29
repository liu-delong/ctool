#include "planarea.h"

#include <QPainter>

PlanArea::PlanArea(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color:#1a448c;");

    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(30, 10, 10, 10);

    spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout_->addItem(spacer_);
}

void PlanArea::Init(int row, double stride, int pixPerSmallCell, int planHeight)
{
    for (int i=0; i<row; ++i)
    {
        Plan *plan = new Plan(this);
        plan->setMinimumSize(1000, planHeight);
        plan->resize(dynamic_cast<QWidget*>(parent())->width(), planHeight);
        plan->Init(stride, pixPerSmallCell);

        int count = layout_->count();
        layout_->insertWidget(count-1, plan);

        connect(plan, &Plan::sgRectClicked, this, &PlanArea::OnClickRectangle);
        plans_.push_back(plan);
    }


}

int PlanArea::Add(int row, double from, double to, QString color)
{
    if(row > (plans_.count() - 1))
    {
        return -1;
    }

    return plans_[row]->Add(from, to, color);
}

void PlanArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#1a4400"));
    p.drawRect(rect());
}

void PlanArea::OnClickRectangle(int index)
{
    for (int i=0; i<plans_.count(); ++i)
    {
        if(plans_[i] == sender())
        {
            emit sgRectClicked(i, index);
            return;
        }
    }
}
