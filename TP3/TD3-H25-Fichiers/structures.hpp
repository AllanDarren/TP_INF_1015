#pragma once
// Structures mémoires pour une collection de films.

#include <string>
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
	Acteur* trouverActeur(const std::string& nom) const;
	Film** data();
};

struct ListeActeurs {
	int capacite, nElements;
	//Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
	unique_ptr<Acteur*[]> elements;
public:
	ListeActeurs() : capacite(0), nElements(0), elements(nullptr) {};

	ListeActeurs(int capacite) {
		this -> capacite = capacite;
		this -> nElements = 0;
		if (capacite > 0) {
			this -> elements = make_unique<Acteur*[]>(capacite);
		}
		else {
			this -> elements = nullptr;
		}
	}


};

struct Film
{
	std::string titre = "aucun", realisateur = "aucun"; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 0, recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;


	Film(int capaciteActeurs) : acteurs(capaciteActeurs) {}

};

struct Acteur
{
	std::string nom = "aucun"; int anneeNaissance = 0; char sexe = 'N';
	ListeFilms joueDans;


};
