#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Calculator.h"
using namespace std;

class Faza2 : public Calculator
{
public:
    void scrieIstoricRezultateInFisier(const string& numeFisier);
  
    void afiseazaContinutFisier();

    virtual void afiseazaMeniu() = 0;
};

class Meniu : public Faza2
{
public:

    void afiseazaMeniu();
};