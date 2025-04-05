// techniki_programowania2.cpp

#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <deque>
using namespace std;

struct operacja
{
    char znak;
    int priorytet;
};

bool isNumber(const string& wyraz)
{
    for (char c : wyraz)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

int Toint(string wyraz)
{
    int liczba = 0;
    for (char c : wyraz)
    {
        liczba = liczba * 10 + (c - '0');
    }
    return liczba;
}

int jakwazny(char znak)
{
    if (znak == '+' || znak == '-')
    {
        return 1;
    }
    else if (znak == '*' || znak == '/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

string rozdziel(string& input, int& pozycja)
{
    string wyraz;
    while (pozycja < input.length() && isspace(input[pozycja]))
    {
        pozycja++;
    }
    if (pozycja < input.length() && isdigit(input[pozycja]))
    {
        while (pozycja < input.length() && isdigit(input[pozycja]))
        {
            wyraz += input[pozycja++];
        }
    }
    else if (pozycja < input.length() && (input[pozycja] == '+' || input[pozycja] == '-' || input[pozycja] == '*' || input[pozycja] == '/' || input[pozycja] == '(' || input[pozycja] == ')'))
    {
        wyraz += input[pozycja++];
    }
    return wyraz;
}
int dzialanie(deque<string>& kolejka)
{
	
    if (kolejka.empty())
    {
        return 0;
    }

    string element = kolejka.front();
    kolejka.pop_front();

    if (isNumber(element))
    {
        return Toint(element);
    }
    else
    {
        int b = dzialanie(kolejka);
        int a = dzialanie(kolejka);
        char op = element[0];

        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b != 0)
                return a / b;
            else
                cout << "Dzielenie przez zero!" << endl;
            return 0;
        default:
            cout << "Nieznany operator!" << endl;
            return 0;
        }
    }
}
int main()
{
    stack<char> stos;
    deque<string> kolejkawyjscie;
    string input;
    getline(cin, input);
    string wyraz;
    int pozycja = 0;

    while (pozycja < input.length())
    {
        wyraz = rozdziel(input, pozycja);
        if (isNumber(wyraz))
        {
            kolejkawyjscie.push_front(wyraz);
        }
        else if (wyraz == "+" || wyraz == "-" || wyraz == "*" || wyraz == "/")
        {
            operacja op;
            op.priorytet = jakwazny(wyraz[0]);
            if (op.priorytet == 0)
            {
                cout << "Bledny operator" << endl;
                return 0;
            }
            else
            {
                while (!stos.empty() && jakwazny(stos.top()) >= op.priorytet)
                {
                    kolejkawyjscie.push_front(string(1, stos.top()));
                    stos.pop();
                }
                stos.push(wyraz[0]);
            }
        }
        else if (wyraz == "(")
        {
            stos.push(wyraz[0]);
        }
        else if (wyraz == ")")
        {
            while (!stos.empty() && stos.top() != '(')
            {
                kolejkawyjscie.push_front(string(1, stos.top()));
                stos.pop();
            }
            if (!stos.empty())
            {
                stos.pop();
            }
            else
            {
                cout << "Bledny nawias" << endl;
                return 0;
            }
        }
        else if (!wyraz.empty())
        {
            cout << "Bledny znak" << endl;
            return 0;
        }
    }

    while (!stos.empty())
    {
        kolejkawyjscie.push_front(string(1, stos.top()));
        stos.pop();
    }    
        
    
   cout<< dzialanie(kolejkawyjscie);
	

    return 0;
}
