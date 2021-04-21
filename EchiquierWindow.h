#pragma once
#include "EchiquierGraphique.h"
#include "interfaceMediateur.h"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

class EchiquierWindow : public QMainWindow {
	Q_OBJECT
public:
	EchiquierWindow(QWidget* parent = nullptr);
	~EchiquierWindow() override = default;
	virtual void paintEvent(QPaintEvent* event);
	void lierEchiquier(Echiquier* echiquier) { echiquierGraphique_.mediateur.lierEchiquier(echiquier); };
	void modifierContenuCase(int id, string typePiece, string couleurEquipe);
public slots:

private:
	template <typename T = decltype(nullptr)>
	QPushButton* nouveauBouton(const QString& text, const T& slot = nullptr);
	EchiquierGraphique echiquierGraphique_;
	QLabel* affichage_;
	QVector<QPushButton*> vecteursCases;
};