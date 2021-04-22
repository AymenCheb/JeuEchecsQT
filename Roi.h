#pragma once
#include "Piece.h"
class Roi :public piece {
private:
	static int compteurInstances_;
public:
	Roi(std::string nature, std::string couleur);
	~Roi();
	std::vector<std::pair<int, int>>trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
	bool demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) override;
};