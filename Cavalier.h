#pragma once
#include "Piece.h"

namespace modele {

	class Cavalier : public piece {
	private:
	public:
		Cavalier(std::string couleur);
		std::vector<std::pair<int, int>> trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
		bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	};
}