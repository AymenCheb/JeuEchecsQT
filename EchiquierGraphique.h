#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()
#include <iostream>
using namespace std;
class EchiquierGraphique : public QObject {
	Q_OBJECT
public:
	EchiquierGraphique() = default;
	pair<int, int> traduireIDenCoordonnes(int id);
public slots:
	/*pair<int, int> obtenirCoordonnes();*/
	/*void changerTypeAffiche(string nouveauType);
	void changerRemplissage();*/
	void afficherCoordonnes(int id) { traduireIDenCoordonnes(id); };
signals:
	/*void coordonnesDemandee();
	void typeChange();
	void remplissageChange();*/
private:
	string typePiece_;
	bool estVide_ = true;
};