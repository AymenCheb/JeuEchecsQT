#pragma once
#include "EchiquierWindow.h"
using namespace std;

// Mediateur résponsable de la communication depuius le modèle à la vue
class MediateurModeleVue : public MediateurQT {
private:
	EchiquierWindow* echiquierWindow_;

public:
	// Constructeur du médiateur. Il se lie à la fenêtre graphique
	MediateurModeleVue(EchiquierWindow* echiquierWindow) { echiquierWindow_ = echiquierWindow; };
	// Fonction pour passer d'une pair de coordonnes à un ID de bouton
	int transformerCordonnesID(pair<int, int> cordonnes) { return (cordonnes.second + (8 * cordonnes.first)); };
	// Notifie la fenêtre d'un changement au niveau des cases 
	void notifierWindow(pair<int, int> coordonnes, string typePiece, string couleur) override { 
		echiquierWindow_->modifierContenuCase(transformerCordonnesID(coordonnes), typePiece, couleur); 
	};
};