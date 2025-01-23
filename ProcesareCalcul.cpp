#define _CRT_SECURE_NO_WARNINGS
#include "ProcesareCalcul.h"
#include "Operatii.h"
#include <iostream>
#include <string>

void ProcesareCalcul::CautParanteze(char*& expresie)
{
	int x = 0, y = 0; 
	int nrParanteze = 0;
	for (int i = 0; i < strlen(expresie); i++)
	{
		if (expresie[i] == '(' || expresie[i] == '[')
		{
			nrParanteze++;
		}
	}
	for (int q = 0; q < nrParanteze; q++)
	{
		for (int i = 0; i < strlen(expresie); i++)
		{
			if (expresie[i] == '(' || expresie[i] == '[')
			{
				x = i;
			}
			if (expresie[i] == ')' || expresie[i] == ']')
			{
				y = i;
				break;
			}
		}

		char* expresieDintreParanteze = new char[y - x];
		for (int i = 0; i < y - x - 1; i++)
		{
			expresieDintreParanteze[i] = expresie[i + x + 1];
		}
		expresieDintreParanteze[y - x - 1] = '\0';

		int pozFinalResult = strlen(expresieDintreParanteze);

		for (int i = x; i < strlen(expresie); i++)
		{
			expresie[i] = expresie[i + 1];
		}
		for (int i = y - 1; i < strlen(expresie); i++)
		{
			expresie[i] = expresie[i + 1];
		}
		
		CalculParanteze(0, expresieDintreParanteze);

		InlocuireRezultat(x, x + pozFinalResult - 1, expresie, expresieDintreParanteze);

		delete[] expresieDintreParanteze;
	}
	CalculParanteze(0, expresie);
	
}


//ORDINEA IMPORTANTEI OPERATORILOR
void ProcesareCalcul::CalculParanteze(int x, char*& expresie)
{
	VerificaPutere(x, strlen(expresie), expresie);
	
	VerificaRadical(x, strlen(expresie), expresie);

	VerificaInmultire(x, strlen(expresie), expresie);

	VerificaImpartire(x, strlen(expresie), expresie);

	VerificaAdunare(x, strlen(expresie), expresie);
	
	VerificaScadere(x, strlen(expresie), expresie);

	VerificaPutere(x, strlen(expresie), expresie);

	VerificaRadical(x, strlen(expresie), expresie);

	VerificaInmultire(x, strlen(expresie), expresie);

	VerificaImpartire(x, strlen(expresie), expresie);
	
}

double ProcesareCalcul::ParteaStangaOperator(int x, char* expresie)
{
	int pozitie = 0;
	int i;
	for (i = x - 1; i >= 0; i--)
	{
		if (!isdigit(expresie[i]) && expresie[i] != '.')
		{
			pozitie = i + 1;
			break;
		}
	}

	char* exprToDouble = new char[x - pozitie + 1];
	for (int i = 0; i < x - pozitie + 1; i++)
	{
		exprToDouble[i] = expresie[i + pozitie];
	}
	exprToDouble[x - pozitie] = '\0';

	double rezultat = charToDouble(exprToDouble);
	delete[] exprToDouble;

	return rezultat;

}

double ProcesareCalcul::ParteaDreaptaOperator(int x, char* expresie)
{
	int pozitie = strlen(expresie);
	int i;
	for (i = x + 1; i <= strlen(expresie); i++)
	{
		if (!isdigit(expresie[i]) || expresie[i] != '.')
		{
			pozitie = i;
		}
	}
	char* exprToDouble = new char[strlen(expresie) - (x + 1) + 1];
	memcpy(exprToDouble, expresie + x + 1, pozitie - (x + 1));
	exprToDouble[pozitie - (x + 1)] = '\0';

	double rezultat = charToDouble(exprToDouble);
	delete[] exprToDouble;

	return rezultat;
}

double ProcesareCalcul::charToDouble(char* array)
{
	if (array != nullptr && strcmp(array, "") != 0)
		return stod(array);
	return 0.0;
}

char* ProcesareCalcul :: doubleToCharArray(double number) 
{
	string str = to_string(number);

	char* charArray = &str[0];

	return charArray;
}

void  ProcesareCalcul::VerificaPutere(int x, int y, char*& expresie)
{
	double rezultat = 0;
	for (int i = x + 1; i < y; i++)
	{
		if (expresie[i] == '^')
		{
			rezultat = operatie.Putere(ParteaStangaOperator(i, expresie), ParteaDreaptaOperator(i, expresie));
			
			string stringResult = to_string(rezultat);

			int pozResult = 0;
			for (int q = i - 1; q >= 0; q--)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozResult = q + 1;
					break;
				}
			}
			int pozFinalResult = 0;
			for (int q = i + 1; q <= strlen(expresie); q++)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozFinalResult = q - 1;
					break;
				}
			}
			if (pozFinalResult == 0)
			{
				pozFinalResult = strlen(expresie);
			}

			InlocuireRezultat(pozResult, pozFinalResult, expresie, stringResult.c_str());
			i--;
		}

	}
}

void  ProcesareCalcul::VerificaRadical(int x, int y, char*& expresie)
{
	double rezultat = 0;
	for (int i = x + 1; i < y; i++)
	{
		if (expresie[i] == '#')
		{
			rezultat = operatie.Radical(ParteaStangaOperator(i, expresie), ParteaDreaptaOperator(i, expresie));

			string stringResult = to_string(rezultat);

			int pozResult = 0;
			for (int q = i - 1; q >= 0; q--)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozResult = q + 1;
					break;
				}
			}
			int pozFinalResult = 0;
			for (int q = i + 1; q <= strlen(expresie); q++)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozFinalResult = q - 1;
					break;
				}
			}
			if (pozFinalResult == 0)
			{
				pozFinalResult = strlen(expresie);
			}

			InlocuireRezultat(pozResult, pozFinalResult, expresie, stringResult.c_str());
			i--;
		}

	}
}

