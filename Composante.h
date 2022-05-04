/**
* Projet de INF1015 : Livrable 2
* \file   Carte.h
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#pragma once

#include <string>
#include <iostream>
#include <memory>

class Composante
{
public:
	Composante() = default;
	Composante (const std::string& nom, 
			    const std::string& description, 
			    const bool& estCache);

	virtual	~Composante() = default;

	virtual void			  look(std::ostream& os) const = 0;
	virtual const std::string obtenirNom()			 const;
	virtual const std::string obtenirDescription()	 const;
	virtual const bool		  obtenirEstCache()		 const;
	virtual void			  modifierEstCache(bool estCache);

protected:
	std::string nom_;
	std::string description_;
	bool estCache_;
};