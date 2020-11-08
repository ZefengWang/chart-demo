#include "chart.h"

#include <QtMath>
#include <QDebug>

Chart::Chart(QOpenGLWidget *parent)
    : QOpenGLWidget(parent),
      count(0), max(1000), step(250)
{
    this->setMinimumSize(800,600);
    pushButton = new QPushButton();
    chart = new QChart();
    lineSeries0 = new QLineSeries(chart);
    lineSeries1 = new QLineSeries(chart);
    valueAxisX = new QValueAxis(chart);
    valueAxisY = new QValueAxis(chart);
    timer = new QTimer(this);
    valueAxisX->setTickCount(7);
    valueAxisX->setLabelFormat("%d");
    valueAxisX->setTitleText(tr("Count"));
    valueAxisY->setRange(-1024, 1023);
    valueAxisY->setTickCount(5);
    valueAxisY->setLabelFormat("%d");
    valueAxisY->setTitleText(tr("Value"));

    layout = new QGridLayout(this);
    chartview = new QChartView(chart);
    layout->addWidget(chartview, 0, 0);
    layout->addWidget(pushButton, 1, 0);

    chart->addAxis(valueAxisX,Qt::AlignBottom);
    chart->setTitle(tr("Demo for test plot"));


    chart->addAxis(valueAxisY,Qt::AlignRight);
    valueAxisY->setLabelsVisible(false);
    lineSeries0->setUseOpenGL(true);
    lineSeries1->setUseOpenGL(true);
    chart->addSeries(lineSeries0);
    chart->addSeries(lineSeries1);

    lineSeries0->attachAxis(valueAxisX);
    lineSeries0->attachAxis(valueAxisY);
    lineSeries1->attachAxis(valueAxisX);
    lineSeries1->attachAxis(valueAxisY);

    chart->legend()->hide();
    chart->setTheme(QChart::ChartThemeDark);
    //lineSeries0->setPen(QPen(QBrush(Qt::yellow),1,Qt::SolidLine));
    chartview->setChart(this->chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    pushButton->setCheckable(true);
    pushButton->setText(tr("Start"));
    connect(pushButton, SIGNAL(toggled(bool)), this, SLOT(processButtonToggled(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(generateData()));
}

Chart::~Chart()
{
}

void Chart::generateData()
{
    count +=1;// count*step >= max? -max/step: count+1 ;
    lineSeries0->append(lineSeries0->count() +1, (max*2/step)*((count%step >step/2)? count%step-step:count %step ));
    lineSeries1->append(lineSeries1->count() +1, 1000*qCos(count*M_PI/2.0)*qSin(((count%step)/(1.0*step)) *2*M_PI) );
    valueAxisX->setRange(lineSeries1->count() -600 , lineSeries1->count());
}

void Chart::processButtonToggled(bool flag)
{
    if (flag) {
        pushButton->setText(tr("Stop"));
        timer->start(10);
    }else {
        pushButton->setText(tr("Start"));
        timer->stop();
    }
}

