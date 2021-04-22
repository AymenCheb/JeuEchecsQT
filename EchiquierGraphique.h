#pragma once
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QObject>
#pragma pop()
#include <iostream>
#include "Mediateur.h"
using namespace std;
// Cette classe int�ragit avec le m�diateur vue-mod�le
namespace interfaceGraphique {

	class EchiquierGraphique : public QObject {
		Q_OBJECT
	public:
		EchiquierGraphique() = default;
		pair<int, int> traduireIDenCoordonnes(int id);
		MediateurVueModele mediateur;
	public slots:
		void traiterAppuiBouton(int id) { mediateur.interpreterAppui(traduireIDenCoordonnes(id)); };
	signals:
	private:
		string typePiece_;
	
		bool estVide_ = true;
	};
}