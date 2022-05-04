/**
* Projet de INF1015 : Livrable 2
* \file   PositionJoueur.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 décembre 2021
* Créé le 1 décembre 2021
*/

#include "PositionJoueur.h"

PositionJoueur::PositionJoueur(Carte& carte)
{
	positionActuelle_ = carte.obtenirCaseDepart();
	carte_ = carte;
}

Case* PositionJoueur::obtenirCaseCourante() const
{
	return positionActuelle_;
}

void PositionJoueur::initialiserCarte()
{
	// Initialiser des cases du jeu.
	std::unique_ptr<Case> entree = std::make_unique<Case>
		("Entrée",
		 "Il y a un tapis sur le sol.");

	std::unique_ptr<Case> salon = std::make_unique<Case>
		("Salon",
		 "Il y a un professeur de INF1015 emballé dans un cadeau à côté du sapin de Noël.");

	std::unique_ptr<Case> couloir = std::make_unique<Case>
		("Couloir",
		 "Il y a des boîtes proches du mur ainsi qu'un sabre laser de la guerre des étoiles.");

	std::unique_ptr<Case> petiteChambre = std::make_unique<Case>
		("Petite chambre",
		 "Elle n'est pas particulièrement propre ou organisée. Il y a une petite fenêtre et une affiche murale de Pink Floyd.");

	std::unique_ptr<Case> cuisine = std::make_unique<Case>
		("Cuisine",
		 "Vous remarquez Gordon Ramsey dans la pièce, celui-ci ne veut pas être dérangé. Il cherche la sauce à l'agneau.");

	std::unique_ptr<Case> pieceBlanche = std::make_unique<Case>
		("Pièce blanche",
		 "Cette pièce est constituée de vide intersidéral.",
		  true);

	// Initialiser des objets.
	std::unique_ptr<ObjetDeverouillant> yeezy = std::make_unique<ObjetDeverouillant>
		("Une paire de yeezys",
		 "Les yeezys Boost 350 V2 ont beaucoup trop de style.",
		 "En reniflant les souliers, vous vous rendez compte qu'ils dégagent une odeur néfaste.",
		 "En examinant les souliers, vous découvrez un bitcoin dans ceux-ci!");

	std::unique_ptr<Objet> bitcoin = std::make_unique<Objet>
		("Un bitcoin", 
		 "Wow, c'est un bitcoin, cela va vous rapporter beaucoup de bidous.", 
		 "Vous gardez le bitcoin, vous possédez maintenant 63 128.56 dollars canadien en bitcoin dans votre compte bancaire.", 
		  true);

	std::unique_ptr<ObjetDeverouillant> professeur = std::make_unique<ObjetDeverouillant>
		("Un professeur",
		 "C'est un professeur d'objet orienté qui peut vous aider avec votre travail pratique. il est recouvert d'emballage étrangement.",
		 "Il rajoute un point-virgule à la fin d'une ligne de code et votre code compile par magie.",
		 "Après avoir rajouté un point-virgule à la fin d'une ligne de votre travail pratique, le professeur dépose un contenant avec des pillules rouges.");

	std::unique_ptr<Objet> pillule = std::make_unique<Objet>
		("Des pillules rouges",
		 "C'est un contenant avec des pillules rouges qui vous permet de sortir de la matrice.",
		 "Vous consommez une pillule et la porte pour sortir de la matrice est dans le corridor!",
		  true);

	std::unique_ptr<Objet> python = std::make_unique<Objet>
		("Un python",
		 "C'est un python dans votre aquarium.",
		 "Vous pointez le python, mais il ne vous pointe pas.");

	std::unique_ptr<Objet> java = std::make_unique<Objet>
		("Des java",
		 "Ce sont des cafés java remplis de caféine pour programmer.",
		 "Vous consommez un café et vous avez soudainement une envie incroyable de programmer en Java.");

	// Ajouter des cases sur la carte.
	carte_.modifierCaseDepart(move(entree));
	carte_.ajouterCase(move(salon));
	carte_.ajouterCase(move(couloir));
	carte_.ajouterCase(move(petiteChambre));
	carte_.ajouterCase(move(cuisine));
	carte_.ajouterCase(move(pieceBlanche));

	// Ajouter des objets dans les cases.
	carte_.ajouterObjet(move(yeezy), "Entrée");
	carte_.ajouterObjet(move(bitcoin), "Entrée");
	carte_.ajouterObjet(move(professeur), "Salon");
	carte_.ajouterObjet(move(pillule), "Salon");
	carte_.ajouterObjet(move(python), "Petite chambre");
	carte_.ajouterObjet(move(java), "Cuisine");

	// Connecter les cases.
	carte_.connecterCases("Entrée", "Salon", "E");
	carte_.connecterCases("Entrée", "Couloir", "N");
	carte_.connecterCases("Couloir", "Petite chambre", "O");
	carte_.connecterCases("Couloir", "Cuisine", "N");
	carte_.connecterCases("Couloir", "Pièce blanche", "E");

	// Relier les objets à des composantes cachées.
	carte_.relierObjetComposante("Des pillules rouges", "Pièce blanche");
	carte_.relierObjetComposante("Une paire de yeezys", "Un bitcoin");
	carte_.relierObjetComposante("Un professeur", "Des pillules rouges");

	positionActuelle_ = carte_.obtenirCaseDepart();
}

bool PositionJoueur::prochaineCase(std::string direction)
{
	Case* prochain = positionActuelle_->obtenirDirection(direction);
	if (prochain != nullptr && !prochain->obtenirEstCache())
	{
		positionActuelle_ = prochain;
		return true;
	}
	return false;
}

void PositionJoueur::lookObjet(std::ostream& os,
	                           std::function<bool(const Objet*)> fonction)
{
	auto iterateur = std::find_if(positionActuelle_->obtenirObjets().begin(),
		                          positionActuelle_->obtenirObjets().end(),
		                          fonction);

	if (iterateur != positionActuelle_->obtenirObjets().end() 
		&& !(*iterateur)->obtenirEstCache())
		(*iterateur)->look(os);

	else
		throw std::out_of_range("Je n'ai pas cet objet dans cette pièce.\n");
}

void PositionJoueur::useObjet(std::ostream& os, 
	                          std::function<bool(const Objet*)> fonction)
{
	auto iterateur = std::find_if (positionActuelle_->obtenirObjets().begin(),
		                           positionActuelle_->obtenirObjets().end(),
		                           fonction);

	if (iterateur != positionActuelle_->obtenirObjets().end() 
		&& !(*iterateur)->obtenirEstCache())
	{
		std::string nom = (*iterateur)->obtenirNom();
		if (carte_.verifierComposanteVisible(nom))
			carte_.modifierComposanteVisible(nom);
		(*iterateur)->use(os);
	}
	else
		throw std::out_of_range("Je n'ai pas cet objet dans cette pièce.\n");
}