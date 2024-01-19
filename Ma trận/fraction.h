#include <iostream>
#include <cmath>
using namespace std;
using ll = long long;
using ull = unsigned long long;
class fraction
{
    private:
        // Dấu
        bool sign;
        // Tử số
        ull numerator;
        // Mẫu số
        ull denominator;
        // Tìm ước chung lớn nhất
        ull gcd(ull a, ull b);
        // Tối giản phân số
        void simplify();
    public:
        // Hàm tạo rỗng
        fraction();
        // Hàm tạo với giá trị ban đầu
        template <typename T>
        fraction(T a);
        // Hàm tạo với hai đối
        fraction(ll a, ll b);
        // Hàm tạo với ba đối
        fraction(int sign, ull a, ull b);
        // Overwrite operator=
        template <typename T>
        void operator=(T a);
        // Overwrite operator+
        template <typename T>
        fraction operator+(T a);
        // In ra phân số
        friend std::ostream &operator<<(std::ostream &os, const fraction &f);
        // Overload operator- bên trái
        fraction operator-();
        // Overload operator- bên phải
        template <typename T>
        fraction operator-(T a);
        // Overload operator*
        template <typename T, typename X>
        friend fraction operator*(T a, X y);
        // Overload operator/
        template <typename T, typename X>
        friend fraction operator/(T a, X y);
};

//------------------------------------------------------------------------------------------------------------
// Tìm ước chung lớn nhất
ull fraction::gcd(ull a, ull b)
{
    while(b != 0)
    {
        ull c = a % b;
        a = b;
        b = c;
    }
    return a;
}

//------------------------------------------------------------------------------------------------------------
// Tối giản phân số
void fraction::simplify()
{
    ull c = gcd(numerator, denominator);
    numerator /= c;
    denominator /= c;
}

//------------------------------------------------------------------------------------------------------------
// Hàm tạo rỗng
fraction::fraction()
{
    sign = 1;
    numerator = 0;
    denominator = 1;
}

//------------------------------------------------------------------------------------------------------------
// Hàm tạo với giá trị khởi đầu
template <typename T>
fraction::fraction(T a)
{
    sign = (a >= 0) ? 1 : 0;
    short precision = std::numeric_limits<T>::digits10;
    if(a >= 0)
    {
        numerator = static_cast<ull>(a * std::pow(10, precision));
    }
    else
    {
        numerator = static_cast<ull>((-a) * std::pow(10, precision));
    }
    denominator = static_cast<ull>(std::pow(10, precision));
    simplify();
}

//------------------------------------------------------------------------------------------------------------
// Hàm tạo với hai đối
fraction::fraction(ll a, ll b)
{
    this->sign = ((a >= 0) & (b >= 0)) ? 1 : 0;
    this->numerator = abs(a);
    this->denominator = abs(b);
}

//------------------------------------------------------------------------------------------------------------
// Hàm tạo với ba đối
fraction::fraction(int sign, ull a, ull b)
{
    this->sign = (sign == 1) ? 1 : 0;
    this->numerator = a;
    this->denominator = b;
}

//------------------------------------------------------------------------------------------------------------
// Overwrite operator=
template <typename T>
void fraction::operator=(T a)
{
    (*this) = fraction(a);
}

//------------------------------------------------------------------------------------------------------------
// Overwrite operator+
template <typename T>
fraction fraction::operator+(T a)
{
    fraction b = a;
    fraction result;
    ull c = gcd(this->denominator, b.denominator);
    ull lcm = (this->denominator / c) * b.denominator;
    result.denominator = lcm;
    short x = (sign == 1) ? 1 : -1;
    short y = (b.sign == 1) ? 1 : -1;
    ull e = numerator * (lcm / denominator);
    ull f = b.numerator * (lcm / b.denominator);
    if(x * y < 0)
    {
        result.numerator = max(e, f) - min(e, f);
        if(result.numerator == 0)
        {
            result.sign = 1;
        }
        else
        {
            result.sign = (e >= f) ? sign : b.sign;
        }
    }
    else
    {
        result.numerator = e + f;
        if(result.numerator == 0)
        {
            result.sign = 1;
        }
        else
        {
            result.sign = (x > 0) ? 1 : 0;
        }
    }
    result.simplify();
    return result;
}

//------------------------------------------------------------------------------------------------------------
// Overload operator- bên trái
fraction fraction::operator-()
{
    fraction result(*this);
    result.sign = !sign;  // Negate the sign of the fraction
    return result;
}

//------------------------------------------------------------------------------------------------------------
// Overload operator- bên phải
template <typename T>
fraction fraction::operator-(T a)
{
    fraction b = -a;
    return (*this) + b;
}

//------------------------------------------------------------------------------------------------------------
// Overload operator*
template <typename T, typename X>
fraction operator*(T a, X y) {
    fraction b(a);
    fraction f(y);
    b.sign &= f.sign;
    b.numerator *= f.numerator;
    b.denominator *= f.denominator;
    b.simplify();
    return b;
}

//------------------------------------------------------------------------------------------------------------
// Overload operator/
template <typename T, typename X>
fraction operator/(T a, X y) {
    fraction b(a);
    fraction f(y);
    b.sign &= f.sign;
    b.numerator *= f.denominator;
    b.denominator *= f.numerator;
    b.simplify();
    return b;
}

//------------------------------------------------------------------------------------------------------------
// In ra phân số
std::ostream &operator<<(std::ostream &os, const fraction &f)
{
    if(!f.sign)
    {
        os << '-';
    }
    os << f.numerator;
    if (f.denominator != 1)
        os << '/' << f.denominator;
    return os;
}