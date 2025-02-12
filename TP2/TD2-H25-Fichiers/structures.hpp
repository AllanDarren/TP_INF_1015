#pragma once

#include <string>

struct Film; struct Acteur; 

class ListeFilms {
public:
    ListeFilms() = default;

    ~ListeFilms() {
        detruireListeFilms();
    }

    int getNElements() const {
        return nElements;
    }

    Film** getElements() const {
        return elements;
    }

    void ajouterFilm(Film* film);
    void supprimerFilm(Film* film);
    void detruireListeFilms();
    void afficherListeFilms() const;

private:
    int capacite = 0, nElements = 0;
    Film** elements = nullptr;
};

struct ListeActeurs {
    int capacite, nElements;
    Acteur** elements;
};

struct Film {
    std::string titre, realisateur;
    int anneeSortie, recette;
    ListeActeurs acteurs;
};

struct Acteur {
    std::string nom;
    int anneeNaissance;
    char sexe;
    ListeFilms joueDans;
};

void detruireFilm(Film* film); 
void afficherFilm(const Film* film);
