#include "modelcredit.h"

using namespace s21;

ModelCredit::ModelCredit(double sum_credit, unsigned term, bool month,
                         double procent, bool annuity)
    : sum_credit(sum_credit),
      term(term),
      month(month),
      procent(procent),
      annuity(annuity) {
  Calc();
}

void ModelCredit::CalcAnnuity() {
  procent = procent / 100.0 / 12.0;
  monthly_payment = sum_credit * (procent * pow((1.0 + procent), term) /
                                  (pow(1.0 + procent, term) - 1.0));
  monthly_payment = round(monthly_payment * 100.0) / 100.0;
  debt_interest = monthly_payment * (double)term;
  interest_charges = debt_interest - sum_credit;
}

void ModelCredit::CalcDifferentiated() {
  procent = procent / 100.0;
  double mon_price = sum_credit / term;
  double temp_sum = sum_credit;
  while (temp_sum >= 1e-6) {
    interest_charges += (temp_sum * procent * 30.4) / 365.0;
    if (temp_sum == sum_credit) monthly_payment = mon_price + interest_charges;
    temp_sum -= mon_price;
  }
  monthly_payment_dif = mon_price + (mon_price * procent * 30.4) / 365.0;
  monthly_payment = round(monthly_payment * 100.0) / 100.0;
  monthly_payment_dif = round(monthly_payment_dif * 100.0) / 100.0;
  debt_interest = sum_credit + interest_charges;
  debt_interest = round(debt_interest * 100.0) / 100.0;
  interest_charges = round(interest_charges * 100.0) / 100.0;
}

void ModelCredit::CalcResult() {
  if (month) {
    term *= 12;
  }
  if (annuity) {
    CalcAnnuity();
    ostringstream ost;
    ost << monthly_payment;
    monthly_payment_str_ = ost.str();
  } else {
    CalcDifferentiated();
    ostringstream ost, ost_dif;
    ost << monthly_payment;
    ost_dif << monthly_payment_dif;
    monthly_payment_str_ = ost.str() + " ... " + ost_dif.str();
  }
  ostringstream debt, inter;
  debt << debt_interest;
  inter << interest_charges;
  debt_interest_str_ = debt.str();
  interest_charges_str_ = inter.str();
}

void ModelCredit::Calc() {
  if (sum_credit && term && procent) {
    CalcResult();
  } else {
    monthly_payment_str_ = "0";
    debt_interest_str_ = "0";
    interest_charges_str_ = "0";
  }
}

string ModelCredit::GetMonPay() { return monthly_payment_str_; }

string ModelCredit::GetInterCharg() { return interest_charges_str_; }

string ModelCredit::GetDebtInter() { return debt_interest_str_; }
