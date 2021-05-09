#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include <iostream>
#include "Mediateur.h"
using namespace std;
enum parties
{
	DeuxAdeux,
	TroisContreUn,
	NonSelectionne
};
// Cette classe intéragit avec le médiateur vue-modèle
namespace interfaceGraphique {

	class EchiquierGraphique : public QObject {
		Q_OBJECT
	public:
		vector<modele::Echiquier*> echiquiers;
		EchiquierGraphique() = default;
		pair<int, int> traduireIDenCoordonnes(int id);
		MediateurVueModele mediateur;
		parties verifierPartie() { return partie_; };
	public slots:
		void traiterAppuiBouton(int id) { 
			switch (id)
			{
			case 65: 
				mediateur.lierEchiquier(echiquiers[0]);
				cout << "Switch sur echiquier 0" << endl;
				echiquiers[0]->reAffichageGraphique();
				break;
			case 66:
			case 67:
				cout << "Switch sur echiquier 1" << endl;
				mediateur.lierEchiquier(echiquiers[1]);
				echiquiers[1]->reAffichageGraphique();
				break;
			default:
				mediateur.interpreterAppui(traduireIDenCoordonnes(id));
				break;
			}
				
		};
	signals:
	private:
		string typePiece_;
		parties partie_ = NonSelectionne;
		bool estVide_ = true;
	};
}