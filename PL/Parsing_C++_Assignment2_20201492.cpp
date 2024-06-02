#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

unordered_map<string, int> variables;
vector<string> COMPARE_OP = {"==", "!=", "<", ">", "<=", ">="};
string result;

void program(vector<string>);
void declaration(vector<string>);
void statement(vector<string>);
bool bexpr(vector<string>);
string relop(string);
int aexpr(vector<string>);
int term(vector<string>);
bool type(string);
bool number(string);
char dec(char);
bool var(string);
char alphabet(char);

void raise_error() {
    throw runtime_error("Syntax Error!!");
}

int main() {
    while (true) {
        string input, token;
        vector<string> tokens;
        cout << ">> ";
        getline(cin, input);
        if (input == "terminate") { break; }
        istringstream iss(input);
        while (iss >> token) {
            tokens.push_back(token);
        }
        try {
            program(tokens);
            if (result == "") {
                continue;
            } else {
                cout << ">> " << result << '\n';
            }
        } catch (runtime_error& e) {
            cout << ">> " << e.what() << '\n';
        }
        result.clear();
    }
    return 0;
}

void program(vector<string> tokens) {
    if (tokens.empty()) { return; }
    if (tokens.back() != ";") { raise_error(); }

    int token_start = 0;
    int dowhile_cnt = 0;
    bool statement_start = false;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i] == "{") {
            dowhile_cnt++;
        } else if (tokens[i] == "}") {
            if (dowhile_cnt == 0) {
                raise_error();
            }
            dowhile_cnt--;
        } else if (tokens[i] == ";" && dowhile_cnt == 0) {
            if (tokens[token_start] == "int") {
                if (statement_start) {
                    raise_error();
                }
                try {
                    declaration(vector<string>(tokens.begin() + token_start, tokens.begin() + i + 1));
                } catch (runtime_error& e) {
                    raise_error();
                }
            } else {
                statement_start = true;
                try {
                    statement(vector<string>(tokens.begin() + token_start, tokens.begin() + i + 1));
                } catch (runtime_error& e) {
                    raise_error();
                }
            }
            token_start = i + 1;
        }
    }
    if (dowhile_cnt != 0) {
        raise_error();
    }
}

void declaration(vector<string> tokens) {
    if (tokens.size() != 3 || tokens.back() != ";") {
        raise_error();
    }
    if (!type(tokens[0]) || !var(tokens[1])) {
        raise_error();    
    }
    variables[tokens[1]] = 0;
}

void statement(vector<string> tokens) {
    if (tokens.back() != ";") {
        raise_error();
    }
    if (tokens[1] == "=") {
        if (!var(tokens[0]) || variables.find(tokens[0]) == variables.end()) {
            raise_error();
        }
        vector<string> v;
        for (int i = 2; i < tokens.size() - 1; i++) {
            v.push_back(tokens[i]);
        }
        try {
            variables[tokens[0]] = aexpr(v);
        } catch (runtime_error& e) {
            raise_error();
        }
    } else if (tokens[0] == "print") {
        if (find(COMPARE_OP.begin(), COMPARE_OP.end(), tokens[1]) != COMPARE_OP.end()) {
            vector<string> v;
            for (int i = 1; i < tokens.size() - 1; i++) {
                v.push_back(tokens[i]);
            }
            try {
                if (bexpr(v)) { result += ("TRUE" + string(" ")); } 
                else { result += ("FALSE " + string(" ")); }
            } catch (runtime_error& e) {
                raise_error();
            }
            
        } else {
            vector<string> v;
            for (int i = 1; i < tokens.size() - 1; i++) {
                v.push_back(tokens[i]);
            }
            try {
                int tmp = aexpr(v);
                result += (to_string(tmp) + string(" "));
            } catch (runtime_error& e) {
                raise_error();
            }
        }
    } else if (tokens[0] == "do" && tokens[1] == "{") {
        int end;
        try {
            do {
                int dowhile_cnt = 0;
                int start = 1; 
                end = -1;
                for (int i = 2; i < tokens.size(); i++) {
                    if (tokens[i] == "{") {
                        dowhile_cnt++;
                    } else if (tokens[i] == "}" && dowhile_cnt == 0) {
                        if (tokens[i-1] == "}" || tokens[i-1] != ";" || tokens[i+1] != "while"|| tokens.back() != ";") {
                            raise_error();
                        }
                        if (tokens[i+2] != "(" || tokens[tokens.size()-2] != ")") {
                            raise_error();
                        }
                        end = i + 2;
                        break;
                    } else if (tokens[i] == "}" && dowhile_cnt != 0) {
                        if (dowhile_cnt == 0) {
                            raise_error();
                        }
                        dowhile_cnt--;
                    } else if (tokens[i]  == ";" && dowhile_cnt == 0) {
                        try {
                            statement(vector<string>(tokens.begin() + start + 1, tokens.begin() + i + 1));
                        } catch (runtime_error& e) {
                            raise_error();
                        }
                        start = i;
                    }
                }
                if (dowhile_cnt != 0 || end == -1) {
                    raise_error();
                }
            } while (bexpr(vector<string>(tokens.begin() + end + 1, tokens.end() - 2)));
        } catch (runtime_error& e) {
            raise_error();
        }
    } else {
        raise_error();
    }
}

