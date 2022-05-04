/**
* Projet de INF1015 : Livrable 2
* \file   Carte.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#include "Carte.h"

Carte& Carte::operator=(const Carte&)
{
	return *this;
}

Case* Carte::obtenirCaseDepart()
{
	return caseDepart_;
}

Case* Carte::obtenirCase(const std::string& nom)
{
	for (auto&& piece : carte_)
		if (piece->obtenirNom() == nom)
			return piece.get();
	return nullptr;
}

Composante* Carte::obtenirComposante(const std::string& nom)
{
	for (auto&& piece : carte_)
		if (piece->obtenirNom() == nom)
			return piece.get();

	for (auto&& objet : objets_)
		if (objet->obtenirNom() == nom)
			return objet.get();

	return nullptr;
}

void Carte::modifierCaseDepart(std::unique_ptr<Case> caseDepart)
{
	caseDepart_ = caseDepart.get();
	carte_.push_back(move(caseDepart));
}

void Carte::ajouterCase(std::unique_ptr<Case> piece)
{
	carte_.push_back(move(piece));
}

void Carte::ajouterObjet(std::unique_ptr<Objet> objet, 
	                     const std::string& nomCase)
{
	Case* piece = obtenirCase(nomCase);
	piece->ajouterObjet(objet.get());
	objets_.push_back(move(objet));
}

void Carte::connecterCases(const std::string& nomA, 
	                       const std::string& nomB, 
	                       const std::string& direction)
{
	Case* caseA = obtenirCase(nomA);
	Case* caseB = obtenirCase(nomB);

	caseA->modifierCase(caseB, direction);
	caseB->modifierCase(caseA, directionsOpposees_.at(direction));
}

void Carte::relierObjetComposante(const std::string& nomObjet,
								  const std::string& nomComposante)
{
	Composante* composante = obtenirComposante(nomComposante);
	composantesCachees_.insert({ nomObjet, composante });
}

bool Carte::verifierComposanteVisible(const std::string& nomObjet)
{
	return composantesCachees_.count(nomObjet);
}

void Carte::modifierComposanteVisible(const std::string& nomObjet)
{
	composantesCachees_.at(nomObjet)->modifierEstCache(false);
	composantesCachees_.erase(nomObjet);
}