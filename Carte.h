/**
* Projet de INF1015 : Livrable 2
* \file   Carte.h
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#pragma once
#include <unordered_map>

#include "Case.h"
#include "ObjetDeverouillant.h"

class Carte
{
public:
	Carte()  = default;
	~Carte() = default;

	Carte& operator=(const Carte&);

	Case* obtenirCaseDepart();
	Case* obtenirCase			   (const std::string& nom);
	Composante* obtenirComposante  (const std::string& nom);

	void modifierCaseDepart		   (std::unique_ptr<Case> caseDepart);
	void ajouterCase			   (std::unique_ptr<Case> piece);
	void ajouterObjet			   (std::unique_ptr<Objet> objet, 
									const std::string& nomCase);

	void connecterCases			   (const std::string& nomA, 
								    const std::string& nomB, 
								    const std::string& direction);

	void relierObjetComposante	   (const std::string& nomObjet,
								    const std::string& nomComposante);
	bool verifierComposanteVisible (const std::string& nomObjet);
	void modifierComposanteVisible (const std::string& nomObjet);

private:
	Case* caseDepart_ = nullptr;
	std::vector<std::unique_ptr<Case>> carte_;
	std::vector<std::unique_ptr<Objet>> objets_;

	const std::unordered_map<std::string, std::string> directionsOpposees_ =
	{
		{"N", "S"},
		{"E", "O"},
		{"S", "N"},
		{"O", "E"},
	};

	// Le nom de l'objet est relié à une case ou objet caché.
	std::unordered_map<std::string, Composante*> composantesCachees_;
};

