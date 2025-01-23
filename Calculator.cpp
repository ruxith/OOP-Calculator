#include <iostream>
#include <string>
#include "Calculator.h"
#include "ProcesareCalcul.h"
#include "Faza2.h"
using namespace std;

string Calculator::numeCalculator = "Ruxandra's Calculator";
double Calculator::istoricRezultate[100];
Meniu meniu;

//CONSTRUCTORI
Calculator::Calculator() : id(-1)
{
    expresie = nullptr;
    Valid = true;
}

Calculator :: Calculator(char* expresie) : id(getNextid())
{
    Valid = true;
    if (expresie != nullptr)
    { 
        this->expresie = new char[strlen(expresie) + 1];
        strcpy_s(this->expresie, strlen(expresie) + 1, expresie);
    }
    else
    {
        this->expresie = nullptr;
    }
}

Calculator::Calculator(const Calculator& x) : id(id)
{
    if (x.expresie != nullptr && strlen(x.expresie) > 0)
    {
        this->expresie = new char[strlen(x.expresie) + 1];
        strcpy_s(this->expresie, strlen(x.expresie) + 1, x.expresie);
    }
    else
    {
        expresie = nullptr;
    }
    Valid = x.Valid;
}

//OPERATOR =
Calculator& Calculator::operator=(const Calculator& x)
{
    if (this != &x)
    {
        if (expresie)
            delete[] expresie;
        if (x.expresie != nullptr && strlen(x.expresie) > 0)
        {
            this->expresie = new char[strlen(x.expresie) + 1];
            strcpy_s(this->expresie, strlen(x.expresie) + 1, x.expresie);
        }
        else
        {
            expresie = nullptr;
        }
        Valid = x.Valid;
    }
    return *this;
}

//DESCTRUCTOR
Calculator::~Calculator()
{
    if (expresie != nullptr)
        delete[] expresie;
    expresie = nullptr;

}

//GETTER&SETTER EXPRESIE
void Calculator::setExpresie(const char* expresie)
{
    if (expresie != nullptr)
    {
        this->expresie = new char[strlen(expresie) + 1];
        strcpy_s(this->expresie, strlen(expresie) + 1, expresie);
    }
    ProcesareInput();
}

char* Calculator::getExpresie()
{
    if (expresie != nullptr)
    {
        char* copie = new char[strlen(expresie) + 1];
        strcpy_s(copie, strlen(expresie) + 1, expresie);
        return copie;
    }
    return nullptr;
}

string Calculator::getNumeCalculator()
{
    return numeCalculator;
}

void Calculator::setNumeCalculator(string nume)
{
    Calculator::numeCalculator = nume;
}

int Calculator::getNextid()
{
    static int nextId = 0;
    return nextId++;
}

void Calculator::setIstoricRezultate(int index, double rezultat)
{
    Calculator::istoricRezultate[index] = rezultat;
}

double Calculator::getIstoricRezultate(int index)
{
    return  Calculator::istoricRezultate[index];
}

int Calculator::getNumarIstoricRezultate()
{
    int nrLinii = 0;
    for (int i = 0; i < 99; i++)
    {
        if (Calculator::istoricRezultate[i] != 0)
        {
            nrLinii++;
        }
    }
    return nrLinii;
}

int Calculator::getId() const
{
    return id;
}

//OPERATORII OSTREAM SI ISTREAM
ostream& operator<<(ostream& out, Calculator c)
{
    out << "Rezultatul expresiei matematice primite: \n";
    for (int i = 0; i < strlen(c.expresie); i++)
    {
        out << c.expresie[i];
    }
    out << endl;
    return out;
}

istream& operator>>(istream& in, Calculator& c)
{
    //cout << "Introduceti expresia matematica: \n";

    string aux;

    while (true)
    {
        getline(in, aux);

        
        if (aux == "exit") 
        {
            cout << "Apasati ENTER pentru a iesi din program\n";
            break;
        }
        if (aux == "help")
        {
            meniu.afiseazaMeniu();
        }
       
        if (c.expresie)
            delete[] c.expresie;

        c.expresie = new char[aux.length() + 1];
        strcpy_s(c.expresie, aux.length() + 1, aux.c_str());

        c.ProcesareInput();

    }
    
    return in;
}

//ALTE METODE
bool Calculator::Validare()
{
    for (int i = 0; i < strlen(expresie); i++)
    {
        if (strchr("1234567890+-/^*#.()[]", expresie[i]) == NULL)
        {
            Valid = false;
            break;
        }
    }
    return Valid; 
}

void Calculator::ProcesareInput()
{
    if (this->Validare() == true)
    {
        ScapDeSpatii(); 
        calculeaza.CautParanteze(expresie);
        setIstoricRezultate(getNextid(), ProcesareCalcul::charToDouble(expresie));
        cout << this->expresie << endl;
    }
    else if(strcmp(expresie, "help") != 0)
    {
        meniu.afiseazaMeniu();
    }
    else
    {
        cout << "Expresia contine caractere invalide";
    }
    
}

void Calculator::ScapDeSpatii()
{
    int i, j;
    for (i = 0; i < strlen(expresie); i++)
    {
        if (expresie[i] == ' ')
        {
            for (j = i; j < strlen(expresie); j++)
            {
                expresie[j] = expresie[j + 1];
            }
            expresie[j] = '\0';
            i--;
        }
    }
}

//ALTI OPERATORI

bool Calculator::operator<(Calculator x)
{
    if (istoricRezultate[this->id] < istoricRezultate[x.id])
        return true;
    else
        return false;
}

double Calculator::operator+(Calculator x)
{
    return istoricRezultate[this->id] + istoricRezultate[x.id];
}


