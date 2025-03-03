﻿//===================================================================================================================================
//
// Auteurs : Allan Darren Kamta Tenefo (239 1399)
// Antoine Grondin (239 4483)
//
// Dernière date de modification: 11 février 2025
//
// Date de remise : 12 février 2025
//
// description : Travail dirigé 2 Passage de paramètres Allocation dynamique Classes (INF1015 - Programmation orientée objet avancée)
//
//===================================================================================================================================

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
#include <memory>
#include <sstream>

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

ListeFilms::ListeFilms() : capacite(0), nElements(0), elements(nullptr) {}


Film* ListeFilms::operator[](int index) const {
    if (index < 0 || index >= nElements)
        throw std::out_of_range("Index hors limites");
    return elements[index];
}

//TODO: Une fonction pour ajouter un Film à une ListeFilms, le film existant déjà; on veut uniquement ajouter le pointeur vers le film existant.  Cette fonction doit doubler la taille du tableau alloué, avec au minimum un élément, dans le cas où la capacité est insuffisante pour ajouter l'élément.  Il faut alors allouer un nouveau tableau plus grand, copier ce qu'il y avait dans l'ancien, et éliminer l'ancien trop petit.  Cette fonction ne doit copier aucun Film ni Acteur, elle doit copier uniquement des pointeurs.
void ListeFilms::ajouterFilm(Film* film) {
    if (nElements >= capacite) {
        int nouvelleCapacite = max(capacite * 2, 1);
        Film** nouveauxElements = new Film * [nouvelleCapacite];
        for (int i : range(nElements)) {
            nouveauxElements[i] = elements[i];
        }
        delete[] elements;
        elements = nouveauxElements;
        capacite = nouvelleCapacite;
    }
    elements[nElements++] = film;
}

//TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film; la fonction prenant en paramètre un pointeur vers le film à enlever.  L'ordre des films dans la liste n'a pas à être conservé.
void ListeFilms::supprimerFilm(Film* film) {
    for (int i = 0; i < nElements; ++i) {
        if (elements[i] == film) {
            elements[i] = elements[--nElements];
            break;
        }
    }
}

//TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms, qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.  Devrait utiliser span.
shared_ptr<Acteur> ListeFilms::trouverActeur(const string& nom) const {
    span<Film*> films(elements, nElements);
    for (Film* film : films) {
        span<shared_ptr<Acteur>> acteurs(film->acteurs.elements.get(), film->acteurs.nElements);
        for (shared_ptr<Acteur> acteur : acteurs) {
            if (acteur->nom == nom)
                return acteur;
        }
    }
    return nullptr;
}

Film** ListeFilms::data() {
    return elements;
}

int ListeFilms::size() const {
    return nElements;
}
//TODO: Compléter les fonctions pour lire le fichier et créer/allouer une ListeFilms.  La ListeFilms devra être passée entre les fonctions, pour vérifier l'existence d'un Acteur avant de l'allouer à nouveau (cherché par nom en utilisant la fonction ci-dessus).
shared_ptr<Acteur> lireActeur(istream& fichier, ListeFilms* liste) {
    Acteur acteur;
    acteur.nom = lireString(fichier);
    acteur.anneeNaissance = lireUint16(fichier);
    acteur.sexe = lireUint8(fichier);

    shared_ptr<Acteur> existant = liste->trouverActeur(acteur.nom);
    if (existant != nullptr)
        return existant;

    shared_ptr<Acteur> nouvelActeur = make_shared<Acteur>(acteur);
    cout << "Création de l'acteur: " << nouvelActeur->nom << endl;
    return nouvelActeur; //TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations, selon si l'acteur existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées; vous ne devriez pas voir le même nom d'acteur affiché deux fois pour la création.
}


Film* lireFilm(istream& fichier, ListeFilms* liste) {
    string titre = lireString(fichier);
    string realisateur = lireString(fichier);
    int anneeSortie = lireUint16(fichier);
    int recette = lireUint16(fichier);
    int nElements = lireUint8(fichier);
    Film* film = new Film(nElements);
    film->titre = titre;
    film->anneeSortie = anneeSortie;
    film->recette = recette;
    film->acteurs.nElements = nElements;

    for (int i = 0; i < film->acteurs.nElements; ++i) {
        film->acteurs.elements[i] = lireActeur(fichier, liste);//TODO: Placer l'acteur au bon endroit dans les acteurs du film.
        //TODO: Ajouter le film à la liste des films dans lesquels l'acteur joue.
        // film->acteurs.elements[i]->joueDans.ajouterFilm(film);
    }
    return film; //TODO: Retourner le pointeur vers le nouveau film.
}

