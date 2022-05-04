/**
* Projet de INF1015 : Livrable 2
* \file   Composante.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#include "Composante.h"

Composante::Composante(const std::string& nom, 
	                   const std::string& description, 
					   const bool& estCache)
{
	nom_ = nom;
	description_ = description;
	estCache_ = estCache;
}

const std::string Composante::obtenirNom() const
{
	return nom_;
}

const std::string Composante::obtenirDescription() const
{
	return description_;
}

const bool Composante::obtenirEstCache() const
{
	return estCache_;
}

void Composante::modifierEstCache(bool estCache)
{
	estCache_ = estCache;
}