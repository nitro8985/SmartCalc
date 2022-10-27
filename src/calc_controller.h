#ifndef SRC_CALC_CONTROLLER_H
#define SRC_CALC_CONTROLLER_H

#include "calc_model.h"

namespace s21 {
class CalcController {
 public:
    CalcController() {}
    ~CalcController() {}
    static double GetResult(std::string exp, double mp);
    static double GetAnnPayment(double sum, double percent, int months);
    static std::vector<double> GetDiffPayment(double sum, double percent,
                                              int months);
};
}  // namespace s21
#endif  // SRC_CALC_CONTROLLER_H