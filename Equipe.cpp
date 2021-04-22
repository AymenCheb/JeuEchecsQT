#include <string>
#include <iostream>
#include <vector>
#include "Equipe.h"
using namespace std;

// Cette classe garde en mémoire les coordonnées de ses membres d'équipe
modele::Equipe::Equipe(const std::string nom, const std::string couleur) {
	nom_ = nom;
	couleur_ = couleur;
};
void modele::Equipe::ajouterMembre(pair<int, int> nouvellesCoordonnees) {

	if (!verifierPresenceMembre(nouvellesCoordonnees)); {
		listeDesCasesMembres_.push_back(nouvellesCoordonnees); // Ajoute le membre à la liste si il n'y est pas déjà
		nMembres_++;
	}
};
void modele::Equipe::retirerMembre(const std::pair<int, int> coordonneesMembre) {
	for (int i = 0; i < nMembres_; i++)
	{
		if (listeDesCasesMembres_[i] == coordonneesMembre) {
			listeDesCasesMembres_.erase(listeDesCasesMembres_.begin() + i); // Supprime le membre de la liste
			nMembres_--;
		}
	}
};
// Cette fonction verifie si une case appartient à l'équipe
bool modele::Equipe::verifierPresenceMembre(std::pair<int, int> coordonnees) {
	for (int i = 0; i < nMembres_; i++)
	{
		if (listeDesCasesMembres_[i] == coordonnees)
			return true;
	}
	return false;
}