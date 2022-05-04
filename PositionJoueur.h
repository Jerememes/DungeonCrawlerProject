/**
* Projet de INF1015 : Livrable 2
* \file   PositionJoueur.h
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#pragma once

#include "Carte.h"

class PositionJoueur
{
public:
	PositionJoueur() = default;
	PositionJoueur(Carte& carte);

	Case* obtenirCaseCourante() const;
	void initialiserCarte();
	
	// La méthode retourne true si on peut changer de case, sinon elle retourne false.
	bool prochaineCase (std::string direction);

	void lookObjet	   (std::ostream& os, 
				   	    std::function<bool(const Objet*)> fonction);
	void useObjet	   (std::ostream& os, 
					    std::function<bool(const Objet*)> fonction);

private:
	Case* positionActuelle_ = nullptr;
	Carte carte_;
};