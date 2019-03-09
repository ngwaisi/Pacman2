#pragma once
template <class S,class T>
class Graphe {
	//Cette m¨¦thode dessine toutes les ar¨ºtes du graphe sur fenetre. 
	template< class FENETRE>
	bool dessineToutesAretes(FENETRE & fenetre) const;

	/**
dessine tous les sommets du graphe de mani¨¨re ind¨¦pendante de la librairie graphique utilis¨¦e

Attention ! ici, FENETRE repr¨¦sente n'importe quelle classe munie de la m¨¦thode appel¨¦e.
On n'a pas forc¨¦ment FENETRE == Fenetre<S,T> !
Cette solution est plus g¨¦n¨¦rale
renvoie true en cas de succ¨¨s complet, false en cas d'¨¦chec partiel
*/

	template<class FENETRE>
	dessineTousSommets(FENETRE fenetre)


	/**
Dessine une ar¨ºte du graphe. Exemples :  nom, couleur, informations associ¨¦es, etc.
renvoie true en cas de succ¨¨s, false en cas d'¨¦chec
*/

	template <class S, class T>
	bool dessine(const Arete<S, T> * arete);
 



};