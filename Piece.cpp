#include <string>
#include <iostream>
#include <vector>
#include "Piece.h"

using namespace std;
// implémentations de la classe Piece 
//[
std::vector<std::pair<int, int>> modele::piece::trouverChemin(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	vector<pair<int, int>> chemin;
	// Un objet qui est simplement une pièce est une case vide, donc le déplacement est impossible, d'où un chemin vide
	return chemin;
}
bool modele::piece::demanderMouvement(const std::pair<int, int> depart, const std::pair<int, int> destination) {
	// Un objet qui est simplement une pièce est une case vide, donc aucun mouvement n'est possible
	cout << "La case est vide, il n'y a rien a deplacer" << endl;
	return false;
}
modele::piece::piece() {
	nature_ = "X"; // Une nature X signifie une case vide pour l'instant
	couleur_ = "aucune";
}
modele::piece::piece(string nature, std::string couleur) {
	nature_ = nature;
	couleur_ = couleur;

}
void modele::piece::afficher() {
	cout << nature_ << " "; // Affiche la nature de la piece
}
//]