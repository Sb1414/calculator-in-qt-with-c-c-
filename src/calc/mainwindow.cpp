#include "mainwindow.h"
#include "ui_mainwindow.h"

double num_first;
int flag = 0;
int dot = 0;
int count = 0;
int min_flag = 0;
int pl_falg = 0;
int is_digit = 1;
int is_r_bracket = 1;
int is_sign = 0;
int is_x = 0;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
//    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
//    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(ariph_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigon_numbers()));
    connect(ui->pushButton_plusminus, SIGNAL(clicked()), this, SLOT(s21_arithmetic()));
//    ui->result->setValidator(val_form);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers() {
    QPushButton *button = (QPushButton *) sender();
    QString all_numbers;
    if (ui->result->text() == '0') {
        ui->result->setText("");
    }
        all_numbers = (ui->result->text() + button->text());
        ui->result->setText(all_numbers);

    flag = 0;
    min_flag = 0;
    pl_falg = 0;
    is_digit = 0;
    is_r_bracket = 1;
    is_sign = 1;
    is_x = 1;
}

void MainWindow::ariph_numbers() {
    QPushButton *button = (QPushButton *) sender();
    if (ui->result->text() == '0') flag = 1;
    if (flag == 0) {
        ui->result->setText(ui->result->text() + button->text());
        flag = 1;
        dot = 0;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
    }
}

void MainWindow::trigon_numbers() {
    QPushButton *button = (QPushButton *) sender();
    int loc_falg = 1;
    if (dot == 0) {
        if (ui->result->text() == '0') {
            ui->result->setText("");
            loc_falg = 0;
        }
        if ((is_digit == 0 || is_r_bracket == 0) && loc_falg == 1) {
            ui->result->setText(ui->result->text() + "*" + button->text()  + "(");
        } else {
            ui->result->setText(ui->result->text() + button->text()  + "(");
        }
        flag = 1;
        dot = 0;
        count += 1;
        min_flag = 0;
        pl_falg = 0;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
   }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (flag == 0 && dot == 0) {
        ui->result->setText(ui->result->text() + ".");
        flag = 1;
        dot = 1;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 1;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_mul->setChecked(false);
    ui->pushButton_div->setChecked(false);
    ui->result->setText("0");
    flag = 0;
    dot = 0;
    count = 0;
    min_flag = 0;
    pl_falg = 0;
    is_digit = 1;
    is_r_bracket = 1;
    is_sign = 0;
    is_x = 1;
}


void MainWindow::on_pushButton_equals_clicked()
{
    double x = 0;
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);
    QString send = ui->result->text();
    QByteArray ba = send.toLocal8Bit();
    char* buf = ba.data();

    if (ui->x_value->text() != "") {
        x = (ui->x_value->text().toDouble());
    }
    QString toStr = QString::number(s21_parser(buf, x), 'g', 15);
    ui->result->setText(toStr);
    is_x = 1;
}

void MainWindow::on_pushButton_round_bracket_L_clicked()
{
    QString all_numbers;
    if (ui->result->text() == '0') {
        ui->result->setText("");
        is_sign = 0;
    }
    if (is_sign == 0) {
        all_numbers = (ui->result->text() + "(");
        ui->result->setText(all_numbers);
        count += 1;
    }
    is_x = 1;
}

void MainWindow::on_pushButton_round_bracket_R_clicked()
{
    QString all_numbers;
    if (count > 0 && flag == 0) {
        all_numbers = (ui->result->text() + ")");
        ui->result->setText(all_numbers);
        flag = 0;
        count -= 1;
        min_flag = 0;
        pl_falg = 0;
        is_digit = 1;
        is_r_bracket = 0;
        is_sign = 1;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_minus_clicked()
{
    if (min_flag == 0) {
        if (ui->result->text() == '0') ui->result->setText("");
        ui->result->setText(ui->result->text() + "-");
        flag = 1;
        dot = 0;
        min_flag = 1;
        pl_falg = 1;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_plus_clicked()
{
    if (pl_falg == 0) {
        if (ui->result->text() == '0') ui->result->setText("");
        ui->result->setText(ui->result->text() + "+");
        flag = 1;
        dot = 0;
        min_flag = 1;
        pl_falg = 1;
        is_digit = 1;
        is_r_bracket = 1;
        is_sign = 0;
        is_x = 1;
    }
}

void MainWindow::on_pushButton_graph_clicked()
{
    QString send = ui->result->text();
    QByteArray ba = send.toLocal8Bit();
    char* buf = ba.data();
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    result_1 = 0;
    result_2 = 0;
    xBegin = 0;
    xEnd = 0;
    h = 0.1;
    bool fl = true;

    double Y = ui->x_value->text().toDouble();
    double X = 0;
    if (Y == 0) Y = 1;

    xy_1 = ui->x1->text().toDouble();
    xy_2 = ui->x2->text().toDouble();
    result_1 = ui->y1->text().toInt();
    result_2 = ui->y2->text().toInt();

    xBegin = result_2;
    xEnd = result_1 + h;

    ui->widget->xAxis->setRange(xy_2, xy_1);
    ui->widget->yAxis->setRange(result_2, result_1);
    N = (xEnd - xBegin)/h + 2;

    for (X = xBegin; X <= xEnd; X += h) {
        x.push_back(X);
        y.push_back(s21_parser(buf, Y*X));
    }
    for (int i = 0; i < x.size() - 3; i++) {
        if (x[i] == 0 && x[i+1] == 0 && x[i+2] == 0) {
            QMessageBox::warning(this, "Warning","Слишколм сложно..");
            fl = false;
            break;
        }
        if (y[i] == 0 && y[i+1] == 0 && y[i+2] == 0) {
            QMessageBox::warning(this, "Warning","Слишколм сложно..");
            fl = false;
            break;
        }
    }

   if (fl) {
       ui->widget->addGraph();
       ui->widget->graph(0)->addData(x, y);
       ui->widget->replot();
   }

}

void MainWindow::on_pushButton_x_clicked()
{
    int loc_falg = 1;
        if (ui->result->text() == '0') {
            ui->result->setText("");
            loc_falg = 0;
        }
        if ((is_digit == 0 || is_r_bracket == 0 || is_x == 0) && loc_falg == 1) {
            ui->result->setText(ui->result->text() + "*x");
        } else {
           ui->result->setText(ui->result->text() + "x");
        }
        flag = 0;
        min_flag = 0;
        pl_falg = 0;
        is_digit = 0;
        is_r_bracket = 1;
        is_sign = 1;
        is_x = 0;
}

void MainWindow::on_pushButton_backspace_clicked()
{
    std::string rdctstr = ui->result->text().toUtf8().constData();
    std::string result = rdctstr.substr(0, rdctstr.length() - 1);
    ui->result->setText(QString::fromStdString(result));
}


void MainWindow::on_pushButton_div_clicked()
{
    ui->result->setText(ui->result->text() + "/");
}


void MainWindow::on_pushButton_mul_clicked()
{
    ui->result->setText(ui->result->text() + "*");
}


void MainWindow::on_pushButton_plusminus_clicked()
{
    std::string strres = ui->result->text().toStdString();
    if (strres[0] == '-') {
        char ch = '-';
            if (strres.front() == ch) {
                strres.erase(strres.begin());
            }
        ui->result->setText(QString::fromStdString(strres));
    } else {
        flag = true;
        ui->result->setText(QString::fromStdString("-" + strres));
    }
}


void MainWindow::on_credit_clicked()
{
    credit window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_deposit_clicked()
{
    deposit window;
    window.setModal(true);
    window.exec();
}

