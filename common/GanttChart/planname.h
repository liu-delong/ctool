#ifndef PLANNAME_H
#define PLANNAME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSpacerItem>

class PlanName : public QWidget
{
    Q_OBJECT
public:
    explicit PlanName(QWidget *parent = nullptr);

    void Init(int row, int planHeight);

    void SetRowName(int row, QString name);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<QLabel*> plan_names_;
    QVBoxLayout* layout_ = nullptr;
    QSpacerItem* spacer_ = nullptr;
};

#endif // PLANNAME_H
