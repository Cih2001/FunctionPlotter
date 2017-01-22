#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtMath>
#include <QMessageBox>
#include <QList>
#include <tuple>
#include "functionevaluator.h"
#include <typeinfo>
#include <memory>
#include "token.h"
QT_CHARTS_USE_NAMESPACE

QChart *chart;
QList<QLineSeries*> chart_series;
QChartView *chartView;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart();


    //chart->legend()->hide();
    chart->createDefaultAxes();

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    this->ui->loChart->addWidget(chartView);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QPair<QString,double> x = {"x",0};

    QList<QPair<QString,double>> variables_list = {x};

    FunctionEvaluator fe(ui->leFunction->text(),variables_list);

    QLineSeries* serie(new QLineSeries());
    serie->setName(ui->leFunction->text());

    for (double x = -30.0; x <= 30.0; x+=0.1)
    {
        fe.updateVariableValue("x",x);
        double y = fe.evaluate();
        if (y > 100) y = 100;
        if (y < -100) y = -100;
        serie->append(x,y);
    }

    chart->addSeries(serie);
    chart->createDefaultAxes();
    chartView->setChart(chart);
    chartView->show();

    //std::vector<std::shared_ptr<Literal<double>>> vec;
    //vec.push_back(std::make_shared<Literal<double>>(123));
    //vec.push_back(std::make_shared<Literal<double>>(445));
    //for (auto a: vec)
    //    QMessageBox::warning(nullptr,"asdasdasd",a->toString());
}

void MainWindow::on_pushButton_3_clicked()
{
    chart->removeAllSeries();

}
