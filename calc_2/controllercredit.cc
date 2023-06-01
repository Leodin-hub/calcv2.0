#include "controllercredit.h"

#include "ui_veivcredit.h"

using namespace s21;

CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
  CreditCalc::setWindowTitle("Credit Calc v2.0");
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_button_calc_clicked() {
  ModelCredit credit_model(ui->sum_credit->value(), ui->term->value(),
                           !ui->year_month->currentIndex(),
                           ui->procent->value(), ui->annuity->isChecked());
  ui->monthly_payment_num->setText(
      QString::fromStdString(credit_model.GetMonPay()));
  ui->interest_charges_num->setText(
      QString::fromStdString(credit_model.GetInterCharg()));
  ui->debt_interest_num->setText(
      QString::fromStdString(credit_model.GetDebtInter()));
}
