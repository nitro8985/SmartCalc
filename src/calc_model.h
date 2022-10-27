#ifndef SRC_CALC_MODEL_H
#define SRC_CALC_MODEL_H
#include <vector>

#include "parser.h"
namespace s21 {
class CalcModel {
 private:
    double data_;
    Parser par_;

    token Calculate(double multiplicator);
    double DiffPaymentCalc(double debt, double percent);

 public:
    CalcModel(double a, std::string &str) : data_(a), par_(str) {}
    ~CalcModel() {}
    double GetCalculatedData(double multiplicator);
    double GetCalculatedData();
    double CalculateAnnCredit(double sum, double percent, int months);
    std::vector<double> CalculateDiffCredit(double sum, double percent,
                                            int months);
};
}  // namespace s21
#endif  // SRC_CALC_MODEL_H