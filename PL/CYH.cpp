#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>

using namespace std;

unordered_map<string, int> variables;
string output;

const string LETTERS = "abcdefghijklmnopqrstuvwxyz";
const vector<string> RELATIONAL_OPERATORS = {"==", "!=", "<", ">", "<=", ">="};
const vector<string> MATH_OPERATORS = {"+", "-", "*", "/"};
bool DEBUG_MODE = false;

void debug_log(const string& message) {
    if (DEBUG_MODE) {
        cout << "[DEBUG] " << message << endl;
    }
}

void parse_program(const vector<string>& code_tokens);
void parse_declaration(const vector<string>& code_tokens);
bool validate_type(const string& var_type);
bool validate_variable(const string& var_name);
void parse_statement(const vector<string>& code_tokens);
bool evaluate_boolean_expression(const vector<string>& tokens);
string get_relational_operator(const string& operator_);
int evaluate_arithmetic_expression(const vector<string>& tokens);
int parse_term(const vector<string>& tokens);
int parse_number(const string& number_str);
string validate_digit(const string& digit);

void parse_program(const vector<string>& code_tokens) {
    debug_log("parse_program: " + code_tokens[0]);
    size_t token_start = 0;
    if (code_tokens.back() != ";") {
        throw runtime_error("syntax error!!");
    }

    int while_count = 0;
    bool statement_started = false;
    for (size_t index = 0; index < code_tokens.size(); ++index) {
        if (code_tokens[index] == "do") {
            while_count++;
        } else if (code_tokens[index] == "}") {
            if (while_count == 0) {
                throw runtime_error("syntax error!!");
            }
            while_count--;
        } else if (while_count == 0 && code_tokens[index] == ";") {
            if (code_tokens[token_start] == "int") {
                if (statement_started) {
                    throw runtime_error("syntax error!!");
                }
                parse_declaration(vector<string>(code_tokens.begin() + token_start, code_tokens.begin() + index + 1));
            } else {
                statement_started = true;
                parse_statement(vector<string>(code_tokens.begin() + token_start, code_tokens.begin() + index + 1));
            }
            token_start = index + 1;
        }
    }

    if (while_count != 0) {
        throw runtime_error("syntax error!!");
    }
}

void parse_declaration(const vector<string>& code_tokens) {
    debug_log("parse_declaration: " + code_tokens[0]);
    if (code_tokens.size() != 3) {
        throw runtime_error("syntax error!!");
    }

    if (!validate_type(code_tokens[0]) || !validate_variable(code_tokens[1])) {
        throw runtime_error("syntax error!!");
    }

    variables[code_tokens[1]] = 0;
}

bool validate_type(const string& var_type) {
    debug_log("validate_type: " + var_type);
    return var_type == "int";
}

bool validate_variable(const string& var_name) {
    debug_log("validate_variable: " + var_name);
    if (var_name.size() > 10) {
        throw runtime_error("syntax error!!");
    }

    for (char c : var_name) {
        if (LETTERS.find(c) == string::npos) {
            throw runtime_error("syntax error!!");
        }
    }

    return true;
}

