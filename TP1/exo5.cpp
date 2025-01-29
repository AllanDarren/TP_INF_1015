/**
* Programme qui renvoie le tableau de 10 entiers lue du clavier avec les nombres pair avant les nombres impairs.
* \file   exo5.cpp
* \author Grondin et Darren Kamta Tenefo
* \date   29 janvier 2025
* Cr�� le 20 janvier 2025
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void exo5()
{
    constexpr int nEntiers = 10;

    int entiers[nEntiers];
    cout << "Veuillez saisir 10 entiers" << endl;

    for (int i = 0; i < nEntiers; i++) {
        cin >> entiers[i];
    }
    int entiersClasses[nEntiers];

    for (int i = 0; i < nEntiers; i++) {
        entiersClasses[i] = entiers[i];
    }
    partition(begin(entiersClasses), end(entiersClasses), [](int x) {
        return x % 2 == 0;
        });

    for (int i = 0; i < nEntiers; i++) {
        cout << entiersClasses[i] << " ";
    }
}

int main()
{
    exo5();
}