#pragma once
#include "EchiquierWindow.h"
using namespace std;

// Mediateur résponsable de la communication depuius le modèle à la vue
class MediateurModeleVue : public MediateurQT {
private:
	interfaceGraphique::EchiquierWindow* echiquierWindow_;
	vector<pair<int, int>> boutonTraites_;
	int nbBoutonsTraites_ = 0;
public:
	// Constructeur du médiateur. Il se lie à la fenêtre graphique
	MediateurModeleVue(interfaceGraphique::EchiquierWindow* echiquierWindow) { echiquierWindow_ = echiquierWindow; };
	// Fonction pour passer d'une pair de coordonnes à un ID de bouton
	int transformerCordonnesID(pair<int, int> cordonnes) { return (cordonnes.second + (8 * cordonnes.first)); };
	// Notifie la fenêtre d'un changement au niveau des cases 
	void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) override { 
		echiquierWindow_->modifierContenuCase(transformerCordonnesID(coordonnes), typePiece, couleur); 
	};
	void changerCouleurCase(pair<int, int> cordonnees) override {
		boutonTraites_.push_back(cordonnees);
		echiquierWindow_->modifierCouleurCase(transformerCordonnesID(cordonnees));
		nbBoutonsTraites_++;
	}

	void remettreCouleurCase(pair<int, int> cordonnees) override {
		echiquierWindow_->couleurCaseOriginale(transformerCordonnesID(cordonnees));
		
	}

	void retablirCase() override {
		for (int i = 0; i < nbBoutonsTraites_; i++)
		{
			remettreCouleurCase(boutonTraites_[i]);
			boutonTraites_.erase(boutonTraites_.begin()+i);
			nbBoutonsTraites_--;
		}
	}
};