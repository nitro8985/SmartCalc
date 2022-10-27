#include "parser.h"

using namespace s21;

bool Parser::IsNum(char ch) { return (ch >= '0' && ch <= '9') ? true : false; }

bool Parser::IsOperator(char ch) {
    return (ch == '+' || ch == '*' || ch == '/' || ch == '-' || ch == '^' ||
            ch == '%')
               ? true
               : false;
}

bool Parser::IsFunc(char ch) {
    return (ch >= 'a' && ch <= 'z' && ch != 'x') ? true : false;
}

bool Parser::IsMod(char ch) { return (ch == 'm') ? true : false; }

int Parser::IsPar(char ch) {
    int ret = 0;
    if (ch == '(')
        ret = 1;
    else if (ch == ')')
        ret = 2;
    return ret;
}

char *Parser::UnaryMinus(char *ptr) {
    token zero_tok, mul;
    zero_tok.type = '0';
    zero_tok.value = -1;
    mul.type = '*';
    mul.value = 0;
    if (*ptr == '-') {
        in_.push_back(zero_tok);
        in_.push_back(mul);
        ptr++;
    }
    return ptr;
}

char *Parser::ScanNum(char *ptr) {
    token tok;
    tok.value = atof(ptr);
    tok.type = '0';
    in_.push_back(tok);
    char prev = '0';
    for (; (*ptr >= '0' && *ptr <= '9') || *ptr == ',' || *ptr == '.' ||
           *ptr == 'e' || *ptr == 'E' ||
           (*ptr == '-' && (prev == 'e' || prev == 'E')) ||
           (*ptr == '+' && (prev == 'e' || prev == 'E'));) {
        prev = *ptr;
        ptr++;
    }
    return ptr;
}

char *Parser::ScanOperator(char *ptr, int par_flag) {
    token tok;
    if (par_flag) {
        ptr = UnaryMinus(ptr);
    } else {
        tok.value = 0;
        tok.type = *ptr;
        in_.push_back(tok);
        ptr++;
    }
    return ptr;
}

char Parser::FuncDef(char *ptr, int &flag) {
    char ret = 'E';
    char buffer[6];
    int i = 0;
    for (; *ptr != '(' && *ptr != '\0'; ptr++, i++) {
        if (i > 5) {
            flag = 1;
            break;
        }
        if (*ptr == ' ') {
            break;
        }
        buffer[i] = *ptr;
    }
    buffer[i] = '\0';
    if (strcmp(buffer, "sin") == 0) ret = 's';
    if (strcmp(buffer, "cos") == 0) ret = 'c';
    if (strcmp(buffer, "tan") == 0) ret = 't';
    if (strcmp(buffer, "atan") == 0) ret = 'n';
    if (strcmp(buffer, "sqrt") == 0) ret = 'r';
    if (strcmp(buffer, "ln") == 0) ret = 'l';
    if (strcmp(buffer, "acos") == 0) ret = 'o';
    if (strcmp(buffer, "asin") == 0) ret = 'i';
    if (strcmp(buffer, "log") == 0) ret = 'g';
    return ret;
}

char *Parser::ScanFunc(char *ptr, int &flag) {
    token tok;
    char T = FuncDef(ptr, flag);
    if (T == 'E') {
        flag = 1;
    } else {
        tok.type = T;
        tok.value = 0;
        in_.push_back(tok);
        for (; *ptr != '(' && *ptr != '\0' && !IsNum(*ptr); ptr++) {
        }
    }
    return ptr;
}

char *Parser::ScanMod(char *ptr) {
    token tok;
    char buf[4];
    for (int i = 0; i < 3; i++, ptr++) {
        buf[i] = *ptr;
    }
    buf[3] = '\0';
    if (strcmp(buf, "mod") == 0) {
        tok.type = '%';
        tok.value = 0;
        in_.push_back(tok);
    }
    return ptr;
}

char *Parser::ScanPar(char *ptr) {
    token tok;
    if (*ptr == '(') {
        tok.type = '(';
    } else {
        tok.type = ')';
    }
    tok.value = 0;
    in_.push_back(tok);
    ptr++;
    return ptr;
}

