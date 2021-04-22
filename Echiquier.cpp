#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Piece.h"
#include "Equipe.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Echiquier.h"
using namespace std;


//Constructeur de l'echiquier

modele::Echiquier::Echiquier(Equipe equipe1, Equipe equipe2) {
	// Quand on crée l'échiquier, on veut que les cases soient vides initialement 
	equipes_[0] = equipe1;
	equipes_[1] = equipe2;
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'échiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'échiquier
		{
			tableau_[i][j] = make_shared<piece>(); // Instantiation d'une case vide aux bonnes coordonnees
		}
	}
}

// Cette fonction retourne un int pour indiquer à quelle équipe appartient une piece 
int modele::Echiquier::determinerEquipe(std::pair<int, int> coordonnees) {
	if (equipes_[0].verifierPresenceMembre(coordonnees))
		return 0;
	if (equipes_[1].verifierPresenceMembre(coordonnees))
		return 1;
	else return 2;
};
// Cette fonction attribu correctement une equipe a une case en fonction de sa couleur
void modele::Echiquier::attribuerEquipe(std::pair<int, int> coordonnes) {
	using namespace modele;
	string couleurPiece = tableau_[coordonnes.first][coordonnes.second].get()->couleur_;
	if (couleurPiece == equipes_[0].couleur_)
		equipes_[0].ajouterMembre(coordonnes);
	else if (couleurPiece == equipes_[1].couleur_)
		equipes_[1].ajouterMembre(coordonnes);
	else cout << "La case n'a pas la meme couleur d'une des equipes" << endl;
}
bool modele::Echiquier::verifierEchec(pair<int, int> positionRoi) {
	using namespace modele;
	// Ajouter des tests pour vérifier que l'on passe bien un roi 
	int indexEquipe = determinerEquipe(positionRoi);
	// Ce switch s'occupe de retirer la case de l'équipe qui lui correspond
	switch (indexEquipe)
	{
	case 0:
		for (int i = 0; i < equipes_[1].nMembres_; i++)
		{
			if (validerMouvement(equipes_[1].listeDesCasesMembres_[i], positionRoi))
				return true;
		}
		break;
	case 1:
		for (int i = 0; i < equipes_[0].nMembres_; i++)
		{
			if (validerMouvement(equipes_[0].listeDesCasesMembres_[i], positionRoi))
				return true;
		}
		break;
	case 2: // Si la piece n'est dans aucune equipe, on peut juste passer
		break;
	}
	return false;
}



//Cette methode permet de vider une case, en y inserant une Piece ( directement de la classe Piece, cette Piece n'est ni une tour, ni un fou etc..)
void modele::Echiquier::viderCase(const std::pair<int, int> coordonnees) {
	int indexEquipe = determinerEquipe(coordonnees);
	// Ce switch s'occupe de retirer la case de l'équipe qui lui correspond
	switch (indexEquipe)
	{
	case 0:
	case 1:
		equipes_[indexEquipe].retirerMembre(coordonnees);
		break;
	case 2: // Si la piece n'est dans aucune equipe, on peut juste passer
		break;
	}
	memoriserPiece(tableau_[coordonnees.first][coordonnees.second]); // Pour vider une case, on place une nouvelle piece X dans le tableau à son endroit
	tableau_[coordonnees.first][coordonnees.second] = make_shared<piece>();
}
//Methode pour afficher l'echiquier dans le terminal
void modele::Echiquier::afficherEchiquier() {
	for (int i = 0; i < 8; i++) // Parcours les lignes de l'échiquier
	{
		for (int j = 0; j < 8; j++) // Parcours les colonnes de l'échiquier
		{
			tableau_[i][j].get()->afficher(); // Affiche la case
		}
		cout << '\n'; // 
	}
}
void modele::Echiquier::afficherMembresEquipe(string nom) {
	if (equipes_[0].nom_ == nom)
	{
		for (int i = 0; i < equipes_[0].nMembres_; i++) {
			pair<int, int> coordonneesMembre = equipes_[0].listeDesCasesMembres_[i];
			afficherInfosCase(coordonneesMembre);
		}
	}
}
bool modele::Echiquier::validerMouvement(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	// Demande à la pièce de vérifier si le mouvement demander est possible
	bool mouvementPossible = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->demanderMouvement(coordonneesInitiales, coordonneesDestination);
	if (mouvementPossible)
	{
		// Si le mouvement est possible, on élabore le chemin à suivre en fonction de la pièce
		std::vector<std::pair<int, int>> chemin = tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->trouverChemin(coordonneesInitiales, coordonneesDestination);
		// On vérifie que le mouvement ne brise aucune règle de jeu
		bool mouvementLegal = verifierLegaliteMouvement(chemin, coordonneesDestination, tableau_[coordonneesInitiales.first][coordonneesInitiales.second].get()->couleur_);
		return mouvementLegal;
	}
	return false;
}


