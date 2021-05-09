#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Roi.h"
#include "Exceptions.h"
using namespace std;
int modele::Roi::compteurInstances_ = 0;
//Constructeur des Rois
void modele::Roi::verifierSurplusRoi() {
	if (compteurInstances_ > 2)
	{
		throw ErreurSurplusRoi("Il y a déjà 2 rois dans la partie ");
	}
}
modele::Roi::Roi(string couleur) : piece("R", couleur) {
	compteurInstances_++;
	try
	{
		verifierSurplusRoi();
	}
	catch (const ErreurSurplusRoi& e)
	{
		this->~Roi();
		cout << "Il y avait déjà 2 rois, dommage pour le nouveau né!" << endl;
	}
}
//]

modele::Roi::~Roi() { compteurInstances_--; };
bool modele::Roi::demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	/*Le roi peut se deplacer uniquement d'une cases dans toute les direction. Si il part de (x,y) et arrive a (w,z)
	alors,  |x-w| > 1 ou si |y-z| > 1, cela signifie que le roi ne s'est pas deplacer uniquement d'une case,
	et son mouvement est donc illegal*/
	int differenceX = depart.first - destination.first;
	int differenceY = depart.second - destination.second;
	if (abs(differenceX) > 1 || abs(differenceY) > 1)		//Roi peut seulement bouger de 1 cases a la fois
		return false;
	else
		return true;
}

std::vector<std::pair<int, int>> modele::Roi::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	//Le roi se deplace uniquement d'une case, son chemin de deplacement est donc uniquement composer de sa case d'arrivee
	vector<pair<int, int>> chemin;
	chemin.push_back(destination);
	return chemin;
}