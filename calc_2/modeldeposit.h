#ifndef MODELDEPOSIT_H
#define MODELDEPOSIT_H

#include <QDate>

namespace s21 {
class ModelDeposit {
 public:
  ModelDeposit();
  void Init(double sum, unsigned term, unsigned days, QDate start,
            double procent, unsigned period, bool capital, double nalog);
  void Calc();

  QString GetProcent();
  QString GetNalog();
  QString GetSum();

  QVector<unsigned> *GetWithPeriod();
  QVector<QDate> *GetWithDate();
  QVector<double> *GetWithSum();

  QVector<unsigned> *GetReplPeriod();
  QVector<QDate> *GetReplDate();
  QVector<double> *GetReplSum();

 private:
  double sum_calc_ = 0;
  unsigned term_num_ = 0;
  unsigned days_str_ = 0;
  QDate date_ = QDate::currentDate();
  QDate end_date_ = QDate::currentDate();
  double procent_num_ = 0;
  double procent_calc_ = 0;
  unsigned period_str_ = 0;
  bool capital_b_ = false;
  double nalog_num_ = 0;
  double nalog_calc_ = 0;

  QString procent_str_ = "0";
  QString nalog_str_ = "0";
  QString sum_str_ = "0";

  QVector<unsigned> withdrawls_period_list_;
  QVector<QDate> withdrawls_date_list_;
  QVector<double> withdrawls_sum_list_;

  QVector<unsigned> replenishment_period_list_;
  QVector<QDate> replenishment_date_list_;
  QVector<double> replenishment_sum_list_;

  QVector<QDate> withdrawls_date_list2_;
  QVector<QDate> replenishment_date_list2_;

  unsigned period_list_num_[5] = {1, 7, DayInMonth_(), DayInYear_(), term_num_};
  QVector<QString> period_list_ = {"Разовое", "Ежедневно", "Еженедельно",
                                   "Ежемесячно", "Ежегодно"};

  unsigned DayInMonth_();
  unsigned DayInYear_();
  void ParsingWithdrawals_();
  void ParsingReplenishment_();
  QDate CorrectDate_(unsigned i, QDate d);
  void AddSum_();
  void PopSum_();
  void CalcSum_();
  void EndDayCalc_();
};
};  // namespace s21

#endif  // MODELDEPOSIT_H
