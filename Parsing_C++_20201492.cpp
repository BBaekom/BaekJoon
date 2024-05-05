#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void program(vector<string>);
string statement(vector<string>);
string expr(vector<string>);
string bexpr(vector<string>);
string relop(string);
string aexpr(vector<string>);
string term(vector<string>);
string factor(string);
string number(string);
char dec(char);
string var(string);

string x = "0";
string y = "0";
string z = "0";

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
        } catch (runtime_error& e) {
            cout << e.what() << '\n';
        }
    }
    return 0;
}

void program(vector<string> tkns) {
    vector<string> current;
    vector<string> result;
    string res;
    try {
        for (int i = 0; i < tkns.size(); i++) {
            if (tkns[i] == ";") {
                current.push_back(tkns[i]);
                res = statement(current);
                current.clear();
                if (res == "execute") {
                    continue;
                } else {
                    result.push_back(res);
                }
            } else {   
                current.push_back(tkns[i]);
            }
        }
        if (!current.empty()) {
            result.push_back(statement(current));
            current.clear();
        }
        for  (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << "\n";

    } catch (runtime_error& e) {
        throw runtime_error("syntax error!!");
    } 

}

string statement(vector<string> tkns) {
    vector<string> current;
    if (tkns[0] == var(tkns[0])) {
        if (tkns[tkns.size()-1] != ";" || tkns[tkns.size()-2] == "=") {
            throw runtime_error("syntax error!!");
        }
        if (tkns[1] == "=") {
            for (int i = 2; i < tkns.size() - 1; i++) {
                current.push_back(tkns[i]);
            }
            if (tkns[0] == "x") {
                x = expr(current);
                return "execute";
            } else if (tkns[0] == "y") {
                y = expr(current);
                return "execute";
            } else if (tkns[0] == "z") {
                z = expr(current);
                return "execute";
            }
        } else {
            throw runtime_error("syntax error!!");
        }

    } else if (tkns[0] == "print") {
        if (tkns[tkns.size()-1] != ";") {
            throw runtime_error("syntax error!!");
        }
        if (tkns[1] == var(tkns[1])) { // x, y, z 중에 하나
            if (tkns[1] == "x") {
                return x;
            } else if (tkns[1] == "y") {
                return y;
            } else if (tkns[1] == "z") {
                return z;
            }
        } else {
            throw runtime_error("syntax error!!");
        }
    } else {
        throw runtime_error("syntax error!!");
    }
    
}

string expr(vector<string> tkns) {
    string result;

    if (tkns.size() == 1) {
        return aexpr(tkns);
    }

    if (tkns[1] == relop(tkns[1])) {
        try {
            result = bexpr(tkns);
        } catch (runtime_error& e) {
            throw runtime_error("syntax error!!");
        }
    } else if (relop(tkns[1]) == "error" && tkns[1].length() == 1) {
        try {
            result = aexpr(tkns);
        } catch (runtime_error& e) {
            throw runtime_error("syntax error!!");
        }
    }
    return result;

}

string bexpr(vector<string> tkns) {
    string result;
    string op;
    if (tkns.size() > 3) { throw runtime_error("syntax error!!");}
    try {
        if (tkns[0] == number(tkns[0])) {
            int first = stoi(tkns[0]);
            if (tkns[1] == relop(tkns[1])) {
                string op = relop(tkns[1]);
                if (tkns[2] == number(tkns[2])) {
                    int second = stoi(tkns[2]);
                    if (op == "==") {
                        if (first == second) {
                            result = "TRUE";
                        } else {
                            result = "FALSE";
                        }
                    } else if (op == "!=") {
                        if (first != second) {
                            result = "TRUE";
                        } else {
                            result = "FALSE";
                        }
                    } else if (op == "<") {
                        if (first < second) {
                            result = "TRUE";
                        } else {
                            result = "FALSE";
                        }
                    } else if (op == ">") {
                        if (first > second) {
                            result = "TRUE";
                        } else {
                            result = "FALSE";
                        }
                    } else if (op == "<=") {
                        if (first <= second) {
                            result = "TRUE";
                        } else {
                            result = "FALSE";
                        }
                    } else if (op == ">=") {
                        if (first >= second) {
                            result = "TRUE";
                        } else {
                            result = "FALSE";
                        }
                    }
                }
            } else {
                throw runtime_error("syntax error!!");
            }
        } 
        return result;
    } catch (runtime_error& e) {
        throw runtime_error("syntax error!!");
    } 

}

string relop(string token) {
    string result;
    if (token == "==") {
        result = "==";
    } else if (token == "!=") {
        result = "!=";
    } else if (token == "<=") {
        result = "<=";
    } else if (token == ">=") {
        result = ">=";
    } else if (token == "<") {
        result = "<";
    } else if (token == ">") {
        result = ">";
    } else if (token == "+" || token == "-" || token == "*" || token == "/" ) {
        result = "error";
    } else {
        throw runtime_error("syntax error!!");
    }
    return result;
}

string aexpr(vector<string> tkns) {
    vector<string> previous;
    int result = 0;
    string previous_op = "+";
    for (int i = 0 ; i < tkns.size(); i++) {
        if (tkns[i] == "+" || tkns[i] == "-") {

            if (previous_op == "+") {
                try {
                    result += stoi(term(previous));
                    previous_op = tkns[i];
                    previous.clear();
                } catch (runtime_error& e) {
                    throw runtime_error("syntax error!!");
                } 
            } else if (previous_op == "-") {
                try {
                    result -= stoi(term(previous));
                    previous_op = tkns[i];
                    previous.clear();
                } catch (runtime_error& e) {
                    throw runtime_error("syntax error!!");
                } 
            }

        } else {
            previous.push_back(tkns[i]);
        }
    }

    if (previous_op == "+") {
        try {
            result += stoi(term(previous));
            previous_op = "+";
        } catch (runtime_error& e) {
            throw runtime_error("syntax error!!");
        } 
    } else if (previous_op == "-") {
        try {
            result -= stoi(term(previous));
            previous_op = "-";
        } catch (runtime_error& e) {
            throw runtime_error("syntax error!!");
        } 
    }

    return to_string(result);
}

string term(vector<string> tkns) {
    try {
        factor(tkns[0]);
    } catch (runtime_error& e) {
        throw runtime_error("syntax error!!");
    } 
    int result = stoi(tkns[0]);
    for (int i = 1; i < tkns.size(); i++) {
        if (tkns[i] == "/") {
            try {
                factor(tkns[i+1]);
                result /= stoi(tkns[i+1]);
            } catch (runtime_error& e) {
                throw runtime_error("syntax error!!");
            } 
        } else if (tkns[i] == "*") {
            try {
                factor(tkns[i+1]);
                result *= stoi(tkns[i+1]);
            } catch (runtime_error& e) {
                throw runtime_error("syntax error!!");
            } 
        } else { 
            try {
                factor(tkns[i]);
                continue;
            } catch (runtime_error& e) {
                throw runtime_error("syntax error!!");
            } 
        }
    }
    return to_string(result);
}

string factor(string token) { 
    try {
        string result =  number(token);
        return result;
    } catch (runtime_error& e) {
        throw runtime_error("syntax error!!");
    }
}

string number(string token) {
    string num_result = "";
    for (int i = 0; i < token.length(); i++) {
        if (isdigit(token[i])) {
            num_result += dec(token[i]);
        } else {
            throw runtime_error("syntax error!!");
        }
    }
    return num_result;
}

char dec(char token) {
    int number = token - '0';
    for (int i = 0; i <= 9; i++) {
        if (i == number) { 
            return token; 
        } 
    }
}

string var(string token) {
    if (token == "x") { return "x"; }
    else if (token == "y") { return "y"; }
    else if (token == "z") { return "z"; }
    else { 
        return "error";
    }
}
