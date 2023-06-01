#ifndef CONTROLLERREPLENISHMENTLIST_H
#define CONTROLLERREPLENISHMENTLIST_H

#include <QDialog>

namespace Ui {
class ReplenishmentList;
}

namespace s21 {
class ReplenishmentList : public QDialog {
  Q_OBJECT

 public:
  explicit ReplenishmentList(QWidget *parent = nullptr);
  ~ReplenishmentList();

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
  Ui::ReplenishmentList *ui;
};
};  // namespace s21

#endif  // CONTROLLERREPLENISHMENTLIST_H
