#include "calc_2/modelcalc.h"
#include <climits>
#include <cstring>
#include <gtest/gtest.h>

using namespace s21;
using namespace std;

ModelCalc model;

// Test ModelCalc Valid
TEST(ModelCalcTestValid, TestParsingValid) {
  model.Validation("8+2", "0");
  string main = model.Printer();
  ASSERT_EQ(main, "8+2");
  model.Clear();
  model.Validation("(2+2)-sin(13)*2^2", "0");
  main = model.Printer();
  ASSERT_EQ(main, "(2+2)-sin(13)*2^2");
  model.Clear();
  model.Validation("x+sin(x)-2", "2");
  main = model.Printer();
  ASSERT_EQ(main, "x+sin(x)-2");
  model.Clear();
}

TEST(ModelCalcTestValid, TestCalcValid) {
  model.Validation("2^2^3", "0");
  double main = stod(model.Calculate());
  double valid = pow(2, pow(2, 3));
  ASSERT_EQ(abs(main - valid) < 1e-6, true);
  model.Clear();
  model.Validation("sin(2)", "0");
  main = stod(model.Calculate());
  valid = sin(2);
  ASSERT_EQ(abs(main - valid) < 1e-6, true);
  model.Clear();
  model.Validation("(2+2)-sin(13)*2^2", "0");
  main = stod(model.Calculate());
  valid = (2.0 + 2.0) - sin(13.0) * pow(2.0, 2.0);
  ASSERT_EQ(abs(main - valid) < 1e-5, true);
  model.Clear();
  model.Validation("((2-3)*((2*8)-2)-tan(2))^3", "0");
  string man = model.Calculate();
  valid = pow(((2.0 - 3.0) * ((2.0 * 8.0) - 2.0) - tan(2.0)), 3.0);
  std::ostringstream vad;
  vad << valid;
  ASSERT_EQ(man, vad.str());
  model.Clear();
  model.Validation("x+sin(x)-2", "2");
  main = stod(model.Calculate());
  valid = 2 + sin(2) - 2;
  ASSERT_EQ(abs(main - valid) < 1e-6, true);
  model.Clear();
}

TEST(ModelCalcTestValid, TestUnarValid) {
  string main = model.Unar("2");
  string valid = "-2";
  ASSERT_EQ(main, valid);
  model.Clear();
  main = model.Unar("-2");
  valid = "2";
  ASSERT_EQ(main, valid);
  model.Clear();
  main = model.Unar("x");
  valid = "-x";
  ASSERT_EQ(main, valid);
  model.Clear();
}

// Test ModelCalc No Valid

TEST(ModelCalcTestNoValid, TestParsingNoValid) {
  model.Validation("23(+2*sin()54", "");
  string main = model.Printer();
  string valid = "23*(+2*sin()*54";
  ASSERT_EQ(main, valid);
  model.Clear();
  model.Validation("xxxxxxxxxxxxxxxx", "0");
  main = model.Printer();
  valid = "";
  ASSERT_EQ(main, valid);
  model.Clear();
  model.Validation("asdadasdgsadgasdgasfa123124124_2313-2321", "0");
  main = model.Printer();
  valid = "";
  ASSERT_EQ(main, valid);
  model.Clear();
}

TEST(ModelCalcTestNoValid, TestCalcNoValid) {
  model.Validation("23(+2*sin()54", "");
  string main = model.Calculate();
  string valid = "Error!";
  ASSERT_EQ(main, valid);
  model.Clear();
  model.Validation("0/0", "");
  main = model.Calculate();
  ASSERT_EQ(main, valid);
  model.Clear();
  model.Validation("()()()(((((((()))))(())())()(", "32");
  ASSERT_EQ(main, valid);
  model.Clear();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
