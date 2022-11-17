#include "credit.h"
#include "ui_credit.h"
#include <QMessageBox>

credit::credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
    ui->monthly_payment->setReadOnly(true);
    ui->total_payment->setReadOnly(true);
    ui->overpayment->setReadOnly(true);
}

credit::~credit()
{
    delete ui;
}


bool isNumeric(std::string const &str)
{
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

void credit::on_pushButton_credit_clicked()
{
    double overpayment = 0, monthly_payment = 0, first_month_payment = 0, last_month_payment = 0, total_payment = 0;

    double total_credit_amount = ui->total_credit_amount->text().toDouble();
    double interes_rate = ui->interes_rate->text().toDouble();
    double term = ui->term->text().toDouble();
    double monthly_interes_rate = interes_rate / (100 * 12);

    QString str_monthly_payment = "";
    QString str_overpayment = "";
    QString str_total_payment = "";
    QString str_first_month_payment = "";
    QString str_last_month_payment = "";

    if (ui->total_credit_amount->text() != "" && ui->interes_rate->text() != "" && ui->term->text() != "") {
        std::string total_text = ui->total_credit_amount->text().toStdString();
        std::string interes_text = ui->interes_rate->text().toStdString();
        std::string term_text = ui->term->text().toStdString();
        if (isNumeric(total_text) && isNumeric(interes_text) && isNumeric(term_text)) {
            if (ui->radioButton_Annuity->isChecked()) {
                monthly_payment = total_credit_amount * (monthly_interes_rate / (1 - pow((1 + monthly_interes_rate), -term)));
                total_payment = monthly_payment * term;
                overpayment = total_payment - total_credit_amount;
                str_monthly_payment = QString::number(monthly_payment);
                str_total_payment = QString::number(total_payment);
                str_overpayment = QString::number(overpayment);
                ui->monthly_payment->setText(str_monthly_payment);
                ui->total_payment->setText(str_total_payment);
                ui->overpayment->setText(str_overpayment);
            } else if (ui->radioButton_Differentiated->isChecked()) {
                double rest = total_credit_amount;
                double monthly = 0;
                for (int i = 0; i < term; i++) {
                    if (i == 0) {
                        first_month_payment = rest * monthly_interes_rate + total_credit_amount / term;
                        total_payment += first_month_payment;
                        rest -= first_month_payment;
                    } else if (i == (term - 1)) {
                        last_month_payment = rest * monthly_interes_rate + total_credit_amount / term;
                        total_payment += last_month_payment;
                        rest -= last_month_payment;
                    } else {
                        monthly = rest * monthly_interes_rate + total_credit_amount / term;
                        total_payment += monthly;
                        rest -= monthly;
                    }
                }
                overpayment = total_payment - total_credit_amount;
                str_first_month_payment = QString::number(first_month_payment);
                str_last_month_payment = QString::number(last_month_payment);
                str_total_payment = QString::number(total_payment);
                str_overpayment = QString::number(overpayment);
                ui->monthly_payment->setText(str_first_month_payment + "..." + str_last_month_payment);
                ui->total_payment->setText(str_total_payment);
                ui->overpayment->setText(str_overpayment);
            } else {
                QMessageBox::warning(this, "Warning","Выберите тип платежа!");
            }
        } else {
            QMessageBox::warning(this, "Warning","Вводите только числа!");
        }

    } else {
        QMessageBox::warning(this, "Warning","Заполните поля!");
    }
}
