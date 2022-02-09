#ifndef __SMARTFRIGO__
#define __SMARTFRIGO__

#include <iostream>
#include "vector"
#include "set"
#include "map"

using namespace std;

class SmartFrigo{
    private:
        map<string, vector<pair<string,int>>> Recettes;
        map<string,pair<string,int>> listeIngrediants1;
    public:
        SmartFrigo();
        SmartFrigo(SmartFrigo& frigo);
        ~SmartFrigo();

        map<string,pair<string, int>>& getListeIngrediants();
        map<string, vector<pair<string,int>>>& getRecettes();

        void ajoutRecette(istream& in);
        void ajoutIngrediant(istream& in);
        bool retraitIngrediant(istream& in);
        bool retraitIngrediant(string nomIngrediant, int quantite);
        void recommendation();
        void utilisation(istream& in);
        bool utilisation(string nomRecette);

        friend ostream& operator<<(ostream& out, SmartFrigo frigo); 
};

#endif