#ifndef RECT_H
#define RECT_H

#include <QWidget>

class Rect : public QWidget
{
    Q_OBJECT
public:
    explicit Rect(QWidget *parent = nullptr);
    void Init(QString color);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void sgClicked();

private:
    QString color_;

};

#endif // RECT_H
