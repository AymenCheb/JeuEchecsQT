#include "interfaceMediateur.h"
#include "Mediateur.h"

// Cette fonction s'occupe de mémoriser un appui et de l'interpréter quand la mémoire d'appuis est pleine
void MediateurVueModele::interpreterAppui(std::pair<int, int> coordonnesQT) {
	// Si la mémoire n'est pas pleine, on enregistre l'appui et incrèment le nombre d'appuis enregistrés
	if (nAppuisEnregistres_ <= 1)
	{
		memoireAppuis[nAppuisEnregistres_] = coordonnesQT;
		nAppuisEnregistres_++;
	}
	// Si la mémoire est pleine, on traite les appuis et réinitialise  le nombre d'appuis enregistrés
	if (nAppuisEnregistres_ > 1)
	{
		// Cette condition vérifie que l'on essaye pas de déplacer une case vers ses propres coordonnes
		if (memoireAppuis[0] != memoireAppuis[1])
		{
			echiquier_->deplacerPiece(memoireAppuis[0], memoireAppuis[1]);
			echiquier_->afficherEchiquier();
		}
		nAppuisEnregistres_ = 0;
	}
 };

