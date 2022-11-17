#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QValidator>

namespace Ui {
class credit;
}

class credit : public QDialog
{
    Q_OBJECT

public:
    explicit credit(QWidget *parent = 0);
    ~credit();

private slots:
    void on_pushButton_credit_clicked();

private:
    Ui::credit *ui;
};

#endif // CREDIT_H
