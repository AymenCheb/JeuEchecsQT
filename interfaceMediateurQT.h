#pragma once
#include <string>
using namespace std;
// Interface d'un m�diateur QT
class MediateurQT {
public:
	virtual void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) = 0;
};