#ifndef MODELCREDIT_H
#define MODELCREDIT_H

#include <math.h>

#include <sstream>

using namespace std;

namespace s21 {
class ModelCredit {
 public:
  ModelCredit(double sum_credit, unsigned term, bool month, double procent,
              bool annuity);

  string GetMonPay();
  string GetInterCharg();
  string GetDebtInter();

 private:
  double sum_credit = 0;
  unsigned term = 0;
  bool month = true;
  double procent = 0;
  bool annuity = true;

  string monthly_payment_str_ = "0";
  string interest_charges_str_ = "0";
  string debt_interest_str_ = "0";

  double monthly_payment = 0;
  double monthly_payment_dif = 0;
  double interest_charges = 0;
  double debt_interest = 0;

  void Calc();
  void CalcResult();
  void CalcAnnuity();
  void CalcDifferentiated();
};
};  // namespace s21

#endif  // MODELCREDIT_H
