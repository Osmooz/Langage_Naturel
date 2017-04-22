//
//  main.cpp
//  LangageNat
//
//  Created by Anthony Bertrant on 18/04/2017.
//  Copyright © 2017 Anthony Bertrant. All rights reserved.
//
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "Mot.hpp"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int mettrePhraseLigne2 (string nomFichier) {
	fstream fichier(nomFichier.c_str(), ios::in | ios::out /*| ios::ate*/);
	ofstream nouveauFichier("1PhraseParLigne.txt", ios::out | ios::trunc);
	if(fichier.fail() || nouveauFichier.fail()) {
		cout << "Echec de l'ouverture du fichier" << endl;
		return -1;
	}
	if(fichier)
	{
		string ligne;
		string lignebis;
		unsigned index;
		while(getline(fichier, ligne)) { //On stocke une ligne du fichier "fichier" dans un la string "ligne"
			for(index = 1 ; index < ligne.length() ; index++) { //On parcourt tous les caracteres de cette ligne
				if(isupper(ligne[index])) {
					tolower(ligne[index]);
				}
				if(ligne[index] == '\'') { //On remplace les ' par un espace
					ligne[index] = ' ';
				}
				else if(ligne[index] == ',') { //On remplace les , par un espace
					ligne[index] = ' ';
				}
				if(ligne[index-1] == '.') { //S'il y a un . suivit d'un espace, on remplace le . par un espace et l'espace par un saut de ligne
					if(ligne[index] == ' ') {
						ligne[index-1] = ' ';
						ligne[index] = '\n';
					}
				}
				else if(ligne[index-1] == '?') { //S'il y a un ? suivit d'un espace, on remplace le ? par un espace et l'espace par un saut de ligne
					if(ligne[index] == ' ') {
						ligne[index-1] = ' ';
						ligne[index] = '\n';
					}
				}
				else if(ligne[index-1] == '!') { //S'il y a un ! suivit d'un espace, on remplace le ! par un espace et l'espace par un saut de ligne
					if(ligne[index] == ' ') {
						ligne[index-1] = ' ';
						ligne[index] = '\n';
					}
				}
				else if(index == ligne.length()-1) { //On remplace tous les . ? et ! en fin de ligne par un espace
					if(ligne[index] == '.') {
						ligne[index] = ' ';
					}
					else if(ligne[index] == '?') {
							ligne[index] = ' ';
					}
					else if(ligne[index] == '!') {
							ligne[index] = ' ';
					}
				}
			}
			nouveauFichier << ligne << "\n";
		}
		fichier.close();
		nouveauFichier.close();
	}
	else {
		cerr << "Impossible d'ouvrir le fichier !" << endl;
		return -1;
	}
	return 1;
}

int main(int argc, const char * argv[]) {
    if(argc != 2) {
		cout << "Nombre arguments incorrects, nbr argument actuel " << argc << " : executable nom-fichier.txt" << endl;
		return -1;
	}
	string nomFichier = argv[1];
    
    XMLDocument doc;
    Dico dictionnaire;
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
    
    
    for (int j = 0; j < 10; ++j) {
        //Mot mot = dictionnaire.getMot(j);
        cout << dictionnaire.getMot(j).getValeur() << endl;
    }
    
    Mot mot2 = dictionnaire.rechercheParNom("comcom");
    cout << endl;
    cout << "valeur rechercher:  abeille," << endl;
    
    if(dictionnaire.estNull(mot2))
        cout << "Aucune valeur trouvée" << endl;
    else
        cout << "valeur trouvée: " << mot2.getValeur() << endl;
    
    cout << "il y a " << i <<"mots\n" << endl;
    
    
    
    int scoreLigne = 0;
    int scoreTotal = 0;
    vector<int> tabScoreLigne;
    int poidsPosMax = 0;
    int poidsNegMax = 0;
    int moyenne = 0;
    
    if(mettrePhraseLigne2(nomFichier) != 1) {
    	cout << "L'ouverture du fichier a échouée" << endl;
    	return -1;
    }
    
    //TODO: prendre en compte les '
    
    fstream fichier("1PhraseParLigne.txt", ios::in | ios::out /*| ios::ate*/);
	if(fichier.fail()) {
		cout << "Echec de l'ouverture du fichier \"1PhraseParLigne.txt\"" << endl;
		return -1;
	}
	if(fichier)
	{
		string ligne;
		string mot = "";
		unsigned index;
		while(getline(fichier, ligne)) { //On parcourt le fichier ligne par ligne
			for(index = 0 ; index < ligne.length() ; index++) { //On parcourt la phrase caractere par caractere
				if(ligne[index] != ' ') { //Tant que ce n'est pas un espace, on stock la lettre dans la variable "mot"
					mot += ligne[index];
				}
				else { //Comme il y a un espace, les caracteres placés dans la variable sont un mot
					//cout << "Le mot est : \"" << mot << "\"" << endl;
					Mot motActuel = dictionnaire.rechercheParNom(mot);
					if(dictionnaire.estNull(motActuel) == 0) { //Si le mot existe dans le dictionnaire
						//cout << "\tLa polarité du mot est : \"" << motActuel.getPolarite() << "\"" << endl; 
						if(motActuel.getPolarite() == "NEUTRE") { 
							//cout << "\tSon poids est : \"" << motActuel.getPoid() << "\"" << endl;
							//scoreLigne += 0;
						}
						else if(motActuel.getPolarite() == "POS") {
							//cout << "\tSon poids est : \"" << motActuel.getPoid() << "\"" << endl;
							scoreLigne += motActuel.getPoid();
							poidsPosMax += motActuel.getPoid();
						}
						else if(motActuel.getPolarite() == "NEG") {
							//cout << "\tSon poids est : \"" << (motActuel.getPoid() * -1) << "\"" << endl;
							scoreLigne -= motActuel.getPoid();
							poidsNegMax -= motActuel.getPoid();							
						}
					}
					mot = "";
				}
			}
			tabScoreLigne.push_back(scoreLigne); //On stock le score de la ligne dans un tableau
			mot = "";
		}
		for(index = 0 ; index < tabScoreLigne.size() ; index++) { //On calcule le score totale des toutes les lignes
			scoreTotal += tabScoreLigne.at(index);
		}
		cout << "Le score total est " << scoreTotal << endl;
		moyenne = (poidsPosMax + abs(poidsNegMax)) / 2;
		cout << "Le texte est donc à connotation "; 	
		if((moyenne * 0.05) >= abs(scoreTotal)) {
			cout << "neutre." << endl;
		}
		else if(scoreTotal > 0) {
			cout << "positive." << endl;
		}
		else if(scoreTotal < 0) {
			cout << "negative." << endl;			
		}
		else {
			cout << " !!! Erreur lors de l'assignation de la connotation du texte !!! " << endl;
		}
		fichier.close();
	}
	else {
		cerr << "Impossible d'ouvrir le fichier !" << endl;
		return -1;
	}
	return 1;
    
    
    
    return 0;
}
