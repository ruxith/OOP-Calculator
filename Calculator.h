#pragma once
#include <iostream>
#include <string>
#include "ProcesareCalcul.h"
using namespace std;

class Calculator
{
protected:

	static double istoricRezultate[100];
	char* expresie;
	bool Valid;
	ProcesareCalcul calculeaza;
	static string numeCalculator;
	const int id;

public:

	Calculator(); 

	Calculator(char* expresie); 

	Calculator(const Calculator& x); 

	Calculator& operator=(const Calculator& x); 

	~Calculator(); 


	void setExpresie(const char* expresie);
	
	char* getExpresie();

	static string getNumeCalculator();

	static void setNumeCalculator(string nume);

	static int getNextid();

	static void setIstoricRezultate(int index, double rezultat);

	static double getIstoricRezultate(int index);
	static int getNumarIstoricRezultate();
	

	int getId() const;

	friend 
		ostream& operator<<(ostream& out, Calculator c);
	friend
		istream& operator>>(istream& in, Calculator& c);

	bool Validare();

	void ProcesareInput();

	void ScapDeSpatii();

	bool operator<(Calculator x);

	double operator+(Calculator x);
	
};



