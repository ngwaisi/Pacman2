#ifndef FENETREGRAPHESFML_H
#define FENETREGRAPHESFML_H

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/VertexArray.hpp>
//#include <SFML/Graphics/Vertex.hpp>
#include<SFML/GRAPHICS/CircleShape.hpp>
#include<SFML/GRAPHICS/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "VSommet.h"
#include "Arete.h"
//#include "InfosGrapheDessin.h"
//#include <InfoSommet.h>
//#include <InfoArete.h>
#include"Peinture.h"
#include "TransfoAffine2D.h"
#include "Vecteur2D.h"
using namespace sf;
using namespace std;

/**
Prend en charge le dessin d'un graphe.
Suppose que les coordonn閑s des sommets sont d閒inies par rapport au rep鑢e Monde.
Prend en charge le passage fen阾re-cl魌ure
*/


inline const Vector2f vecteur2DToVector2f(const Vecteur2D & v) { float x, y; v.arrondit(x, y); return Vector2f(x, y); }


/**

vSommet : en coordonn閑s monde
*/
inline bool dessinePetitRond(RenderWindow & fenetre, const TransfoAffine2D & t, const VSommet & vSommet, const Font & font,
	const Vecteur2D & deltaTextePixels = Vecteur2D(VSommet::rayonDisquePixels, VSommet::rayonDisquePixels))
{
	Vecteur2D position = t.applique(vSommet.p);
	Vecteur2D position1 = position - VSommet::rayonDisquePixels*Vecteur2D(1, 1);

	// si on appliquait la transfo t globalement ?tout le graphe avant de commencer ?dessiner, on optimiserait
	// bcp de calculs !!!!

	CircleShape disque((float)VSommet::rayonDisquePixels);
	disque.setFillColor(Color(vSommet.couleur));
	float epaisseurBord = (float)(0.15*VSommet::rayonDisquePixels);
	disque.setOutlineThickness(epaisseurBord);
	disque.setOutlineColor(Color(VSommet::couleurBord));

	Vector2f p1 = vecteur2DToVector2f(position1);

	disque.setPosition(p1);

	fenetre.draw(disque);

	Vecteur2D position2 = position - deltaTextePixels;
	unsigned int tailleEnPixels = 17;
	Text texte(vSommet.nom, font, tailleEnPixels);
	texte.setFillColor(Color::Black);
	texte.setPosition(vecteur2DToVector2f(position2));
	fenetre.draw(texte);
	return true;
}

