#pragma once
#include "Operatii.h"
#include <iostream>
#include <string>

class ProcesareCalcul 
{
	Operatii operatie;
	public:

		void CautParanteze(char*& expresie);

		void CalculParanteze(int x, char*& expresie);


		void VerificaPutere(int x, int y, char*& expresie);

		void VerificaRadical(int x, int y, char*& expresie);

		void VerificaInmultire(int x, int y, char*& expresie);

		void VerificaImpartire(int x, int y, char*& expresie);

		void VerificaAdunare(int x, int y, char*& expresie);

		void VerificaScadere(int x, int y, char*& expresie);


		void InlocuireRezultat(int x, int y, char*& expresie,const char* result);


		double ParteaDreaptaOperator(int x, char* expresie);

		double ParteaStangaOperator(int x, char* expresie);


		static double charToDouble(char* array);
		
		char* doubleToCharArray(double number);
};