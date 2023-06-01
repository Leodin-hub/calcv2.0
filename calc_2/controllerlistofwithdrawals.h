#ifndef CONTROLLERLISTOFWITHDRAWALS_H
#define CONTROLLERLISTOFWITHDRAWALS_H

#include <QDialog>

namespace Ui {
class ListOfWithdrawals;
}

namespace s21 {
class ListOfWithdrawals : public QDialog {
  Q_OBJECT

 public:
  explicit ListOfWithdrawals(QWidget *parent = nullptr);
  ~ListOfWithdrawals();
  void SetVector(QVector<unsigned> *uns_list_, QVector<QDate> *date_list_,
                 QVector<double> *double_list_);

 private slots:
  void on_add_clicked();
  void on_delete_2_clicked();
  void on_clear_clicked();
  void on_close_clicked();

 private:
  void Print();
  QVector<unsigned> *uns_list_ = nullptr;
  QVector<QDate> *date_list_ = nullptr;
  QVector<double> *double_list_ = nullptr;
  Ui::ListOfWithdrawals *ui;
};
};  // namespace s21

#endif  // CONTROLLERLISTOFWITHDRAWALS_H
