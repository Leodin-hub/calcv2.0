#include "modeldeposit.h"

using namespace s21;

ModelDeposit::ModelDeposit() { ; }

void ModelDeposit::Init(double sum, unsigned term, unsigned days, QDate start,
                        double procent, unsigned period, bool capital,
                        double nalog) {
  sum_calc_ = sum;
  term_num_ = term;
  period_list_num_[4] = term_num_;
  days_str_ = days;
  date_ = start;
  procent_num_ = procent * 0.01;
  period_str_ = period;
  capital_b_ = capital;
  nalog_num_ = nalog * 0.01;
}

unsigned ModelDeposit::DayInMonth_() {
  return date_.daysTo(date_.addMonths(1));
}

unsigned ModelDeposit::DayInYear_() { return date_.daysTo(date_.addYears(1)); }

void ModelDeposit::ParsingWithdrawals_() {
  withdrawls_date_list2_.clear();
  for (int i = 0; i < withdrawls_period_list_.size(); ++i) {
    withdrawls_date_list2_.push_back(
        CorrectDate_(withdrawls_period_list_[i], withdrawls_date_list_[i]));
  }
}

void ModelDeposit::ParsingReplenishment_() {
  replenishment_date_list2_.clear();
  for (int i = 0; i < replenishment_period_list_.size(); ++i) {
    replenishment_date_list2_.push_back(CorrectDate_(
        replenishment_period_list_[i], replenishment_date_list_[i]));
  }
}

QDate ModelDeposit::CorrectDate_(unsigned i, QDate d) {
  if (i == 0 && d <= date_) {
    d = date_.addDays(1);
  }
  if (d < date_ && i != 4) {
    if (i == 1) {
      while (d < date_) d = d.addDays(7);
    } else if (i == 2) {
      while (d < date_) d = d.addMonths(1);
    } else if (i == 3) {
      while (d < date_) d = d.addYears(1);
    }
  }
  return d;
}

void ModelDeposit::AddSum_() {
  for (int i = 0; i < replenishment_period_list_.size(); ++i) {
    if (replenishment_date_list2_[i] == date_) {
      sum_calc_ += replenishment_sum_list_[i];
      replenishment_date_list2_[i] = replenishment_date_list2_[i].addDays(
          period_list_num_[replenishment_period_list_[i]]);
    } else if (replenishment_date_list2_[i] < date_ &&
               replenishment_period_list_[i] != 4) {
      replenishment_date_list2_[i] = replenishment_date_list2_[i].addDays(
          period_list_num_[replenishment_period_list_[i]]);
    }
  }
}

void ModelDeposit::PopSum_() {
  for (int i = 0; i < withdrawls_period_list_.size(); ++i) {
    if (withdrawls_date_list2_[i] == date_) {
      double temp = withdrawls_sum_list_[i];
      if (sum_calc_ >= temp) {
        sum_calc_ -= temp;
      }
      withdrawls_date_list2_[i] = withdrawls_date_list2_[i].addDays(
          period_list_num_[withdrawls_period_list_[i]]);
    } else if (withdrawls_date_list2_[i] < date_ &&
               withdrawls_period_list_[i] != 4) {
      withdrawls_date_list2_[i] = withdrawls_date_list2_[i].addDays(
          period_list_num_[withdrawls_period_list_[i]]);
    }
  }
}

void ModelDeposit::CalcSum_() {
  double proc = (sum_calc_ * ((procent_num_ / (double)period_list_num_[3]) *
                              (double)period_list_num_[period_str_]));
  //  proc = round(proc * 100.0) / 100.0;
  double nalg = proc * nalog_num_;
  //  nalg = round(nalg * 100.0) / 100.0;
  if (capital_b_) sum_calc_ += proc - nalg;
  procent_calc_ += proc;
  nalog_calc_ += nalg;
}

void ModelDeposit::EndDayCalc_() {
  end_date_ = date_;
  if (!days_str_) {
    end_date_ = end_date_.addDays(term_num_);
  } else if (days_str_ == 1) {
    end_date_ = end_date_.addMonths(term_num_);
    term_num_ = date_.daysTo(end_date_);
  } else {
    end_date_ = end_date_.addYears(term_num_);
    term_num_ = date_.daysTo(end_date_);
  }
}

void ModelDeposit::Calc() {
  nalog_calc_ = 0;
  procent_calc_ = 0;
  ParsingWithdrawals_();
  ParsingReplenishment_();
  EndDayCalc_();

  QDate up_date = date_;
  up_date = up_date.addDays(period_list_num_[period_str_]);
  date_ = date_.addDays(1);

  while (date_ <= end_date_) {
    if (up_date == date_) {
      up_date = up_date.addDays(period_list_num_[period_str_]);
      CalcSum_();
    }
    AddSum_();
    PopSum_();
    if (date_.month() < date_.addDays(1).month()) {
      period_list_num_[2] = DayInMonth_();
    }
    if (date_.year() < date_.addDays(1).year()) {
      period_list_num_[3] = DayInYear_();
    }
    date_ = date_.addDays(1);
  }

  procent_str_ = QString::number(round(procent_calc_ * 100.0) / 100.0);
  nalog_str_ = QString::number(round(nalog_calc_ * 100.0) / 100.0);
  sum_str_ = QString::number(round(sum_calc_ * 100.0) / 100.0);
}

QString ModelDeposit::GetProcent() { return procent_str_; }

QString ModelDeposit::GetNalog() { return nalog_str_; }

QString ModelDeposit::GetSum() { return sum_str_; }

QVector<unsigned> *ModelDeposit::GetWithPeriod() {
  return &withdrawls_period_list_;
}

QVector<QDate> *ModelDeposit::GetWithDate() { return &withdrawls_date_list_; }
QVector<double> *ModelDeposit::GetWithSum() { return &withdrawls_sum_list_; }

QVector<unsigned> *ModelDeposit::GetReplPeriod() {
  return &replenishment_period_list_;
}

QVector<QDate> *ModelDeposit::GetReplDate() {
  return &replenishment_date_list_;
}

QVector<double> *ModelDeposit::GetReplSum() { return &replenishment_sum_list_; }
