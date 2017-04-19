//
//  mot.cpp
//  LangageNat
//
//  Created by Anthony Bertrant on 18/04/2017.
//  Copyright © 2017 Anthony Bertrant. All rights reserved.
//

#include "Mot.hpp"
#include <cstdlib>

using namespace std;

//------- CLASSE MOT ---------//
Mot::Mot(string type, int poid, string polarite, string valeur){
    this->type     = type;
    this->poid     = poid;
    this->polarite = polarite;
    this->valeur   = valeur;
}

string Mot::getValeur(){
    return valeur;
}

string Mot::getType(){
    return type;
}

string Mot::getPolarite(){
    return polarite;
}

int Mot::getPoid(){
    return poid;
}


//------- CLASSE DICO -------//
void Dico::addToDico(Mot mot){
    dictionnaire.push_back(mot);
}

Mot Dico::getMot(int index){
    return dictionnaire[index];
}

Mot Dico::rechercheParNom(string nom){
    
    for(Mot mot : dictionnaire){
        if(mot.getValeur() == nom) return mot;
    }
    return Mot("", 0, "",""); //Erreur de mot non-trouvé, soit mot "vide"
}

int Dico::estNull(Mot mot){
    if(mot.getPoid() == 0 && mot.getValeur() == "" && mot.getType() == "" && mot.getPolarite() == "")
        return -1;
    return 0;
}


















