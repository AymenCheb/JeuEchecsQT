#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include <iostream>
#include "Mediateur.h"
using namespace std;
// Cette classe intéragit avec le médiateur vue-modèle
namespace interfaceGraphique {

	class EchiquierGraphique : public QObject {
		Q_OBJECT
	public:
		vector<modele::Echiquier*> echiquiers;
		EchiquierGraphique() = default;
		pair<int, int> traduireIDenCoordonnes(int id);
		MediateurVueModele mediateur;
	public slots:
		void traiterAppuiBouton(int id) { 
			// Le switch traite l'appui en fonction de l'id du bouton
			switch (id)
			{
			// Les cas spéciaux: On a appuyé sur un bouton de partie
			case 65: 
				mediateur.lierEchiquier(echiquiers[0]);
				cout << "Switch sur echiquier 0" << endl;
				echiquiers[0]->reAffichageGraphique();
				break;
			case 66:
				cout << "Switch sur echiquier 1" << endl;
				mediateur.lierEchiquier(echiquiers[1]);
				echiquiers[1]->reAffichageGraphique();
				break;
			case 67:
				cout << "Switch sur echiquier 2" << endl;
				mediateur.lierEchiquier(echiquiers[2]);
				echiquiers[2]->reAffichageGraphique();
				break;
			// Le cas par défaut: On a appuyé sur une case
			default:
				mediateur.interpreterAppui(traduireIDenCoordonnes(id));
				break;
			}
				
		};
	signals:
	private:
		string typePiece_;
		bool estVide_ = true;
	};
}