#include "deposit.h"
#include "ui_deposit.h"
#include <QMessageBox>

deposit::deposit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deposit)
{
    ui->setupUi(this);
    ui->accured_interest->setReadOnly(true);
    ui->tax_ammount->setReadOnly(true);
    ui->deposit_end->setReadOnly(true);
}

deposit::~deposit()
{
    delete ui;
}

bool isNum(std::string const &str)
{
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

void deposit::on_pushButton_credit_clicked()
{
    double accrued_interest = 0, tax_amount = 0, deposit_end = 0;

    double deposit_amount = ui->deposit_amount->text().toDouble();
    double deposit_term = ui->deposit_term->text().toDouble();
    double interest_rate = ui->interes_rate->text().toDouble();
    double tax_rate = ui->tax_rate->text().toDouble();
    double partial_withdrawals_sum = ui->withdraw_sum->text().toDouble();
    double partial_withdrawals_month = ui->partial_withdraw_month->text().toDouble();
    double replenishments_sum = ui->replenishments_sum->text().toDouble();
    double replenishments_month = ui->partial_replanishment_month->text().toDouble();

    QString str_accrued_interest = "";
    QString str_tax_amount = "";
    QString str_deposit_end = "";

    if (ui->deposit_amount->text() != "" && ui->deposit_term->text() != "" && ui->interes_rate->text() != "") {

        std::string amount_text = ui->deposit_amount->text().toStdString();
        std::string term_text = ui->deposit_term->text().toStdString();
        std::string rate_text = ui->interes_rate->text().toStdString();
        if (isNum(amount_text) && isNum(term_text) && isNum(rate_text)) {

            if (ui->periodicity_of_payments->text() != "") {
                if (isNum(ui->periodicity_of_payments->text().toStdString())) {
                    if (ui->checkBox->isChecked()) {
                            double accrued_month_interest = 0;
                            double month_tax_amount = 0;
                            for (int i = 0; i < deposit_term; i++) {
                                accrued_month_interest = (((deposit_amount/100)*interest_rate)/12);
                                month_tax_amount = accrued_month_interest * (tax_rate / 100);
                                accrued_month_interest = accrued_month_interest - month_tax_amount;
                                deposit_amount += accrued_month_interest;
                                accrued_interest += accrued_month_interest;
                                tax_amount += month_tax_amount;
                                if (i == replenishments_month && replenishments_sum > 0) {
                                    deposit_amount += replenishments_sum;
                                }
                                if (i == partial_withdrawals_month && partial_withdrawals_sum > 0) {
                                    deposit_amount -= partial_withdrawals_sum;
                                }
                            }
                        } else if (partial_withdrawals_month != 0 || replenishments_month != 0) {
                            double accrued_month_interest = 0;
                            for (int i = 0; i < deposit_term; i++) {
                                accrued_month_interest = (((deposit_amount/100)*interest_rate)/12);
                                accrued_interest += accrued_month_interest;
                                if (i == replenishments_month && replenishments_sum > 0) {
                                    deposit_amount += replenishments_sum;
                                }
                                if (i == partial_withdrawals_month && partial_withdrawals_sum > 0) {
                                    deposit_amount -= partial_withdrawals_sum;
                                }
                            }
                            tax_amount = accrued_interest * (tax_rate / 100);
                            accrued_interest = accrued_interest - tax_amount;
                        } else {
                            accrued_interest = (((deposit_amount/100)*interest_rate)/12)*deposit_term;
                            tax_amount = accrued_interest * (tax_rate / 100);
                            accrued_interest = accrued_interest - tax_amount;
                        }
                    deposit_end = accrued_interest + deposit_amount;

                    str_accrued_interest = QString::number(accrued_interest);
                    str_deposit_end = QString::number(deposit_end);
                    str_tax_amount = QString::number(tax_amount);

                    ui->accured_interest->setText(str_accrued_interest);
                    ui->deposit_end->setText(str_deposit_end);
                    ui->tax_ammount->setText(str_tax_amount);
                } else {
                    QMessageBox::warning(this, "Warning","Периодичность выплат должна быть числом!");
                }
            } else {
                QMessageBox::warning(this, "Warning","Заполните периодичность выплат!");
            }
        } else {
            QMessageBox::warning(this, "Warning","Вводите только числа!");
        }
    } else {
        QMessageBox::warning(this, "Warning","Заполните сумму, срок и процентную ставку!");
    }
}
