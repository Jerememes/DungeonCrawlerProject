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