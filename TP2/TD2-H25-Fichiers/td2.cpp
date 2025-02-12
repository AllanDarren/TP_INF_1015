#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

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

void ListeFilms::ajouterFilm(Film* film) {
    if (nElements >= capacite) {
        int nouvelleCapacite = max(capacite * 2, 1);
        Film** nouveauxElements = new Film * [nouvelleCapacite];
        for (int i = 0; i < nElements; ++i) {
            nouveauxElements[i] = elements[i];
        }
        delete[] elements;
        elements = nouveauxElements;
        capacite = nouvelleCapacite;
    }
    elements[nElements++] = film;
}

void ListeFilms::supprimerFilm(Film* film) {
    for (int i = 0; i < nElements; ++i) {
        if (elements[i] == film) {
            elements[i] = elements[--nElements];
            break;
        }
    }
}

void ListeFilms::detruireListeFilms() {
    for (int i = 0; i < nElements; ++i) {
        detruireFilm(elements[i]);
    }
    delete[] elements;
    elements = nullptr;
    nElements = capacite = 0;
}

void ListeFilms::afficherListeFilms() const {
    for (int i = 0; i < nElements; ++i) {
        afficherFilm(elements[i]);
    }
}

Acteur* trouverActeur(const ListeFilms* liste, const string& nom) {
    span<Film*> films(liste->getElements(), liste->getNElements());
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
    nouvelActeur->joueDans = { 0, 0, nullptr };
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
    film->acteurs.elements = new Acteur * [film->acteurs.nElements];

    for (int i = 0; i < film->acteurs.nElements; ++i) {
        film->acteurs.elements[i] = lireActeur(fichier, liste);
        ListeFilms::ajouterFilm(film);
    }
    return film;
}

ListeFilms creerListe(const string& nomFichier) {
    ifstream fichier(nomFichier, ios::binary);
    if (!fichier.is_open()) {
        cerr << "Erreur d'ouverture du fichier." << endl;
        exit(1);
    }

    ListeFilms liste;
    int nElements = lireUint16(fichier);
    for (int i = 0; i < nElements; ++i) {
        Film* film = lireFilm(fichier, &liste);
        ListeFilms::ajouterFilm(film);
    }
    return liste;
}

void detruireFilm(Film* film) {
    cout << "Destruction du film: " << film->titre << endl;
    for (int i = 0; i < film->acteurs.nElements; ++i) {
        Acteur* acteur = film->acteurs.elements[i];
        ListeFilms::supprimerFilm(film);
        if (acteur->joueDans.getNElements() == 0) {
            cout << "Destruction de l'acteur: " << acteur->nom << endl;
            delete[] acteur->joueDans.getElements(); // Désallouer le tableau de films
            delete acteur;
        }
    }
    delete[] film->acteurs.elements;
    delete film;
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

//TODO: Une fonction pour afficher une ListeFilms.
void ListeFilms::afficherListeFilms() {
    span<Film*> films(elements, nElements);
    for (Film* film : films) {
        afficherFilm(film);
    }
}

//TODO: Une fonction pour afficher la filmographie d'un acteur.
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

    //TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.
    ListeFilms liste = creerListe("/Users/allankamta/CLionProjects/Debut_en_C++/TP_INF_1015/TP2/TD2-H25-Fichiers/films.bin");

    //TODO: Afficher le premier film de la liste.
    cout << ligneSep << "Premier film:\n";
    if (liste.getNElements() > 0)
        afficherFilm();

    //TODO: Afficher tous les films.
    cout << ligneSep << "Tous les films:\n";
    ListeFilms::afficherListeFilms();

    //TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976.
    Acteur* benedict = trouverActeur(&liste, "Benedict Cumberbatch");
    if (benedict)
        benedict->anneeNaissance = 1976;

    //TODO: Afficher la liste des films où Benedict Cumberbatch joue.
    cout << ligneSep << "Filmographie de Benedict Cumberbatch:\n";
    afficherFilmographieActeur(liste, "Benedict Cumberbatch");

    //TODO: Détruire et enlever le premier film de la liste (Alien).
    if (liste.getNElements > 0) {
        Film* alien = liste.getElements(0);
        ListeFilms::supprimerFilm(alien);
        detruireFilm(alien);
    }

    //TODO: Afficher les films restants.
    cout << ligneSep << "Films restants:\n";
    ListeFilms::afficherListeFilms(liste);

    //TODO: Détruire tout avant de terminer le programme.
    ListeFilms::detruireListeFilms(&liste);
}
