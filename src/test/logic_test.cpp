#include "logic_test.h"

TEST(model, constr) {
    std::string test("3+2");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(5, mod.GetCalculatedData());
}

TEST(model, unmin) {
    std::string test("-(3+2)");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(-5, mod.GetCalculatedData());
}

TEST(model, unmin1) {
    std::string test("3--2");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(5, mod.GetCalculatedData());
}

TEST(model, mod) {
    std::string test("3mod2");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(1, mod.GetCalculatedData());
}

TEST(model, pow) {
    std::string test("3^3");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(27, mod.GetCalculatedData());
}

TEST(model, func) {
    std::string test("-sin(x)");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(-0.8414709848078965, mod.GetCalculatedData());
}

TEST(model, func1) {
    std::string test("tan(log(2.5))");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(0.42036710509516118, mod.GetCalculatedData());
}

TEST(model, func2) {
    std::string test("atan(ln(10))");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(1.1610795826858162, mod.GetCalculatedData());
}

TEST(model, func3) {
    std::string test("sqrt((-10 * -x)^3)");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(31.622776601683793, mod.GetCalculatedData());
}

TEST(model, func4) {
    std::string test("asin(-x)");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(-1.5707963267948966, mod.GetCalculatedData());
}

TEST(model, func5) {
    std::string test("acos(-x/2)");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(2.0943951023931957, mod.GetCalculatedData());
}

TEST(model, priority) {
    std::string test("-sin(x)*24+(cos(26))");
    s21::CalcModel mod(0, test);
    ASSERT_DOUBLE_EQ(-19.548384313060875, mod.GetCalculatedData());
}

TEST(controller, result) {
    ASSERT_DOUBLE_EQ(3000, s21::CalcController::GetResult("6e3/2", 1));
}

TEST(controller, ann) {
    ASSERT_DOUBLE_EQ(17816.572542119939,
                     s21::CalcController::GetAnnPayment(200000, 12.5, 12));
}

TEST(controller, diff) {
    std::vector<double> vd{10250, 10164.583333333334, 10079.878472222223};
    std::vector<double> test =
        s21::CalcController::GetDiffPayment(30000, 10, 3);
    for (int i = 0; i < vd.size(); i++) {
        ASSERT_DOUBLE_EQ(vd[i], test[i]);
    }
}

TEST(controller, throwpar) {
    ASSERT_ANY_THROW(s21::CalcController::GetResult("sinus(-x)", 1));
}

TEST(controller, throwbr) {
    ASSERT_ANY_THROW(s21::CalcController::GetResult("tan(-x))", 1));
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running main() from test.cpp\n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
