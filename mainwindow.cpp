#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "cmath"
#include "poland.h"
#include "QPainterPath"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    resize(800, 600);
    ui->lineEdit->setGeometry(width() * 0.18, height()*0.03, 0.2*width(), 0.06*height());
    ui->label_fx->setGeometry(width()*0.11, height()*0.03, 0.12*width(), 0.06*height());
    ui->label_fx->setText("Function");
    ui->label_scale->setGeometry(width()*0.48, height()*0.03, 0.12*width(), 0.06*height());
    ui->label_scale->setText("Scale");
    ui->label->setGeometry(width() - width()*18.5/20, height() - height()*18/20, width()*15/20, height()*16/20);
    QPushButton* button = new QPushButton(this);
    (*button).setGeometry(width()*0.707, height()*0.03, 0.12*width(), 0.06*height());
    (*button).setText("Draw");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    QPushButton* plusbutton = new QPushButton(this);
    (*plusbutton).setGeometry(width()*0.53, height()*0.03, 0.057*width(), 0.06*height());
    (*plusbutton).setText("+");
    connect(plusbutton, SIGNAL(clicked()), this, SLOT(plusbuttonClicked()));
    QPushButton* minusbutton = new QPushButton(this);
    (*minusbutton).setGeometry(width()*0.6, height()*0.03, 0.057*width(), 0.06*height());
    (*minusbutton).setText("-");
    connect(minusbutton, SIGNAL(clicked()), this, SLOT(minusbuttonClicked()));

}

bool algos(QString f, double x, double &ans) {
    f.replace('x', '(' + QString::number(x) + ')');
    double tmp = 0;
    if (calc(f.toStdString(), tmp) == "Good") {
        ans = tmp;
        return true;
    } else {
        ans = 0;
        return false;
    }
}
int scale = 2;
void MainWindow::plusbuttonClicked() {
    scale--;
}
void MainWindow::minusbuttonClicked() {
    scale++;
}

void MainWindow::buttonClicked() {
    QString func = ui->lineEdit->text();
    QPixmap pm(width()*15/20, height()*16/20);
    QPainter painter;
    QPen pencil;
    QPainterPath path;
    painter.begin(&pm);
    pm.fill(0xF2F3FF);
    ui->label_x->setGeometry(width()*0.817, height()*0.486, 0.12*width(), 0.06*height());
    ui->label_x->setText("x");
    ui->label_y->setGeometry(width()*0.46, height()*0.08, 0.12*width(), 0.06*height());
    ui->label_y->setText("y");
    if (scale == 0) {
        scale++;
    }
    double xmin = M_PI * -1 * (scale), xmax = M_PI * (scale);
    double ymin = M_PI * -1 * (scale), ymax = M_PI * (scale);
    int xgmin = 0, xgmax = pm.width();
    int ygmin = 0, ygmax = pm.height();
    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;
    int xg = 0, yg = 0;
    double x, y;
    x = xmin;
    pencil.setColor(0x182FFF);
    pencil.setWidth(2);
    painter.setPen(pencil);
    painter.drawLine(0, y0, pm.width(), y0);
    painter.drawLine(x0, 0, x0, pm.height());
    pencil.setColor(0xE008EF);
    pencil.setWidth(2);
    painter.setPen(pencil);
    double stepx = (xmax - xmin) / (xgmax - xgmin);
    if (func == "") {
        ui->label->setPixmap(pm);
        return;
    }
    bool check = algos(func, x, y);
    xg = x0 + kx * x;
    yg = y0 + ky * y;
    path.moveTo(xg, yg);
    while (x <= xmax) {
        check = algos(func, x, y);
        xg = x0 + kx * x;
        yg = y0 + ky * y;
        if (!check) {
            path.moveTo(xg, yg);
        }
        while (x <= xmax && !(ygmin <= yg && yg <= ygmax)) {
            x += stepx;
            check = algos(func, x, y);
            xg = x0 + kx * x;
            yg = y0 + ky * y;
            path.moveTo(xg, yg);
        }
        if ((ygmin <= yg && yg <= ygmax)) {
            path.lineTo(xg, yg);
            painter.drawPath(path);
        } else {
            path.moveTo(xg, yg);
        }
        x += stepx;
    }
    ui->label->setPixmap(pm);
}


MainWindow::~MainWindow()
{
    delete ui;
}
