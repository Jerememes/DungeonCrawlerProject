/**
* Projet de INF1015 : Livrable 2
* \file   Case.h
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#pragma once

#include "Composante.h"

class Objet : public Composante
{
public:
	Objet() = default;
	Objet(const std::string & nom, 
		  const std::string & description, 
		  const std::string & utilisation, 
		  const bool& estCache = false);

	virtual void      look(std::ostream& os) const override;
	virtual void      use(std::ostream& os);
	void              afficherNom(std::ostream& os) const;

private:
	std::string utilisation_;
};

