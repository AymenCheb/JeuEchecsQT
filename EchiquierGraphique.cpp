#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include "EchiquierGraphique.h"
#include <iostream>
using namespace std;

pair<int, int> EchiquierGraphique::traduireIDenCoordonnes(int id) {
	int indexColonne = 0;
	int indexLigne = 0;
	for (int i = 0; (8 * indexLigne) + indexColonne != id; i++)
	{
		if (indexColonne == 7)
		{
			indexColonne = 0;
			indexLigne++;
		}
		else indexColonne++;
	}
	pair<int, int> coordonnes(indexLigne, indexColonne);
	cout << "Les coordonnes du bouton appuyé sont: " << coordonnes.first << " et " << coordonnes.second << endl;
	return coordonnes;
	
};



