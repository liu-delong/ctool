#include "rect.h"

#include <QPainter>

Rect::Rect(QWidget *parent) : QWidget(parent)
{

}

void Rect::Init(QString color)
{
    color_ = color;
    update();
}

void Rect::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit sgClicked();
}

void Rect::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(color_));
    p.drawRect(rect());

}

