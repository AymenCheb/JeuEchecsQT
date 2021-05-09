/**
* Programme qui implément un jeu d'échecs
* \file   main.cpp
* \author Chebbi Mohamed Aymen, Jaafar Hady, Panoyan Arthur
* \date   12 avril 2021
* Créé le 08 avril 2021
*/



#include "EchiquierWindow.h"
#include "EchiquierGraphique.h"
#include <QApplication>
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
#include "Tests.h"
#include "MediateurModeleVue.h"
#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif
	//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}


int main(int argc, char *argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	// Les lignes de codes suivantes s'occupe de créer les pièces de la partie: 
	// Note: Les prochaines versions du projet auront une fonction pour se charger de ces étapes
	
	modele::Echiquier echiquier;
	modele::Echiquier finQuadratique, finTriangulaire;

	// Pour l'instant, nous commencons une partie dans un scénario de fin de jeu
	pair<int, int> crdRoiNoir, crdTourNoir, crdTourBlance, crdRoiBlanc, crdCavalierBlanc, crdCavalierNoir;

	interfaceGraphique::EchiquierWindow echiquierWindow;
	echiquierWindow.ajouterEchiquier(&finTriangulaire);
	echiquierWindow.ajouterEchiquier(&finQuadratique);
	MediateurModeleVue mediateurModeleVue(&echiquierWindow);
	
	echiquier.lierMediateur(&mediateurModeleVue);
	finTriangulaire.lierMediateur(&mediateurModeleVue);
	finQuadratique.lierMediateur(&mediateurModeleVue);
	echiquierWindow.lierEchiquier(&echiquier);
	testPartie1(echiquier);
	
	modele::Roi roiNoir("Noir");
	modele::Roi roiBlanc("Blanc");
	modele::Tour tourBlanche("Blanc");
	modele::Tour tourNoir("Noir");
	modele::Cavalier cavalierNoir("Noir"), cavalierBlanc("Blanc");
	shared_ptr<modele::Roi> pointeurRoiNoir = make_shared<modele::Roi>(roiNoir);
	shared_ptr<modele::Roi> pointeurRoiBlanc = make_shared<modele::Roi>(roiBlanc);
	shared_ptr<modele::Tour> pointeurTourBlanche = make_shared<modele::Tour>(tourBlanche);
	shared_ptr<modele::Tour> pointeurTourNoir = make_shared<modele::Tour>(tourNoir);
	shared_ptr<modele::Cavalier> pointeurCavalierNoir = make_shared<modele::Cavalier>(cavalierNoir);
	shared_ptr<modele::Cavalier> pointeurCavalierBlanc = make_shared<modele::Cavalier>(cavalierBlanc);
	
	// Il y a certainement des manières plus élégantes de réaliser cela, mais par soucis de simpliciter nous avons implémenté les différentes parties avec un switch des valeurs des coordonnées

		crdRoiNoir = pair<int, int>(0, 0);
		crdTourNoir = pair<int, int>(0, 1);
		crdTourBlance = pair<int, int>(1, 0);
		crdRoiBlanc = pair<int, int>(0, 2);
		crdCavalierBlanc = pair<int, int>(5, 0);
		crdCavalierNoir = pair<int, int>(0, 6);

		finTriangulaire.placerPiece(crdRoiNoir, &pointeurRoiNoir);
		finTriangulaire.placerPiece(crdTourBlance, &pointeurTourBlanche);
		finTriangulaire.placerPiece(crdTourNoir, &pointeurTourNoir);

		finTriangulaire.placerPiece(crdRoiBlanc, &pointeurRoiBlanc);
		finTriangulaire.placerPiece(crdCavalierNoir, &pointeurCavalierNoir);
		finTriangulaire.placerPiece(crdCavalierBlanc, &pointeurCavalierBlanc);

		crdRoiNoir = pair<int, int>(5, 5);
		crdTourNoir = pair<int, int>(7, 5);
		crdTourBlance = pair<int, int>(6, 5);
		crdRoiBlanc = pair<int, int>(5, 7);
		crdCavalierBlanc = pair<int, int>(7, 7);
		crdCavalierNoir = pair<int, int>(6, 6);

		finQuadratique.placerPiece(crdRoiNoir, &pointeurRoiNoir);
		finQuadratique.placerPiece(crdTourBlance, &pointeurTourBlanche);
		finQuadratique.placerPiece(crdTourNoir, &pointeurTourNoir);

		finQuadratique.placerPiece(crdRoiBlanc, &pointeurRoiBlanc);
		finQuadratique.placerPiece(crdCavalierNoir, &pointeurCavalierNoir);
		finQuadratique.placerPiece(crdCavalierBlanc, &pointeurCavalierBlanc);
	// Test de la vérification de la mise en échecs: 
	

	
	
	
	// On place les pièces initialisées au début une fois que la fenêtre est lancée 
	echiquierWindow.setWindowState(Qt::WindowMaximized);
	echiquierWindow.show();
	return app.exec();
}
