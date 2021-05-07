#pragma once
#include <string>
#include <memory>
#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Tour.h"

using namespace std;
class FabriqueAbstraite {
	shared_ptr<modele::piece>* creerPiece(string nature, string couleur);
	shared_ptr<modele::Tour> creerTour(string nature, string couleur);
	shared_ptr<modele::Roi> creerRoi(string nature, string couleur);
	shared_ptr<modele::Cavalier> creerCavalier(string nature, string couleur);
};