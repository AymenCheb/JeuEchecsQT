#pragma once
#include "interfaceMediateur.h"

// Cette classe s'occupe de la communication entre l'interface gaphique et l'�chiquier
class MediateurVueModele: public Mediateur {
private:
	// Cette liste de pairs m�morise les cordonnes des 2 derni�res cases appuy�es
	std::pair<int, int> memoireAppuis[2];
	Echiquier* echiquier_;
	// Cette fonction s'occupe de notifier l'�chiquier en cas d'�v�nements sp�cifique
	// Pour l'instant, nous n'en avons pas besoin, mais elle pourrait �tre utile pour le livrable 3
	void notifierEchiquier(Echiquier& echiquier, std::string evenement) override {};
	int nAppuisEnregistres_ = 0;
public:
	// Cette fonction s'occupe de m�moriser un appui et de l'interpr�ter quand la m�moire d'appuis est pleine
	void interpreterAppui(std::pair<int, int> coordonnesQT);
	// Cette fonction permet de lier le m�diateur � un �chiquier
	void lierEchiquier(Echiquier* echiquier) { echiquier_ = echiquier; };

};