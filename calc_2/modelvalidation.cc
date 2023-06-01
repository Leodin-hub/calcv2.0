#include "modelvalidation.h"

using namespace s21;

void ModelValidation::Init(string str, vector<string> vect) {
  pre_valid_ = str;
  post_valid_ = vect;
  Validation_();
}

void ModelValidation::Validation_() {
  ToLower(&pre_valid_);
  Parser_();
  ValidatUnar_();
}

void ModelValidation::Parser_() {
  size_t i = 0;
  int check_unar = 0;
  while (!pre_valid_.empty() && i < pre_valid_.size() && error_flag_) {
    string temp_str = "";
    if (i < pre_valid_.size() && IsNumb(pre_valid_[i])) {
      if (EnableMul_(i)) {
        post_valid_.emplace_back("*");
      }
      temp_str = IsNumber_(&i);
      if (!temp_str.empty() && check_unar) {
        temp_str = (check_unar == 1 ? "-" : "+") + temp_str;
        check_unar = 0;
      }
      if (!temp_str.empty() && !post_valid_.empty()) {
        if (MergeNumb_(temp_str)) temp_str.clear();
      }
    } else if (i < pre_valid_.size() && IsChar(pre_valid_[i])) {
      const bool check = EnableMul_(i);
      temp_str = IsFunction_(&i);
      if (temp_str.empty() || (temp_str != "x" && pre_valid_[i] != '(')) {
        error_flag_ = false;
      } else {
        if (check) post_valid_.emplace_back("*");
      }
    } else if (i < pre_valid_.size() &&
               find(operator_.begin(), operator_.end(), pre_valid_[i]) !=
                   operator_.end()) {
      if (pre_valid_.size() > 1 &&
          (pre_valid_[i] == '-' || pre_valid_[i] == '+')) {
        if ((!i || pre_valid_[i - 1] == '(' || (!post_valid_.empty() && !i) ||
             (!i && post_valid_.back() == "(")) &&
            (i < pre_valid_.size() && IsNumb(pre_valid_[i + 1]))) {
          check_unar = pre_valid_[i++] == '-' ? 1 : 2;
        }
      }
      if (pre_valid_[i] == '(') {
        temp_str = pre_valid_[i++];
      } else if (!check_unar) {
        string st;
        st.push_back(pre_valid_[i]);
        post_valid_.emplace_back(st);
        i++;
      }
      if (EnableMul_(i - 1)) post_valid_.emplace_back("*");
    } else {
      error_flag_ = false;
    }
    if (!temp_str.empty()) {
      is_x_ = is_x_ || temp_str == "x";
      post_valid_.emplace_back(temp_str);
    }
  }
}

bool ModelValidation::MergeNumb_(string str) {
  const bool ok = IsNumber(post_valid_[post_valid_.size() - 1]).first;
  if (ok) post_valid_[post_valid_.size() - 1] += str;
  return ok;
}

bool ModelValidation::EnableMul_(size_t id) {
  bool result = false;
  if (id + 1 < pre_valid_.size() && pre_valid_[id] == ')') {
    size_t it = id + 1, iz = id + 1;
    result = !IsNumber_(&it).empty() || !IsFunction_(&iz).empty() ||
             pre_valid_[id + 1] == '(';
  } else if (id > 0 && IsChar(pre_valid_[id])) {
    size_t it = id;
    if (!IsFunction_(&it).empty()) {
      result = find(operator_.begin(), operator_.end(), pre_valid_[id - 1]) ==
               operator_.end();
    }
  } else if (id > 0 && pre_valid_[id] == '(') {
    result = IsNumb(pre_valid_[id - 1]);
  } else if (!id && !post_valid_.empty() && IsChar(pre_valid_[id])) {
    size_t it = id, iz = id;
    if (!IsFunction_(&it).empty() || !IsNumber_(&iz).empty()) {
      string temp_str = post_valid_[post_valid_.size() - 1];
      result = !(temp_str == "+" || temp_str == "-" || temp_str == "*" ||
                 temp_str == "/" || temp_str == "mod");
    }
  } else if (!id && !post_valid_.empty() && pre_valid_[id] == '(') {
    string temp_num = post_valid_[post_valid_.size() - 1];
    result = IsNumb(temp_num[temp_num.size() - 1]) || temp_num[0] == ')';
  }
  return result;
}

