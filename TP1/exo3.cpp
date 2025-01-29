/**
* Programme qui selon les donn�s lue du clavier d�termine la hauteur de la balle apr�s le dernier rebond de cette derni�re.
* \file   exo2.cpp
* \author Grondin et Darren Kamta Tenefo
* \date   29 janvier 2025
* Cr�� le 20 janvier 2025
*/

#include <iostream>
#include <cmath>
#include <fstream>
#define CONSTANTE_GRAVITATIONELLE 9.81
using namespace std;

double obtenirEntreUtilisateur(double valMin, double valMax)
{
    double entre = 0;
    cin >> entre;

    while (!((valMin < entre) && (valMax > entre))) {
        cout << "la valeur entr� est invalide veuillez ressayer: " << endl;
        cin >> entre;
    }
    return entre;
}

void exo3()
{
    cout << "Entrer la hauteur initiale de la balle en m�tres: " << endl;
    double hauteurInitiale = obtenirEntreUtilisateur(0, INFINITY);

    cout << "Entrer le nombre de rebonds de la balle: " << endl;
    double nRebond = obtenirEntreUtilisateur(0, INFINITY);

    cout << "Entrer le coefficient de rebonds de la balle: " << endl;
    double coefficientRebond = obtenirEntreUtilisateur(0, 1);

    double vitesseInitiale = 0;
    double vitesseApresRebond = 0;
    double hauteurApresRebond = 0;

    for (int i = 0; i < nRebond; i++) {
        vitesseInitiale = sqrt(2 * CONSTANTE_GRAVITATIONELLE * hauteurInitiale);
        vitesseApresRebond = vitesseInitiale * coefficientRebond;
        hauteurApresRebond = (pow(vitesseApresRebond, 2)) / (2 * CONSTANTE_GRAVITATIONELLE);
    }
    cout << "La hauteur de la balle apr�s "; cout << nRebond; cout << " rebonds est de: "; cout << hauteurApresRebond; cout << " m�tres" << endl;
}

int main()
{
    exo3();
}