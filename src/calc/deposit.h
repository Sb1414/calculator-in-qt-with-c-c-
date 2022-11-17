#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>

namespace Ui {
class deposit;
}

class deposit : public QDialog
{
    Q_OBJECT

public:
    explicit deposit(QWidget *parent = 0);
    ~deposit();

private slots:
    void on_pushButton_credit_clicked();

private:
    Ui::deposit *ui;
};

#endif // DEPOSIT_H
