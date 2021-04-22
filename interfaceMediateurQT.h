#pragma once
#include <string>
using namespace std;
// Interface d'un médiateur QT
class MediateurQT {
public:
	virtual void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) = 0;
};