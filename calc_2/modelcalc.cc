#include "modelcalc.h"

using namespace s21;

void ModelCalc::Validation(string str, string x) {
  validator.Init(str, string_buffer_);
  if (validator.GetErrorFalg()) string_buffer_ = validator.GetPostValid();
  is_x_ = is_x_ || validator.GetIsX();
  x_variable_ = x;
  validator.Clear();
}

string ModelCalc::Printer() {
  string result = "";
  for (auto i : string_buffer_) result += i;
  return result;
}

void ModelCalc::Clear() {
  string_buffer_.clear();
  while (!up_buffer_.empty()) up_buffer_.pop();
  while (!down_buffer_.empty()) down_buffer_.pop();
  error_flag_ = true;
  res_x_.clear();
  res_y_.clear();
  min_y_ = max_y_ = 0;
  x_variable_ = "0";
}

void ModelCalc::Backspace() {
  if (!string_buffer_.empty()) {
    auto iter = string_buffer_.end();
    string_buffer_.erase(--iter);
  }
}

string ModelCalc::Calculate(double x) {
  x_variable_ = validator.ToString(x);
  return Calculate();
}

string ModelCalc::Calculate() {
  Parser_();
  double result_d = 0;
  stack<double> result;
  while (!down_buffer_.empty() && error_flag_) {
    string temp_pars = down_buffer_.front();
    if (validator.IsNumber(temp_pars).first) {
      result.push(validator.FromString(temp_pars));
      down_buffer_.pop();
    } else if (validator.Contains(operator_, temp_pars)) {
      double temp = result.top();
      result.pop();
      if (result.empty()) {
        error_flag_ = false;
      } else {
        temp = operators_[validator.IndexOf(operator_, temp_pars)](result.top(),
                                                                   temp);
        result.pop();
        result.push(temp);
        down_buffer_.pop();
      }
    } else {
      double temp = result.top();
      if (result.empty()) {
        error_flag_ = false;
      } else {
        result.pop();
        result.push(functions_[validator.IndexOf(function_, temp_pars)](temp));
        down_buffer_.pop();
      }
    }
  }
  if (error_flag_ && down_buffer_.empty() && result.size() == 1) {
    result_d = result.top();
  }
  string result_s = "";
  if (error_flag_ && !isnan(result_d) && !isinf(result_d)) {
    result_s = validator.ToString(result_d);
  } else {
    result_s = "Error!";
  }
  return result_s;
}

void ModelCalc::DrawGraphic(double min, double max) {
  if (is_x_) {
    if (min > max) {
      double tmp = min;
      min = max;
      max = tmp;
    }
    double step = (abs(min) + abs(max)) / 1000.0;
    double x = min;
    while (x < max) {
      string temp_str = Calculate(x);
      if (validator.IsNumber(temp_str).first) {
        res_x_.push_back(x);
        res_y_.push_back(validator.FromString(temp_str));
        if (res_y_.size() == 1 || res_y_.back() > max_y_) {
          max_y_ = res_y_.back();
        }
        if (res_y_.size() == 1 || res_y_.back() < min_y_) {
          min_y_ = res_y_.back();
        }
      }
      x += step;
    }
  }
}

void ModelCalc::Parser_() {
  for (auto i : string_buffer_) {
    if (validator.IsNumber(i).first) {
      down_buffer_.push(i);
    } else if (validator.Contains(function_, i) || i == "(") {
      up_buffer_.push(i);
    } else if (validator.Contains(operator_, i)) {
      SortOperator_(i);
    } else if (i == ")") {
      PushScobka_();
    } else if (i == "x") {
      down_buffer_.push(x_variable_);
      is_x_ = true;
    } else {
      error_flag_ = false;
    }
    if (!error_flag_) {
      break;
    }
  }
  if (error_flag_ && !up_buffer_.empty()) PushUpToDown_();
}

void ModelCalc::PushUpToDown_() {
  error_flag_ = up_buffer_.top() != "(";
  while (!up_buffer_.empty() && error_flag_) {
    error_flag_ = up_buffer_.top() != "(";
    down_buffer_.push(up_buffer_.top());
    up_buffer_.pop();
  }
}

void ModelCalc::PushScobka_() {
  if (!up_buffer_.empty() && up_buffer_.top() == "(" && error_flag_) {
    up_buffer_.pop();
    if (!up_buffer_.empty() &&
        validator.Contains(function_, up_buffer_.top())) {
      down_buffer_.push(up_buffer_.top());
      up_buffer_.pop();
    }
  } else if (!up_buffer_.empty() && error_flag_) {
    while (!up_buffer_.empty() && up_buffer_.top() != "(") {
      down_buffer_.push(up_buffer_.top());
      up_buffer_.pop();
    }
    if (!up_buffer_.empty() && up_buffer_.top() == "(") {
      up_buffer_.pop();
      if (!up_buffer_.empty() &&
          validator.Contains(function_, up_buffer_.top())) {
        down_buffer_.push(up_buffer_.top());
        up_buffer_.pop();
      }
    } else {
      error_flag_ = false;
    }
    if (!up_buffer_.empty() &&
        validator.Contains(function_, up_buffer_.top())) {
      down_buffer_.push(up_buffer_.top());
      up_buffer_.pop();
    }
  } else {
    error_flag_ = false;
  }
}

void ModelCalc::SortOperator_(string str) {
  while (!up_buffer_.empty() && !(up_buffer_.top() == "^" && str == "^") &&
         PriorityOperator_(up_buffer_.top()) >= PriorityOperator_(str)) {
    down_buffer_.push(up_buffer_.top());
    up_buffer_.pop();
  }
  up_buffer_.push(str);
}

int ModelCalc::PriorityOperator_(string str) {
  int result = 0;
  if (str == "+" || str == "-") {
    result = 1;
  } else if (str == "*" || str == "/" || str == "mod") {
    result = 2;
  } else if (str == "^") {
    result = 3;
  }
  return result;
}

string ModelCalc::Unar(string str) {
  vector<string> temp_vect;
  validator.Init(str, temp_vect);
  if (validator.GetErrorFalg()) {
    temp_vect = validator.GetPostValid();
    auto it = temp_vect.end();
    --it;
    if (!temp_vect.empty()) {
      if (temp_vect.size() > 1 && *it == ")") {
        --it;
      }
      if (*it == "-") {
        temp_vect.clear();
      } else {
        auto bol = validator.IsNumber(*it);
        if ((bol.first && bol.second)) {
          double td = validator.FromString(*it) * -1.0;
          *it = validator.ToString(td);
        } else if ((bol.first && !bol.second) || *it == "x") {
          (*it) = "-" + (*it);
        } else if (*it == "-x") {
          *it = "x";
        }
      }
    } else {
      temp_vect.push_back("-");
    }
    if (!temp_vect.empty()) {
      str.clear();
      for (auto i : temp_vect) str += i;
    } else {
      str.clear();
    }
  }
  validator.Clear();
  return str;
}

double ModelCalc::GetMaxY() const { return max_y_; }

double ModelCalc::GetMinY() const { return min_y_; }

vector<double> ModelCalc::GetResX() const { return res_x_; }

double ModelCalc::GetResX(const int i) const { return res_x_[i]; }

vector<double> ModelCalc::GetResY() const { return res_y_; }

double ModelCalc::GetResY(const int i) const { return res_y_[i]; }

bool ModelCalc::GetIsX() const { return is_x_; }
