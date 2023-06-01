#ifndef CONTROLLERDEPOSIT_H
#define CONTROLLERDEPOSIT_H

#include <QWidget>

#include "controllerlistofwithdrawals.h"
#include "controllerreplenishmentlist.h"
#include "modeldeposit.h"

namespace Ui {
class DepositCalc;
}

namespace s21 {
class DepositCalc : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget *parent = nullptr);
  ~DepositCalc();
  ModelDeposit model_deposit;
  ListOfWithdrawals lof;
  ReplenishmentList rl;

 private slots:
  void on_replenishment_list_clicked();
  void on_list_withdrawals_clicked();
  void on_calc_clicked();

 private:
  Ui::DepositCalc *ui;
};
};  // namespace s21

#endif  // CONTROLLERDEPOSIT_H
