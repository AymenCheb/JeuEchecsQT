#include <string>
#include <iostream>
#include <vector>
#include "Equipe.h"
using namespace std;

// Cette classe garde en m�moire les coordonn�es de ses membres d'�quipe
modele::Equipe::Equipe(const std::string nom, const std::string couleur) {
	nom_ = nom;
	couleur_ = couleur;
};
void modele::Equipe::ajouterMembre(pair<int, int> nouvellesCoordonnees) {

	if (!verifierPresenceMembre(nouvellesCoordonnees)); {
		listeDesCasesMembres_.push_back(nouvellesCoordonnees); // Ajoute le membre � la liste si il n'y est pas d�j�
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
// Cette fonction verifie si une case appartient � l'�quipe
bool modele::Equipe::verifierPresenceMembre(std::pair<int, int> coordonnees) {
	for (int i = 0; i < nMembres_; i++)
	{
		if (listeDesCasesMembres_[i] == coordonnees)
			return true;
	}
	return false;
}