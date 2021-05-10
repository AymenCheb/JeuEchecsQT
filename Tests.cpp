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


void testModele(modele::Echiquier& echiquier) {
	// Les tests suivants visent à tester les foncitons du modèle:

	string sepratation = " \n --------------------------------------------------------------- \n";
	cout << "Tableau initial" << endl;
	cout << '\n';
	echiquier.afficherEchiquier();
	cout << sepratation;
	cout << '\n';
	pair<int, int> nouvelleCoordonnees, coordonneesInitiales;
	echiquier.reAffichageGraphique();
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
	// Test: déplacer une case sur elle même
	echiquier.deplacerPiece(coordonneesInitiales, coordonneesInitiales);
	// Test trouver chemin piece vide: 
	modele::piece unePiece; 
	unePiece.trouverChemin(coordonneesInitiales, nouvelleCoordonnees);
	// Test contour: 
	echiquier.contour(coordonneesInitiales);
	// Tests déplacement de pièces: 
	// Test du nombre limite de rois:
	// 
	// Préparation de pièces pour tester
	modele::Roi roiNoir("Noir");
	modele::Roi roiBlanc("Blanc");
	modele::Roi roiKazakistan("Bleu"); // On tente de créer un 3ème roi
	modele::Tour tourNoir("Noir");
	modele::Cavalier cavalierNoir("Noir");

	shared_ptr<modele::Roi> pointeurRoiNoir = make_shared<modele::Roi>(roiNoir);
	shared_ptr<modele::Tour> pointeurTourNoir = make_shared<modele::Tour>(tourNoir);
	shared_ptr<modele::Cavalier> pointeurCavalierNoir = make_shared<modele::Cavalier>(cavalierNoir);

	pair<int, int> crdTour(1, 0), crdCavalier(1, 1), crdRoi(0, 0);

	// Placement des pièces sur l'échiquier:
	echiquier.modifierCase(crdTour, &pointeurTourNoir);
	echiquier.modifierCase(crdRoi, &pointeurRoiNoir);
	echiquier.modifierCase(crdCavalier, &pointeurCavalierNoir);

	echiquier.afficherEchiquier();

	// Tests déplacements de la tour:
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

	destinationCavalier.first = 4;
	destinationCavalier.second = 3;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);
	crdCavalier = destinationCavalier;

	destinationCavalier.first = 1;
	destinationCavalier.second = 1;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);

	destinationCavalier.first = 7;
	destinationCavalier.second = 6;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);

	destinationCavalier.first = 6;
	destinationCavalier.second = 7;
	echiquier.deplacerPiece(crdCavalier, destinationCavalier);


	//Test mise en echec du roi
	shared_ptr<modele::Roi> pointeurRoiBlanc = make_shared<modele::Roi>(roiBlanc);
	pair<int, int> coordonneesRoiBlanc(2, 5);
	echiquier.modifierCase(coordonneesRoiBlanc, &pointeurRoiBlanc);
	pair<int, int> destinationRoiBlanc(2, 4);
	echiquier.deplacerPiece(coordonneesRoiBlanc, destinationRoiBlanc);
	echiquier.afficherEchiquier();

	//Test deplacement sur une case ou une piece alliee se trouve
	destinationTour.first = 4;
	destinationTour.second = 3;
	echiquier.deplacerPiece(crdTour, destinationTour);

	//Test depalcment de la tour alors qu'une piece alliee se trouve sur le chemin
	destinationTour.first = 4;
	destinationTour.second = 4; 
	echiquier.deplacerPiece(crdTour, destinationTour);

	destinationTour.first = 4;
	destinationTour.second = 1;
	echiquier.deplacerPiece(crdTour, destinationTour);
	echiquier.afficherMembresEquipe("Equipe noire");

	// Test des fonctions pour vider des cases
	echiquier.viderCase(crdTour);
	echiquier.viderEchiquier();
}


