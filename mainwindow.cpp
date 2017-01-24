#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QList>
#include "functionevaluator.h"
#include "scanner.h"
#include "infixtopostfix.h"
#include <memory>
#include "token.h"
QT_CHARTS_USE_NAMESPACE

QChart *chart;
QChartView *chartView;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new QChart();

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
    //Initiating a new QT line serie.
    QLineSeries* serie(new QLineSeries());
    serie->setName(ui->leFunction->text());

    //Makeing a list of variables, which includes only x
    QPair<QString,double> x = {"x",0};
    QList<QPair<QString,double>> variables_list = {x};

    //Stage1: Tokenizing function definition.
    Scanner scanner(ui->leFunction->text());
    auto infix_expression = scanner.scan();

    //Stage2: Convert function definition into a postfix notation
    InfixToPostfix infix_to_postfix(infix_expression);
    auto postfix_expression = infix_to_postfix.convert();

    //Stage3: Evaluating the postfix_function for x in range [-30,+30]
    FunctionEvaluator evaluator(postfix_expression);

    for (double x = -30.0; x <= 30.0; x+=0.1)
    {
        variables_list[0].second = x;

        double y = evaluator.evaluate(variables_list);
        /* since the result of an arbitrary function can be limitlese and
         * converge to infinity, it can deform our chart. so better to set
         * some boundries.
         */
        if (y > 100) y = 100;
        if (y < -100) y = -100;

        serie->append(x,y);
    }

    //Update the chart.
    chart->addSeries(serie);
    chart->createDefaultAxes();
    chartView->setChart(chart);
}

void MainWindow::on_pushButton_3_clicked()
{
    chart->removeAllSeries();
}