char *Parser::ScanX(char *ptr) {
    token tok;
    tok.type = 'x';
    tok.value = 1.0;
    in_.push_back(tok);
    ptr++;
    return ptr;
}

void Parser::Tokenize(std::string &input, int &flag) {
    std::setlocale(LC_NUMERIC, "C");
    int par_flag = 0;
    token tmp;
    char *ptr = new char[256];
    char *initial = ptr;
    const char *cstr = input.c_str();
    strcpy(ptr, cstr);
    ptr = UnaryMinus(ptr);
    while (*ptr) {
        if (IsNum(*ptr)) {
            ptr = ScanNum(ptr);
        } else if (IsOperator(*ptr)) {
            tmp = in_.back();
            if (tmp.type != '0' && tmp.type != ')' && tmp.type != 'x') {
                ptr = UnaryMinus(ptr);
            } else {
                ptr = ScanOperator(ptr, par_flag);
            }
        } else if (*ptr == 'x') {
            ptr = ScanX(ptr);
        } else if (IsFunc(*ptr)) {
            if (IsMod(*ptr)) {
                ptr = ScanMod(ptr);
            } else {
                ptr = ScanFunc(ptr, flag);
            }
            if (*ptr == '\0') {
                flag = 1;
            }
        } else if (IsPar(*ptr)) {
            ptr = ScanPar(ptr);
            if (IsPar(*ptr) == 2) {
                par_flag = 1;
            }
            continue;
        } else if (*ptr == ' ') {
            ptr++;
        } else {
            flag = 1;
        }
        if (flag == 1) {
            ptr = initial;
            delete[] ptr;
            throw std::logic_error("parsing error");
        }
        par_flag = 0;
    }
    ptr = initial;
    delete[] ptr;
    BracketCount(in_);
}

int Parser::Priority(token tok) {
    char ch = tok.type;
    int ret = 0;
    if (ch == '+' || ch == '-') ret = 1;
    if (ch == '*' || ch == '/' || ch == '%') ret = 2;
    if (ch == '^' || ch == '!') ret = 3;
    return ret;
}

void Parser::BracketCount(std::list<token> &list) {
    typename std::list<token>::iterator it = list.begin();
    int open_count = 0;
    int close_count = 0;
    for (; it != list.end(); ++it) {
        if (it.operator*().type == '(') {
            open_count++;
        } else if (it.operator*().type == ')') {
            close_count++;
        }
    }
    if (open_count != close_count) {
        throw std::logic_error("invalid expression: bracket count");
    }
}

void Parser::MakeRpn() {
    std::list<token> ops;
    while (in_.size()) {
        token tok = in_.front();
        in_.pop_front();
        token tmp = ops.front();
        if (IsNum(tok.type) || tok.type == 'x') {
            polish_.push_back(tok);
        } else if (IsFunc(tok.type) || tok.type == '(') {
            ops.push_front(tok);
        } else if (IsOperator(tok.type)) {
            while (Priority(tok) <= Priority(tmp)) {
                polish_.push_back(ops.front());
                ops.pop_front();
                tmp = ops.front();
            }
            ops.push_front(tok);
        } else if (tok.type == ')') {
            while (tmp.type != '(' && ops.size()) {
                polish_.push_back(ops.front());
                ops.pop_front();
                tmp = ops.front();
            }
            if (tmp.type == '(') {
                ops.pop_front();
                tmp = ops.front();
                if (IsFunc(tmp.type)) {
                    polish_.push_back(ops.front());
                    ops.pop_front();
                }
            } else {
                throw std::logic_error("invalid expression");
            }
        }
    }
    while (ops.size() > 0) {
        token temp = ops.front();
        if (IsPar(temp.type)) {
            throw std::logic_error("invalid expression");
        } else {
            polish_.push_back(ops.front());
            ops.pop_front();
        }
    }
}

std::list<token> &Parser::GetRpn() { return polish_; }
