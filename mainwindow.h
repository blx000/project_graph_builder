#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton button;
    ~MainWindow();

private slots:
    void buttonClicked();
    void plusbuttonClicked();
    void minusbuttonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
