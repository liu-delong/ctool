#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->showMaximized();

    ui->widget_2->Init(15, 10, 10, "us", 100);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_init_clicked()
{
    delete ui->widget_2;
    ui->widget_2 = new GanttChart(ui->widget);
    ui->gridLayout_2->addWidget(ui->widget_2, 0, 0, 1, 1);

    int row = ui->lineEdit_row->text().toInt();
    double stride = ui->lineEdit_stride->text().toDouble();
    int pix_per_small_cell = ui->lineEdit_pix_per_small_cell->text().toInt();
    QString unit = ui->lineEdit_unit->text();
    int plan_height = ui->lineEdit_plan_height->text().toInt();

    ui->widget_2->Init(row, stride, pix_per_small_cell, unit, plan_height);
}

void Widget::on_pushButton_set_row_name_clicked()
{
    int row = ui->lineEdit_row_2->text().toInt();
    QString name = ui->lineEdit_name->text();

    ui->widget_2->SetRowName(row, name);
}

void Widget::on_pushButton_add_clicked()
{
    int row = ui->lineEdit_row_3->text().toInt();
    double from = ui->lineEdit_from->text().toDouble();
    double to = ui->lineEdit_to->text().toDouble();
    QString color = ui->lineEdit_color->text();

    int index = ui->widget_2->Add(row, from, to, color);

    ui->lineEdit_index->setText(QString::number(index));
}
