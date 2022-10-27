#include "SmartCalc.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), graph(new QCustomPlot) {
    ui->setupUi(this);
    ui->verticalLayout->addWidget(graph);
    graph->adjustSize();
    graph->addGraph();
    graph->xAxis->setLabel("x");
    graph->yAxis->setLabel("y");
    graph->xAxis->setRange(-domain, domain);
    graph->yAxis->setRange(-domain, domain);
}

MainWindow::~MainWindow() {
    delete ui;
    delete graph;
}

void MainWindow::on_pushButton_num1_clicked() { ui->lineEdit->insert("1"); }

void MainWindow::on_pushButton_num2_clicked() { ui->lineEdit->insert("2"); }

void MainWindow::on_pushButton_num0_clicked() { ui->lineEdit->insert("0"); }

void MainWindow::on_pushButton_result_clicked() {
    if (!ui->lineEdit->text().isEmpty()) {
        try {
            std::string exp = ui->lineEdit->text().toStdString();
            double result =
                s21::CalcController::GetResult(exp, 1);
            QString tmp = QString::number(result, 'f', precision);
            ui->lineEdit->setText(tmp);
        } catch (std::logic_error &) {
            ui->lineEdit->setText("Invalid input");
        }
    }
    on_pushButton_draw_graph_clicked();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {
    precision = position;
}

void MainWindow::on_pushButton_num3_clicked() { ui->lineEdit->insert("3"); }

void MainWindow::on_pushButton_num4_clicked() { ui->lineEdit->insert("4"); }

void MainWindow::on_pushButton_num5_clicked() { ui->lineEdit->insert("5"); }

void MainWindow::on_pushButton_num6_clicked() { ui->lineEdit->insert("6"); }

void MainWindow::on_pushButton_num7_clicked() { ui->lineEdit->insert("7"); }

void MainWindow::on_pushButton_num8_clicked() { ui->lineEdit->insert("8"); }

void MainWindow::on_pushButton_num9_clicked() { ui->lineEdit->insert("9"); }

void MainWindow::on_pushButton_plus_clicked() { ui->lineEdit->insert("+"); }

void MainWindow::on_pushButton_minus_clicked() { ui->lineEdit->insert("-"); }

void MainWindow::on_pushButton_mult_clicked() { ui->lineEdit->insert("*"); }

void MainWindow::on_pushButton_div_clicked() { ui->lineEdit->insert("/"); }

void MainWindow::on_pushButton_dot_clicked() { ui->lineEdit->insert("."); }

void MainWindow::on_lineEdit_returnPressed() { on_pushButton_result_clicked(); }

void MainWindow::on_pushButton_correct_clicked() { ui->lineEdit->backspace(); }

void MainWindow::on_pushButton_clear_clicked() { ui->lineEdit->clear(); }

void MainWindow::on_pushButton_bracket_open_clicked() {
    ui->lineEdit->insert("(");
}

void MainWindow::on_pushButton_bracket_close_clicked() {
    ui->lineEdit->insert(")");
}

void MainWindow::on_pushButton_mod_clicked() { ui->lineEdit->insert("mod"); }

void MainWindow::on_pushButton_sqrt_clicked() { ui->lineEdit->insert("sqrt("); }

void MainWindow::on_pushButton_log_clicked() { ui->lineEdit->insert("log("); }

void MainWindow::on_pushButton_ln_clicked() { ui->lineEdit->insert("ln("); }

void MainWindow::on_pushButton_sin_clicked() { ui->lineEdit->insert("sin("); }

void MainWindow::on_pushButton_asin_clicked() { ui->lineEdit->insert("asin("); }

void MainWindow::on_pushButton_cos_clicked() { ui->lineEdit->insert("cos("); }

void MainWindow::on_pushButton_acos_clicked() { ui->lineEdit->insert("acos("); }

void MainWindow::on_pushButton_tan_clicked() { ui->lineEdit->insert("tan("); }

void MainWindow::on_pushButton_atan_clicked() { ui->lineEdit->insert("atan("); }

void MainWindow::on_pushButton_X_clicked() { ui->lineEdit->insert("x"); }

void MainWindow::on_pushButton_pow_clicked() { ui->lineEdit->insert("^"); }

void MainWindow::on_pushButton_draw_graph_clicked() {
    if (!ui->lineEdit_graph->text().isEmpty()) {
        std::string exp = ui->lineEdit_graph->text().toStdString();
        try {
            QVector<double> xs(10000), ys(10000);
            double start = -domain;
            double step = 0.0002 * domain;
            for (int i = 0; i < 10000; ++i, start += step) {
                xs[i] = start;
                ys[i] = s21::CalcController::GetResult(exp, xs[i]);
                if (i != 0) {
                    if (ys[i] > domain * 4.0 || ys[i] < -domain * 4.0) {
                        ys[i] = qQNaN();
                        continue;
                    }
                }
            }
            graph->graph(0)->setData(xs, ys);
            graph->setInteraction(QCP::iRangeDrag, true);
            graph->setInteraction(QCP::iRangeZoom, true);
            graph->replot();
        } catch (std::logic_error &) {
            ui->lineEdit_graph->setText("invalid input");
        }
    } else {
        ui->lineEdit_graph->setText(ui->lineEdit->text());
    }
}

void MainWindow::on_lineEdit_graph_returnPressed() {
    on_pushButton_draw_graph_clicked();
}

void MainWindow::on_spinBox_domain_valueChanged(int arg1) {
    domain = arg1;
    graph->xAxis->setRange(-domain, domain);
    graph->yAxis->setRange(-domain, domain);
    on_pushButton_draw_graph_clicked();
}

void MainWindow::on_calc_credit_clicked() {
    ui->textBrowser->clear();
    if (!ui->lineEdit_cr_sum->text().isEmpty() &&
        !ui->lineEdit_cr_per->text().isEmpty() &&
        !ui->lineEdit_cr_mon->text().isEmpty()) {
        double sum = ui->lineEdit_cr_sum->text().toDouble();
        double percent = ui->lineEdit_cr_per->text().toDouble();
        int months = ui->lineEdit_cr_mon->text().toInt();
        double total = 0;
        if (ui->radioButton_2->isChecked()) {
            double result =
                s21::CalcController::GetAnnPayment(sum, percent, months);
            total = result * months;
            ui->textBrowser->append("Your payment is:");
            ui->textBrowser->append(QString::number(result));
            ui->textBrowser->append("\nTotal:");
            ui->textBrowser->append(QString::number(total));
            ui->textBrowser->append("\nOverpay:");
            ui->textBrowser->append(QString::number(total - sum));
        } else {
            std::vector<double> payments =
                s21::CalcController::GetDiffPayment(sum, percent, months);
            ui->textBrowser->append("Your payments are:");
            for (int i = 0; i < int(payments.size()); i++) {
                total += payments[i];
                QString s = QString::number(i + 1) + ": " +
                            QString::number(payments[i]);
                ui->textBrowser->append(s);
            }
            ui->textBrowser->append("\nTotal:");
            ui->textBrowser->append(QString::number(total));
            ui->textBrowser->append("\nOverpay:");
            ui->textBrowser->append(QString::number(total - sum));
        }
    }
}
