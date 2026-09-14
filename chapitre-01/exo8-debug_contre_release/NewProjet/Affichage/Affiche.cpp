#include "Affiche.h"
#include"../Calculateur/Calcul.h"
#include <iostream>

void Affichage::AfficherResultat(int valeur) {
    Calcul calculer ;
    int res = calculer.additionner(valeur,0);
    std::cout << "Le resultat du calcul est : " << valeur << std::endl;
}
 void Affichage::Tester(){
    Calcul calculer;
  calculer. Bonjour();
 }