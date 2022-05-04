/**
* Projet de INF1015 : Livrable 2
* \file   PositionJoueur.cpp
* \author Lana Pham et Jeremy Rouillard
* \date   22 d�cembre 2021
* Cr�� le 1 d�cembre 2021
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
		("Entr�e",
		 "Il y a un tapis sur le sol.");

	std::unique_ptr<Case> salon = std::make_unique<Case>
		("Salon",
		 "Il y a un professeur de INF1015 emball� dans un cadeau � c�t� du sapin de No�l.");

	std::unique_ptr<Case> couloir = std::make_unique<Case>
		("Couloir",
		 "Il y a des bo�tes proches du mur ainsi qu'un sabre laser de la guerre des �toiles.");

	std::unique_ptr<Case> petiteChambre = std::make_unique<Case>
		("Petite chambre",
		 "Elle n'est pas particuli�rement propre ou organis�e. Il y a une petite fen�tre et une affiche murale de Pink Floyd.");

	std::unique_ptr<Case> cuisine = std::make_unique<Case>
		("Cuisine",
		 "Vous remarquez Gordon Ramsey dans la pi�ce, celui-ci ne veut pas �tre d�rang�. Il cherche la sauce � l'agneau.");

	std::unique_ptr<Case> pieceBlanche = std::make_unique<Case>
		("Pi�ce blanche",
		 "Cette pi�ce est constitu�e de vide intersid�ral.",
		  true);

	// Initialiser des objets.
	std::unique_ptr<ObjetDeverouillant> yeezy = std::make_unique<ObjetDeverouillant>
		("Une paire de yeezys",
		 "Les yeezys Boost 350 V2 ont beaucoup trop de style.",
		 "En reniflant les souliers, vous vous rendez compte qu'ils d�gagent une odeur n�faste.",
		 "En examinant les souliers, vous d�couvrez un bitcoin dans ceux-ci!");

	std::unique_ptr<Objet> bitcoin = std::make_unique<Objet>
		("Un bitcoin", 
		 "Wow, c'est un bitcoin, cela va vous rapporter beaucoup de bidous.", 
		 "Vous gardez le bitcoin, vous poss�dez maintenant 63 128.56 dollars canadien en bitcoin dans votre compte bancaire.", 
		  true);

	std::unique_ptr<ObjetDeverouillant> professeur = std::make_unique<ObjetDeverouillant>
		("Un professeur",
		 "C'est un professeur d'objet orient� qui peut vous aider avec votre travail pratique. il est recouvert d'emballage �trangement.",
		 "Il rajoute un point-virgule � la fin d'une ligne de code et votre code compile par magie.",
		 "Apr�s avoir rajout� un point-virgule � la fin d'une ligne de votre travail pratique, le professeur d�pose un contenant avec des pillules rouges.");

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
		 "Ce sont des caf�s java remplis de caf�ine pour programmer.",
		 "Vous consommez un caf� et vous avez soudainement une envie incroyable de programmer en Java.");

	// Ajouter des cases sur la carte.
	carte_.modifierCaseDepart(move(entree));
	carte_.ajouterCase(move(salon));
	carte_.ajouterCase(move(couloir));
	carte_.ajouterCase(move(petiteChambre));
	carte_.ajouterCase(move(cuisine));
	carte_.ajouterCase(move(pieceBlanche));

	// Ajouter des objets dans les cases.
	carte_.ajouterObjet(move(yeezy), "Entr�e");
	carte_.ajouterObjet(move(bitcoin), "Entr�e");
	carte_.ajouterObjet(move(professeur), "Salon");
	carte_.ajouterObjet(move(pillule), "Salon");
	carte_.ajouterObjet(move(python), "Petite chambre");
	carte_.ajouterObjet(move(java), "Cuisine");

	// Connecter les cases.
	carte_.connecterCases("Entr�e", "Salon", "E");
	carte_.connecterCases("Entr�e", "Couloir", "N");
	carte_.connecterCases("Couloir", "Petite chambre", "O");
	carte_.connecterCases("Couloir", "Cuisine", "N");
	carte_.connecterCases("Couloir", "Pi�ce blanche", "E");

	// Relier les objets � des composantes cach�es.
	carte_.relierObjetComposante("Des pillules rouges", "Pi�ce blanche");
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
		throw std::out_of_range("Je n'ai pas cet objet dans cette pi�ce.\n");
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
		throw std::out_of_range("Je n'ai pas cet objet dans cette pi�ce.\n");
}