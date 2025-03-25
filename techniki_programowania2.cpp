// techniki_programowania2.cpp

#include <iostream>
#include <stack>
#include <cctype>
#include <queue>
#include <string>
using namespace std;

struct operacja {
    char znak;
    int priorytet;
};

bool isNumber(const string& wyraz) {
    for (char c : wyraz) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int Toint(const string& wyraz) {
    int liczba = 0;
    for (char c : wyraz) {
        liczba = liczba * 10 + (c - '0');
    }
    return liczba;
}

int jakwazny(char znak) {
    if (znak == '+' || znak == '-') {
        return 1;
    } else if (znak == '*' || znak == '/') {
        return 2;
    } else {
        return 0;
    }
}

int main() {
    stack<char> stos;
    queue<string> kolejkawyjscie;
    string input;
    getline(cin, input);
    string wyraz;
    int pozycja = 0;

    while (pozycja < input.length()) {
        wyraz = ""; // resetowanie zmiennej wyraz
        while (pozycja < input.length() && input[pozycja] != ' ') {
            wyraz += input[pozycja];
            pozycja++;
        }
        pozycja++; // pominięcie spacji

        if (isNumber(wyraz)) {
            kolejkawyjscie.push(wyraz);
        } else if (wyraz == "+" || wyraz == "-" || wyraz == "*" || wyraz == "/") {
            operacja op;
            op.priorytet = jakwazny(wyraz[0]);
            if (op.priorytet == 0) {
                cout << "Bledny operator" << endl;
                return 0;
            } else {
                while (!stos.empty() && jakwazny(stos.top()) >= op.priorytet) {
                    kolejkawyjscie.push(string(1, stos.top()));
                    stos.pop();
                }
                stos.push(wyraz[0]);
            }
        } else if (wyraz == "(") {
            stos.push(wyraz[0]);
        } else if (wyraz == ")") {
            while (!stos.empty() && stos.top() != '(') {
                kolejkawyjscie.push(string(1, stos.top()));
                stos.pop();
            }
            if (!stos.empty()) {
                stos.pop();
            } else {
                cout << "Bledny nawias" << endl;
                return 0;
            }
        } else if (!wyraz.empty()) {
            cout << "Bledny znak" << endl;
            return 0;
        }
    }

    while (!stos.empty()) {
        kolejkawyjscie.push(string(1, stos.top()));
        stos.pop();
    }

    while (!kolejkawyjscie.empty()) {
        cout << kolejkawyjscie.front() << " ";
        kolejkawyjscie.pop();
    }

    return 0;
}