void  ProcesareCalcul::VerificaInmultire(int x, int y, char*& expresie)
{
	double rezultat = 0;
	for (int i = x + 1; i < y; i++)
	{
		if (expresie[i] == '*')
		{
			rezultat = operatie.Inmultire(ParteaStangaOperator(i, expresie), ParteaDreaptaOperator(i, expresie));
			
			string stringResult = to_string(rezultat);

			int pozResult = 0;
			for (int q = i - 1; q >= 0; q--)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozResult = q + 1;
					break;
				}
			}
			int pozFinalResult = 0;
			for (int q = i + 1; q <= strlen(expresie); q++)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozFinalResult = q - 1;
					break;
				}
			}
			if (pozFinalResult == 0)
			{
				pozFinalResult = strlen(expresie);
			}

			InlocuireRezultat(pozResult, pozFinalResult, expresie, stringResult.c_str());
			i--;
		}

	}
}

void  ProcesareCalcul::VerificaImpartire(int x, int y, char*& expresie)
{
	double rezultat = 0;
	for (int i = x + 1; i < y; i++)
	{
		if (expresie[i] == '/')
		{
			rezultat = operatie.Impartire(ParteaStangaOperator(i, expresie), ParteaDreaptaOperator(i, expresie));
			
			string stringResult = to_string(rezultat);

			int pozResult = 0;
			for (int q = i - 1; q >= 0; q--)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozResult = q + 1;
					break;
				}
			}
			int pozFinalResult = 0;
			for (int q = i + 1; q <= strlen(expresie); q++)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozFinalResult = q - 1;
					break;
				}
			}
			if (pozFinalResult == 0)
			{
				pozFinalResult = strlen(expresie);
			}

			InlocuireRezultat(pozResult, pozFinalResult, expresie, stringResult.c_str());
			i--;
		}

	}
}

void  ProcesareCalcul::VerificaAdunare(int x, int y, char*& expresie)
{
	double rezultat = 0;
	for (int i = x + 1; i < y; i++)
	{
		if (expresie[i] == '+')
		{
			rezultat = operatie.Plus(ParteaStangaOperator(i, expresie), ParteaDreaptaOperator(i, expresie));

			string stringResult = to_string(rezultat);

			int pozResult = 0;
			for (int q = i - 1; q >= 0; q--)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozResult = q + 1;
					break;
				}
			}
			int pozFinalResult = 0;
			for (int q = i + 1; q <= strlen(expresie); q++)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozFinalResult = q - 1;
					break;
				}
			}
			if (pozFinalResult == 0)
			{
				pozFinalResult = strlen(expresie);
			}

			InlocuireRezultat(pozResult, pozFinalResult, expresie, stringResult.c_str());
			i--;
		}

	}

}

void  ProcesareCalcul::VerificaScadere(int x, int y, char*& expresie)
{
	double rezultat = 0;
	for (int i = x + 1; i < y; i++)
	{
		if (expresie[i] == '-')
		{
			rezultat = operatie.Minus(ParteaStangaOperator(i, expresie), ParteaDreaptaOperator(i, expresie));
			
			string stringResult = to_string(rezultat);

			int pozResult = 0;
			for (int q = i - 1; q >= 0; q--)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozResult = q + 1;
					break;
				}
			}
			int pozFinalResult = 0;
			for (int q = i + 1; q <= strlen(expresie); q++)
			{
				if (strchr("+-*/^#", expresie[q]) != 0)
				{
					pozFinalResult = q - 1;
					break;
				}
			}
			if (pozFinalResult == 0)
			{
				pozFinalResult = strlen(expresie);
			}

			InlocuireRezultat(pozResult, pozFinalResult, expresie, stringResult.c_str());
			i--;
		}

	}
}

void ProcesareCalcul::InlocuireRezultat(int pozResult, int pozFinalResult, char*& expresie, const char* result)
{
	char* sirInceput = new char[pozResult + 1];
	for (int i = 0; i < pozResult; i++)
	{
		sirInceput[i] = expresie[i];
	}
	sirInceput[pozResult] = '\0';

	char* sirFinal = new char[strlen(expresie) - pozFinalResult + 2];
	for (int i = 0; i <= strlen(expresie) - pozFinalResult; i++)
	{
		sirFinal[i] = expresie[pozFinalResult + i + 1];
	}
	sirFinal[strlen(expresie) - pozFinalResult] = '\0';

	delete[] expresie;

	int lungime = strlen(result);
	if (sirInceput != nullptr && strlen(sirInceput))
		lungime += strlen(sirInceput);
	if (sirFinal != nullptr && strlen(sirFinal))
		lungime += strlen(sirFinal);

	expresie = new char[lungime + 1];

	if (sirInceput != nullptr && strlen(sirInceput) > 0)
	{
		strcpy(expresie, sirInceput);

		strcat(expresie, result);

		if (sirFinal != nullptr && strlen(sirFinal) > 0)
			strcat(expresie, sirFinal);

	}
	else
	{
		strcpy(expresie, result);

		if (sirFinal != nullptr && strlen(sirFinal) > 0)
			strcat(expresie, sirFinal);
	}

	expresie[strlen(expresie)] = '\0';

	delete[] sirInceput; delete[] sirFinal;
}







