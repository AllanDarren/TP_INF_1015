#include <algorithm>
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
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

double user_input(double val_min, double val_max){
    double Input = 0;
    cin >> Input;
    while (!((val_min < Input) && (val_max > Input))){
        cout << "la valeur entré est invalide veuillez ressayer: " << endl;
        cin >> Input;
    }

    return Input;
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
 
    return 0;
}

int exo3() {
    double hauteurInitiale;
    int nombreRebond;
    double coefficientRebond;

    while (true){
        cout << "Entrer la hauteur initiale de la balle en mètres: " << endl;
        cin >> hauteurInitiale;
        if (hauteurInitiale <= 0) {
            cout << "La hauteur initiale doit être positive" << endl;
        } else {
            break;
        }
    }
    while (true){
        cout << "Entrer le nombre de rebonds de la balle: " << endl;
        cin >> nombreRebond;
        if (nombreRebond <= 0) {
            cout << "Le nombre de rebonds de la balle doit être un entier positif" << endl;
        } else {
            break;
        }
    }
    while (true){
        cout << "Entrer le coefficient de rebonds de la balle: " << endl;
        cin >> coefficientRebond;
        if (coefficientRebond <= 0 || coefficientRebond >= 1) {
            cout << "Le coefficient de rebonds de la balle doit être compris entre 0 et 1" << endl;
        } else {
            break;
        }
    }

    double g = 9.81;
    double vi;
    double vApresRebond;
    double hi = hauteurInitiale;
    double hApresRebond;

    for (int i = 0; i < nombreRebond; i++) {
        vi = sqrt(2 * g * hi);
        vApresRebond = vi * coefficientRebond;
        hApresRebond = (pow(vApresRebond,2))/(2 * g);
    }
    cout << "La hauteur de la balle après "; cout << nombreRebond; cout << " rebonds est de: "; cout << hApresRebond; cout << " mètres" << endl;
    return 0;
}

int exo4() {
    cout << fixed << setprecision(6);
    default_random_engine aleatoire(random_device{}());
    uniform_int_distribution<int> dist(-100, 100);
    int nombreIterations;
    double a = 0;

    cout << "Nombre d'itérations souhaitées: " << endl;
    cin >> nombreIterations;

    for (int i = 0; i < nombreIterations; i++) {
        double nb1 = dist(aleatoire);
        double nb2 = dist(aleatoire);
        double pointCercle = ((nb1/100 * nb1/100) + (nb2/100 * nb2/100));
        if (pointCercle < 1) {
            a += 1;
        }
        }
    double valeurEstime = 4*(a / nombreIterations);
    cout << "La valeur approchée de pi est: " << valeurEstime << endl;

    const double pi = 3.141593;
    double ecartRelatif = ((valeurEstime - pi) / pi)*100;
    cout << "Écart relatif entre la valeur approchée et la valeur précise: " << ecartRelatif << "%" << endl;


    return 0;
}

int exo5() {
    const int nbEntiers = 10;
    int entiers[nbEntiers];
    int entiersClasse[nbEntiers];

    cout << "Veuillez saisir 10 entiers" << endl;
    for (int i = 0; i < nbEntiers; i++) {
        cin >> entiers[i];
    }
    for (int i = 0; i < nbEntiers; i++) {
        entiersClasse[i] = entiers[i];
    }
    partition(begin(entiersClasse), end(entiersClasse),[](int x) {
        return x % 2 == 0;
    });
    for (int i = 0; i < nbEntiers; i++) {
        cout << entiersClasse[i] << " ";
    }
    return 0;
}

//int exo6() {}



int main() {
    //exo1();
    //exo2();
    //exo3();
    //exo4();
    //exo5();
    //exo6();
}

