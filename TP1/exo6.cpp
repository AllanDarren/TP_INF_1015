/**
* Programme traitant les donn�es d'un dictionnaire pris comme entr�e.
* \file   exo6.cpp
* \author Grondin et Darren Kamta Tenefo
* \date   29 janvier 2025
* Cr�� le 20 janvier 2025
*/

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
using namespace std;

void exo6()
{

    ifstream dictionnaire("/Users/allankamta/CLionProjects/Debut_en_C++/TP_INF_1015/TP1/dictionnaire.txt");

    if (!dictionnaire) {
        cout << "le fichier ne s'est pas ouvert correctement";
    }

    string ligne;
    vector<string> mots;
    vector<string> natures;
    vector<string> definitions;

    enum dico {
        mot,
        nature,
        definition
    };
    while (getline(dictionnaire, ligne)) {
        string section;
        dico TabCounter = mot;
        for (char lettre : ligne) {
            if (lettre == '\t' or lettre == '.') {
                switch (TabCounter) {
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
            else {
                section += lettre;

            }
        }
    }
    int posMotLePlusLong = 0;

    for (int i = 1; i < mots.size(); i++) {
        if (mots[i].size() > mots[posMotLePlusLong].size()) {
            posMotLePlusLong = i;
        }
    }
    cout << mots[posMotLePlusLong] << "    " << natures[posMotLePlusLong] << "    " << definitions[posMotLePlusLong];
}

int main()
{
    exo6();
}