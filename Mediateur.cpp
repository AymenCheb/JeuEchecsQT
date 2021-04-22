#include "interfaceMediateur.h"
#include "Mediateur.h"

// Cette fonction s'occupe de m�moriser un appui et de l'interpr�ter quand la m�moire d'appuis est pleine
void MediateurVueModele::interpreterAppui(std::pair<int, int> coordonnesQT) {
	// Si la m�moire n'est pas pleine, on enregistre l'appui et incr�ment le nombre d'appuis enregistr�s
	if (nAppuisEnregistres_ <= 1)
	{
		memoireAppuis[nAppuisEnregistres_] = coordonnesQT;
		nAppuisEnregistres_++;
	}
	// Si la m�moire est pleine, on traite les appuis et r�initialise  le nombre d'appuis enregistr�s
	if (nAppuisEnregistres_ > 1)
	{
		// Cette condition v�rifie que l'on essaye pas de d�placer une case vers ses propres coordonnes
		if (memoireAppuis[0] != memoireAppuis[1])
		{
			echiquier_->deplacerPiece(memoireAppuis[0], memoireAppuis[1]);
			echiquier_->afficherEchiquier();
		}
		nAppuisEnregistres_ = 0;
	}
 };

