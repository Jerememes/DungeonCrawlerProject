/**
* Projet de INF1015 : Livrable 2
* \file   Case.h
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#include "Objet.h"

Objet::Objet(const std::string& nom, 
	         const std::string& description,
	         const std::string& utilisation, 
	         const bool& estCache) : 
	         Composante(nom, description, estCache)
{
	utilisation_ = utilisation;
}

void Objet::afficherNom(std::ostream& os) const
{
	os << "\t" << nom_ << std::endl;
}

void Objet::look(std::ostream& os) const
{
	os << description_ << std::endl;
}

void Objet::use(std::ostream& os)
{
	os << utilisation_ << std::endl;
}