#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <memory>
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
	unique_ptr<Acteur*[]> elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.

	ListeActeurs(int nElements) :
		elements(make_unique<Acteur* []>(nElements)) {}
};

struct Film
{
	std::string titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;

	Film(string titre, string realisateur, int anneeSortie, int recette, int nActeurs)
		: titre(titre), realisateur(realisateur), anneeSortie(anneeSortie), recette(recette), acteurs(nActeurs) {
	}
};

struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};
