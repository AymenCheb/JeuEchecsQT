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
#include "MediateurModeleVue.h"
using namespace std;


void testPartie1(modele::Echiquier& echiquier) {
	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	cout << '\n';
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
	echiquier.deplacerPiece(coordonneesInitiales, coordonneesInitiales);
	// Tests déplacement de pièces: 
	// Test du nombre limite de rois:
	modele::Roi roiNoir("Noir");
	modele::Roi roiBlanc("Blanc");
	modele::Roi roiKazakistan("Bleu"); // On tente de créer un 3ème roi
	modele::Tour tourNoir("Noir");
	modele::Cavalier cavalierNoir("Noir");
	shared_ptr<modele::Roi> pointeurRoiNoir = make_shared<modele::Roi>(roiNoir);
	shared_ptr<modele::Tour> pointeurTourNoir = make_shared<modele::Tour>(tourNoir);
	shared_ptr<modele::Cavalier> pointeurCavalierNoir = make_shared<modele::Cavalier>(cavalierNoir);
	pair<int, int> crdTour(1, 0), crdCavalier(1, 1), crdRoi(0, 0);
	echiquier.modifierCase(crdTour, &pointeurTourNoir);
	echiquier.modifierCase(crdRoi, &pointeurRoiNoir);
	echiquier.modifierCase(crdCavalier, &pointeurCavalierNoir);
	echiquier.afficherEchiquier();
	// Tests déplacements de la tour
	// Deplacement tour vers le bas
	pair<int, int> destinationTour(5, 0);
	echiquier.deplacerPiece(crdTour, destinationTour);
	crdTour = destinationTour;
	// Deplacement tour vers la droite
	destinationTour.second = 2;
	echiquier.deplacerPiece(crdTour, destinationTour);
	// Deplacement tour vers la gauche 
	echiquier.deplacerPiece(destinationTour, crdTour);
	// Test deplacement vers le haut
	destinationTour.first = 4;
	destinationTour.second = crdTour.second;
	echiquier.deplacerPiece(crdTour, destinationTour);
	// Test deplacement illegal: 
	crdTour = destinationTour; 
	destinationTour.first = crdTour.first + 1;
	destinationTour.second = crdTour.second + 1;
	echiquier.deplacerPiece(crdTour, destinationTour);
	

	//Test deplacment du cavalier
	pair<int, int> destinationCavalier(3, 2);
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);
	crdCavalier = destinationCavalier;

	destinationCavalier.first = 5;
	destinationCavalier.second = 1;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);
	crdCavalier = destinationCavalier;

	destinationCavalier.first = 3;
	destinationCavalier.second = 2;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);
	crdCavalier = destinationCavalier;

	destinationCavalier.first = 1;
	destinationCavalier.second = 1;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);
	crdCavalier = destinationCavalier;



	echiquier.viderCase(crdTour);
	echiquier.viderEchiquier();
}


