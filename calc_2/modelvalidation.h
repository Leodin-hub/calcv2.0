#ifndef MODELVALIDATION_H
#define MODELVALIDATION_H

#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace s21 {
class ModelValidation {
 public:
  void Init(string str, vector<string> vect);
  pair<bool, bool> IsNumber(string str);
  bool IsNumb(char ch);
  bool IsChar(char ch);
  unsigned IndexOf(vector<string> vect, string value);
  bool Contains(vector<string> vect, string value);
  string ToString(double value);
  double FromString(string str);
  void ToLower(string *value);
  void Clear();
  bool GetErrorFalg();
  vector<string> GetPostValid();
  bool GetIsX();

 private:
  void Validation_();
  void Parser_();
  bool MergeNumb_(string str);
  bool EnableMul_(size_t id);
  void ValidatUnar_();
  string IsFunction_(size_t *id);
  string IsNumber_(size_t *id);
  string IsExponNumber_(size_t *id);
  vector<string> funciton_ = {"cos",  "sin", "tan", "acos", "asin", "atan",
                              "sqrt", "ln",  "log", "mod",  "x"};
  vector<char> operator_ = {'+', '-', '*', '/', '^', '(', ')'};
  string pre_valid_ = "";

  bool error_flag_ = true;
  vector<string> post_valid_;
  bool is_x_ = false;
};
};  // namespace s21

#endif  // MODELVALIDATION_H
