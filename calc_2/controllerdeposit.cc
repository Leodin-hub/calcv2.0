#include "controllerdeposit.h"

#include "ui_vievdeposit.h"

using namespace s21;

DepositCalc::DepositCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
  DepositCalc::setWindowTitle("Deposit Calc v2.0");
  ui->date->setDate(QDate::currentDate());
  lof.SetVector(model_deposit.GetWithPeriod(), model_deposit.GetWithDate(),
                model_deposit.GetWithSum());

  rl.SetVector(model_deposit.GetReplPeriod(), model_deposit.GetReplDate(),
               model_deposit.GetReplSum());
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_calc_clicked() {
  model_deposit.Init(ui->sum->value(), ui->term->value(),
                     ui->year_month->currentIndex(), ui->date->date(),
                     ui->procent->value(), ui->payments->currentIndex(),
                     ui->capital_box->isChecked(), ui->nalog->value());
  model_deposit.Calc();
  ui->procent_calc->setText(model_deposit.GetProcent());
  ui->nalog_calc->setText(model_deposit.GetNalog());
  ui->sum_calc->setText(model_deposit.GetSum());
}

void DepositCalc::on_replenishment_list_clicked() { rl.show(); }

void DepositCalc::on_list_withdrawals_clicked() { lof.show(); }