void parse_statement(const vector<string>& code_tokens) {
    // debug_log("parse_statement: " + code_tokens[0]);
    if (code_tokens[1] == "=") {
        if (!validate_variable(code_tokens[0])) {
            throw runtime_error("syntax error!!");
        }
        if (variables.find(code_tokens[0]) == variables.end()) {
            throw runtime_error("syntax error!!");
        }

        // debug_log("BEFORE: " + to_string(variables[code_tokens[0]]));
        variables[code_tokens[0]] = evaluate_arithmetic_expression(vector<string>(code_tokens.begin() + 2, code_tokens.end() - 1));
        // debug_log("AFTER: " + to_string(variables[code_tokens[0]]));
    } else if (code_tokens[0] == "print") {
        if (any_of(RELATIONAL_OPERATORS.begin(), RELATIONAL_OPERATORS.end(), [&code_tokens](const string& op) { return find(code_tokens.begin(), code_tokens.end(), op) != code_tokens.end(); })) {
            // debug_log("PRINTING BOOLEAN EXPRESSION");
            output += (evaluate_boolean_expression(vector<string>(code_tokens.begin() + 1, code_tokens.end() - 1)) ? "TRUE" : "FALSE") + string(" ");
        } else {
            output += to_string(evaluate_arithmetic_expression(vector<string>(code_tokens.begin() + 1, code_tokens.end() - 1))) + " ";
        }
    } else if (code_tokens[0] == "do" && code_tokens[1] == "{") {
        while (true) {
            int nested_while_count = 0;
            int end_while_idx = -1;
            size_t start_idx = 1;
            for (size_t i = 2; i < code_tokens.size(); ++i) {
                if (code_tokens[i] == "do") {
                    nested_while_count++;
                } else if (nested_while_count == 0 && code_tokens[i] == "}") {
                    end_while_idx = i + 1;
                    break;
                } else if (nested_while_count != 0 && code_tokens[i] == "}") {
                    if (nested_while_count == 0) {
                        throw runtime_error("syntax error!!");
                    }
                    nested_while_count--;
                } else if (nested_while_count == 0 && code_tokens[i] == ";") {
                    parse_statement(vector<string>(code_tokens.begin() + start_idx + 1, code_tokens.begin() + i + 1));
                    start_idx = i;
                }
            }

            if (end_while_idx == -1 || nested_while_count != 0) {
                throw runtime_error("syntax error!!");
            }

            if (!evaluate_boolean_expression(vector<string>(code_tokens.begin() + end_while_idx + 2, code_tokens.end() - 2))) {
                break;
            }
        }
    } else {
        throw runtime_error("syntax error!!");
    }
}

bool evaluate_boolean_expression(const vector<string>& tokens) {
    debug_log("evaluate_boolean_expression: " + tokens[0]);
    string relop = get_relational_operator(tokens[0]);

    vector<string> expr1, expr2;
    for (size_t i = 1; i < tokens.size() - 1; ++i) {
        if ((isdigit(tokens[i].back()) || isalpha(tokens[i].back()) || tokens[i].back() == ')') &&
            (isdigit(tokens[i + 1][0]) || isalpha(tokens[i + 1][0]) || tokens[i + 1][0] == '(')) {
            expr1 = vector<string>(tokens.begin() + 1, tokens.begin() + i + 1);
            expr2 = vector<string>(tokens.begin() + i + 1, tokens.end());
            break; // 10 + 2 3 * 3 3
        }
    }

    int val1 = evaluate_arithmetic_expression(expr1);
    int val2 = evaluate_arithmetic_expression(expr2);
    debug_log("EVALUATING: " + to_string(val1) + " " + relop + " " + to_string(val2));

    if (relop == "==") {
        return val1 == val2;
    } else if (relop == "!=") {
        return val1 != val2;
    } else if (relop == "<") {
        return val1 < val2;
    } else if (relop == ">") {
        return val1 > val2;
    } else if (relop == "<=") {
        return val1 <= val2;
    } else if (relop == ">=") {
        return val1 >= val2;
    } else {
        throw runtime_error("syntax error!!");
    }
}

string get_relational_operator(const string& operator_) {
    if (find(RELATIONAL_OPERATORS.begin(), RELATIONAL_OPERATORS.end(), operator_) != RELATIONAL_OPERATORS.end()) {
        return operator_;
    } else {
        throw runtime_error("syntax error!!");
    }
}

