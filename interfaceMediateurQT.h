#pragma once
#include <string>
using namespace std;
// Interface d'un médiateur QT
class MediateurQT {
public:
	virtual void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) = 0;
	virtual void changerCouleurCase(pair <int, int> coordonnes) = 0;
	virtual void remettreCouleurCase(pair <int, int> coordonnees) = 0;
	virtual void retablirCase() = 0;
	virtual void colorerContour(pair<int, int> coordonnees) = 0;
	virtual void retirerContour(pair<int, int> coordonnees) = 0;
	
};