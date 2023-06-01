#ifndef MODELCALC_H
#define MODELCALC_H

#include <math.h>

#include <queue>
#include <sstream>
#include <stack>

#include "modelvalidation.h"

namespace s21 {
class ModelCalc {
 public:
  string Calculate();
  string Calculate(double x);
  void Validation(string str, string x);
  string Printer();
  void DrawGraphic(double min, double max);
  void Clear();
  void Backspace();
  string Unar(string str);
  double GetMinY() const;
  double GetMaxY() const;
  vector<double> GetResX() const;
  double GetResX(int i) const;
  vector<double> GetResY() const;
  double GetResY(int i) const;
  bool GetIsX() const;

 private:
  ModelValidation validator;
  vector<string> string_buffer_;
  string x_variable_ = "0";

  double min_y_ = 0, max_y_ = 0;
  vector<double> res_x_, res_y_;
  bool is_x_ = false;

  void Parser_();
  void PushUpToDown_();
  void SortOperator_(string str);
  int PriorityOperator_(string str);
  void PushScobka_();
  vector<string> function_ = {"cos",  "sin",  "tan", "acos", "asin",
                              "atan", "sqrt", "ln",  "log"};
  vector<string> operator_ = {"+", "-", "*", "/", "^", "mod"};
  stack<string> up_buffer_;
  queue<string> down_buffer_;
  double (*operators_[6])(double, double) = {
      [](double a, double b) { return a + b; },
      [](double a, double b) { return a - b; },
      [](double a, double b) { return a * b; },
      [](double a, double b) { return a / b; },
      pow,
      fmod};
  double (*functions_[9])(double) = {cos,  sin,  tan,   acos, asin,
                                     atan, sqrt, log10, log};
  bool error_flag_ = true;
};
};  // namespace s21

#endif  // MODELCALC_H
