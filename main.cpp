#include <iostream>
#include <fstream>
#include "SmartFrigo.h"

using namespace std;

void affichage(SmartFrigo frigo){
    cout<<frigo<<endl;
}

void selectionOrder(string order, SmartFrigo& frigo, istream& in){
    if(order == "recette"){
        frigo.ajoutRecette(in);
    }
    else if (order == "ajout"){
        frigo.ajoutIngrediant(in);
    }
    else if(order == "retrait"){
        frigo.retraitIngrediant(in);
    }
    else if(order == "recommendation"){
        frigo.recommendation();
    }
    else if (order == "utilisation"){
        frigo.utilisation(in);
    }
    else if (order == "affichage"){
        affichage(frigo);
    }
    else{
        cout<<"aucune action ne correspond a l'ordre : "<<order<<endl;
    }
}

void readOrder(istream& in, SmartFrigo& frigo){
    string order;
    while(!in.eof()){
        in>>order;
        selectionOrder(order, frigo, in);
    }
}

int main(int argc, char** argv)
{
    SmartFrigo frigo;
    if(argc == 2){
        ifstream in(argv[1]);
        if(in.is_open()){
            readOrder(in, frigo);
        }
    } else {
        readOrder(cin, frigo);    
    }
    return 0;
}
