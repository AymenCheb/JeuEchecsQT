#pragma once
using namespace std;
// Interface pour 
#include "Echiquier.h"
// Interface des m�diateurs
class Mediateur {
	virtual void notifierEchiquier(modele::Echiquier& echiquier, std::string evenement) = 0;
};
