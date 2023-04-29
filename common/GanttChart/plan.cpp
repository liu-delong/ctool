#include "plan.h"

#include <QPainter>

Plan::Plan(QWidget *parent) : QWidget(parent)
{

}

void Plan::Init(double stride, int pixPerSmallCell)
{
    stride_ = stride;
    pix_per_small_cell_ = pixPerSmallCell;
}

int Plan::Add(double from, double to, QString color)
{
    Rect *rect = new Rect(this);
    rect->Init(color);

    QString style_sheet("background-color:%1;");
    rect->setStyleSheet(style_sheet.arg(color));

    int w = (to - from) * pix_per_small_cell_;
    int x = from * pix_per_small_cell_;
    int h = this->height();

    if((w + x + 100) >= width())
    {
        this->resize(width()+ w + x + 500,
                     height());
    }

    rect->setGeometry(x, 0, w, h);
    rect->show();

    connect(rect, &Rect::sgClicked, this, &Plan::OnClickRectangle);

    rects_.push_back(rect);

    return rects_.count() - 1;
}

void Plan::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#1a448c"));
    p.drawRect(rect());
}

void Plan::OnClickRectangle()
{
    for (int i=0; i<rects_.count(); ++i)
    {
        if(rects_[i] == sender())
        {
            emit sgRectClicked(i);
            return;
        }
    }
}
