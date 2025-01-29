/**
* Programme qui d�termine si le nombre lue du clavier est premier.
* \file   exo1.cpp
* \author Grondin et Darren Kamta Tenefo
* \date   29 janvier 2025
* Cr�� le 20 janvier 2025
*/

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void exo1()
{
    int nombre;
    cout << "Entrer un nombre: ";
    cin >> nombre;

    if (nombre % 2 == 0) {
        cout << "Ce nombre n'est pas premier car il est divisible par 2." << endl;
    }
    else {
        bool estPremier = true;
        for (int i = 3; i <= sqrt(nombre); i += 2) {
            if (nombre % i == 0) {
                cout << "Ce nombre n'est pas premier car il est divisible par "; cout << i;
                estPremier = false;
                break;
            }
        }
        if (estPremier) {
            cout << "Ce nombre est premier";
        }
    }
}
int main()
{
    exo1();
}