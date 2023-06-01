#ifndef CONTROLLERCALC_H
#define CONTROLLERCALC_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QString>
#include <vector>

#include "controllercredit.h"
#include "controllerdeposit.h"
#include "modelcalc.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  ModelCalc model_calc;
  CreditCalc credit;
  DepositCalc deposit;

 private slots:
  void on_button_enter_clicked();
  void on_button_ravno_clicked();
  void ButtonNumbers_();
  void ButtonFunctions_();
  void keyPressEvent(QKeyEvent *event);
  void on_button_ac_clicked();
  void on_button_backspace_clicked();
  void on_button_draw_graphic_clicked();
  void on_button_unar_clicked();
  void on_button_credit_clicked();
  void on_button_deposit_clicked();

 private:
  Ui::MainWindow *ui;
};
};  // namespace s21

#endif  // CONTROLLERCALC_H
