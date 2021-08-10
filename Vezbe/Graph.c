#include "dialog.h"
#include "ui_dialog.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE
Dialog::Dialog(QWidget *parent) :
 QDialog(parent),
 ui(new Ui::Dialog)
{
 ui->setupUi(this);
 //kreiranje podataka za prikaz
 QLineSeries *series = new QLineSeries();
 // prvi način dodavanja podataka za prikaz
 series->append(0, 0);
 series->append(1, 1);
 series->append(2, 2);
 series->append(3, 3.3);
 // drugi način dodavanja podataka za prikaz
 *series << QPointF(4, 3) << QPointF(4, 2) << QPointF(5,1);
 
 QChart *chart = new QChart();
 chart->legend()->hide();
 chart->addSeries(series);
 chart->createDefaultAxes();
 //postavljanje opsega
 chart->axisX()->setMin(0);
 chart->axisX()->setMax(5);
 //2. način za postavljanje opsega
 chart->axisY()->setRange(0,3.3);
 chart->setTitle("Merenje napona");
 
 QChartView *chartView = new QChartView(chart);
 chartView->setRenderHint(QPainter::Antialiasing);
 
 //postavljanje grafika u vertikal layout
 ui->verticalLayout->addWidget(chartView);
}
Dialog::~Dialog()
{
 delete ui;
}
