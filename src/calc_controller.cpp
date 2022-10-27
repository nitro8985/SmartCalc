#include "calc_controller.h"

using namespace s21;

double CalcController::GetResult(std::string exp, double mp) {
    CalcModel model(0, exp);
    return model.GetCalculatedData(mp);
}

double CalcController::GetAnnPayment(double sum, double percent, int months) {
    std::string str;
    CalcModel model(0, str);
    return model.CalculateAnnCredit(sum, percent, months);
}

std::vector<double> CalcController::GetDiffPayment(double sum, double percent,
                                                   int months) {
    std::string str;
    CalcModel model(0, str);
    return model.CalculateDiffCredit(sum, percent, months);
}
