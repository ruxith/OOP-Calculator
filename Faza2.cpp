#include <iostream>
#include <string>
#include <fstream>
#include "Calculator.h"
#include "Faza2.h"
using namespace std;

void Faza2::scrieIstoricRezultateInFisier(const string& numeFisier)
{
    fstream fisier(numeFisier, ios::in | ios::out | ios::trunc);

    if (fisier.is_open())
    {

        fisier << "Istoric Rezultate:\n";
 
        string linie; int i = 0;
        for (int i = 0; i < getNumarIstoricRezultate(); i++)
        {
            fisier << "Rezultat " << i + 1 << ": " << getIstoricRezultate(i) << "\n";
        }

        cout << "Istoricul rezultatelor a fost scris in fisierul " << numeFisier << endl;
    }
    else
    {
        cerr << "Eroare la deschiderea fisierului " << numeFisier << endl;
    }
}

void Faza2 :: afiseazaContinutFisier()
{
    string numeFisier;

    cout << "Introduceti numele fisierului: ";
    cin >> numeFisier;

    ifstream fisier(numeFisier);

    if (fisier.is_open())
    {
        cout << "Continutul fisierului " << numeFisier << ":\n";
        string linie;
        while (getline(fisier, linie))
        {
            cout << linie << "\n";
        }
    }
    else
    {
        cerr << "Eroare la deschiderea fisierului " << numeFisier << endl;
    }
}

void Meniu::afiseazaMeniu()
{
    int optiune;
    string numeFisier;
    string aux;

    cout << "\n===== Meniu Calculator =====\n";
    cout << "1. Introduceti expresia pentru calcul\n";
    cout << "2. Scrieti expresia si rezultatele in fisier\n";
    cout << "3. Afisati continutul unui fisier\n";
    cout << "0. Iesire din program sau instructiune\n";
    

    do {
        
        cout << "Alegeti o optiune: ";
        cin >> optiune;

        switch (optiune)
        {
        case 1:
            cin.ignore();
            while (aux != "0")
            {
                getline(cin, aux);

                if (expresie)
                    delete[] expresie;

                expresie = new char[aux.length() + 1];
                strcpy_s(expresie, aux.length() + 1, aux.c_str());

                ProcesareInput();

            }
            
            break;

        case 2:
            cin.ignore();

            cout << "Introduceti numele fisierului pentru salvarea rezultatelor: ";
            getline(cin, numeFisier);
            scrieIstoricRezultateInFisier(numeFisier);
            break;

        case 3:
            cin.ignore();
            afiseazaContinutFisier();
            break; 

        case 0:
            cout << "La revedere!\n";
            break;

        default:
            cout << "Optiune invalida. Va rugam alegeti o optiune valida.\n";
        }
    } while (optiune != 0);
}