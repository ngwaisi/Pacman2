#pragma once
#ifndef FENETREGRAPHESFMLAVECAXESREPEREMONDE_H
#define FENETREGRAPHESFMLAVECAXESREPEREMONDE_H

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/VertexArray.hpp>
//#include <SFML/Graphics/Vertex.hpp>
#include<SFML/GRAPHICS/CircleShape.hpp>
#include<SFML/GRAPHICS/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "FenetreGrapheSFML.h"
#include  "Sommet.h"
#include "Arete.h"
//#include<InfosGrapheDessin.h>
//#include <InfoSommet.h>
//#include <InfoArete.h>
#include  "TransfoAffine2D.h"

using namespace sf;
using namespace std;
class FenetreGrapheSFMLAvecAxesRepereMonde : public FenetreGrapheSFML
{
	const Font & font2;

public:

	/**
	Crée la fenêtre qui va contenir le dessin du graphe.

	DONNEES : titre : titre de la fenêtre
			  fondCarte : couleur du fond de la scène au formar RGBA
			  coinBG : coin Bas Gauche de la scène en coordonnées monde
			  coinHD : coin Haut Droit de la scène en coordonnées monde
			  largeur : largeur de la fenêtre écran (en pixels)
			  hauteur : hauteur de la fenêtre écran (en pixels)
			  font1 : police ?utiliser pour les annotations sur les sommets
			  font2 : police ?utiliser pour les annotations sur les axes du repère
	*/

	FenetreGrapheSFMLAvecAxesRepereMonde(const string & titre, unsigned int fondCarte,
		const Vecteur2D & coinBG, const Vecteur2D & coinHD,
		const int largeur, const int hauteur, const Font & font1, const Font & font2) :
		FenetreGrapheSFML(titre, fondCarte, coinBG, coinHD, largeur, hauteur, font1), font2(font2)
	{
		//------------ on va dessiner les axes du repère avec les annotations usuelles O, I et J -------------

		//---------- d'abord on définit les points utiles

		Vecteur2D O, I(1, 0), J(0, 1);
		Vecteur2D A0(coinBG.x, 0), A1(coinHD.x, 0);	// restriction de l'axe des abscisses au rectangle monde
		Vecteur2D B0(0, coinBG.y), B1(0, coinHD.y);	// restriction de l'axe des ordonnées au rectangle monde

		//---------------- on passe des coordonnées monde ---> écran

		O = t.applique(O);
		I = t.applique(I);
		J = t.applique(J);

		A0 = t.applique(A0);
		A1 = t.applique(A1);

		B0 = t.applique(B0);
		B1 = t.applique(B1);

		//-------------------- on dessine les 2 axes --------------------------------

		VertexArray axeAbscisses(PrimitiveType::Lines);

		axeAbscisses.append(Vertex(vecteur2DToVector2f(A0), Color::Black));
		axeAbscisses.append(Vertex(vecteur2DToVector2f(A1), Color::Black));

		fenetre.draw(axeAbscisses);

		VertexArray axeOrdonnees(PrimitiveType::Lines);

		axeOrdonnees.append(Vertex(vecteur2DToVector2f(B0), Color::Black));
		axeOrdonnees.append(Vertex(vecteur2DToVector2f(B1), Color::Black));

		fenetre.draw(axeOrdonnees);

		//------------------------------ on dessine les points O, I et J

		float rayonPointPixels = 4;
		Vecteur2D u(1, 1);

		Vecteur2D ru = rayonPointPixels * u;

		CircleShape O1(rayonPointPixels);
		O1.setFillColor(Color::Red);
		O1.setPosition(vecteur2DToVector2f(O - ru));
		fenetre.draw(O1);
		O1.setPosition(vecteur2DToVector2f(I - ru));
		fenetre.draw(O1);
		O1.setPosition(vecteur2DToVector2f(J - ru));
		fenetre.draw(O1);

		//----------------- on dessine les annotations -----------------------

		unsigned int tailleEnPixels = 12;
		Text annotation("O", font2, tailleEnPixels);
		annotation.setFillColor(Color::Red);
		double d = 2 * rayonPointPixels;
		Vecteur2D v(1, -1);
		annotation.setPosition(vecteur2DToVector2f(O + d * v));
		fenetre.draw(annotation);

		annotation.setString("I");
		annotation.setPosition(vecteur2DToVector2f(I + d * v));
		fenetre.draw(annotation);

		annotation.setString("J");
		annotation.setPosition(vecteur2DToVector2f(J + d * v));
		fenetre.draw(annotation);

		// on  pourrait optimiser les lignes de calcul ci-dessus pour éviter quelques répétitions ----------------

	}
};


#endif