#pragma once
#include "EchiquierWindow.h"
using namespace std;

// Mediateur r�sponsable de la communication depuius le mod�le � la vue
class MediateurModeleVue : public MediateurQT {
private:
	EchiquierWindow* echiquierWindow_;

public:
	// Constructeur du m�diateur. Il se lie � la fen�tre graphique
	MediateurModeleVue(EchiquierWindow* echiquierWindow) { echiquierWindow_ = echiquierWindow; };
	// Fonction pour passer d'une pair de coordonnes � un ID de bouton
	int transformerCordonnesID(pair<int, int> cordonnes) { return (cordonnes.second + (8 * cordonnes.first)); };
	// Notifie la fen�tre d'un changement au niveau des cases 
	void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) override { 
		echiquierWindow_->modifierContenuCase(transformerCordonnesID(coordonnes), typePiece, couleur); 
	};
};