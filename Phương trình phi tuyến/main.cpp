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

//------------------------------------------------------------------------------------------------------------

class function
{
    private:
        FunctionParser_ld f;
    public:
        // Hàm tạo
        function();
        NODISCARD long double operator()(long double x);
        // Overwrite cin để nhập hàm
        friend std::istream &operator>>(std::istream &is, function& f);
        // Phương pháp chia đôi
        NODISCARD long double bisect(long double a, long double b, ull N = 100);
        // Phương pháp lặp đơn
        NODISCARD long double iterate(long double x, long double eps = 0.000001, ull N = 100);
        // Phương pháp Newton
        NODISCARD long double newton(long double x, long double eps = 0.000001, ull N = 100);
};

//------------------------------------------------------------------------------------------------------------

function::function()
{
    FunctionParser_ld fparser;
    fparser.AddConstant("pi", 3.1415926535897932L);
    this->f = fparser;
}

//------------------------------------------------------------------------------------------------------------

long double function::operator()(long double x)
{
    long double *y = &x;
    return f.Eval(y);
}

//------------------------------------------------------------------------------------------------------------

std::istream &operator>>(std::istream &is, function& func)
{
    string function;
    bool cont = 1;
    if (std::cin.peek() == '\n') {
        std::cin.ignore(1);
    }
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
            std::cout << "Nhap lai ham" << "\n"; 
        }

    }
    return is;
}

//------------------------------------------------------------------------------------------------------------
// Tìm nghiện của phương trình phi tuyến bằng phương pháp chia đôi
// Giá trị nhập vào:
// - a và b là hai điểm biên của đoạn [a,b]
// - N là số lần chia đôi (giá trị mặc định là 100)
// Giá trị trả về: long double
// Độ phức tạp: O(N)
long double function::bisect(long double a, long double b, ull N)
{
    if((*this)(a) == 0)
    {
        return a;
    }
    if((*this)(b) == 0)
    {
        return b;
    }
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

//------------------------------------------------------------------------------------------------------------
// Tìm nghiệm của phương trình phi tuyến bằng phương pháp lặp đơn
// Giá trị nhập vào:
// - x là giá trị lặp ban đầu
// - eps là sai số cho trước, giá trị mặc định là 10^(-6)
// - N là số lần lặp tối đa, giá trị mặc định là 100
// Giá trị trả về: long double
// Độ phức tạp: O(N)
long double function::iterate(long double x, long double eps, ull N)
{
    if((*this)(x) == 0)
    {
        return x;
    }

    long double err = eps + 1;
    while((N--) && abs(err) > eps)
    {
        long double y = (*this)(x);
        err = abs(y - x);
        x = y;
    }
    return x;
}

//------------------------------------------------------------------------------------------------------------
// Tìm nghiệm của phương trình phi tuyến bằng phương pháp Newton
// Giá trị nhập vào:
// - x là giá trị lặp ban đầu
// - f'(x) là đạo hàm của hàm số f(x)
// - eps là sai số cho trước, giá trị mặc định là 10^(-6)
// - N là số lần lặp tối đa, giá trị mặc định là 100
// Giá trị trả về: long double
// Độ phức tạp: O(N)
long double function::newton(long double x, long double eps, ull N)
{
    if((*this)(x) == 0)
    {
        return x;
    }
    function g;
    cout << "Nhap dao ham f'(x) = ";
    cin >> g;
    long double err = eps + 1;
    while((N--) && abs(err) > eps)
    {
        long double y = x - (*this)(x) / g(x);
        err = abs(y - x);
        x = y;
    }
    return x;
}

int main()
{
    cout << setprecision(17);
    function f;
    cout << "f(x) = ";
    cin >> f;
    int option = 0;
    do
    {
        system("cls");
        cout << "1. Nhap lai ham." << "\n";
        cout << "2. Tinh gia tri cua ham." << "\n";
        cout << "3. Tim nghiem bang phuong phap chia doi." << "\n";
        cout << "4. Tim nghiem bang phuong phap lap don." << "\n";
        cout << "5. Tim nghiem bang phuong phap Newton." << "\n";
        cout << "0. Ket thuc." << "\n";
        cout << "Chon tac vu: ";
        cin >> option;
        switch(option)
        {
            case 1: // Nhập lại hàm
            {
                cout << "f(x) = ";
                cin >> f;
                system("pause");
                break;
            }
            case 2: // Tính giá trị của hàm
            {
                cout << "Nhap gia tri x = ";
                long double x;
                cin >> x;
                cout << "f(x) = " << f(x) << "\n";
                system("pause");
                break;
            }
            case 3: // Tìm nghiệm bằng phương pháp chia đôi
            {
                cout << "Nhap gia tri a = ";
                long double a;
                cin >> a;
                cout << "Nhap gia tri b = ";
                long double b;
                cin >> b;
                cout << "Nhap so lan lap toi da N = ";
                ull N;
                cin >> N;
                cout << "Nghiem can tim la "  << f.bisect(a, b, N) << "\n";
                system("pause");
                break;
            }
            case 4: // Tìm nghiệm bằng phương pháp lặp đơn
            {
                cout << "Nhap gia tri x = ";
                long double x;
                cin >> x;
                cout << "Nhap gia tri eps = ";
                long double eps;
                cin >> eps;
                cout << "Nhap so lan lap toi da N = ";
                ull N;
                cin >> N;
                cout << "Nghiem can tim la " << f.iterate(x, eps, N) << "\n";
                system("pause");
                break;
            }
            case 5: // Tìm nghiệm bằng phương pháp Newton
            {
                cout << "Nhap gia tri x = ";
                long double x;
                cin >> x;
                cout << "Nhap gia tri eps = ";
                long double eps;
                cin >> eps;
                cout << "Nhap so lan lap toi da N = ";
                ull N;
                cin >> N;
                cout << f.newton(x, eps, N) << " la nghiem can tim" << "\n";
                system("pause");
                break;
            }
        }
    } while (option != 0);
}
