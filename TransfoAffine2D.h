#ifndef TRANSFOAFFINE2D_H
#define TRANSFOAFFINE2D_H


#include "Matrice22.h"

inline int signe(const double & a) { return a >= 0 ? 1 : -1; }

inline const Vecteur2D abs(const Vecteur2D & v) { return Vecteur2D(abs(v.x), abs(v.y)); }

inline const Vecteur2D divisionSpeciale(const Vecteur2D & v1, const Vecteur2D & v2)
{
	return Vecteur2D(v1.x / v2.x, v1.y / v2.y);
}

/**

représente la transformation v |---> M*v + B
*/
class TransfoAffine2D
{
public:
	Matrice22 M;
	Vecteur2D B;

	/**
	par défaut la transformation construite est l'application identit?: v |---> v
	*/
	TransfoAffine2D(const Matrice22 & M = Matrice22(), const Vecteur2D & B = Vecteur2D()) : M(M), B(B) {}
	const Vecteur2D applique(const Vecteur2D & v) const { return M * v + B; }
	const TransfoAffine2D inverse() const { Matrice22 M1 = M.inverse(); return TransfoAffine2D(M1, -M1 * B); }

	/**
	 * HYPOTHESES :
	 * Notons
	 * On suppose que {coinBG1, coinHD1} représente la diagonale d'un rectangle R1. ce sont respectivement les coins bas gauche et haut droit de R1
	 * R1 est donn?dans un certain repère Rep1 (O1,i1,j1),
	 * R1 n'est pas dégénér?
	 * On suppose que {coinBG2, coinHD2} représente la diagonale d'un rectangle R2. ce sont respectivement les coins bas gauche et haut droit de R2
	 * R2 est donn?dans un certain repère Rep2 (O2,i2,j2)
	 * R2 n'est pas dégénér?
	 *
	 * On suppose qu'on peut transformer  R1 en  R2 sans rotation, c'est-?dire uniquement par translation et/ou étirement sur l'axe x ou sur l'axe y
	 *
	 * Autrement dit, on suppose que i1 et i2 sont colinéaires et j1 et j2 sont aussi colinéaires
	 *
	 *
	 * TACHE :
	 *
	 * Le but est de calculer le changement de repère t qui transforme R1 en R2
	  *
	 * construit donc la transfo affine 2D t tel que :
	 * 1) t(R1) ne soit pas déform?par rapport ?R1
	 * 2) t(R1) soit inclus dans R2 et t(R1) le plus grand possible
	 * 3) t(coinBG1) le plus proche possible de coinBG2
	 * 4) t(coinHD1) le plus proche possible de coinHDD2
	 *
	 * t est de la forme :
	 *
	 * /   \   /                          \   /   \   /    \
	 * | x'|   | Eps1*lambda       0      |   | x |   | b1 |
	 * | y'| = |     0         Eps2*lambda| * | y | + | b2 |
	 * \   /   \                          /   \   /   \    /
	 *
	 * avec |Eps1|=|Eps2|= 1 et lambda > 0
	 *
	 * On construit t telle que que t(C1) = C2 o?Ci est le centre respectif de Ri pour i = 1,2
	 *
	 *
	 * DONNEES : coinBG1, coinHD1, coinBG2, coinHD2
	 *
	 * RESULTATS : t telle que si P = [X] dans Rep1 et P = [X'] dans Rep2 alors t(X) = X'
	 *
	 * */
	inline static const TransfoAffine2D passageMondeEcran(const Vecteur2D & coinBG1, const Vecteur2D & coinHD1,
		const Vecteur2D & coinBG2, const Vecteur2D & coinHD2)
	{
		Vecteur2D A1B1 = coinHD1 - coinBG1;
		Vecteur2D A2B2 = coinHD2 - coinBG2;

		//---------- on cherche lambda --------------------

		Vecteur2D q = divisionSpeciale(A2B2, A1B1);

		Vecteur2D vq = abs(q);

		double lambda = min(vq.x, vq.y);

		//----------------- on cherche Eps1 et Eps2 ----------------------

		double Eps1 = signe(q.x), Eps2 = signe(q.y);

		Matrice22 M(Eps1*lambda, 0,
			0, Eps2*lambda);

		// ------------------------ on cherche B ---------------------------

		Vecteur2D C1 = 0.5*(coinBG1 + coinHD1);
		Vecteur2D C2 = 0.5*(coinBG2 + coinHD2);

		Vecteur2D B = C2 - M * C1;

		//------------- c'est fini, on crée t -------------------

		return TransfoAffine2D(M, B);
	}
};

#endif // TRANSFOAFFINE2D_H
