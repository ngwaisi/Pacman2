#pragma once
#include "Arete.h"
#include "Sommet.h"
class Fenetre {

	template <class S,class T>
	bool dessine(Arete<S, T> arete);
	template <class S, class T>
	bool dessine(Sommet<T> sommet);
};