#ifndef PLAN_H
#define PLAN_H

#include <QWidget>
#include "rect.h"

class Plan : public QWidget
{
    Q_OBJECT
public:
    explicit Plan(QWidget *parent = nullptr);

    void Init(double stride, int pixPerSmallCell);

    int Add(double from, double to, QString color);

signals:
    void sgRectClicked(int index);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void OnClickRectangle();

private:
    QList<Rect*> rects_;
    double stride_ = 10;
    int pix_per_small_cell_ = 10;
};

#endif // PLAN_H
