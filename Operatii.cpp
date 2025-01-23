#include <iostream>
#include <string>
#include <cmath>
#include "Operatii.h"
using namespace std;


double Operatii::Plus(double x, double y)
{
    return x + y;
    return 0.0;
}

double Operatii::Minus(double x, double y)
{
    return x - y;
    return 0.0;
}

double Operatii::Impartire(double x,  double y)
{
    if (y != 0) {
        return x / y;
    }
    else {
        cout << "Eroare! Nu se poate imparti la zero.\n";
    }
    return 0.0;
}

double Operatii::Inmultire(double x,  double y)
{
    return x * y;
    return 0.0;
}

double Operatii::Radical(double x, double y)
{
    int r = (int)y;
    if (r % 2 == 0)
    {
        if (x >= 0) {
            return pow(x, 1.0 / r);
        }
        else {
            cout << "Eroare! Nu se poate extrage radicalul dintr-un numar negativ.\n";
        }
    }
    else
    {
        return pow(x, 1.0 / r);
    }
    return 0.0;
}

double Operatii::Putere(double x, double y)
{
    return pow(x, y);
    return 0.0;
}
