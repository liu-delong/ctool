#include "ganttchart.h"
#include "ui_ganttchart.h"

#include <QDebug>
#include <QMessageBox>
#include <QPainter>

GanttChart::GanttChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GanttChart)
{
    ui->setupUi(this);

    connect(ui->scrollAreaWidgetContents_2, &PlanArea::sgRectClicked, this, &GanttChart::OnClickRectangle);

    connect(ui->horizontalScrollBar, &QScrollBar::valueChanged, this, &GanttChart::OnHScrollBarValueChanged);
    connect(ui->verticalScrollBar, &QScrollBar::valueChanged, this, &GanttChart::OnVScrollBarValueChanged);

    connect(ui->scrollAreaWidgetContents_3, &Ruler::sgWidthChange, this, &GanttChart::OnChangedWidth);

    ui->scrollArea->viewport()->installEventFilter(this);
    ui->scrollArea_2->viewport()->installEventFilter(this);
    this->installEventFilter(this);
}

GanttChart::~GanttChart()
{
    delete ui;
}

void GanttChart::Init(int row, double stride, int pixPerSmallCell, QString unit, int planHeight)
{
    ui->scrollAreaWidgetContents_3->Init(stride, pixPerSmallCell, unit);
    ui->scrollAreaWidgetContents->Init(row, planHeight);
    ui->scrollAreaWidgetContents_2->Init(row, stride, pixPerSmallCell, planHeight);
}

void GanttChart::SetRowName(int row, QString name)
{
    ui->scrollAreaWidgetContents->SetRowName(row, name);
}

int GanttChart::Add(int row, double from, double to, QString color)
{
    int index = -1;

    index = ui->scrollAreaWidgetContents_2->Add(row, from, to, color);
    ui->scrollAreaWidgetContents_3->Add(to);

    return index;
}

void GanttChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#1a448c"));
    p.drawRect(rect());
}

bool GanttChart::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->scrollArea->viewport() ||
            watched == ui->scrollArea_2->viewport())
    {
        if(event->type() == QEvent::Wheel)
        {
            //event->ignore();
            return true;      //只针对scrollArea窗口禁用滚轮滚动功能，返回true表示过滤
        }
    }

    return QWidget::eventFilter(watched, event);
}

void GanttChart::OnClickRectangle(int row, int index)
{
    QString content("row: %1, index: %2");
    QMessageBox::information(this, "rect clicked", content.arg(row).arg(index));
}

void GanttChart::OnHScrollBarValueChanged(int val)
{
    //    qDebug() << val;
    int y = ui->scrollAreaWidgetContents_2->y();
    int y_3 = ui->scrollAreaWidgetContents_3->y();
    int w = ui->scrollAreaWidgetContents_2->width();

    int x = val * w / ui->verticalScrollBar->maximum();
    //    qDebug() << QString("x:%1|w:%2|%3")

    ui->scrollAreaWidgetContents_2->move(-x, y);
    ui->scrollAreaWidgetContents_3->move(-x, y_3);
}

void GanttChart::OnVScrollBarValueChanged(int val)
{
    //    qDebug() << ui->verticalScrollBar->maximum();
    int x = ui->scrollAreaWidgetContents->x();
    int x_2 = ui->scrollAreaWidgetContents_2->x();
    int h = ui->scrollAreaWidgetContents->height();

    int y = val * h / ui->verticalScrollBar->maximum();

    //    qDebug() << val << "|" << -y;
    ui->scrollAreaWidgetContents->move(x, -y);
    ui->scrollAreaWidgetContents_2->move(x_2, -y);
}

void GanttChart::OnChangedWidth(int w)
{
    qDebug() << "w: " << w;
    //    qDebug() << "w1: " << ui->scrollAreaWidgetContents_3->width();
    //    ui->scrollAreaWidgetContents_3->setFixedSize(w, ui->scrollAreaWidgetContents_3->height());
    ui->scrollAreaWidgetContents_2->setFixedSize(w, ui->scrollAreaWidgetContents_2->height());
    qDebug() << "w2: " << ui->scrollAreaWidgetContents_2->width();
    qDebug() << "w3: " << ui->scrollAreaWidgetContents_3->width();
}
