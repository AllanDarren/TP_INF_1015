/**
* Programme qui calcule une valeur approch�e de PI selon le nombre d'it�rations le du clavier.
* \file   exo4.cpp
* \author Grondin et Darren Kamta Tenefo
* \date   29 janvier 2025
* Cr�� le 20 janvier 2025
*/

#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
using namespace std;

void exo4()
{
    cout << fixed << setprecision(6);
    default_random_engine aleatoire(random_device{}());
    uniform_int_distribution<int> dist(-100, 100);

    cout << "Nombre d'it�rations souhait�es: " << endl;
    int nIterations;
    cin >> nIterations;

    double a = 0;

    for (int i = 0; i < nIterations; i++) {
        double nombre1 = dist(aleatoire);
        double nombre2 = dist(aleatoire);
        double pointCercle = ((nombre1 / 100 * nombre1 / 100) + (nombre2 / 100 * nombre2 / 100));
        if (pointCercle < 1) {
            a += 1;
        }
    }
    double valeurEstime = 4 * (a / nIterations);
    cout << "La valeur approch�e de pi est: " << valeurEstime << endl;

    constexpr double pi = 3.141593;
    double ecartRelatif = ((valeurEstime - pi) / pi) * 100;
    cout << "�cart relatif entre la valeur approch�e et la valeur pr�cise: " << ecartRelatif << "%" << endl;
}

int main()
{
    exo4();
}