#include <iostream>
#include <string>

using namespace std;


void parser(string input) {
    if (input == "") {
        return;
    }
}

bool program() {

}

void relop(string op) {
    
}

void factor() {

}

char dec(char num) {
    switch (num) {
        case '0':
            return '0';
            break;
        case '1':
            return '1';
            break;
        case '2':
            return '2';
            break;
        case '3':
            return '3';
            break;
        case '4':
            return '4';
            break;
        case '5':
            return '5';
            break;
        case '6':
            return '6';
            break;
        case '7':
            return '7';
            break;
        case '8':
            return '8';
            break;
        case '9':
            return '9';
            break;
        default:
            //에러 처리!
    }
}

char var(char xyz) {
    if (xyz == 'x') {
        return 'x';
    } else if (xyz == 'y') {
        return 'y';
    } else if (xyz == 'z') {
        return 'z';
    } 
    
}


int main() {
    while (true) {
        string input;
        cout << ">> ";
        getline(cin, input);
        parser(input);

    }
    return 0;
}