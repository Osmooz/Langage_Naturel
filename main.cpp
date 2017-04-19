//
//  main.cpp
//  LangageNat
//
//  Created by Anthony Bertrant on 18/04/2017.
//  Copyright © 2017 Anthony Bertrant. All rights reserved.
//

#include <iostream>
#include "Mot.hpp"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, const char * argv[]) {
    
    XMLDocument doc;
    Dico::Dico dictionnaire;
    int i = 1;
    
    if(doc.LoadFile("dico.xml") != XML_SUCCESS){
        cerr << "Erreur lors du chargement" << endl;
        cerr << "Error #" << doc.ErrorID() << " : " << doc.ErrorIDToName(doc.ErrorID()) << endl;
        return 1;
        
    }//controle si le fichier existe et qu'on peut y acceder
    
    XMLHandle hdl(&doc);
    XMLElement *elem = hdl.FirstChildElement().FirstChildElement().ToElement(); //on accede a: <lexicon><entry>..., soit le 2nd noeud
    
    if(!elem){
        cerr << "Le noeud a atteindre existe pas" << endl;
        return 2;
    }
    
    while(elem){
        //printf("mot: %s, polarite: %s, poid: %s\n", elem->FirstChildElement()->GetText(), elem->Attribute("pol"), elem->Attribute("weight"));
        dictionnaire.addToDico(Mot(elem->Attribute("pos"), atoi(elem->Attribute("weight")), elem->Attribute("pol"), elem->FirstChildElement()->GetText()));
        ++i;
        elem = elem->NextSiblingElement();
    }
    
    for (int j; j < 10; ++j) {
        //Mot mot = dictionnaire.getMot(j);
        cout << dictionnaire.getMot(j).getValeur() << endl;
    }
    
    Mot mot2 = dictionnaire.rechercheParNom("comcom");
    cout << endl;
    cout << "valeur rechercher:  abeille," << endl;
    
    if(dictionnaire.estNull(mot2))
        cout << "Aucune valeur trouvé" << endl;
    else
        cout << "valeur trouvée: " << mot2.getValeur() << endl;
    
    cout << "il y a " << i <<"mots\n" << endl;
    
    
    return 0;
}
