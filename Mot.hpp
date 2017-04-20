//
//  Mot.hpp
//  LangageNat
//
//  Created by Anthony Bertrant on 18/04/2017.
//  Copyright © 2017 Anthony Bertrant. All rights reserved.
//

#ifndef Mot_hpp
#define Mot_hpp

#include <stdio.h>
#include <string>
#include <vector>


class Mot {
    
	private:
		int poid;             //c'est le pourcentage defini dans le xml
		std::string polarite; // le mot est-il NEUTRE, POSITIF ou NEGATIF ?
		std::string type;     // Le mot est-il un verbe, un nom feminin, un nom masculin...
		std::string valeur;   //valeur du mot
		
	public:
		Mot(std::string type, int poid, std::string polarite, std::string valeur);
		std::string getValeur();
		std::string getType();
		std::string getPolarite();
		int getPoid();
};

class Dico {
    
	public:
		std::vector<Mot>dictionnaire;
		void addToDico(Mot mot);
		Mot getMot(int index);
		Mot rechercheParNom(std::string nom); //Return mot vide ("",0,0,"","") si aucun resultat trouvé
		int estNull(Mot mot);                 //Permet de controler facilement si un mot est vide
    
};

#endif /* Mot_hpp */
