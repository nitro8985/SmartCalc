#ifndef SRC_PARSER_H
#define SRC_PARSER_H
#include <cmath>
#include <cstring>
#include <list>
#include <stdexcept>
#include <string>

namespace s21 {

struct token {
    char type;
    double value;
};

class Parser {
 private:
    std::list<token> polish_, in_;

 public:
    explicit Parser(std::string &input) {
        int flag = 0;
        Tokenize(input, flag);
        MakeRpn();
    }
    ~Parser() {}
    std::list<token> &GetRpn();
    bool IsOperator(char ch);
    bool IsFunc(char ch);
    bool IsMod(char ch);
    bool IsNum(char ch);
    int IsPar(char ch);
    int Priority(token tok);

 private:
    void MakeRpn();
    void Tokenize(std::string &input, int &flag);
    char *UnaryMinus(char *ptr);
    char *ScanNum(char *ptr);
    char *ScanOperator(char *ptr, int par_flag);
    char *ScanPar(char *ptr);
    char *ScanX(char *ptr);
    char FuncDef(char *ptr, int &flag);
    char *ScanMod(char *ptr);
    char *ScanFunc(char *ptr, int &flag);
    void BracketCount(std::list<token> &list);
};
}  // namespace s21
#endif  // SRC_PARSER_H