#include <iostream>
#include <string>
#include "Calculator.h"
#include "ProcesareCalcul.h"
#include "Faza2.h"
using namespace std;

int main(int argc, char* argv[])
{

    Meniu meniu;

    Calculator calc;

    string temp;

        cout << "   *************\n";
        cout << "  *   *   *   *   *\n";
        cout << " *                 *\n";
        cout << "*   O         O     *\n";
        cout << "*    *       *      *\n";
        cout << "*        ||         *\n";
        cout << " *     \____/      *\n";
        cout << "  *     *****     *\n";
        cout << "    *************\n";
        cout << "   _________\n";
        cout << "  | 7 | 8 | 9 | + |\n";
        cout << "  |---|---|---|---|\n";
        cout << "  | 4 | 5 | 6 | - |\n";
        cout << "  |---|---|---|---|\n";
        cout << "  | 1 | 2 | 3 | * |\n";
        cout << "  |---|---|---|---|\n";
        cout << "  | 0 | . | = | / |\n";
        cout << "   -----------\n";

        cout << "Scrie 'help' pentru a accesa meniul sau introdu exprresia matematica:";

    if (argc > 1)
    {
        

        for (int i = 1; i < argc; ++i)
        {
            temp += argv[i];
        }
        //cout << temp << endl;

        for (char& ch : temp) {
            ch = tolower(ch);
        }
      
        calc.setExpresie(temp.c_str());
        
    }
    
    cin >> calc;
    

    return 0;
}