ListeFilms creerListe(const string& nomFichier) {
    ifstream fichier(nomFichier, ios::binary);
    if (!fichier.is_open()) {
        cerr << "Erreur d'ouverture du fichier." << endl;
        exit(1);
    }
    //TODO: Créer une liste de films vide.
    ListeFilms liste;
    int nElements = lireUint16(fichier);
    for (int i = 0; i < nElements; ++i) {
        Film* film = lireFilm(fichier, &liste); //TODO: Ajouter le film à la liste.
        liste.ajouterFilm(film);
    }
    return liste; //TODO: Retourner la liste de films.
}


//TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film, et les acteurs qui ne jouent plus dans aucun films de la collection).  Noter qu'il faut enleve le film détruit des films dans lesquels jouent les acteurs.  Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.
void detruireFilm(Film* film) {
    cout << "Destruction du film: " << film->titre << endl;
    // for (int i = 0; i < film->acteurs.nElements; ++i) {
    //     Acteur* acteur = film->acteurs.elements[i];
    //     acteur->joueDans.supprimerFilm(film);
    //     if (acteur->joueDans.size() == 0) {
    //         cout << "Destruction de l'acteur: " << acteur->nom << endl;
    //         delete[] acteur->joueDans.data();
    //         delete acteur;
    //     }
    // }
    // delete[] film->acteurs.elements;
    delete film;
}

//TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.
void ListeFilms::detruireListeFilms() {
    for (int i = 0; i < nElements; ++i) {
        detruireFilm(elements[i]);
    }
    delete[] elements;
    elements = nullptr;
    nElements = capacite = 0;
}

void afficherActeur(const Acteur& acteur) {
    cout << "  " << acteur.nom << ", né en " << acteur.anneeNaissance
        << ", sexe: " << acteur.sexe << endl;
}

//TODO: Une fonction pour afficher un film avec tous ces acteurs (en utilisant la fonction afficherActeur ci-dessus).

ostream& operator<<(ostream& os, const Film* film) {
    // TODO: Utiliser des caractères Unicode pour définir la ligne de séparation (différente des autres lignes de séparations dans ce programme).
    os << "\033[35m════════════════════════════════════════\033[0m\n";
    os << "Titre: " << film->titre << endl
        << "Réalisateur: " << film->realisateur << endl
        << "Année: " << film->anneeSortie << "  Recette: " << film->recette << "M$" << endl
        << "Acteurs:" << endl;
    // TODO: Changer le for pour utiliser un span.
    span<shared_ptr<Acteur>> acteurs(film->acteurs.elements.get(), film->acteurs.nElements);
    for (shared_ptr<Acteur> acteur : acteurs) {
        // TODO: Afficher le film.
        afficherActeur(*acteur);
    }
    return os;
}


//TODO: Une fonction pour afficher une ListeFilms.
void ListeFilms::afficher() const {
    span<Film*> films(elements, nElements);
    for (Film* film : films) {
        cout << film;
    }
}

int main() {
    bibliotheque_cours::activerCouleursAnsi();
    static const string ligneSep = "\n\033[35m════════════════════════════════════════\033[0m\n";
    //TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

    //TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
    ListeFilms liste = creerListe("C:\\INF1015\\TP_INF_1015\\TP2\\TD2-H25-Fichiers\\films.bin");

    cout << ligneSep << "Le premier film de la liste est:" << endl;
    //TODO: Afficher le premier film de la liste.  Devrait être Alien.

    if (liste.size() > 0)
        cout << liste[0];

    cout << ligneSep << "Les films sont:" << endl;
    //TODO: Afficher la liste des films.  Il devrait y en avoir 7.
    liste.afficher();

    //TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).  Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
    shared_ptr<Acteur> benedict = liste.trouverActeur("Benedict Cumberbatch");
    if (benedict)
        benedict->anneeNaissance = 1976;

    //cout << ligneSep << "Liste des films où Benedict Cumberbatch joue sont:" << endl;
    //TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
    // afficherFilmographieActeur(liste, "Benedict Cumberbatch");

    //Chapitre 7 - 8: TD3 {
    cout << ligneSep << "TD3 - Chapitre 7 - 8:" << endl;
    Film Skylien = *liste[0];
    Skylien.titre = "Skylien";
    Skylien.acteurs.elements[0] = liste[1]->acteurs.elements[0];
    Skylien.acteurs.elements[0]->nom = "Danie Wroughton Craig";
    Film* ptrSkylien = &Skylien;
    cout << ptrSkylien;
    cout << liste[0];
    cout << liste[1];
    //}

    //Chapitre 10:TD3 {
    cout << ligneSep << "TD3 - Chapitre 10:" << endl;
    Film* filmTrouve = liste.chercherFilm([](const Film* film) {
        return film->recette == 955;
        });
    cout << filmTrouve;
    //}

    //TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
    if (liste.size() > 0) {
        Film* alien = liste[0];
        liste.supprimerFilm(alien);
        detruireFilm(alien);
    }

    cout << ligneSep << "Les films sont maintenant:" << endl;
    //TODO: Afficher la liste des films.
    liste.afficher();
    //TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

    //TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
    liste.detruireListeFilms();
}
