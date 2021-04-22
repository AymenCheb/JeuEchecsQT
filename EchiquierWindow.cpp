#include "EchiquierWindow.h"
#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
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
#include <QLineEdit>
using iter::range;

template <typename T>
// Fonction pour cr�er un nouveau bouton
QPushButton* interfaceGraphique::EchiquierWindow::nouveauBouton(const QString& text, const T& slot)
{
	auto bouton = new QPushButton(this);
	bouton->setFixedSize(95, 95);
	if constexpr (!is_same_v<T, decltype(nullptr)>)
		QObject::connect(bouton, &QPushButton::clicked, &echiquierGraphique_, slot);
	return bouton;
}

// Constructeur par d�faut de notre EchiquierWindow
interfaceGraphique::EchiquierWindow::EchiquierWindow(QWidget* parent) : QMainWindow(parent) {
	auto widgetPrincipal = new QWidget(this);
	auto layoutPrincipal = new QVBoxLayout(widgetPrincipal);
	// Layout contenant les boutons. On utilise grid pour faciliter le placement
	auto layout = new QGridLayout();
	// Permet de s'assurer que notre layout ne prenne pas plus d'espace que n�cessaire
	layout->setSizeConstraint(QLayout::SetFixedSize);
	layoutPrincipal->addLayout(layout);
	// Permet de s'assurer que notre layout ne prenne pas plus d'espace que n�cessaire
	layoutPrincipal->setSizeConstraint(QLayout::SetFixedSize);
	// On veut un espacement minime entre les boutons pour �viter la superposition de clicks
	layout->setSpacing(5);
	layout->setMargin(5);
	auto groupeBoutons = new QButtonGroup(this);
	// Cest indexs sont utiles pour placer les boutons
	int indexLigne = 0;
	int indexColonne= 0;
	for (int i : range(64)) {
		auto buton = nouveauBouton(QString::number(i));
		buton->setFlat(true);
		buton->setStyleSheet("QPushButton { background-color: transparent }");
		groupeBoutons->addButton(buton, i);
		vecteursCases.push_back(buton);
		layout->addWidget(buton, indexLigne, indexColonne);
		// On place le bouton � la bonne position sur l'�chiquier
		if (indexColonne == 7) {
			// Si on a remplit une ligne enti�re, on r�initialise l'index des colonnes et on passe � la suivante 
			indexLigne++;
			indexColonne = 0;
		}
		else
		{
			indexColonne++;
		}
	}
	// Cette portion du code provient est grandement inspir� de l'exemple de projet fournit par Fr Boyer sur moodle : 
	#if QT_VERSION >= QT_VERSION_CHECK(5,15,0)  // Le nom du signal idClicked existe depuis Qt 5.15
		QObject::connect(groupeBoutons, &QButtonGroup::idClicked, &echiquierGraphique_, &EchiquierGraphique::traiterAppuiBouton); 
#else
		QObject::connect(groupeBoutons, SIGNAL(buttonClicked(int)), &echiquierGraphique_, SLOT(traiterAppuiBouton(int)));
	#endif
}

// Fonction pour modifier l'image affich�e par un bouton
void interfaceGraphique::EchiquierWindow::modifierContenuCase(int id, string typePiece, string couleurEquipe) {
	
	vecteursCases[id]->setText("");
	std::string nomFichier = typePiece + couleurEquipe + ".png";
	QPixmap pixmap(QString::fromStdString(nomFichier));
	QIcon ButtonIcon(pixmap);
	vecteursCases[id]->setIcon(ButtonIcon);
	vecteursCases[id]->setIconSize(QSize(60, 60));
	
}

void interfaceGraphique::EchiquierWindow::modifierBordureCase(int id) {
	vecteursCases[id]->setFlat(false);
	vecteursCases[id]->setStyleSheet("QPushButton{ border-width: 5px; border-style: solid; border-color: rgb(125, 232, 127) rgb(125, 232, 127) rgb(125, 232, 127) rgb(125, 232, 127); }");
}

void interfaceGraphique::EchiquierWindow::retirerBordureCase(int id) {
	vecteursCases[id]->setFlat(false);
	vecteursCases[id]->setStyleSheet("QPushButton{ border-width: 5px; border-style: solid; border-color: transparent transparent transparent transparent; }");
}

void interfaceGraphique::EchiquierWindow::modifierCouleurCase(int id) {
	vecteursCases[id]->setFlat(false);
	vecteursCases[id]->setStyleSheet("QPushButton { background-color: rgb(230,83,83); }");

	
	
}
void interfaceGraphique::EchiquierWindow::couleurCaseOriginale(int id) {
	
	vecteursCases[id]->setFlat(true);
	vecteursCases[id]->setStyleSheet("QPushButton { background-color: transparent }");
}
void interfaceGraphique::EchiquierWindow::paintEvent(QPaintEvent* ev) {
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