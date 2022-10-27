#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

#include "../calc_controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 private slots:
    void on_pushButton_num1_clicked();
    void on_pushButton_num2_clicked();
    void on_pushButton_num0_clicked();
    void on_pushButton_result_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_pushButton_num3_clicked();
    void on_pushButton_num4_clicked();
    void on_pushButton_num5_clicked();
    void on_pushButton_num6_clicked();
    void on_pushButton_num7_clicked();
    void on_pushButton_num8_clicked();
    void on_pushButton_num9_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_mult_clicked();
    void on_pushButton_div_clicked();
    void on_pushButton_dot_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_correct_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_bracket_open_clicked();
    void on_pushButton_bracket_close_clicked();
    void on_pushButton_mod_clicked();
    void on_pushButton_sqrt_clicked();
    void on_pushButton_log_clicked();
    void on_pushButton_ln_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_asin_clicked();
    void on_pushButton_cos_clicked();
    void on_pushButton_acos_clicked();
    void on_pushButton_tan_clicked();
    void on_pushButton_atan_clicked();
    void on_pushButton_draw_graph_clicked();
    void on_lineEdit_graph_returnPressed();
    void on_spinBox_domain_valueChanged(int arg1);
    void on_pushButton_X_clicked();
    void on_pushButton_pow_clicked();
    void on_calc_credit_clicked();

 private:
    Ui::MainWindow *ui;
    int precision = 1, domain = 10;
    QCustomPlot *graph;
};
#endif  // MAINWINDOW_H
