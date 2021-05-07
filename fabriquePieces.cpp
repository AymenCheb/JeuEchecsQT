#include <memory>
#include "fabriquePieces.h"

using namespace std;

shared_ptr<modele::Tour> FabriqueAbstraite::creerTour(string nature, string couleur) {
	return make_shared<modele::Tour>(nature, couleur);
}
shared_ptr<modele::Roi> FabriqueAbstraite::creerRoi(string nature, string couleur) {
	return make_shared<modele::Roi>(nature, couleur);
}
shared_ptr<modele::Cavalier> FabriqueAbstraite::creerCavalier(string nature, string couleur) {
	return make_shared<modele::Cavalier>(nature, couleur);
}
shared_ptr<modele::piece>* FabriqueAbstraite::creerPiece(string nature, string couleur) {
	if (nature == "T")
	{
		return 
	}
	else if (nature == "R")
	{

	}
	else if (nature == "C")
	{

	}
}