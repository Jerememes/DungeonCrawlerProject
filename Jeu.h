/**
* Projet de INF1015 : Livrable 2
* \file   main.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#pragma once

#include <utility>

#include "PositionJoueur.h"

class Jeu
{
public:
	Jeu() = default;
	Jeu(PositionJoueur& caseCourante);

	void jouer             (std::ostream& os, 
			                std::istream& is, 
			                std::string nom, 
			                std::string edition);

	void nomJeu            (std::ostream& os, 
		 	                std::string nom, 
			                std::string edition);

	void commandeDirection (std::ostream& os, 
						    std::string commande);

	void commandeLook      (std::ostream& os, 
					        std::string nomJeu = "");

	void commandeUse       (std::ostream& os, 
					        std::string nomJeu);

	void commandeExit      (std::ostream& os);

private:
	PositionJoueur positionActuelle_;
	bool estJoue_ = true;

	const std::unordered_map<std::string, std::string> commandesDirection_ =
	{
		{"N", "Je me dirige vers le Nord\n\n"},
		{"E", "Je me dirige vers l'Est\n\n"},
		{"S", "Je me dirige vers le Sud\n\n"},
		{"O", "Je me dirige vers l'Ouest\n\n"}
	};

	std::unordered_map<
		std::string,
		std::function<void(std::ostream& os, std::string nomJeu)>> commandes_ =
	{
		{"N",    [this](std::ostream& os, std::string nomJeu) 
					   {commandeDirection(os, "N"); }},
		{"E",    [this](std::ostream& os, std::string nomJeu) 
					   {commandeDirection(os, "E"); }},
		{"S",    [this](std::ostream& os, std::string nomJeu) 
					   {commandeDirection(os, "S"); }},
		{"O",    [this](std::ostream& os, std::string nomJeu) 
					   {commandeDirection(os, "O"); }},
		{"look", [this](std::ostream& os, std::string nomJeu) 
					   {commandeLook(os, nomJeu); }},
		{"use",  [this](std::ostream& os, std::string nomJeu) 
					   {commandeUse(os, nomJeu); }},
		{"exit", [this](std::ostream& os, std::string nomJeu) 
					   {commandeExit(os); }}
	};

	std::pair<std::string, std::string> separerCommande(std::string ligne);

	bool verifierCommandeDansNomObjet(std::string nomObjet, 
									  std::string nomJeu);
};

