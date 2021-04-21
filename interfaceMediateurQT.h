#pragma once
#include <string>
using namespace std;
class MediateurQT {
public:
	virtual void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) = 0;
};