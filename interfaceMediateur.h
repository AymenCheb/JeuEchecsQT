#pragma once
#include "Echiquier.h"

// Interface pour 
class Mediateur {
	virtual void notifierEchiquier(Echiquier& echiquier, std::string evenement);
};