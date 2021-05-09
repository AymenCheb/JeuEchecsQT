#pragma once
#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Equipe.h"
#include "interfaceMediateurQT.h"

using namespace std;
namespace modele{
	class Echiquier {
	private:
		std::shared_ptr<piece> historiquePiecesDeplacees[2];
		int nPiecesMemorisees = 0;
		bool modeMemorisation = false;
		MediateurQT* mediateur_;
		std::shared_ptr<piece> tableau_[8][8]; // Géneration d'un échiquier de 8x8 
		Equipe equipes_[2];
		bool affichable_ = true;
	public:
		Echiquier(Equipe equipe1 = Equipe("Equipe noire", "Noir"), Equipe equipe2 = Equipe("Equipe blanche", "Blanc"));
		// Vu que cette fonction utilise un template, il est nécessaire qu'elle soit implémentée dans le hpp ou le main directement
		template <class TypePiece>
		void modifierCase(const std::pair<int, int> coordonnees, const std::shared_ptr<TypePiece>* remplacement) {
			// On vide la case par précaution pour éviter des oublis au niveau de la gestion d'équipes
			viderCase(coordonnees);
			// L'usage du template TypePiece permet d'éviter l'object slicing 
			tableau_[coordonnees.first][coordonnees.second] = *remplacement;
			// On réattribue une équipe à la pièce en fonction de sa nouvelle couleur
			attribuerEquipe(coordonnees);
		};
		void retirerContour(std::pair<int, int> cordonnees);
		void contour(std::pair<int, int> coordonneesinitiales);
		void viderCase(const std::pair<int, int> coordonnees);
		void viderEchiquier();
		void deplacerPiece(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
		bool verifierLegaliteMouvement(const std::vector<std::pair<int, int>>, const std::pair<int, int> destination, std::string couleurPiece);
		void afficherEchiquier();
		void afficherInfosCase(std::pair<int,int> coordonnees);
		// Fonction pour déterminer à quelle équipe une case appartient 
		int determinerEquipe(std::pair<int, int> coordonnees);
		// Fonction pour modifier les équipes:
		void attribuerEquipe(std::pair<int, int> coordonnes);
		// Fonction pour afficher les membres d'une équipe
		void afficherMembresEquipe(std::string nom);
		// Verifier la condition d'échec
		bool verifierEchec(std::pair<int,int> positionRoi);
		bool validerMouvement(const std::pair<int, int> coordonneesInitiales, const std::pair<int, int> coordonneesDestination);
		std::pair<int, int> trouverPiece(std::string nature, std::string couleur);
		void memoriserPiece(shared_ptr<piece>& pieceDeplacee);
		void lierMediateur(MediateurQT* mediateur) { mediateur_ = mediateur; };
		void miseAjourGraphique(pair<int, int> coordonnesCase);
		// Cette fonction étant générique, il faut l'implémenter au moment de sa déclaration
		template <class TypePiece>
		void placerPiece(pair<int, int> caseInitial, shared_ptr<TypePiece>* pieceAplacer) {
			modifierCase(caseInitial, pieceAplacer);
			//miseAjourGraphique(caseInitial);
		};
		
		void reAffichageGraphique();
		void prevenirAffichage() { affichable_ = false; };
	};
}






