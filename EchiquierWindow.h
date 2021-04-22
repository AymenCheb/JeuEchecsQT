#pragma once
#include "EchiquierGraphique.h"
#include "interfaceMediateur.h"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

// Cette classe représente la fenetre graphique de l'application
namespace interfaceGraphique {

	class EchiquierWindow : public QMainWindow {
		Q_OBJECT
	public:
		EchiquierWindow(QWidget* parent = nullptr);
		~EchiquierWindow() override = default;
		virtual void paintEvent(QPaintEvent* event);
		// Cette fonction lie le mediateur de l'échiquier graphique au modèle echiquier
		void lierEchiquier(modele::Echiquier* echiquier) { echiquierGraphique_.mediateur.lierEchiquier(echiquier); };
		void modifierContenuCase(int id, string typePiece, string couleurEquipe);
		void modifierCouleurCase(int id);
		void couleurCaseOriginale(int id);
		void modifierBordureCase(int id);
		void retirerBordureCase(int id);
	public slots:

	private:
		template <typename T = decltype(nullptr)>
		QPushButton* nouveauBouton(const QString& text, const T& slot = nullptr);
		EchiquierGraphique echiquierGraphique_;
		QLabel* affichage_;
		QVector<QPushButton*> vecteursCases;
	};
}