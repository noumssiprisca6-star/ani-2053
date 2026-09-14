#include<iostream>
#include"Calculateur/Calcul.h"
#include"Affichage/Affiche.h"

int main(){

    Calcul op;
    Affichage ecran ;
    Affichage test ;
    
    int resultat = op.additionner(15,25);
    ecran.AfficherResultat(resultat);
    test.Tester();
    return 0;
}