// Methode permettant de deplacer une piece, on donne en parametres les coordonnees initiales de la piece ainsi que les coordonnees de destination
void modele::Echiquier::deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination) {
	mediateur_->retablirCase();
	retirerContour(coordonneesInitiales);
	// On mémorise les pointeurs des pieces aux cases de départ et de destination
	afficherInfosCase(coordonneesDestination);
	
	// Dans un premier temps, on vérifie que la pièce a le droit d'effectuer ce mouvement
	if (validerMouvement(coordonneesInitiales, coordonneesDestination)) {
		// Si le mouvement est légal, on modifie la case de destination et on vide la case de départ
		modeMemorisation = true;
		modifierCase(coordonneesDestination, &tableau_[coordonneesInitiales.first][coordonneesInitiales.second]);
		viderCase(coordonneesInitiales);
		modeMemorisation = false;
		 /*Dans un deuxième temps, on vérifie si ce déplacement a mis le roi de la pièce en échec*/
		if (verifierEchec(trouverPiece("R", historiquePiecesDeplacees[1].get()->couleur_)))
		{
			// Si oui, on annule le déplacement
			modifierCase(coordonneesInitiales, &historiquePiecesDeplacees[1]);
			modifierCase(coordonneesDestination, &historiquePiecesDeplacees[0]);
			mediateur_->changerCouleurCase(coordonneesDestination);
			cout << "Ce mouvement mettrait le roi de la " << historiquePiecesDeplacees[0].get()->nature_ << " en echec! " << endl;
		}
		else
		{
			miseAjourGraphique(coordonneesInitiales);
			miseAjourGraphique(coordonneesDestination);
		}
	}
	else {
		mediateur_->changerCouleurCase(coordonneesDestination);
		
		
		cout << "Mouvement impossible " << endl;
	}
}

/*Methode permettant de verifier la legallite d'un mouvement : ce n'est pas cette methode qui verifie les regles de deplacement specifiques a chaque pieces,
cette methode verifie plutot des regles plus generales, comme par exemple si une piece alliee se trouve sur la case sur laquelle on souhaite se deplacer etc*/
bool modele::Echiquier::verifierLegaliteMouvement(const std::vector<std::pair<int, int>> chemin, const std::pair<int, int> destination, string couleurPiece) {
	int etapeChemin = 0;
	pair<int, int> prochaineCase = chemin[etapeChemin];
	do
	{
		// Cette boucle Do While s'assure de la legalite du chemin en testant divers règles:
		prochaineCase = chemin[etapeChemin];
		// Note: On cherche la prochaine case au début de la boucle pour pouvoir effectuer des tests sur la case finale si besoin est
		// Si il y a une piece sur le chemin, autre que la case finale, le mouvement est illegal
		if (tableau_[prochaineCase.first][prochaineCase.second].get()->nature_ != "X" and prochaineCase != destination) {
			cout << "Il y a une piece sur le chemin voulu autre que sur la case finale: Mouvement illegal!" << endl;
			return false;
		}
		else if (prochaineCase == destination and tableau_[prochaineCase.first][prochaineCase.second].get()->couleur_ == couleurPiece) {
			cout << "La destiantion contient une piece de la meme couleur: Mouvement illegal!" << endl;
			return false;
		}
		etapeChemin++;
	} while (prochaineCase != destination); // Tant que la destination finale n'a pas été atteinte, on continue de suivre le chemin
	return true; // Si aucun des tests n'a échoué, le mouvement est jugé légal 
}

//Methode qui permet d'afficher les informations d'une case precise, on passe en parametre les coordonnees de la case
void modele::Echiquier::afficherInfosCase(pair<int, int> coordonnees) {
	cout << "La case aux coordonnees: " << coordonnees.first << ',' << coordonnees.second << endl;
	cout << "Est une " << tableau_[coordonnees.first][coordonnees.second].get()->nature_;

	cout << " de couleur " << tableau_[coordonnees.first][coordonnees.second].get()->couleur_ << endl;
}//]

pair<int, int> modele::Echiquier::trouverPiece(std::string nature, std::string couleur) {

	// Maybe use method pattern instead
	if (couleur == "Noir") {
		for (int i = 0; i < equipes_[0].nMembres_; i++)
		{
			pair<int, int> membre = equipes_[0].listeDesCasesMembres_[i];
			if (tableau_[membre.first][membre.second].get()->nature_ == nature)
			{
				return membre;
			}
		}
	}
	else if(couleur == "Blanc") {
		for (int i = 0; i < equipes_[1].nMembres_; i++)
		{
			pair<int, int> membre = equipes_[1].listeDesCasesMembres_[i];
			if (tableau_[membre.first][membre.second].get()->nature_ == nature)
			{
				return membre;
			}
		}
	}
	// Ajouter une exception pour le cas où aucun if n'est satisfait
}

// Fonction pour mémoriser une pièce 
void modele::Echiquier::memoriserPiece(shared_ptr<piece>& pieceDeplacee) {
	// Si on est dans le mode mémorisation et que la mémoire n'est pas pleine, on mémorise la pièce
	if (nPiecesMemorisees <= 1 and modeMemorisation)
	{
		historiquePiecesDeplacees[nPiecesMemorisees].swap(pieceDeplacee);
		nPiecesMemorisees++;
	}
	// Si on est dans le mode mémorisation et que la mémoire est pleine, on réinitialise l'index de mémoire, puis enregistre
	else if (modeMemorisation and nPiecesMemorisees > 1)
	{
		nPiecesMemorisees = 0;
		historiquePiecesDeplacees[nPiecesMemorisees].swap(pieceDeplacee);
		nPiecesMemorisees++;
	}
}
// Fonction faisant appel au médiateur ModeleVue pour mettre à jour l'interface graphique
void modele::Echiquier::miseAjourGraphique(pair<int, int> coordonnesCase) {
	mediateur_->notifierWindow(coordonnesCase, tableau_[coordonnesCase.first][coordonnesCase.second].get()->nature_,
		tableau_[coordonnesCase.first][coordonnesCase.second].get()->couleur_);
};

void modele::Echiquier::contour(pair<int, int> coordonneesInitiales) {
	mediateur_->colorerContour(coordonneesInitiales);
}

void modele::Echiquier::retirerContour(pair<int, int> coordonnees) {
	mediateur_->retirerContour(coordonnees);
}