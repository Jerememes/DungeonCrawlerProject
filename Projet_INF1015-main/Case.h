/**
* Projet de INF1015 : Livrable 2
* \file   Case.h
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include "Composante.h"
#include "Objet.h"

class Case : public Composante
{
public:
	Case() = default;
	Case(const std::string& nom, 
		 const std::string& description, 
		 const bool& estCache = false);

	const std::string          obtenirNom()		    const;
	const std::string          obtenirDescription() const;
	const bool		           obtenirEstCache()    const;
	const std::vector<Objet*>& obtenirObjets();
	Case* obtenirDirection    (const std::string& direction);

	// On ajoute une autre case au (nord / est / sud / ouest) de la case this.
	void modifierCase         (Case* autreCase,
		                       std::string direction);
	void modifierEstCache     (bool estCache);
	void ajouterObjet         (Objet* objet);

	virtual void look         (std::ostream& os) const override;

protected:
	std::map<std::string, Case*> directions_ = 
	{
		{"Est",   nullptr},
		{"Nord",  nullptr},
		{"Ouest", nullptr},
		{"Sud",   nullptr},
	};

	std::vector<Objet*> objets_;
};

