/**
* Programme qui simule a partir des entr�es lue du clavir un emprunt.
* \file   exo2.cpp
* \author Grondin et Darren Kamta Tenefo
* \date   29 janvier 2025
* Cr�� le 20 janvier 2025
*/

#include <iostream>
#include <cmath>
#include <fstream>
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

void exo2()
{
    // taux mensuel 1/12 taux anuelle
    cout << "entre le montant pr�t�" << endl;
    double totalARemboursser = obtenirEntreUtilisateur(0, INFINITY);

    cout << "entre le montant rembours�e par mois: " << endl;
    double sommeParMois = obtenirEntreUtilisateur(0, INFINITY);

    cout << "entre le taut d'int�r�t annuel: " << endl;
    double tauxMensuel = (obtenirEntreUtilisateur(0, 100) / 12.0) / 100;

    double interetTotal = 0;
    double moisPourRembousser = 0;

    while (totalARemboursser > 0) {
        interetTotal += totalARemboursser * tauxMensuel;
        totalARemboursser += totalARemboursser * tauxMensuel;
        totalARemboursser -= sommeParMois;
        moisPourRembousser += 1;

    }
    cout << "la somme � �t� rembourser en " << moisPourRembousser << " mois et le taux int�r�t total est " << interetTotal << endl;
}

int main()
{
    exo2();
}