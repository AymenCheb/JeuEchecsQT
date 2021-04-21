#pragma once
#include "EchiquierWindow.h"
using namespace std;
class MediateurModeleVue : public MediateurQT {
private:
	EchiquierWindow* echiquierWindow_;

public:
	MediateurModeleVue(EchiquierWindow* echiquierWindow) { echiquierWindow_ = echiquierWindow; };
	int transformerCordonnesID(pair<int, int> cordonnes) { return (cordonnes.second + (8 * cordonnes.first)); };
	void notifierWindow(pair<int, int> coordonnes, string typePiece) override { echiquierWindow_->modifierContenuCase(transformerCordonnesID(coordonnes), typePiece); };
};