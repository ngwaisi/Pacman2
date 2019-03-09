#ifndef MATRICE22_H
#define MATRICE22_H

#include <iostream>
#include<sstream>
#include<string>
#include<math.h>
#include "Vecteur2D.h"


using namespace std;

class Matrice22
{

public:
	Vecteur2D ligneHaut, ligneBas;

	Matrice22(const Vecteur2D& ligneHaut,
		const Vecteur2D& ligneBas) : ligneHaut(ligneHaut), ligneBas(ligneBas) {}

	/**
	matrice identit?par défaut

	*/
	explicit Matrice22(const double & a00 = 1, const double & a01 = 0,
		const double & a10 = 0, const double & a11 = 1) : Matrice22(Vecteur2D(a00, a01), Vecteur2D(a10, a11)) {}



	static const Matrice22 creeMatriceDiagonale(const double & a00, const double & a11) { return Matrice22(a00, 0, 0, a11); }

	/**
	alfa : exprim?en radians

	*/
	static const Matrice22 creeRotation(const double & alfa)
	{
		double cosalfa = cos(alfa);
		double sinalfa = sin(alfa);

		return Matrice22(cosalfa, -sinalfa,
			sinalfa, cosalfa);
	}

	double det() const { return Vecteur2D::det(ligneHaut, ligneBas); }

	const Matrice22 transposee() const
	{
		return Matrice22(ligneHaut.x, ligneBas.x,
			ligneHaut.y, ligneBas.y);
	}

	const Matrice22 cofacteur() const
	{
		return Matrice22(ligneBas.y, -ligneBas.x,
			-ligneHaut.y, ligneHaut.x);
	}

	const Matrice22 operator * (const double & a) const { return Matrice22(a*ligneHaut, a*ligneBas); }


	const Matrice22 operator - () const { return Matrice22(-ligneHaut, -ligneBas); }

	friend const Matrice22 operator * (const double & a, const Matrice22 & m) { return m * a; }

	const Matrice22 inverse() const { double d = this->det(); return this->cofacteur().transposee() / d; }

	const Vecteur2D operator * (const Vecteur2D & u) const { return Vecteur2D(ligneHaut*u, ligneBas*u); }
	friend const Vecteur2D operator * (const Vecteur2D& u, const Matrice22 & m)
	{
		return m.transposee()*u;
	}
	const Matrice22 operator * (const Matrice22 & m) const { return Matrice22(ligneHaut*m, ligneBas*m); }

	operator string () const
	{
		ostringstream o; o << "[" << endl << ligneHaut << endl << ligneBas << endl << "]"; return o.str();
	}

	friend ostream & operator << (ostream & o, const Matrice22 & m) { return o << (string)m; }

};

#endif // MATRICE22_H
