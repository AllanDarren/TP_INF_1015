#pragma once

#include <string>
#include <memory>
#include <functional>
#include <span>
using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.
class ListeFilms {
private:
	int capacite;
	int nElements;
	Film** elements; // Pointeur vers un tableau de Film*
public:
	ListeFilms();

	void ajouterFilm(Film* film);
	void supprimerFilm(Film* film);
	int size() const;
	Film* operator[](int index) const;
	void afficher() const;
	void detruireListeFilms();
	shared_ptr<Acteur> trouverActeur(const std::string& nom) const;
	Film** data();

	Film* chercherFilm(const function<bool(const Film*)>& critere) {
		for (int i = 0; i < nElements; ++i) {
			if (critere(elements[i])) {
				return elements[i];
			}
		}
		return nullptr;
	}
};

struct ListeActeurs {
	int capacite, nElements;
	//Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
	unique_ptr<shared_ptr<Acteur>[]> elements;
public:
	ListeActeurs() : capacite(0), nElements(0), elements(nullptr) {};

	ListeActeurs(int capacite) {
		this->capacite = capacite;
		this->nElements = 0;
		if (capacite > 0) {
			this->elements = make_unique<shared_ptr<Acteur>[]>(capacite);
		}
		else {
			this->elements = nullptr;
		}
	}
	ListeActeurs(const ListeActeurs& autre)
		: capacite(autre.capacite), nElements(autre.nElements) {
		if (autre.capacite > 0) {
			elements = make_unique<shared_ptr<Acteur>[]>(autre.capacite);
			for (int i = 0; i < autre.nElements; ++i) {
				elements[i] = autre.elements[i];
			}
		}
	}
	ListeActeurs& operator=(const ListeActeurs& autre) {
		if (this != &autre) {
			capacite = autre.capacite;
			nElements = autre.nElements;
			if (autre.capacite > 0) {
				elements = make_unique<shared_ptr<Acteur>[]>(autre.capacite);
				for (int i = 0; i < autre.nElements; ++i) {
					elements[i] = autre.elements[i]; // Partage du même Acteur via shared_ptr
				}
			}
			else {
				elements = nullptr;
			}
		}
		return *this;
	}
};

struct Film
{
	std::string titre = "aucun", realisateur = "aucun"; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 0, recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;

	Film() : acteurs(0) {}

	Film(int capaciteActeurs) : acteurs(capaciteActeurs) {}

	Film(const Film& autre) = default;
};

struct Acteur
{
	std::string nom = "aucun"; int anneeNaissance = 0; char sexe = 'N';
	// ListeFilms joueDans;
};
