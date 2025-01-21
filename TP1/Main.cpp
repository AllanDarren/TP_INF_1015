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
                cout << "Ce nombre n'est pas premier car il est divisible par "; cout <<i;
                estPremier = false;
                break;
            }
        }
        if (estPremier){
            cout << "Ce nombre est premier";
        }
    }
    return 0;
}
int exo2() {}

int exo3() {}

int exo4() {}

int exo5() {}

int exo6() {}



int main() {
    exo1();
    //exo2();
    //exo3();
    //exo4();
    //exo5();
    //exo6();
}

