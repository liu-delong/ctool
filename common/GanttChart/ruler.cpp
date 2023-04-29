#include "ruler.h"

#include <QPainter>

Ruler::Ruler(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background:#ffffff;");
}

void Ruler::Init(double stride, int pixPerSmallCell, QString unit)
{
    stride_ = stride;
    pix_per_small_cell_ = pixPerSmallCell;
    unit_ = unit;
    update();
}

void Ruler::Add(double to)
{
    if(max_ <= to)
    {
        max_ = to + 100;
    }

    if(max_*pix_per_small_cell_ > width())
    {
        this->setFixedSize(max_*pix_per_small_cell_+100,
                           height());
        emit sgWidthChange(max_*pix_per_small_cell_ + 100);
    }

    update();
}

void Ruler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#ffffff"));
    p.drawRect(rect());

    QPen pen;
    pen.setColor(Qt::black);
    p.setPen(pen);

    int h = height();
    //first line 0
    QString t("%1 %2");
    p.drawLine(QLine(30, h/2, 30, h));
    p.drawText(30-2*pix_per_small_cell_, h/4, t.arg(0).arg(unit_));

    for (int i=0; i<max_; ++i)
    {
        int x = (i+1)*pix_per_small_cell_ + 30;
        if(((i+1)%10 == 0))
        {
            p.drawLine(QLine(x, h/2, x, h));
            p.drawText(x-2*pix_per_small_cell_, h/4, t.arg((i+1)/10 * stride_).arg(unit_));
        }
        else
        {
            p.drawLine(QLine(x, h*3/4, x, h));
        }
    }
}
