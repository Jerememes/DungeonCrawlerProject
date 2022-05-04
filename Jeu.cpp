/**
* Projet de INF1015 : Livrable 2
* \file   main.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#include "Jeu.h"

Jeu::Jeu(PositionJoueur& caseCourante)
{
	positionActuelle_ = caseCourante;
}

void Jeu::jouer(std::ostream& os, 
	            std::istream& is,
	            std::string nom, 
	            std::string edition)
{
	positionActuelle_.initialiserCarte();

	nomJeu(os, nom, edition);

	std::string commandeEntree;

	while (estJoue_)
	{
		os << "\n> ";
		std::getline(is, commandeEntree);
		std::pair commande = separerCommande(commandeEntree);
		try
		{
			if (commandes_.count(commande.first) == 0)
				throw std::out_of_range ("Je ne connais pas cette commande.\n");
			commandes_[commande.first](os, commande.second);
		}
		catch (std::out_of_range& erreur)
		{
			os << erreur.what();
		}
	}
}

void Jeu::nomJeu(std::ostream& os,
				 std::string nom,
				 std::string edition)
{
	os << ">>>>>>>>>>> " << nom << " <<<<<<<<<<<" << std::endl;
	os << "> > > > " << edition << " < < < <" << std::endl << std::endl;
	positionActuelle_.obtenirCaseCourante()->look(os);
}

void Jeu::commandeDirection(std::ostream& os,
							std::string commande)
{
	try
	{
		if (positionActuelle_.prochaineCase(commande))
		{
			os << commandesDirection_.at(commande);
			commandeLook(os);
		}
		else
			throw std::invalid_argument("Je ne peux pas aller là.\n");
	}
	catch (std::invalid_argument& erreur)
	{
		os << erreur.what();
	}
}

void Jeu::commandeLook(std::ostream& os, 
					   std::string nomJeu)
{
	if (nomJeu.empty())
		positionActuelle_.obtenirCaseCourante()->look(os);
	else
	{
		try
		{
			positionActuelle_.lookObjet(os, [nomJeu, this](const Objet* objet)
				{ 
					return verifierCommandeDansNomObjet
					       (objet->obtenirNom(), nomJeu); 
				}
			);
		}
		catch (std::out_of_range& erreur)
		{
			os << erreur.what();
		}
	}
}

void Jeu::commandeUse(std::ostream& os, 
					  std::string nomJeu)
{
	if (nomJeu.empty())
		os << "Vous devez spécifier l'objet à utiliser." << std::endl;
	else
	{
		try
		{
			positionActuelle_.useObjet(os, [nomJeu, this](const Objet* objet) 
			{ return verifierCommandeDansNomObjet
			         (objet->obtenirNom(), nomJeu); 
			});
		}
		catch (std::out_of_range& erreur)
		{
			os << erreur.what();
		}
	}
}

void Jeu::commandeExit(std::ostream& os)
{
	os << "D'accord, je m'en vais! À la prochaine!" << std::endl;
	estJoue_ = false;
}

std::pair<std::string, std::string> Jeu::separerCommande(std::string ligne)
{
	std::string commande = ligne.substr(0, ligne.find(' '));

	if (ligne.find(' ') < ligne.length())
		ligne.erase(0, ligne.find(' ') + 1);
	else
		ligne = "";
	return { commande, ligne };
}

bool Jeu::verifierCommandeDansNomObjet(std::string nomObjet, 
									   std::string nomJeu)
{
	std::vector<std::string> mots;
	std::string motTemporaire = "";
	for (char caractere : nomObjet)
	{
		if (caractere == ' ')
		{
			mots.push_back(motTemporaire);
			motTemporaire = "";
		}
		else
			motTemporaire += caractere;
	}
	mots.push_back(motTemporaire);

	for (std::string mot : mots)
	{
		if (nomJeu.find(mot) != std::string::npos)
			return true;
	}
	return false;
}