#include "controllerlistofwithdrawals.h"

#include "ui_vievlistofwithdrawals.h"

using namespace s21;

ListOfWithdrawals::ListOfWithdrawals(QWidget *parent)
    : QDialog(parent), ui(new Ui::ListOfWithdrawals) {
  ui->setupUi(this);
  ui->date->setDate(QDate::currentDate());
  ListOfWithdrawals::setWindowTitle("List Of Withdrawals v2.0");
}

ListOfWithdrawals::~ListOfWithdrawals() { delete ui; }

void ListOfWithdrawals::on_add_clicked() {
  uns_list_->push_back(ui->period->currentIndex());
  date_list_->push_back(ui->date->date());
  double_list_->push_back(ui->sum->value());
  Print();
}

void ListOfWithdrawals::on_delete_2_clicked() {
  if (!uns_list_->empty()) {
    uns_list_->pop_back();
    date_list_->pop_back();
    double_list_->pop_back();
  }
  Print();
}

void ListOfWithdrawals::on_clear_clicked() {
  uns_list_->clear();
  date_list_->clear();
  double_list_->clear();
  Print();
}

void ListOfWithdrawals::Print() {
  ui->listWidget->clear();
  if (!uns_list_->empty()) {
    for (int i = 0; i < uns_list_->size(); ++i)
      ui->listWidget->addItem(ui->period->itemText((*uns_list_)[i]) + " " +
                              (*date_list_)[i].toString() + " " +
                              QString::number((*double_list_)[i]));
  }
}

void ListOfWithdrawals::on_close_clicked() { this->close(); }

void ListOfWithdrawals::SetVector(QVector<unsigned> *uns_list_,
                                  QVector<QDate> *date_list_,
                                  QVector<double> *double_list_) {
  this->uns_list_ = uns_list_;
  this->date_list_ = date_list_;
  this->double_list_ = double_list_;
}
