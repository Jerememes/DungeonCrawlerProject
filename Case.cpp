/**
* Projet de INF1015 : Livrable 2
* \file   Case.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#include "Case.h"

Case::Case(const std::string& nom, 
		   const std::string& description, 
	       const bool& estCache) : 
		   Composante(nom, description, estCache)
{}

const std::vector<Objet*>& Case::obtenirObjets()
{
	return objets_;
}

Case* Case::obtenirDirection(const std::string& direction)
{
	for (auto const& [directionCase, caseVoisine] : directions_)
		if (directionCase.find(direction) != std::string::npos)
			return caseVoisine;
	return nullptr;
}

void Case::modifierCase(Case* autreCase,
					 	 std::string direction)
{
	for (auto const& [directionCase, caseVoisine] : directions_)
		if (directionCase.find(direction) != std::string::npos)
			directions_[directionCase] = autreCase;
}

void Case::ajouterObjet(Objet* objet)
{
	objets_.push_back(objet);
}

void Case::look(std::ostream& os) const
{
	os << "-- " << nom_ << " --" << std::endl
		<< description_ << std::endl;

	for (auto const& [direction, caseVoisine] : directions_)
		if (caseVoisine != nullptr && !caseVoisine->estCache_)
			os << caseVoisine->nom_ <<  " est à "   << 
			      direction         << " ("         << 
			      direction[0]      << ")"          <<
			      std::endl;

	if (!objets_.empty())
		os << "Vous remarquez :" << std::endl;

	for (Objet* objet : objets_)
		if (!objet->obtenirEstCache())
			objet->afficherNom(os);
}