/**
d閎ut et fin sont en coordonn閑s monde
*/
inline bool dessineSegment(RenderWindow & fenetre, const TransfoAffine2D & t, const unsigned int couleur,
	const Vecteur2D & debut, const Vecteur2D & fin, const unsigned int epaisseurTraitPixels = 2)
{
	// on va dessiner un rectangle tr鑣 fin pour repr閟enter l'ar阾e

	Vecteur2D A, B;	// {AB] est l'ar阾e ?repr閟enter

	A = t.applique(debut); B = t.applique(fin);		// on passe des coordonn閑s monde aux coordonn閑s 閏ran

	Vecteur2D u = B - A;

	double nU = norme(u);
	u /= nU;
	Vecteur2D  n = u.rotationDirecteQuartDeTour();

	//double e = 1;	// 閜aisseur du rectangle = 2*e. longueur du rectangle == AB
	double e = 0.5*epaisseurTraitPixels;	// 閜aisseur du rectangle = 2*e. longueur du rectangle == AB


	Vecteur2D v = e * n;

	Vecteur2D A0 = A - v, A1 = B - v, A2 = B + v, A3 = A + v; // on calcule les 4 sommets du rectangle dont l'ar阾e [AB] est un axe de sym閠rie

	Vector2f F0 = vecteur2DToVector2f(A0);
	Vector2f F1 = vecteur2DToVector2f(A1);
	Vector2f F2 = vecteur2DToVector2f(A2);
	Vector2f F3 = vecteur2DToVector2f(A3);

	ConvexShape rectangle(4);
	rectangle.setPoint(0, F0);
	rectangle.setPoint(1, F1);
	rectangle.setPoint(2, F2);
	rectangle.setPoint(3, F3);

	rectangle.setFillColor(Color(couleur));
	fenetre.draw(rectangle);

	return true;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
Prend en charge le dessin d'un graphe
Prend en charge le passage de coordonn閑s monde ---> 閏ran
*/
class FenetreGrapheSFML
{
public:
	RenderWindow fenetre;
	const Font & font;


	TransfoAffine2D t;	// r閍lise le passage fen阾re-cl魌ure (ou encore monde vers 閏ran)
	/**
	Cr閑 la fen阾re qui va contenir le dessin du graphe.

	DONNEES : titre : titre de la fen阾re
			  fondCarte : couleur du fond de la sc鑞e au formar RGBA
			  coinBG : coin Bas Gauche de la sc鑞e en coordonn閑s monde
			  coinHD : coin Haut Droit de la sc鑞e en coordonn閑s monde
			  largeur : largeur de la fen阾re 閏ran (en pixels)
			  hauteur : hauteur de la fen阾re 閏ran (en pixels)
			  font : police ?utiliser pour les annotations sur les sommets

	*/
	FenetreGrapheSFML(const string & titre, const unsigned int fondCarte,
		const Vecteur2D & coinBG, const Vecteur2D & coinHD,
		const int largeur, const int hauteur, const Font & font) :
		fenetre(sf::VideoMode(largeur, hauteur), titre), font(font)
	{
		fenetre.clear(Color(fondCarte));
		// calcul de la transformation affine - changement de rep鑢e : monde ---> 閏ran
		Vecteur2D coinEcranBG(0, hauteur), coinEcranHD(largeur, 0);
		t = TransfoAffine2D::passageMondeEcran(coinBG, coinHD, coinEcranBG, coinEcranHD);
	}
	
	template <class T>
	bool dessine(const Sommet<T> * sommet);

	template <class T>
	bool dessine(const Sommet<T> * debut, const Sommet<T> * fin, unsigned int couleur);

	template <class S, class T>
	bool dessine(const Arete<S, T> * arete);


};

template <>
bool FenetreGrapheSFML::dessine<VSommet>(const Sommet<VSommet> * sommet)
{
	return dessinePetitRond(this->fenetre, this->t, sommet->v, this->font);	
}

/*
{
Vecteur2D position = t.applique(sommet->v.p)-VSommet::rayonDisquePixels*Vecteur2D(1,1);

// si on appliquait la transfo t globalement ?tout le graphe avant de commencer ?dessiner, on optimiserait
// bcp de calculs !!!!

CircleShape disque((float)VSommet::rayonDisquePixels);
disque.setFillColor(Color(sommet->v.couleur));
float epaisseurBord = (float)(0.15*VSommet::rayonDisquePixels);
disque.setOutlineThickness(epaisseurBord);
disque.setOutlineColor(Color(VSommet::couleurBord));
float x,y;
position.arrondit(x,y);

disque.setPosition(x, y);

fenetre.draw(disque);

unsigned int tailleEnPixels = 15;
Text texte(sommet->v.nom, font,tailleEnPixels);
texte.setFillColor(Color::Black);
texte.setPosition(x,y);
fenetre.draw(texte);
return true;
}
*/

template <>
bool FenetreGrapheSFML::dessine<Peinture, VSommet>(const Arete<Peinture, VSommet> * arete)
{
	dessineSegment(this->fenetre, this->t, arete->v.fond, arete->debut->v.p, arete->fin->v.p);
	return dessineSegment(this->fenetre, this->t, arete->v.devant, arete->debut->v.p, arete->fin->v.p);
}

/*{
// on va dessiner un rectangle tre fin pour repreenter l'arte

Vecteur2D A(arete->debut->v.p), B(arete->fin->v.p);	// {AB] est l'ar阾e ?repr閟enter

A = t.applique(A); B = t.applique(B);		// on passe des coordonn閑s monde aux coordonn閑s 閏ran

Vecteur2D u = B-A;

double nU = norme(u);
u /=nU;
Vecteur2D  n = u.rotationDirecteQuartDeTour();

double e = 1;	// 閜aisseur du rectangle = 2*e. longueur du rectangle == AB

Vecteur2D v = e*n;

Vecteur2D A0= A-v,A1 = B-v, A2 = B+v,A3 = A+v; // on calcule les 4 sommets du rectangle dont l'ar阾e [AB] est un axe de sym閠rie

Vector2f F0 = vecteur2DToVector2f(A0);
Vector2f F1 = vecteur2DToVector2f(A1);
Vector2f F2 = vecteur2DToVector2f(A2);
Vector2f F3 = vecteur2DToVector2f(A3);

ConvexShape rectangle(4);
rectangle.setPoint(0,F0);
rectangle.setPoint(1,F1);
rectangle.setPoint(2,F2);
rectangle.setPoint(3,F3);

rectangle.setFillColor(Color(arete->v.fond));
fenetre.draw(rectangle);
rectangle.setFillColor(Color(arete->v.devant));
fenetre.draw(rectangle);

return true;
}*/

//---------------------------------------dessine le cas particulier de InfoSommet et InfoArete ------------------------------

/* *
Dessine un sommet du graphe. Exemples :  nom, couleur, informations associ閑s, etc.
renvoie true en cas de succ鑣, false en cas d'閏hec
On suppose que les coordonn閑s du sommet sont d閒inies par rapport au rep鑢e du monde
* /
template <>
bool FenetreGrapheSFML::dessine<InfoSommet>(const Sommet<InfoSommet> * sommet)
{
return dessinePetitRond(this->fenetre, this->t, sommet->v.vSommet, this->font);
}

/ **
Dessine un ar阾e du graphe. Exemples :  nom, couleur, informations associ閑s, etc.
renvoie true en cas de succ鑣, false en cas d'閏hec
On suppose que les coordonn閑s des sommets sont d閒inies par rapport au rep鑢e du monde
* /
template <>
bool FenetreGrapheSFML::dessine<InfoArete,InfoSommet>(const Arete<InfoArete,InfoSommet> * arete)
{
return dessineSegment( this->fenetre, this->t, arete->v.couleur, arete->debut->v.vSommet.p, arete->fin->v.vSommet.p);
}
*/


//----------------------------------------------------------------------------------
/**
par rapport ?la classe de base, cette fen阾re dessine en plus les axes du rep鑢e monde

*/
 
#endif // FENETRE_H
 


