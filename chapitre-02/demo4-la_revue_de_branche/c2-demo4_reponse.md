
# Compte-Rendu de Revue de Code (Code Review)

>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git


**Groupe Relecteur :** Groupe A . pour les tests unitaires `(Dikoume, Emma)`
**Groupe Auteur :** Groupe B . pour la mise en place des classes fonctionnelles`(Nyeck , Noumssi)`
**Branche examinée :** `toutes celles utilisees (feature-soustraction , feature-multiplication , feature-add)`  
**Date :** 21 Septembre 2026  

---

## 1. Description Générale (Ce que fait la branche)

* **Objectif principal :** Realiser une calculatrice simple  qui effectue quatre operations de base : l'addition , la soustraction , la division , la multiplication  des nombres .
* **Fichiers impactés :** `[Calculator.cpp , Calculator.h , main.cpp]`

---

## 2. Lisibilité et Qualité des Commits

*  **Clarté des messages :** Les messages decrivent precisement les modifications
*  **Granularité :** les commits ne presentent pas tous une etapes logiques du travail

### Remarques sur l'historique (`git log`) :
* **Points positifs :** Bon usage des préfixes conventionnels (feat, fix) convernant mes collaborateur
* **Points à améliorer :**  Le commit `46d57487086eadd04f8d38d13c581a91918ee011` ("ajout de la modification par type simple") manque de précision. explicite du sujet mais est comprehensible.

---

## 3. Ce qui manque (Oublis ou Lacunes)

*  **Documentation / Commentaires :** Les commentaires sont pas tous presents dans les fichiers pour decrirent certaines fonctions
*  **Gestion des erreurs :**  Pas de vérification sur la saisie utilisateur dans `main.cpp`.

---

## 4. Ce qui ne devrait pas y être 

Il y'en a pas 
---

## 5. Synthèse et Recommandations

| Catégorie | Statut | Action recommandée |
| :--- | :---: | :--- |
| **Fonctionnalité** |  Valide | Aucune modification majeure |
| **Historique Git** |  À améliorer | Réécrire ou clarifier les messages de commit flous |
| **Nettoyage du code** |  Requis et implementer | Supprimer les fichiers temporaires et ajouter un `.gitignore` |

---

## 6. Difficultes rencontrer 
   
Moi par exemple j'ai eu enormement de probleme pour push mon travail , apres validation de mon code par mes collaborateur , le pull request une fois effectuer , mon push ne partait pas et je recevait un enorme message d'erreur  .Mias ce fut resolu 


## 7. Bilan de la Discussion 

* **Points d'accord :**  Les pull request  devraient etre revus et traiter avant une duree de 30min apres leur ouvertures 
* **Décisions prises :** Validation de la fusion de la  branche après correction des éléments bloquants. Creation des branches pour chaque fonctionnalite distinctes
```bash
 
 feature
  feature-add
  feature-calculator
* main
  test-merge
  test-rebase
```
* **Membres présents :** [NYECK], [DIKOUME], [EMMA], [NOUMSSI]
  
 
