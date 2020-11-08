#ifndef CHART_H
#define CHART_H

//#include <QWidget>
#include <QChartView>
#include <QChart>
#include <QGridLayout>
#include <QLineSeries>
#include <QValueAxis>
#include <QTimer>
#include <QSplineSeries>
#include <QOpenGLWidget>
#include <QPushButton>

QT_CHARTS_USE_NAMESPACE

class Chart : public QOpenGLWidget
{
    Q_OBJECT

public:
    Chart(QOpenGLWidget *parent = nullptr);
    ~Chart();

public slots:
    void generateData(void);
    void processButtonToggled(bool);
private:
    QChartView *chartview;
    QChart *chart;
    QLineSeries *lineSeries0;
    QLineSeries *lineSeries1;
    QGridLayout *layout;
    QValueAxis *valueAxisX;
    QValueAxis *valueAxisY;
    QPushButton *pushButton;
    QTimer * timer;
    qint32 count;
    qint32 max;
    qint32 step;
};
#endif // CHART_H
