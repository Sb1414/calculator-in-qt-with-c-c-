#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "credit.h"
#include "deposit.h"
#include "qcustomplot.h"
#include <QVector>
#include <QTimer>
#include <QtMath>
#include <QLineEdit>
#include "ui_mainwindow.h"
#include <QValidator>


#ifdef __cplusplus
extern "C" {
#endif
    #include "../s21_SmartCalc.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QRegularExpressionValidator *val_form = new QRegularExpressionValidator(QRegularExpression("^([-]?\\d*[.]?\\d*|[+-/*^%]?|[x]|[(]|([)][+-/*^%]?)|sin[(]|cos[(]|tan[(]|sqrt[(]|asin[(]|acos[(]|atan[(]|log[(]|ln[(]){0,}$"), 0);
    Ui::MainWindow *ui;

private:
    double xBegin, xEnd, h, X, xy_1, xy_2, result_1, result_2;
    int N;
    bool flag = true;

    QVector<double> x, y;

private slots:
    void digits_numbers();
    void ariph_numbers();
    void trigon_numbers();
    void on_pushButton_dot_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_equals_clicked();
    void on_pushButton_round_bracket_L_clicked();
    void on_pushButton_round_bracket_R_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_graph_clicked();
    void on_pushButton_backspace_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_mul_clicked();
    void on_pushButton_plusminus_clicked();
    void on_credit_clicked();
    void on_deposit_clicked();
};
#endif // MAINWINDOW_H
