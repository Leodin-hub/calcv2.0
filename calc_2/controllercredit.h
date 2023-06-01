#ifndef CONTROLLERCREDIT_H
#define CONTROLLERCREDIT_H

#include <QWidget>

#include "modelcredit.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {
class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_button_calc_clicked();

 private:
  Ui::CreditCalc *ui;
};
};  // namespace s21

#endif  // CONTROLLERCREDIT_H
