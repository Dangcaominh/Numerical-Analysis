#include <cmath>
#include <iostream>
#include <iomanip>
#include "fraction.h"
using namespace std;
using ll = long long;
using ull = unsigned long long;
//------------------------------------------------------------------------------------------------------------
int main()
{
    fraction a;
    fraction b = 0.45;
    a = b * (1 / b) + 1 / b + 9;
    cout << a << "\n";
    return 0;
}
