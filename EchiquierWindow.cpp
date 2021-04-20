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

using iter::range;

template <typename T>
QPushButton* EchiquierWindow::nouveauBouton(const QString& text, const T& slot)
{
	auto bouton = new QPushButton(this);
	bouton->setText(text);
	bouton->setFixedSize(100, 100);
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
	layout->setSpacing(0);
	layout->setMargin(0);
	auto groupeBoutons = new QButtonGroup(this);
	int indexLigne = 0;
	int indexColonne= 0;
	for (int i : range(64)) {
		auto buton = nouveauBouton(QString::number(i));
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