// techniki_programowania2.cpp

#include <iostream>
#include <stack>
#include <cctype>
#include <queue>
#include <string>
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
int dzialanie(string ope, string a, string b)
{
	char op = ope[0];
	int c=Toint(a);
	int d = Toint(b);
	cout<< c<<" " << d <<" "<< op << endl;
	switch (op)
	{
	case '+':
		c += d;
		break;
	case '-':
		c -= d;
		break;
	case '*':
		c *= d;
		break;
	case '/':
		if (d != 0)
			c /= d;
		else
			cout << "Dzielenie przez zero!" << endl;
		break;
	default:
		cout << "Nieznany operator!" << endl;
	}
	return c;
}
int main()
{
    stack<char> stos;
    queue<string> kolejkawyjscie;
    string input;
    getline(cin, input);
    string wyraz;
    int pozycja = 0;

    while (pozycja < input.length())
    {
        wyraz = rozdziel(input, pozycja);
        if (isNumber(wyraz))
        {
            kolejkawyjscie.push(wyraz);
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
                    kolejkawyjscie.push(string(1, stos.top()));
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
                kolejkawyjscie.push(string(1, stos.top()));
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
        kolejkawyjscie.push(string(1, stos.top()));
        stos.pop();
    }

    string a = kolejkawyjscie.front();
    kolejkawyjscie.pop();
    while (!kolejkawyjscie.empty())
    {

        string b = kolejkawyjscie.front();
        kolejkawyjscie.pop();
        string ope = kolejkawyjscie.front();
        kolejkawyjscie.pop();
        a = to_string(dzialanie(ope, a, b));
    }
	cout << "Wynik: " << a << endl;

    return 0;
}
