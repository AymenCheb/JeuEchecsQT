#include "EchiquierWindow.h"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#pragma pop()
#include <iostream>
#include <type_traits>
#include <cppitertools/range.hpp>
#include <qpainter.h>
using iter::range;

template <typename T>
QPushButton* EchiquierWindow::nouveauBouton(const QString& text, const T& slot)
{
	auto bouton = new QPushButton(this);
	bouton->setText(text);
	bouton->setFixedSize(95, 95);
	if constexpr (!is_same_v<T, decltype(nullptr)>)
		QObject::connect(bouton, &QPushButton::clicked, &echiquierGraphique_, slot);
	return bouton;
}

EchiquierWindow::EchiquierWindow(QWidget* parent) : QMainWindow(parent) {
	auto widgetPrincipal = new QWidget(this);
	auto layoutPrincipal = new QVBoxLayout(widgetPrincipal);
	auto layout = new QGridLayout();
	layout->setSizeConstraint(QLayout::SetFixedSize);
	layoutPrincipal->addLayout(layout);
	layoutPrincipal->setSizeConstraint(QLayout::SetFixedSize);
	layout->setSpacing(5);
	layout->setMargin(5);
	auto groupeBoutons = new QButtonGroup(this);
	int indexLigne = 0;
	int indexColonne= 0;
	for (int i : range(64)) {
		auto buton = nouveauBouton(QString::number(i));
		buton->setFlat(true);
		buton->setStyleSheet("QPushButton { background-color: transparent }");
		groupeBoutons->addButton(buton, i);
		layout->addWidget(buton, indexLigne, indexColonne);
		if (indexColonne == 7) {
			indexLigne++;
			indexColonne = 0;
		}
		else
		{
			indexColonne++;
		}
	}
}

void EchiquierWindow::paintEvent(QPaintEvent* ev) {
	QPainter painter(this);
	    
	    QPen pen;
	
	    pen.setColor(Qt::black); //Couleur des lignes formant chaque rectangle
	    pen.setWidth(3); //Epaisseur des lignes formant chaque rectangle
	
	    painter.setPen(pen); //On set le pen du painter en mettant celui que l'on vien de creer
	
	    //Ces coordonnees represente le point superieur gauche de chaque rectangle que l'on va dessiner, on commence donc au coordonnees 30,30
	    int depart = 10; 
	    int depart2 = 10;
	    bool caseNoire = true;
	    for (int i = 0; i <= 7; i++)
	    {
	        for (int j = 0; j <= 7; j++)
	        {
	            if (caseNoire) {  //Si la case doit etre noire, on met un fond noir au rectangle que l'on va dessiner
	                painter.setBrush(QColor(171, 124, 63, 127));
	                caseNoire = false; // A la prochaine iteration, caseNoire sera false, le prochain rectangle sera donc un rectangle blanc
	            }
	            else
	            {
	                painter.setBrush(QColor(171, 124, 63, 255)); //Si la case doit etre blanche, on met un fond blanc au rectangle que l'on va dessiner
	                caseNoire = true; // A la prochaine iteration, caseNoire sera true, le prochain rectangle sera donc un rectangle noir
	            }
	            QRect Case(depart, depart2, 100, 100); //On cree le "rectangle" que l'on veut dessiner, aux coordonnees (x,y), avec une largeur et une longueur de 50
	            painter.drawRect(Case); //On dessine un rectangle, en passant en parametre celui que l'on vien de creer plus haut
	            depart += 100; //On incremente uniquement x de 50, ainsi, le prochain "rectangle" sera juste a droite du precedent, sur la meme ligne (car on ne modifie pas y)
	        }
			if (caseNoire)
				caseNoire = false;
			else
				caseNoire = true;
	        //On remet x a 30, puis on incremente y de 50 (car la largeur est de 50). Ainsi, le prochain "rectangle que l'on dessinera sera juste en dessous du premier rectangle de la ligne d'en haut 
	        depart = 10; 
	        depart2 += 100;
	    }
}