bool bexpr(vector<string> tokens) {
    vector<string> v1, v2;
    string r_op;
    try {
        r_op = relop(tokens[0]);
    } catch (runtime_error& e) {
        raise_error();
    }

    for (int i = 1; i < tokens.size()-1; i++) {
        if ((isdigit(tokens[i].back()) || isalpha(tokens[i].back()) || tokens[i].back() == ')') &&
        (isdigit(tokens[i + 1][0]) || isalpha(tokens[i + 1][0]) || tokens[i + 1][0] == '(')) {
            v1 = vector<string>(tokens.begin() + 1, tokens.begin() + i + 1);
            v2 = vector<string>(tokens.begin() + i + 1, tokens.end());
            break;
        } 
    }

    int val1 = aexpr(v1);
    int val2 = aexpr(v2);

    if (r_op == "==") { return val1 == val2; }
    else if (r_op == "!=") { return val1 != val2; }
    else if (r_op == "<") { return val1 < val2; }
    else if (r_op == ">") { return val1 > val2; }
    else if (r_op == "<=") {return val1 <= val2; }
    else if (r_op == ">=") { return val1 >= val2; }
    else { raise_error(); }
}

string relop(string op) {
    if (find(COMPARE_OP.begin(), COMPARE_OP.end(), op) != COMPARE_OP.end()) {
        return op;
    } else {
        raise_error();
    }
}

int aexpr(vector<string> tokens) {
    int result = 0;
    int bracket = 0;
    vector<string> previous;
    string previous_op = "+";

    if (tokens.empty() || tokens.back() == "+" || tokens.back() == "-" || tokens.back() == "*" || tokens.back() == "/"
    || tokens[0] == "+" || tokens[0] == "-" || tokens[0] == "*" || tokens[0] == "/") {
        raise_error();
    }
    for (int i = 0; i < tokens.size(); i++) {
        if (bracket == 0 && (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")) {
            try {
                if (previous_op == "+") {
                    result += term(previous);
                    previous_op = tokens[i];
                    previous.clear();
                } else if (previous_op == "-") {
                    result -= term(previous);
                    previous_op = tokens[i];
                    previous.clear();
                } else if (previous_op == "*") {
                    result *= term(previous);
                    previous_op = tokens[i];
                    previous.clear();
                } else if (previous_op == "/") {
                    result /= term(previous);
                    previous_op = tokens[i];
                    previous.clear();
                } else {
                    raise_error();
                }
            } catch (runtime_error& e) {
                raise_error();
            }
        } else {
            if (tokens[i] == "(") {
                bracket++;
            } else if (tokens[i] == ")") {
                if (bracket == 0) {
                    raise_error();
                }
                bracket--;
            } 
            previous.push_back(tokens[i]);
        }
    }
    try {
        if (previous_op == "+") {
            result += term(previous);
            previous.clear();
        } else if (previous_op == "-") {
            result -= term(previous);
            previous.clear();
        } else if (previous_op == "*") {
            result *= term(previous);
            previous.clear();
        } else if (previous_op == "/") {
            result /= term(previous);
            previous.clear();
        } else {
            raise_error();
        }
    } catch (runtime_error& e) {
        raise_error();
    }

    if (bracket != 0) {
        raise_error();
    }
    return result;
}

int term(vector<string> tokens) {
    if (tokens.empty()) {
        raise_error();
    }
    vector<string> v;
    if (tokens[0] != "(") {
        if (tokens.size() != 1) {
            raise_error();
        }
        if (number(tokens[0])) {
            return stoi(tokens[0]);
        } else if (var(tokens[0]) && variables.find(tokens[0]) != variables.end()) {
            return variables[tokens[0]];
        } else {
            raise_error();
        }
    } else { 
        if (tokens.back() != ")") {
            raise_error();
        }
        for (int i = 1; i < tokens.size() - 1; i++) {
            v.push_back(tokens[i]);
        }
        try {
            int tmp = aexpr(v);
            return tmp;
        } catch (runtime_error& e) {
            raise_error();
        }
    }
}

bool type(string is_int) {
    if (is_int == "int") {
        return true;
    } else {
        return false;
    }
}

bool number(string token) {
    string num_result = "";
    for (int i = 0; i < token.length(); i++) {
        try {
            num_result += dec(token[i]);
        } catch (runtime_error& e) {
            return false;
        }
    }
    if (num_result.length() > 10) {
        raise_error();
    }
    return true;
}

char dec(char token) {
    if (!isdigit(token)) {
        raise_error();
    }
    int number = token - '0';
    for (int i = 0; i <= 9; i++) {
        if (i == number) { 
            return token; 
        }
    }
}

bool var(string token) {
    string variable = "";
    for (int i = 0; i < token.length(); i++) {
        try {
            variable += alphabet(token[i]);
        } catch (runtime_error& e) {
            return false;
        }
    }
    if (variable.length() > 10) {
        raise_error();
    }
    return true;
}

char alphabet(char token) {
    string letter = "abcdefghijklmnopqrstuvwxyz";
    if (isdigit(token)) {
        raise_error();
    }
    for (int i = 0; i < letter.length(); i++) {
        if (token == letter[i]) {
            return token;
        }
    }
    raise_error();
}