#pragma once
#include "interfaceMediateur.h"

// Cette classe s'occupe de la communication entre l'interface gaphique et l'échiquier
class MediateurVueModele: public Mediateur {
private:
	// Cette liste de pairs mémorise les cordonnes des 2 dernières cases appuyées
	std::pair<int, int> memoireAppuis[2];
	Echiquier* echiquier_;
	// Cette fonction s'occupe de notifier l'échiquier en cas d'événements spécifique
	// Pour l'instant, nous n'en avons pas besoin, mais elle pourrait être utile pour le livrable 3
	void notifierEchiquier(Echiquier& echiquier, std::string evenement) override {};
	int nAppuisEnregistres_ = 0;
public:
	// Cette fonction s'occupe de mémoriser un appui et de l'interpréter quand la mémoire d'appuis est pleine
	void interpreterAppui(std::pair<int, int> coordonnesQT);
	// Cette fonction permet de lier le médiateur à un échiquier
	void lierEchiquier(Echiquier* echiquier) { echiquier_ = echiquier; };

};