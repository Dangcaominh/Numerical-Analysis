#include ".\fpconfig.hh"
#include ".\fparser.hh"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#define NODISCARD [[nodiscard]]

class function
{
    private:
        FunctionParser_ld f;
    public:
        function();
        NODISCARD long double operator()(long double x);
        friend std::istream &operator>>(std::istream &is, function& f);
        NODISCARD long double bisect(double a, double b, ull N);
};

function::function()
{
    FunctionParser_ld fparser;
    fparser.AddConstant("pi", 3.1415926535897932L);
    this->f = fparser;
}

long double function::operator()(long double x)
{
    long double *y = &x;
    return f.Eval(y);
}

std::istream &operator>>(std::istream &is, function& func)
{
    string function;
    bool cont = 1;
    while(cont)
    {
        std::getline(std::cin, function);
        if(std::cin.fail())
        {
            cout << "cin failed";
            exit(0);
        }

        int res = func.f.Parse(function, "x");
        if(res < 0)
        {
            cont = 0;
        }
        else
        {
            std::cout << std::string(res+7, ' ') << "^\n"
                  << func.f.ErrorMsg() << "\n\n";
            std::cout << "Input function again" << "\n"; 
        }

    }
    return is;
}

long double function::bisect(double a, double b, ull N)
{
    
    long double result = (a + b) / 2;
    while(N--)
    {
        if((*this)(result) == 0)
        {
            break;
        }
        else if((*this)(result) * (*this)(a)<0)
        {
            b = result;
            result = (result + a) / 2;
        }
        else
        {
            a = result;
            result = (result + b) / 2;
        }
    }
    return result;
}

int main()
{
    cout << setprecision(10);
    function f;
    cout << "f(x) = ";
    cin >> f;
    cout << f.bisect(0, 1, 100) << "\n";
    return 0;
}