void ModelValidation::ValidatUnar_() {
  for (size_t i = 0; i < post_valid_.size() && post_valid_.size() > 1; ++i) {
    if (!i && (post_valid_[i] == "+" || post_valid_[i] == "-")) {
      if (IsNumber(post_valid_[i + 1]).first || post_valid_[i + 1] == "x") {
        if (post_valid_[i] == "-")
          post_valid_[i + 1] = "-" + post_valid_[i + 1];
        post_valid_.erase(post_valid_.begin() += i);
      }
    } else if (post_valid_[i] == "+" || post_valid_[i] == "-") {
      if (!IsNumber(post_valid_[i - 1]).first && post_valid_[i - 1] != ")" &&
          post_valid_[i - 1] != "x") {
        if (post_valid_[i] == "-")
          post_valid_[i + 1] = "-" + post_valid_[i + 1];
        post_valid_.erase(post_valid_.begin() += i);
      }
    }
  }
}

string ModelValidation::IsFunction_(size_t *id) {
  string temp_str = "";
  while (*id < pre_valid_.size() && IsChar(pre_valid_[*id]))
    temp_str += pre_valid_[(*id)++];
  const bool res_b = Contains(funciton_, temp_str);
  if (!res_b) temp_str.clear();
  return temp_str;
}

string ModelValidation::IsNumber_(size_t *id) {
  string temp_str = "";
  if (*id < pre_valid_.size() && IsNumb(pre_valid_[*id])) {
    while (*id < pre_valid_.size() && IsNumb(pre_valid_[*id]))
      temp_str += pre_valid_[(*id)++];
    if (*id < pre_valid_.size() && pre_valid_[*id] == '.') {
      temp_str += pre_valid_[(*id)++];
      if (*id < pre_valid_.size() && IsNumb(pre_valid_[*id])) {
        while (*id < pre_valid_.size() && IsNumb(pre_valid_[*id]))
          temp_str += pre_valid_[(*id)++];
      } else {
        temp_str.clear();
        error_flag_ = false;
      }
    }
    temp_str += IsExponNumber_(id);
  }
  return temp_str;
}

string ModelValidation::IsExponNumber_(size_t *id) {
  string temp_str = "";
  unsigned it = 0;
  if (*id + 2 < pre_valid_.size() &&
      (pre_valid_[*id] == 'e' &&
       (pre_valid_[*id + 1] == '-' || pre_valid_[*id + 1] == '+'))) {
    temp_str += pre_valid_[(*id)++];
    temp_str += pre_valid_[(*id)++];
    if (*id < pre_valid_.size() && IsNumb(pre_valid_[*id])) {
      while (*id < pre_valid_.size() && IsNumb(pre_valid_[*id])) {
        temp_str += pre_valid_[(*id)++];
        ++it;
      }
    }
    if (it > 16 || it == 0) {
      temp_str.clear();
      error_flag_ = false;
    }
  }
  return temp_str;
}

pair<bool, bool> ModelValidation::IsNumber(string str) {
  bool check_dot = false, check_unar = false, flag = true;
  bool exp_pre = false, exp = false;
  for (size_t i = 0; flag && i < str.size(); ++i) {
    if (!check_unar && !i && (str[i] == '-' || str[i] == '+')) {
      check_unar = true;
      flag = !(str.size() == 1);
    } else if (!check_dot && !exp && i > 0 && str[i] == '.') {
      check_dot = true;
    } else if (!exp_pre && !exp && str[i] == 'e') {
      exp_pre = true;
    } else if (exp_pre && !exp && (str[i] == '-' || str[i] == '+')) {
      exp = true;
    } else if (IsNumb(str[i])) {
      continue;
    } else {
      flag = false;
    }
  }
  return make_pair(flag, check_unar);
}

bool ModelValidation::IsNumb(char ch) { return ch >= '0' && ch <= '9'; }

bool ModelValidation::IsChar(char ch) { return ch >= 'a' && ch <= 'z'; }

unsigned ModelValidation::IndexOf(vector<string> vect, string value) {
  auto it = find(vect.begin(), vect.end(), value);
  return (unsigned)distance(vect.begin(), it);
}

bool ModelValidation::Contains(vector<string> vect, string value) {
  return find(vect.begin(), vect.end(), value) != vect.end();
}

string ModelValidation::ToString(double value) {
  ostringstream ost;
  ost << value;
  return ost.str();
}

double ModelValidation::FromString(string str) { return atof(&str[0]); }

void ModelValidation::ToLower(string *value) {
  for (size_t i = 0; i < value->size(); ++i) (*value)[i] = tolower((*value)[i]);
}

void ModelValidation::Clear() {
  post_valid_.clear();
  pre_valid_.clear();
  is_x_ = false;
  error_flag_ = true;
}

bool ModelValidation::GetErrorFalg() { return error_flag_; }

vector<string> ModelValidation::GetPostValid() { return post_valid_; }

bool ModelValidation::GetIsX() { return is_x_; }
