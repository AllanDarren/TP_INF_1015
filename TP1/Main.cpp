//============================================================================================================================
//
// Auteurs : Allan Darren Kamta Tenefo (239 1399)
// Antoine Grondin (239 4483)
//
// Dernière date de modification: 29 Janvier 2025
//
// Date de remise : 29 Janvier 2025
//
// description : Travail dirigé 1 constitué de 6 exercices (INF1015 - Programmation orientée objet avancée)
//
//============================================================================================================================

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <iomanip>
using namespace std;

void exo1()
{
    int nombre;
    cout << "Entrer un nombre: ";
    cin >> nombre;
    if (nombre % 2 == 0)
    {
        cout << "Ce nombre n'est pas premier car il est divisible par 2." << endl;
    }
    else
    {
        bool estPremier = true;
        for (int i = 3; i <= sqrt(nombre); i += 2)
        {
            if (nombre % i == 0)
            {
                cout << "Ce nombre n'est pas premier car il est divisible par ";
                cout << i;
                estPremier = false;
                break;
            }
        }
        if (estPremier)
        {
            cout << "Ce nombre est premier";
        }
    }
}

double obtenirEntreUtilisateur(double valMin, double valMax)
{
    double entre = 0;
    cin >> entre;
    while (!((valMin < entre) && (valMax > entre)))
    {
        cout << "la valeur entré est invalide veuillez ressayer: " << endl;
        cin >> entre;
    }
    return entre;
}

void exo2()
{
    // taux mensuel 1/12 taux anuelle
    double totalARemboursser = 0;
    double sommeParMois = 0;
    double tauxMensuel = 0;
    double interetTotal = 0;
    double moisPourRembousser = 0;

    cout << "entre le montant prêté" << endl;
    totalARemboursser = obtenirEntreUtilisateur(0, INFINITY);

    cout << "entre le montant remboursée par mois: " << endl;
    sommeParMois = obtenirEntreUtilisateur(0, INFINITY);

    cout << "entre le taut d'intèrêt annuel: " << endl;

    tauxMensuel = (obtenirEntreUtilisateur(0, 100) / 12.0) / 100;

    while (totalARemboursser > 0)
    {
        interetTotal += totalARemboursser * tauxMensuel;
        totalARemboursser += totalARemboursser * tauxMensuel;
        totalARemboursser -= sommeParMois;
        moisPourRembousser += 1;
    }
    cout << "la somme à été rembourser en " << moisPourRembousser << " mois et le taux intèrêt total est " << interetTotal << endl;
}

void exo3()
{
    double hauteurInitiale = 0;
    double nRebond = 0;
    double coefficientRebond = 0;
    const double g = 9.81;
    double vitesseInitiale = 0;
    double vitesseApresRebond = 0;
    double hauteurApresRebond = 0;

    cout << "Entrer la hauteur initiale de la balle en mètres: " << endl;
    hauteurInitiale = obtenirEntreUtilisateur(0, INFINITY);

    cout << "Entrer le nombre de rebonds de la balle: " << endl;
    nRebond = obtenirEntreUtilisateur(0, INFINITY);


    cout << "Entrer le coefficient de rebonds de la balle: " << endl;
    coefficientRebond = obtenirEntreUtilisateur(0, 1);

    for (int i = 0; i < nRebond; i++)
    {
        vitesseInitiale = sqrt(2 * g * hauteurInitiale);
        vitesseApresRebond = vitesseInitiale * coefficientRebond;
        hauteurApresRebond = (pow(vitesseApresRebond, 2)) / (2 * g);
    }
    cout << "La hauteur de la balle après ";
    cout << nRebond;
    cout << " rebonds est de: ";
    cout << hauteurApresRebond;
    cout << " mètres" << endl;
}

void exo4()
{
    cout << fixed << setprecision(6);
    default_random_engine aleatoire(random_device{}());
    uniform_int_distribution<int> dist(-100, 100);
    int nIterations;
    double a = 0;

    cout << "Nombre d'itérations souhaitées: " << endl;
    cin >> nIterations;

    for (int i = 0; i < nIterations; i++)
    {
        double nombre1 = dist(aleatoire);
        double nombre2 = dist(aleatoire);
        double pointCercle = ((nombre1 / 100 * nombre1 / 100) + (nombre2 / 100 * nombre2 / 100));
        if (pointCercle < 1)
        {
            a += 1;
        }
    }
    double valeurEstime = 4 * (a / nIterations);
    cout << "La valeur approchée de pi est: " << valeurEstime << endl;

    constexpr double pi = 3.141593;
    double ecartRelatif = ((valeurEstime - pi) / pi) * 100;
    cout << "Écart relatif entre la valeur approchée et la valeur précise: " << ecartRelatif << "%" << endl;
}

void exo5()
{
    constexpr int nEntiers = 10;
    int entiers[nEntiers];
    int entiersClasses[nEntiers];

    cout << "Veuillez saisir 10 entiers" << endl;
    for (int i = 0; i < nEntiers; i++)
    {
        cin >> entiers[i];
    }
    for (int i = 0; i < nEntiers; i++)
    {
        entiersClasses[i] = entiers[i];
    }
    partition(begin(entiersClasses), end(entiersClasses), [](int x)
              { return x % 2 == 0; });
    for (int i = 0; i < nEntiers; i++)
    {
        cout << entiersClasses[i] << " ";
    }
}

void exo6()
{
    ifstream dictionnaire("dictionnaire.txt");

    if (!dictionnaire)
    {
        cout << "le fichier ne s'est pas ouvert correctement";
    }

    string ligne;
    vector<string> mots;
    vector<string> natures;
    vector<string> definitions;

    enum dico
    {
        mot,
        nature,
        definition
    };

    while (getline(dictionnaire, ligne))
    {
        string section;
        dico TabCounter = mot;
        for (char lettre : ligne)
        {
            if (lettre == '\t' or lettre == '.')
            {
                switch (TabCounter)
                {
                case mot:
                    mots.push_back(section);
                    TabCounter = nature;
                    section = "";
                    break;

                case nature:
                    natures.push_back(section);
                    TabCounter = definition;
                    section = "";
                    break;

                case definition:
                    definitions.push_back(section);
                    TabCounter = mot;
                    section = "";
                    break;
                }
            }
            else
            {
                section += lettre;
            }
        }
    }

    int posMotLePlusLong = 0;
    for (int i = 1; i < mots.size(); i++)
    {
        if (mots[i].size() > mots[posMotLePlusLong].size())
        {
            posMotLePlusLong = i;
        }
    }

    cout << mots[posMotLePlusLong] << "    " << natures[posMotLePlusLong] << "    " << definitions[posMotLePlusLong];
}

int main()
{
    exo1();
    exo2();
    exo3();
    exo4();
    exo5();
    exo6();
}
