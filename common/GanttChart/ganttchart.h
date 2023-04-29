#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <QWidget>

namespace Ui {
class GanttChart;
}

class GanttChart : public QWidget
{
    Q_OBJECT

public:
    explicit GanttChart(QWidget *parent = nullptr);
    ~GanttChart();

    void Init(int row, double stride, int pixPerSmallCell, QString unit, int planHeight);

    void SetRowName(int row, QString name);

    int Add(int row, double from, double to, QString color);

protected:
    void paintEvent(QPaintEvent *event) override;

    bool eventFilter(QObject* watched, QEvent *event) override;

private:
    void OnClickRectangle(int row, int index);

    void OnHScrollBarValueChanged(int val);
    void OnVScrollBarValueChanged(int val);

    void OnChangedWidth(int w);

private:
    Ui::GanttChart *ui;
};

#endif // GANTTCHART_H
