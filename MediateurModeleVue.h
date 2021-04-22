#pragma once
#include "EchiquierWindow.h"
using namespace std;
class MediateurModeleVue : public MediateurQT {
private:
	EchiquierWindow* echiquierWindow_;
	vector<pair<int, int>> boutonTraites_;
	int nbBoutonsTraites_ = 0;
public:
	MediateurModeleVue(EchiquierWindow* echiquierWindow) { echiquierWindow_ = echiquierWindow; };
	int transformerCordonnesID(pair<int, int> cordonnes) { return (cordonnes.second + (8 * cordonnes.first)); };
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