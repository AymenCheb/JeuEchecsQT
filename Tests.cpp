#include <utility>
#include <string>
#include <iostream>
#include <memory>

#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Equipe.h"
#include "Echiquier.h"
#include "EchiquierWindow.h"
using namespace std;


void testPartie1() {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	cout << '\n';
	modele::Echiquier echiquier;
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	pair<int, int> nouvelleCoordonnees, coordonneesInitiales;
	// Test: déplacer une case vide 
	nouvelleCoordonnees.first = 7;
	nouvelleCoordonnees.second = 7;
	cout << sepratation;
	cout << '\n';
	cout << "On demande le deplacement de la piece a la case (6,6), vers la case (7,7) :" << endl;
	cout << '\n';
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Coordonnees pour tester des deplacmeents de pieces
	nouvelleCoordonnees.first = 3;
	coordonneesInitiales.first = 5;
	nouvelleCoordonnees.second = 4;
	coordonneesInitiales.second = 4;

	// Creation d'une tour et test de deplacements
	//Creation de la tour et positionnement de la tour aux coordonnees
	modele::Tour nouvellePiece("Noir");
	shared_ptr<modele::Tour> pointeurTour = make_shared<modele::Tour>(nouvellePiece);
	cout << "On demande la modification de la case (5,4) en une tour: " << endl;
	cout << '\n';
	echiquier.modifierCase(coordonneesInitiales, &pointeurTour);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal de la tour
	cout << "On deplace la tour de 2 cases vers le haut" << endl;
	echiquier.deplacerPiece(coordonneesInitiales, nouvelleCoordonnees);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement illegal de la tour
	cout << "On tente de deplacer la tour en diagonale" << endl;
	pair<int, int> coordonneesTest(2, 3);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesTest);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Creation d'un cavalier et test de deplacements
	//Creation du cavalier et positionnement
	modele::Cavalier premierCavalier("Noir");
	shared_ptr<modele::Cavalier> pointeurCavalier = make_shared<modele::Cavalier>(premierCavalier);
	pair<int, int> coordonneesCavalier(5, 4);
	echiquier.modifierCase(coordonneesCavalier, &pointeurCavalier);
	cout << "On positionne un cavalier aux coordonnees (5,4)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du cavalier
	pair<int, int> deplacementCavalier(3, 3);
	echiquier.deplacerPiece(coordonneesCavalier, deplacementCavalier);
	cout << "On deplace le cavaleir aux coordonnees (3,3)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacment illegal du cavalier
	pair<int, int> deplacementIllegalCavalier(2, 2);
	cout << "On essaie de deplacer le cavalier a la position (2,2)" << endl;
	echiquier.deplacerPiece(deplacementCavalier, deplacementIllegalCavalier);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';



	//Creation d'un roi et test de deplacements
	//Creation du roi et positionnement
	modele::Roi premierRoi("Noir");
	shared_ptr<modele::Roi> pointeurRoi = make_shared<modele::Roi>(premierRoi);
	pair<int, int> coordonneesRoi(2, 4);
	echiquier.modifierCase(coordonneesRoi, &pointeurRoi);
	cout << "On positionne le Roi aux coordonnees(2,4)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement legal du Roi
	pair<int, int> deplacementRoi(2, 5);
	echiquier.deplacerPiece(coordonneesRoi, deplacementRoi);
	cout << "On deplace le Roi aux coordonnees (2,5)" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	//Deplacement illegal du roi
	pair<int, int> deplacementIllegalRoi(4, 6);
	cout << "On essaie de deplacer le Roi aux coordonnees (3,6), donc de deux cases." << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementIllegalRoi);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Test pour deplacer une piece sur une case contenant une autre piece d'une meme couleur
	pair<int, int> deplacementRoiMange(3, 4);
	cout << "On essaie de deplacer le Roi aux coordonnees(3, 4), ou une piece alliee se trouve" << endl;
	cout << '\n';
	echiquier.deplacerPiece(deplacementRoi, deplacementRoiMange);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';


	//Test deplacer une tour alors q'une piece se trouve sur son chemin
	cout << "On essaie de deplacer la Tour des coordonnees (3,4) aux coordonnees (3,2), alors qu'un cavalier allie se trouve aux coordonnees (3,3)" << endl;
	nouvelleCoordonnees.first = 3;
	nouvelleCoordonnees.second = 4;
	pair<int, int> coordonneesDeplacementTour(3, 2);
	echiquier.deplacerPiece(nouvelleCoordonnees, coordonneesDeplacementTour);
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';

	// Test: Affichage d'une case pour vérifier qu'elle a les bonnes coordonnees, nature/couleur... 
	nouvelleCoordonnees.first = 3;
	nouvelleCoordonnees.second = 4;
	cout << "On demande l'affichage de la case aux coordonnees:\n" << nouvelleCoordonnees.first << ',' << nouvelleCoordonnees.second << endl;
	echiquier.afficherInfosCase(nouvelleCoordonnees);
	cout << "On demande l'affichage des membres des deux équipes: " << endl;
	cout << '\n';
	echiquier.afficherMembresEquipe("Equipe noire");
	echiquier.afficherMembresEquipe("Equipe blanche");
	cout << sepratation;
	cout << '\n';
}


