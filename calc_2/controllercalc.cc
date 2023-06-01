#include "controllercalc.h"

#include "ui_viev.h"

using namespace std;
using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  MainWindow::setWindowTitle("Calc v2.0");
  vector<QPushButton *> button_number = {
      ui->button_x,           ui->button_0,           ui->button_1,
      ui->button_2,           ui->button_3,           ui->button_4,
      ui->button_5,           ui->button_6,           ui->button_7,
      ui->button_8,           ui->button_9,           ui->button_exp,
      ui->button_plus,        ui->button_minus,       ui->button_mull,
      ui->button_div,         ui->button_dot,         ui->button_mod,
      ui->button_open_scobka, ui->button_close_scobka};
  vector<QPushButton *> button_function = {
      ui->button_sin,  ui->button_cos,  ui->button_tan,
      ui->button_asin, ui->button_acos, ui->button_atan,
      ui->button_sqrt, ui->button_log,  ui->button_ln};

  for (auto i = 0; i < (int)button_number.size(); i++)
    connect(button_number[i], SIGNAL(clicked()), this, SLOT(ButtonNumbers_()));

  for (auto i = 0; i < (int)button_function.size(); i++)
    connect(button_function[i], SIGNAL(clicked()), this,
            SLOT(ButtonFunctions_()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ButtonNumbers_() {
  ui->pre_line->setText(ui->pre_line->text() +
                        ((QPushButton *)sender())->text());
}

void MainWindow::ButtonFunctions_() {
  ui->pre_line->setText(ui->pre_line->text() +
                        ((QPushButton *)sender())->text() + "(");
}

void MainWindow::on_button_enter_clicked() {
  if (!ui->pre_line->text().isEmpty()) {
    model_calc.Validation(ui->pre_line->text().toStdString(),
                          ui->line_x->text().toStdString());
    ui->funcion_line->setText(QString::fromStdString(model_calc.Printer()));
    ui->pre_line->clear();
  }
}

void MainWindow::on_button_ravno_clicked() {
  if (!ui->pre_line->text().isEmpty())
    model_calc.Validation(ui->pre_line->text().toStdString(),
                          ui->line_x->text().toStdString());
  ui->funcion_line->setText(QString::fromStdString(model_calc.Printer()));
  ui->pre_line->setText(QString::fromStdString(model_calc.Calculate()));
  model_calc.Clear();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return) {
    if (!ui->pre_line->text().isEmpty())
      ui->button_enter->animateClick();
    else
      ui->button_ravno->animateClick();
  } else if (event->key() == Qt::Key_Escape) {
    ui->button_ac->animateClick();
  } else if (event->key() == Qt::Key_Backspace) {
    ui->button_backspace->animateClick();
  }
}

void MainWindow::on_button_ac_clicked() {
  ui->pre_line->clear();
  ui->funcion_line->clear();
  model_calc.Clear();
}

void MainWindow::on_button_backspace_clicked() {
  model_calc.Backspace();
  ui->funcion_line->setText(QString::fromStdString(model_calc.Printer()));
}

void MainWindow::on_button_draw_graphic_clicked() {
  model_calc.Validation(ui->pre_line->text().toStdString(), "0");
  ui->graphic->clearGraphs();
  ui->graphic->replot();
  if (model_calc.GetIsX()) {
    ui->funcion_line->setText(QString::fromStdString(model_calc.Printer()));
    ui->pre_line->clear();

    model_calc.DrawGraphic(ui->line_min_x->value(), ui->line_max_x->value());

    ui->graphic->yAxis->setRange(model_calc.GetMinY(), model_calc.GetMaxY());
    ui->graphic->addGraph();
    for (size_t i = 0; i < model_calc.GetResX().size(); ++i)
      ui->graphic->graph(0)->addData(model_calc.GetResX(i),
                                     model_calc.GetResY(i));
    ui->graphic->replot();
    ui->graphic->setInteraction(QCP::iRangeZoom, true);
    ui->graphic->setInteraction(QCP::iRangeDrag, true);
  }
  model_calc.Clear();
}

void MainWindow::on_button_unar_clicked() {
  ui->pre_line->setText(QString::fromStdString(
      model_calc.Unar(ui->pre_line->text().toStdString())));
}

void MainWindow::on_button_credit_clicked() { credit.show(); }

void MainWindow::on_button_deposit_clicked() { deposit.show(); }
