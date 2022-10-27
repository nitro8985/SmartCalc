#include "calc_model.h"

using namespace s21;

token CalcModel::Calculate(double multiplicator) {
    token res = {'0', 0};
    token a, b;
    int flag = 0;
    std::list<token> nums;
    while (par_.GetRpn().size()) {
        token tok = par_.GetRpn().front();
        par_.GetRpn().pop_front();
        if (tok.type == '0') {
            nums.push_front(tok);
        } else if (par_.IsOperator(tok.type)) {
            b = nums.front();
            nums.pop_front();
            a = nums.front();
            nums.pop_front();
            if (tok.type == '*') {
                res.value = a.value * b.value;
            } else if (tok.type == '/') {
                res.value = a.value / b.value;
            } else if (tok.type == '+') {
                res.value = a.value + b.value;
            } else if (tok.type == '-') {
                res.value = a.value - b.value;
            } else if (tok.type == '^') {
                res.value = std::pow(a.value, b.value);
            } else if (tok.type == '%') {
                res.value = std::fmod(a.value, b.value);
            }
            nums.push_front(res);
        } else if (par_.IsFunc(tok.type)) {
            a = nums.front();
            nums.pop_front();

            if (tok.type == 's') {
                res.value = sin(a.value);
            } else if (tok.type == 'c') {
                res.value = cos(a.value);
            } else if (tok.type == 't') {
                res.value = tan(a.value);
            } else if (tok.type == 'n') {
                res.value = atan(a.value);
            } else if (tok.type == 'g') {
                res.value = log10(a.value);
            } else if (tok.type == 'l') {
                res.value = log(a.value);
            } else if (tok.type == 'r') {
                res.value = sqrt(a.value);
            } else if (tok.type == 'i') {
                res.value = asin(a.value);
            } else if (tok.type == 'o') {
                res.value = acos(a.value);
            }
            nums.push_front(res);
        } else if (tok.type == 'x') {
            tok.value *= multiplicator;
            nums.push_front(tok);
            flag = 1;
        }
    }
    res = nums.front();
    if (flag) {
        res.type = 'x';
    }
    data_ = res.value;
    return res;
}

double CalcModel::GetCalculatedData(double multiplicator) {
    return Calculate(multiplicator).value;
}

double CalcModel::GetCalculatedData() { return Calculate(1).value; }

double CalcModel::CalculateAnnCredit(double sum, double percent, int months) {
    double i = percent / 100 / 12;
    double ann_multiplier = i * pow(1 + i, months) / (pow(1 + i, months) - 1);
    return sum * ann_multiplier;
}

std::vector<double> CalcModel::CalculateDiffCredit(double sum, double percent,
                                                   int months) {
    std::vector<double> ret;
    double debt = sum;
    double payment = sum / months + DiffPaymentCalc(debt, percent);
    for (int i = 0; i < months; i++) {
        ret.push_back(payment);
        debt -= payment;
        payment = sum / months + DiffPaymentCalc(debt, percent);
    }
    return ret;
}

double CalcModel::DiffPaymentCalc(double debt, double percent) {
    return debt * (percent / 100 / 12);
}
