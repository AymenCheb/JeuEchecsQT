#include "interfaceMediateur.h"
#include "Mediateur.h"


void MediateurVueModele::interpreterAppui(std::pair<int, int> coordonnesQT) {
	if (nAppuisEnregistres_ <= 1)
	{
		memoireAppuis[nAppuisEnregistres_] = coordonnesQT;
		nAppuisEnregistres_++;
	}
	if (nAppuisEnregistres_ > 1)
	{
		if (memoireAppuis[0] != memoireAppuis[1])
		{
			echiquier_->deplacerPiece(memoireAppuis[0], memoireAppuis[1]);
			echiquier_->afficherEchiquier();
		}
		nAppuisEnregistres_ = 0;
	}
 };

