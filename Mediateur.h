#pragma once
#include "interfaceMediateur.h"

class MediateurModeleVue: public Mediateur {
private:
	std::pair<int, int> memoireAppuis[2];
	Echiquier* echiquier_;
	void notifierEchiquier(Echiquier& echiquier, std::string evenement) override {};
	int nAppuisEnregistres_ = 0;
public:
	void interpreterAppui(std::pair<int, int> coordonnesQT);
	void lierEchiquier(Echiquier* echiquier) { echiquier_ = echiquier; };


};