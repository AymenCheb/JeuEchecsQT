#pragma once
using namespace std;
// Interface pour 
#include "Echiquier.h"
// Interface des m�diateurs
class Mediateur {
	virtual void notifierEchiquier(Echiquier& echiquier, std::string evenement) = 0;
};
