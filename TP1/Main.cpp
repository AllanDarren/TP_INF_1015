#include <iostream>
#include <cmath>
#include <random>
using namespace std;

//Nombres premiers
int exo1() {
    int nombre;
    cout << "Entrer un nombre: ";
    cin >> nombre;
    if (nombre % 2 == 0) {
        cout << "Ce nombre n'est pas premier car il est divisible par 2."  << endl;
    }
    else {
        bool estPremier = true;
        for (int i = 3 ; i <= sqrt(nombre) ; i += 2) {
            if (nombre % i == 0){
                cout << "Ce nombre n'est pas premier car il est divisible par "; cout <<i;
                estPremier = false;
                break;
            }
        }
        if (estPremier) {
            cout << "Ce nombre est premier";
        }
    }
    return 0;
}
//int exo2() {}

int exo3() {
    double hauteurInitiale;
    int nombreRebond;
    double coefficientRebond;

    while (true) {
        cout << "Entrer la hauteur initiale de la balle en mètres: " << endl;
        cin >> hauteurInitiale;
        if (hauteurInitiale <= 0) {
            cout << "La hauteur initiale doit être positive" << endl;
        }
        else {
            break;
        }
    }
    while (true) {
        cout << "Entrer le nombre de rebonds de la balle: " << endl;
        cin >> nombreRebond;
        if (nombreRebond <= 0) {
            cout << "Le nombre de rebonds de la balle doit être un entier positif" << endl;
        }
        else {
            break;
        }
    }
    while (true) {
        cout << "Entrer le coefficient de rebonds de la balle: " << endl;
        cin >> coefficientRebond;
        if (coefficientRebond <= 0 || coefficientRebond >= 1) {
            cout << "Le coefficient de rebonds de la balle doit être compris entre 0 et 1" << endl;
        }
        else {
            break;
        }
    }

    double g = 9.81;
    double vi;
    double v1;
    double hi = hauteurInitiale;
    double h1;

    for (int i = 0; i < nombreRebond; i++) {
        vi = sqrt(2 * g * hi);
        v1 = vi * coefficientRebond;
        h1 = (pow(v1,2))/(2 * g);
    }
    cout << "La hauteur de la balle après "; cout << nombreRebond; cout << " rebonds est de: "; cout << h1; cout << " mètres" << endl;
    return 0;
}

int exo4() {
    default_random_engine aleatoire(random_device{}());
    uniform_int_distribution<int> dist(-100, 100);
    int nombreIterations;
    double a = 0;
    double b = 0;

    cout << "Nombre d'itérations souhaitées: " << endl;
    cin >> nombreIterations;

    for (int i = 0; i < nombreIterations; i++) {
        double nb1 = dist(aleatoire);
        double nb2 = dist(aleatoire);
        double pointCercle = pow(nb1/100,2) + pow(nb2/100,2);
        if (pointCercle < 1) {
            a += 1;
        }
        else {
            b += 1;
        }
    }
    double valeurEstime = (a / b);
    cout << valeurEstime;


    return 0;
}

int exo5() {

}

//int exo6() {}



int main() {
    //exo1();
    //exo2();
    //exo3();
    exo4();
    //exo5();
    //exo6();
}

