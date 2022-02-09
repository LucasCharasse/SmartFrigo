#include <iostream>
#include "vector"
#include "map"
#include "SmartFrigo.h"


SmartFrigo::SmartFrigo(){

}

SmartFrigo::SmartFrigo(SmartFrigo& frigo){
    this->listeIngrediants1 = frigo.listeIngrediants1;
    this->Recettes = frigo.Recettes;
}

SmartFrigo::~SmartFrigo(){

}

ostream& operator<<(ostream& out, SmartFrigo frigo){
    string res="";
    map<string,int> affichageAlpha;
    int quantite;
    string nomRecette;
    string nom;
    string datePeremption; 

    for (map<string ,pair<string, int>>::iterator it=frigo.getListeIngrediants().begin(); it!=frigo.getListeIngrediants().end(); ++it){
        nom = it->second.first;
        quantite = it->second.second;
        datePeremption = it->first;
        
        if(affichageAlpha.count(nom) > 0){
            std::map<string ,int>::iterator itMap;
            itMap = affichageAlpha.find(nom);
            itMap->second += quantite;
        }else{
            affichageAlpha.insert(pair<string, int>(nom, quantite));
        }
    }

    if (!affichageAlpha.empty()){
        for (map<string ,int>::iterator it=affichageAlpha.begin(); it!=affichageAlpha.end(); ++it){
            nom = it->first;
            quantite = it->second;
            res += nom + " " +  to_string(quantite) + "\n";
        }
    }
    res += ";";

    return out<<res;

}

string adaptDate(string date){
    return date.erase(date.find_last_of("/"), date.size());

}

map<string,pair<string, int>>& SmartFrigo::getListeIngrediants(){
    return listeIngrediants1;
}

map<string, vector<pair<string,int>>>& SmartFrigo::getRecettes(){
    return Recettes;
}

void SmartFrigo::ajoutRecette(istream& in){
    string nom;
    string nomIngrediant;
    int quantite;
    vector<pair<string, int>> ingrediantsNecessaire;
    in>>nom;
    in>>nomIngrediant;

    while(nomIngrediant != ";"){
        in>>quantite;
        ingrediantsNecessaire.push_back(std::make_pair(nomIngrediant,quantite));
        in>>nomIngrediant;
    }    
    Recettes.insert( pair<string, vector<pair<string, int>>>(nom,ingrediantsNecessaire));
}

void SmartFrigo::ajoutIngrediant(istream& in){
    string nom;
    int quantite;
    string dateDePeremption;
    std::map<string,int>::iterator itMap;
    
    in>>nom;
    in>>quantite;
    in>>dateDePeremption;

    int cpt = 0;
    map<string ,pair<string, int>>::iterator it;

    while (listeIngrediants1.find(dateDePeremption+"/"+to_string(cpt)) != listeIngrediants1.end()){
        cpt ++;
    }
    dateDePeremption += "/"+to_string(cpt);
    
    for (int i = 0; i < quantite; i++){
        listeIngrediants1.insert(pair<string,pair<string, int>>(dateDePeremption,std::make_pair(nom,quantite)));
    }
}

bool SmartFrigo::retraitIngrediant(istream& in){
    string nomIngrediant;
    int quantite;
    in>>nomIngrediant;
    in>>quantite;
    map<string ,pair<string, int>>::iterator it=listeIngrediants1.begin();
    string nomActu;

    while (quantite != 0 && it != listeIngrediants1.end()){
        nomActu = it->second.first;
        if (nomActu == nomIngrediant){
            it->second.second -= quantite;
            quantite = 0;
            if(it->second.second <= 0){
                quantite = it->second.second * -1;
                listeIngrediants1.erase(it);
            }
        } 
        if(quantite != 0){
            ++it;
        }
    }
    return it != listeIngrediants1.end();
}

bool SmartFrigo::retraitIngrediant(string nomIngrediant, int quantite){

    map<string ,pair<string, int>>::iterator it=listeIngrediants1.begin();
    string nomActu;

    while (quantite != 0 && it != listeIngrediants1.end()){
        nomActu = it->second.first;

        if (nomActu == nomIngrediant){
            it->second.second -= quantite;
            quantite = 0;

            if(it->second.second <= 0){
                quantite = it->second.second * -1;
                listeIngrediants1.erase(it);
                it = listeIngrediants1.begin();
            }
        } 

        if(quantite != 0 ){
            it++;
        }
        
    }
    return it != listeIngrediants1.end();

}

void SmartFrigo::recommendation(){
    bool found;
    bool alreadyHere;
    string ingrediantProche;
    string ingrediantActu;
    string dateProche;
    map<string ,pair<string, int>>::iterator itIngrediants = listeIngrediants1.begin();
    map<string, vector<pair<string,int>>>::iterator itRecettes;
    vector<string> res;
    size_t cptRecettes;

    if ((itIngrediants != listeIngrediants1.end())){
        dateProche = adaptDate(itIngrediants->first);
    }
    

    while ((itIngrediants != listeIngrediants1.end()) && (res.empty() || (dateProche == adaptDate(itIngrediants->first)))){
        ingrediantProche = itIngrediants->second.first;
        for(itRecettes = Recettes.begin(); itRecettes != Recettes.end(); itRecettes ++){
            alreadyHere = false;
            if(utilisation(itRecettes->first)){   
                cptRecettes = 0;
                found = false;

                while (cptRecettes < itRecettes->second.size() && !found){
                    ingrediantActu = itRecettes->second[cptRecettes].first;
                    
                    if(ingrediantProche == ingrediantActu){
                        found = true;
                        size_t i = 0;
                        
                        while(i<res.size() && !alreadyHere){
                            alreadyHere = (itRecettes->first == res[i]);
                            i++;
                        }
                        
                        if (!alreadyHere){
                            res.push_back(itRecettes->first);
                        }
                    } 
                    cptRecettes ++;
                }
            }
        }
        itIngrediants ++;
    }

    for (size_t i = 0; i < res.size(); i++){
        cout<<res[i]<<" ";     
    }
    cout<<";"<<endl;
}


void SmartFrigo::utilisation(istream& in){
    string nomRecette;
    in >> nomRecette;
    bool stop = true;
    map<string, vector<pair<string,int>>>::iterator it = Recettes.find(nomRecette);

    SmartFrigo copieFrigo = *this;

    
    if(it != Recettes.end()){
        size_t cpt = 0;

        while(cpt<it->second.size() && stop){
            stop = copieFrigo.retraitIngrediant(it->second.at(cpt).first, it->second.at(cpt).second);
            cpt ++;
        }

        cout<<nomRecette<<" : "<<stop<<endl;
        cpt = 0;
        while(cpt<it->second.size() && stop){
            retraitIngrediant(it->second.at(cpt).first, it->second.at(cpt).second);
            cpt ++;
        }
    }else{
        cout<<nomRecette<<" : 0"<<endl;
    }
    

}

bool SmartFrigo::utilisation(string nomRecette){
    bool stop = true;
    map<string, vector<pair<string,int>>>::iterator it = Recettes.find(nomRecette);
    SmartFrigo copieFrigo = *this;

    if(it != Recettes.end()){
        size_t cpt = 0;

        while(cpt<it->second.size() && stop){
            stop = copieFrigo.retraitIngrediant(it->second.at(cpt).first, it->second.at(cpt).second);
            cpt ++;
        }

        return stop;
    }
    return false;
    

}