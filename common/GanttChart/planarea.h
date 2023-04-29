#ifndef PLANAREA_H
#define PLANAREA_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "plan.h"


class PlanArea : public QWidget
{
    Q_OBJECT
public:
    explicit PlanArea(QWidget *parent = nullptr);

    void Init(int row, double stride, int pixPerSmallCell, int planHeight);

    int Add(int row, double from, double to, QString color);

signals:
    void sgRectClicked(int row, int index);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void OnClickRectangle(int index);

private:
    QList<Plan*> plans_;
    QVBoxLayout* layout_ = nullptr;
    QSpacerItem* spacer_ = nullptr;
};

#endif // PLANAREA_H
