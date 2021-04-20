#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()

using namespace std;
class EchiquierGraphique : public QObject {
	Q_OBJECT
public:
	EchiquierGraphique() = default;
public slots:
	/*pair<int, int> obtenirCoordonnes();*/
	/*void changerTypeAffiche(string nouveauType);
	void changerRemplissage();*/
signals:
	/*void coordonnesDemandee();
	void typeChange();
	void remplissageChange();*/
private:
	string typePiece_;
	bool estVide_ = true;
};