int evaluate_arithmetic_expression(const vector<string>& tokens) {
    debug_log("evaluate_arithmetic_expression: " + tokens[0]);
    if (tokens.empty()) {
        throw runtime_error("syntax error!!");
    }

    int result = 0;
    int current_index = -1;
    size_t term_start = -1;

    if (find(MATH_OPERATORS.begin(), MATH_OPERATORS.end(), tokens.back()) != MATH_OPERATORS.end()) {
        throw runtime_error("syntax error!!");
    }

    int open_bracket_count = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i + 1 == tokens.size()) {
            return parse_term(vector<string>(tokens.begin(), tokens.begin() + i + 1));
        }

        if (tokens[i] == "(") {
            open_bracket_count++;
        } else if (tokens[i] == ")") {
            if (open_bracket_count == 0) {
                throw runtime_error("syntax error!!");
            }
            open_bracket_count--;
        } else if (open_bracket_count == 0 && find(MATH_OPERATORS.begin(), MATH_OPERATORS.end(), tokens[i]) != MATH_OPERATORS.end()) {
            result = parse_term(vector<string>(tokens.begin(), tokens.begin() + i));
            current_index = i;
            term_start = i + 1;
            break;
        }
    }

    if (open_bracket_count != 0) {
        throw runtime_error("syntax error!!");
    }

    string current_operator = tokens[current_index];
    while (current_index < tokens.size()) {
        debug_log("CHECKING TOKEN " + tokens[current_index]);
        if (tokens[current_index] == "(") {
            open_bracket_count++;
        } else if (tokens[current_index] == ")") {
            if (open_bracket_count == 0) {
                throw runtime_error("syntax error!!");
            }
            open_bracket_count--;
        }

        if (open_bracket_count == 0 && (current_index + 1 == tokens.size() || find(MATH_OPERATORS.begin(), MATH_OPERATORS.end(), tokens[current_index + 1]) != MATH_OPERATORS.end())) {
            if (current_operator == "+") {
                result += parse_term(vector<string>(tokens.begin() + term_start, tokens.begin() + current_index + 1));
            } else if (current_operator == "-") {
                result -= parse_term(vector<string>(tokens.begin() + term_start, tokens.begin() + current_index + 1));
            } else if (current_operator == "*") {
                result *= parse_term(vector<string>(tokens.begin() + term_start, tokens.begin() + current_index + 1));
            } else if (current_operator == "/") {
                result /= parse_term(vector<string>(tokens.begin() + term_start, tokens.begin() + current_index + 1));
                if (to_string(result).back() == '0') {
                    result = static_cast<int>(result);
                }
            }
        } else if (open_bracket_count == 0 && find(MATH_OPERATORS.begin(), MATH_OPERATORS.end(), tokens[current_index]) != MATH_OPERATORS.end()) {
            current_operator = tokens[current_index];
            term_start = current_index + 1;
        }

        current_index++;
    }

    if (open_bracket_count != 0) {
        throw runtime_error("syntax error!!");
    }

    return result;
}

int parse_term(const vector<string>& tokens) {
    debug_log("parse_term: " + tokens[0]);
    if (tokens[0][0] != '(') {
        if (isdigit(tokens[0][0])) {
            int result = parse_number(tokens[0]);
            debug_log("NUMBER PARSED: " + to_string(result));
            return result;
        } else if (variables.find(tokens[0]) != variables.end()) {
            int result = variables[tokens[0]];
            debug_log("VARIABLE PARSED: " + to_string(result));
            return result;
        } else {
            throw runtime_error("syntax error!!");
        }
    }

    if (tokens.back().back() == ')') {
        int result = evaluate_arithmetic_expression(vector<string>(tokens.begin() + 1, tokens.end() - 1));
        debug_log("ARITHMETIC EXPRESSION PARSED: " + to_string(result));
        return result;
    } else {
        throw runtime_error("syntax error!!");
    }
}

int parse_number(const string& number_str) {
    if (number_str.size() > 10) {
        throw runtime_error("syntax error!!");
    }

    string num;
    for (char c : number_str) {
        num += validate_digit(string(1, c));
    }
    return stoi(num);
}

string validate_digit(const string& digit) {
    if (digit.find_first_of("0123456789") != string::npos) {
        return digit;
    } else {
        throw runtime_error("syntax error!!");
    }
}

int main() {
    while (true) {
        try {
            string input_code;
            cout << ">> ";
            getline(cin, input_code);
            if (input_code == "terminate") {
                break;
            }

            istringstream iss(input_code);
            vector<string> tokens((istream_iterator<string>(iss)), istream_iterator<string>());
            parse_program(tokens);

            if (!output.empty()) {
                cout << ">> " << output << endl;
            }
            output.clear();
            variables.clear();
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
