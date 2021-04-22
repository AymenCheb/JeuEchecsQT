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
	Echiquier echiquier;
	Roi roiNoir("R", "Noir");
	Roi roiBlanc("R", "Blanc");
	Roi roiKazakistan("R", "Bleu");
	Tour tourBlanche("T", "Blanc");
	Tour tourNoir("T", "Noir");
	Cavalier cavalierNoir("C", "Noir"), cavalierBlanc("C", "Blanc");
	shared_ptr<Roi> pointeurRoiNoir = make_shared<Roi>(roiNoir);
	shared_ptr<Roi> pointeurRoiBlanc = make_shared<Roi>(roiBlanc);
	shared_ptr<Tour> pointeurTourBlanche = make_shared<Tour>(tourBlanche);
	shared_ptr<Tour> pointeurTourNoir = make_shared<Tour>(tourNoir);
	shared_ptr<Cavalier> pointeurCavalierNoir = make_shared<Cavalier>(cavalierNoir);
	shared_ptr<Cavalier> pointeurCavalierBlanc = make_shared<Cavalier>(cavalierBlanc);
	// Pour l'instant, nous commencons une partie dans un scénario de fin de jeu
	pair<int, int> crdRoiNoir(7, 6), crdTourNoir(6, 6), crdTourBlance(0, 6), crdRoiBlanc(0,7), crdCavalierBlanc(4,4), crdCavalierNoir(3,4);
	// Test de la vérification de la mise en échecs: 
	

	echiquier.afficherEchiquier();
	EchiquierWindow echiquierWindow;
	MediateurModeleVue mediateurModeleVue(&echiquierWindow);
	echiquier.lierMediateur(&mediateurModeleVue);
	echiquierWindow.lierEchiquier(&echiquier);
	
	
	// On place les pièces initialisées au début une fois que la fenêtre est lancée 
	echiquier.placerPiece(crdRoiNoir, &pointeurRoiNoir);
	echiquier.placerPiece(crdTourBlance, &pointeurTourBlanche);
	echiquier.placerPiece(crdTourNoir, &pointeurTourNoir);
	echiquier.placerPiece(crdRoiBlanc, &pointeurRoiBlanc);
	echiquier.placerPiece(crdCavalierNoir, &pointeurCavalierNoir);
	echiquier.placerPiece(crdCavalierBlanc, &pointeurCavalierBlanc);
	echiquierWindow.setWindowState(Qt::WindowMaximized);
	echiquierWindow.show();
	return app.exec();
}
