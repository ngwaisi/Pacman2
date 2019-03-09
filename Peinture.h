#ifndef PEINTURE_H_INCLUDED
#define PEINTURE_H_INCLUDED

#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
class Peinture
{
public:
	unsigned int fond;		// couleur du fond (ou sous-couche de peinture)
	unsigned int devant;	// couleur masquant  la couleur du fond. ou derni¨¨re couche de peinture.
							// Elle masque pas du tout, partiellement ou enti¨¨rement la couleur du fond
	Peinture(const unsigned int couleurFond, const unsigned int couleurDevant) : fond(couleurFond), devant(couleurDevant) {}

	virtual operator string () const { ostringstream o; o << "( " << fond << ", " << devant << ")"; return o.str(); }

	friend ostream & operator << (ostream & o, const Peinture & peinture) { return o << (string)peinture; }
};


#endif 