//Nombres premiers
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void exo1(){
    int nombre;
    cout << "Entrer un nombre: ";
    cin >> nombre;
    if (nombre % 2 == 0)
    {
        cout << "Ce nombre n'est pas premier car il est divisible par 2."  << endl;
    }
    else{
        bool estPremier = true;
        for (int i = 3 ; i <= sqrt(nombre) ; i += 2){
            if (nombre % i == 0){
                cout << "Ce nombre n'est pas premier car il est divisible par "; cout <<i << endl;
                estPremier = false;
                break;
            }
        }
        if (estPremier){
            cout << "Ce nombre est premier" << endl;
        }
    }
}

double user_input(double val_min, double val_max){
    double Input = 0;
    cin >> Input;
    while (!((val_min < Input) && (val_max > Input))){
        cout << "la valeur entré est invalide veuillez ressayer: " << endl;
        cin >> Input;
    }

    return Input;

}

void exo2() {
    // taux mensuel 1/12 taux anuelle
    double totalARemboursser = 0;
    double sommeParMois = 0;
    double tauxMensuel = 0;
    double interetTotal = 0;
    double moisPourRembousser = 0;
    int anneePourRembousser = 0;

    cout << "entre le montant prêté" << endl;
    double valMin = 0;
    double valMax = INFINITY;
    totalARemboursser = user_input(valMin, valMax);

    cout << "entre le montant remboursée par mois: " << endl;
    sommeParMois = user_input(valMin, valMax);

    cout << "entre le taut d'intèrêt annuel: " << endl;
    valMin = 0;
    valMax = 100;
    tauxMensuel = (user_input(valMin, valMax) / 12.0) / 100;

    while (totalARemboursser > 0){
        interetTotal += totalARemboursser * tauxMensuel;
        totalARemboursser += totalARemboursser * tauxMensuel;
        totalARemboursser -= sommeParMois;
        moisPourRembousser += 1;
        
    }
    cout << "la somme à été rembourser en " << moisPourRembousser << " mois et le taux intèrêt total est " << interetTotal << endl;
 

}

void exo3() {}

void exo4() {}

void exo5() {}

void exo6() {
    ifstream dictionnaire12("/Users/allankamta/vscode_projects/TP_INF_1015/TP1/dictionnaire.txt");

    if(!dictionnaire12){
        cout << "le fichier ne s'est pas ouvert correctement";
    }


    string ligne;
    vector<string> mots;
    vector<string> natures;
    vector<string> definitions;

    enum dico{
        mot,
        nature,
        definition
    };

    while(getline(dictionnaire12, ligne)){
        string section = "";
        dico TabCounter = mot;
        for (char lettre : ligne){
            if (lettre == '\t' or lettre == '.'){
                switch (TabCounter){
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
            else{
                section += lettre;

            }
        }
    }

        int PosMotLePlusLong = 0;
        for(int i = 1; i < mots.size(); i++){
            if (mots[i].size() > mots[PosMotLePlusLong].size()){
                PosMotLePlusLong = i;
            }


        }

        cout <<mots[PosMotLePlusLong] << "    " << natures[PosMotLePlusLong] << "    " << definitions[PosMotLePlusLong];


    
}



int main() {
    exo1();
    exo2();
    //exo3();
    //exo4();
    //exo5();
    exo6();
}
