#ifndef RULER_H
#define RULER_H

#include <QWidget>

class Ruler : public QWidget
{
    Q_OBJECT
public:
    explicit Ruler(QWidget *parent = nullptr);

    void Init(double stride, int pixPerSmallCell, QString unit);
    void Add(double to);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void sgWidthChange(int w);

private:
    double stride_ = 10;
    int pix_per_small_cell_ = 10;
    QString unit_;
    double max_ = 100;
};

#endif // RULER_H
