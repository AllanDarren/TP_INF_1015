#pragma region "Includes"
#define _CRT_SECURE_NO_WARNINGS

#include "structures.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <span>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"

using namespace std;
using namespace iter;

#pragma endregion

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"

UInt8 lireUint8(istream& fichier) {
    UInt8 valeur;
    fichier.read((char*)&valeur, sizeof(valeur));
    return valeur;
}

UInt16 lireUint16(istream& fichier) {
    UInt16 valeur;
    fichier.read((char*)&valeur, sizeof(valeur));
    return valeur;
}

string lireString(istream& fichier) {
    UInt16 taille = lireUint16(fichier);
    string texte;
    texte.resize(taille);
    fichier.read((char*)texte.data(), taille * sizeof(char));
    return texte;
}

#pragma endregion

void ajouterFilm(ListeFilms* liste, Film* film) {
    if (liste->nElements >= liste->capacite) {
        int nouvelleCapacite = max(liste->capacite * 2, 1);
        Film** nouveauxElements = new Film*[nouvelleCapacite];
        for (int i = 0; i < liste->nElements; ++i) {
            nouveauxElements[i] = liste->elements[i];
        }
        delete[] liste->elements;
        liste->elements = nouveauxElements;
        liste->capacite = nouvelleCapacite;
    }
    liste->elements[liste->nElements++] = film;
}

void supprimerFilm(ListeFilms* liste, Film* film) {
    for (int i = 0; i < liste->nElements; ++i) {
        if (liste->elements[i] == film) {
            liste->elements[i] = liste->elements[--liste->nElements];
            break;
        }
    }
}

Acteur* trouverActeur(const ListeFilms* liste, const string& nom) {
    span<Film*> films(liste->elements, liste->nElements);
    for (Film* film : films) {
        span<Acteur*> acteurs(film->acteurs.elements, film->acteurs.nElements);
        for (Acteur* acteur : acteurs) {
            if (acteur->nom == nom)
                return acteur;
        }
    }
    return nullptr;
}

Acteur* lireActeur(istream& fichier, ListeFilms* liste) {
    Acteur acteur;
    acteur.nom = lireString(fichier);
    acteur.anneeNaissance = lireUint16(fichier);
    acteur.sexe = lireUint8(fichier);

    Acteur* existant = trouverActeur(liste, acteur.nom);
    if (existant != nullptr)
        return existant;

    Acteur* nouvelActeur = new Acteur(acteur);
    nouvelActeur->joueDans = {0, 0, nullptr};
    cout << "Création de l'acteur: " << nouvelActeur->nom << endl;
    return nouvelActeur;
}

Film* lireFilm(istream& fichier, ListeFilms* liste) {
    Film* film = new Film;
    film->titre = lireString(fichier);
    film->realisateur = lireString(fichier);
    film->anneeSortie = lireUint16(fichier);
    film->recette = lireUint16(fichier);
    film->acteurs.nElements = lireUint8(fichier);
    film->acteurs.elements = new Acteur*[film->acteurs.nElements];

    for (int i = 0; i < film->acteurs.nElements; ++i) {
        film->acteurs.elements[i] = lireActeur(fichier, liste);
        ajouterFilm(&film->acteurs.elements[i]->joueDans, film);
    }
    return film;
}

ListeFilms creerListe(const string& nomFichier) {
    ifstream fichier(nomFichier, ios::binary);
    if (!fichier.is_open()) {
        cerr << "Erreur d'ouverture du fichier." << endl;
        exit(1);
    }

    ListeFilms liste = {0, 0, nullptr};
    int nElements = lireUint16(fichier);
    for (int i = 0; i < nElements; ++i) {
        Film* film = lireFilm(fichier, &liste);
        ajouterFilm(&liste, film);
    }
    return liste;
}

void detruireFilm(Film* film) {
    cout << "Destruction du film: " << film->titre << endl;
    for (int i = 0; i < film->acteurs.nElements; ++i) {
        Acteur* acteur = film->acteurs.elements[i];
        supprimerFilm(&acteur->joueDans, film);
        if (acteur->joueDans.nElements == 0) {
            cout << "Destruction de l'acteur: " << acteur->nom << endl;
            // Ajouter la désallocation du tableau de films
            delete[] acteur->joueDans.elements;
            delete acteur;
        }
    }
    delete[] film->acteurs.elements;
    delete film;
}
void detruireListeFilms(ListeFilms* liste) {
    for (int i = 0; i < liste->nElements; ++i) {
        detruireFilm(liste->elements[i]);
    }
    delete[] liste->elements;
    liste->elements = nullptr;
    liste->nElements = liste->capacite = 0;
}

void afficherActeur(const Acteur& acteur) {
    cout << "  " << acteur.nom << ", né en " << acteur.anneeNaissance
         << ", sexe: " << acteur.sexe << endl;
}

void afficherFilm(const Film* film) {
    static const string ligneSep = "\033[35m════════════════════════════════════════\033[0m\n";
    cout << ligneSep << "Titre: " << film->titre << endl
         << "Réalisateur: " << film->realisateur << endl
         << "Année: " << film->anneeSortie << "  Recette: "
         << film->recette << "M$" << endl << "Acteurs:\n";
    for (int i = 0; i < film->acteurs.nElements; ++i) {
        afficherActeur(*film->acteurs.elements[i]);
    }
    cout << ligneSep;
}

void afficherListeFilms(const ListeFilms& liste) {
    span<Film*> films(liste.elements, liste.nElements);
    for (Film* film : films) {
        afficherFilm(film);
    }
}

void afficherFilmographieActeur(const ListeFilms& liste, const string& nom) {
    const Acteur* acteur = trouverActeur(&liste, nom);
    if (!acteur) {
        cout << "Acteur non trouvé." << endl;
        return;
    }
    cout << "Films de " << nom << ":\n";
    afficherListeFilms(acteur->joueDans);
}

int main() {
    bibliotheque_cours::activerCouleursAnsi();
    static const string ligneSep = "\n\033[35m════════════════════════════════════════\033[0m\n";

    ListeFilms liste = creerListe("/Users/allankamta/CLionProjects/Debut_en_C++/TP_INF_1015/TP2/TD2-H25-Fichiers/films.bin");

    // Afficher premier film
    cout << ligneSep << "Premier film:\n";
    if (liste.nElements > 0)
        afficherFilm(liste.elements[0]);

    // Afficher tous les films
    cout << ligneSep << "Tous les films:\n";
    afficherListeFilms(liste);

    // Modifier Benedict Cumberbatch
    Acteur* benedict = trouverActeur(&liste, "Benedict Cumberbatch");
    if (benedict)
        benedict->anneeNaissance = 1976;

    // Filmographie de Benedict
    cout << ligneSep << "Filmographie de Benedict Cumberbatch:\n";
    afficherFilmographieActeur(liste, "Benedict Cumberbatch");

    // Supprimer Alien
    if (liste.nElements > 0) {
        Film* alien = liste.elements[0];
        supprimerFilm(&liste, alien);
        detruireFilm(alien);
    }

    // Afficher films restants
    cout << ligneSep << "Films restants:\n";
    afficherListeFilms(liste);

    detruireListeFilms(&liste);
}