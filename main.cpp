// techniki_programowania2.cpp

#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <deque>
#include<future>
using namespace std;

struct operacja
{
    char znak;
    int priorytet;
};


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
bool jestoperatorem(char znak)
{
	return (znak == '+' || znak == '-' || znak == '*' || znak == '/' || znak == '(' || znak == ')');
}
string rozdziel(string& input, int& pozycja,bool &beforeisdigit)
{
    string wyraz;
    while (pozycja < input.length() && (isspace(input[pozycja])))
    {
        pozycja++;
    }
    if (!jestoperatorem(input[pozycja]) && !isdigit(input[pozycja]))
    {
        return "zly";
    }
    if (pozycja < input.length() && isdigit(input[pozycja]))
    {
        while (pozycja < input.length() && isdigit(input[pozycja]))
        {
            wyraz += input[pozycja++];
        }
    }
    else if (pozycja < input.length() && jestoperatorem(input[pozycja]))
    {
        wyraz += input[pozycja++];
    }
    if(isdigit(wyraz[0])&&beforeisdigit==1)
    {
        return "zly";
    }
    else if (isdigit(wyraz[0]))
    {
        beforeisdigit=1;
    }
    else
    {
        beforeisdigit=0;
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
    if (isdigit(element[0]))
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
                std::cout << "Dzielenie przez zero!" << endl;
            return 0;
        default:
            std::cout << "Nieznany operator!" << endl;
            return 0;
        }
    }
}
int main()
{
    stack<char> stos;
    deque<string> kolejkawyjscie;
    string input;
    getline(std::cin, input);
    string wyraz;
    int pozycja = 0;
   bool beforeisdigit=0;
    while (pozycja < input.length())
    {
        wyraz = rozdziel(input, pozycja,beforeisdigit);
		if (wyraz == "zly")
		{
			std::cout << "nieprawidlowa składnia" << endl;
			return 0;   
		}
        if (isdigit(wyraz[0]))
        {
            kolejkawyjscie.push_front(wyraz);
        }
        else if (wyraz == "+" || wyraz == "-" || wyraz == "*" || wyraz == "/")
        {
            operacja op;
            op.priorytet = jakwazny(wyraz[0]);
            if (op.priorytet == 0)
            {
                std::cout << "Bledny operator" << endl;
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
                std::cout << "Bledny nawias" << endl;
                return 0;
            }
        }
        
    }

    while (!stos.empty())
    {
        kolejkawyjscie.push_front(string(1, stos.top()));
        stos.pop();
    }    
    for (int i = kolejkawyjscie.size() - 1; i >= 0; i--)
    {
        std::cout << kolejkawyjscie[i] << " ";
	}std::cout << endl;
    
   

    auto future_result = std::async(std::launch::async, dzialanie, std::ref(kolejkawyjscie));
    int wynik = future_result.get();
    std::cout << wynik << endl;
	

    return 0;
}
