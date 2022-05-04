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

class Carte
{
public:
	Carte()  = default;
	~Carte() = default;

	Carte& operator=(const Carte&);

	Case* obtenirCaseDepart();
	Case* obtenirCase			   (const std::string& nom);
	Objet* obtenirObjet			   (const std::string& nom);

	void modifierCaseDepart		   (std::unique_ptr<Case> caseDepart);
	void ajouterCase			   (std::unique_ptr<Case> piece);
	void ajouterObjet			   (std::unique_ptr<Objet> objet, 
									const std::string& nomCase);

	void connecterCases			   (const std::string& nomA, 
								    const std::string& nomB, 
								    const std::string& direction);

	// Méthodes concernant la case cachée.
	void relierObjetCase            (const std::string& nomObjet, 
						             const std::string& nomCase);
	bool verifierCaseEstDeverouillee(const std::string& nomObjet);
	void modifierCaseVisible        (const std::string& nomObjet);

	// Méthodes concernant l'objet non visible.
	void relierObjetObjet			(const std::string& nomObjet, 
									 const std::string& nomObjetCache, 
										   std::string message);
	std::string obtenirMessage		(const std::string& nomObjet);
	bool verifierObjetEstVisible	(const std::string& nomObjet);
	void modifierObjetVisible		(const std::string& nomObjet);


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

	// Le nom de l'objet est relié à une case cachée.
	std::unordered_map<std::string, Case*> casesCachees_;

	// Le nom de l'objet A est relié à l'objet B et au message à afficher lorsqu'on use l'objet A.
	std::unordered_map<std::string, std::pair<Objet*, std::string>> objetCaches_;
};

