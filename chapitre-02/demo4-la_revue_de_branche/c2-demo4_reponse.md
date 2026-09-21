
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

## 3. Echange de branche 

```bash
commit 46d57487086eadd04f8d38d13c581a91918ee011 (origin/feature-soustraction)
Author: Maël Abondo <emilemaelnyeckabondo@gmail.com>
Date:   Sat Sep 19 23:34:21 2026 +0100

    feat : ajout de l'opération de soustraction
    
    La classe calculator ne présentait pas encore de possibilité de faire l'opération de multiplication. LA fonction template Soustraction prends ainsi en charge l'opération de soustraction pour tous les types de bases de c++.
    La calculatrice peut ainsi soustraire n'importe quelle valeur sans soucis.
```

la branche que j'ai  recuperer chez mon collaborateur 
* **feature-soustraction** : cette  branche permet d'effectuer les operations de soustraction de nombre

## 3. Ce qui manque (Oublis ou Lacunes)

*  **Documentation / Commentaires :** Les commentaires sont pas tous presents dans les fichiers pour decrirent certaines fonctions
*  **Gestion des erreurs :**  Pas de vérification sur la saisie utilisateur dans `main.cpp`.

---

## 4. Ce qui ne devrait pas y être 

* **Le commit mentionne l'abscence de la fonctionnalite de multiplication , mais on se rend compte que le commit inclut plutot une multiplication** : Dans l'analyse du commit de mon collaborateur , on peut constater que l'objectif principal du commit est de presenter la fonctionnalite de l'operation de soustraction  , mais une erreur de saisi a du s'inserer arce qu'il ne parle reellement pas de la multiplication comme il l'introduit . il n'a donc pas introduit la multiplication mais  des operation de  soustraction.
---

## 5. Synthèse et Recommandations

| Catégorie | Statut | Action recommandée |
| :--- | :---: | :--- |
| **Fonctionnalité** |  Valide | Aucune modification majeure |
| **Historique Git** |  À améliorer | Réécrire ou clarifier les messages de commit flous |

---

## 7. Difficultes rencontrer 
   
Moi par exemple j'ai eu enormement de probleme pour push mon travail , apres validation de mon code par mes collaborateur , le pull request une fois effectuer , mon push ne partait pas et je recevait un enorme message d'erreur  .Mias ce fut resolu 


## 8. Bilan de la Discussion 

* **Points d'accord :**  Les pull request  devraient etre revus et traiter avant une duree de 30min apres leur ouvertures 
* **Décisions prises :** Validation de la fusion de la  branche après correction des éléments bloquants. Creation des branches pour chaque fonctionnalite distinctes
* **Membres présents :** [NYECK], [DIKOUME], [EMMA], [NOUMSSI]
  
 
