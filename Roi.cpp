#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Roi.h"
#include "Exceptions.h"
using namespace std;
int Roi::compteurInstances_ = 0;
//Constructeur des Rois
void Roi::verifierSurplusRoi() {
	if (compteurInstances_ > 2)
	{
		throw ErreurSurplusRoi("Il y a déjà 2 rois dans la partie ");
	}
}
Roi::Roi(string nature, string couleur) : piece(nature, couleur) {
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

Roi::~Roi() { compteurInstances_--; };
bool Roi::demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) {
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

std::vector<std::pair<int, int>> Roi::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	//Le roi se deplace uniquement d'une case, son chemin de deplacement est donc uniquement composer de sa case d'arrivee
	vector<pair<int, int>> chemin;
	chemin.push_back(destination);
	return chemin;
}