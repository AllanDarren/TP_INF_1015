//Nombres premiers
#include <iostream>
#include <cmath>
using namespace std;

int exo1(){
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
    return 0;
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

int exo2() {
    // taux mensuel 1/12 taux anuelle
    double TotalARemboursser = 0;
    double SommeParMois = 0;
    double TauxMensuel = 0;
    double InteretTotal = 0;
    double MoisPourRembousser = 0;
    int AnneePourRembousser = 0;

    cout << "entre le montant prêté" << endl;
    double val_min = 0;
    double val_max = INFINITY;
    TotalARemboursser = user_input(val_min, val_max);

    cout << "entre le montant remboursée par mois: " << endl;
    SommeParMois = user_input(val_min, val_max);

    cout << "entre le taut d'intèrêt annuel: " << endl;
    val_min = 0;
    val_max = 100;
    TauxMensuel = (user_input(val_min, val_max) / 12.0) / 100;

    while (TotalARemboursser > 0){
        InteretTotal += TotalARemboursser * TauxMensuel;
        TotalARemboursser += TotalARemboursser * TauxMensuel;
        TotalARemboursser -= SommeParMois;
        MoisPourRembousser += 1;
        
    }
    cout << "la somme à été rembourser en " << MoisPourRembousser << " mois et le taux intèrêt total est " << InteretTotal << endl;
 

}

int exo3() {}

int exo4() {}

int exo5() {}

int exo6() {
    
}



int main() {
    exo1();
    exo2();
    //exo3();
    //exo4();
    //exo5();
    //exo6();
}
