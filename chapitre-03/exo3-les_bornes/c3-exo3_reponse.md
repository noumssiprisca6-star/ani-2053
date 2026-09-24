
# Rapport d'exercice : Test des limites de taille de fenêtre

## 1. Contexte et Objectifs
- **Application / Fenêtre testée :** Systeme de fenetrage avec NKindow
- **Système d'exploitation :** Window
- **Objectif :** Évaluer le comportement de la fenêtre lors de l'application et du dépassement des contraintes de taille minimale et maximale.

---

## 2. Configuration des Contraintes

- **Taille minimale fixée :** `300 x 200 px`
- **Taille maximale fixée :** `800 x 600 px`

---

## 3. Déroulement du Test et Observations

### Étape 1 : Test de la taille minimale (300 x 200 px)
- **Comportement au blocage :**
  -  Avec une taille minimal de 300 x 200 px , La taille de la fenetre est reduite mais les elements qui la constitue (boutons) , s'affiche normalement

### Étape 2 : Tentative de réduction en dessous du seuil
- **une taille de 30 x 20px :**
  - les elements se chevauchent , le curseur n'apparait pas facilement pour fermer la fenetre mais il ne se bloque pas

### Étape 3 : Retrait des contraintes & Recherche du minimum absolu
- **Action :** Suppression des règles min/max.
- **Plus petite taille acceptée par le système :** `3 x 2 px`
- **Comportement à la limite absolue :**
  -  La fenêtre refuse de réduire davantage, lorsque long appuie sur le bouton de reduction , la fenetre disparait et au bout d'un moment , le terminal bogue


### Étape 4 : Test de la taille maximale (800 x 600 px)
- **Agrandissement de la fenêtre :**
  -  La fenêtre ne s'aggrandit pas , le bouton d'aggrandissement devient gris chez moi.
  la fenetre peut atteindre une taille maximale de 2000 x 1500 px et elle remplit entierement mon ecran avant que je ne recoivent un disfonctionnement du genre , `la fenetre ne reponds plus `

---

## 4. Tableau Récapitulatif

| Contrainte | Valeur définie (px) | Observé / Respecté | Limite réelle du système (px) |
| :--- | :--- | :--- | :--- |
| **Taille Minimale** | `300 x 200` | [Oui / Non] | `2 x 1 px` |
| **Taille Maximale** | `800 x 600` | [Oui / Non] | `2000 x 1500px` |

