
```markdown
#  Rapport d'Observation Utilisateur — `NkRef` 

> **Projet / Outil :** `NkRef` (Composant de la suite NK)  
> **Méthodologie :** Test fonctionnel "de l'executable" (10 minutes d'utilisation continue sans inspection du code source).  
> **Date du test :** 14 septembre 2026  
> **Objectif :** Réposer des observations objectives sur le comportement actuel de l'outil et identifier les fonctionnalités manquantes avant l'étude approfondie du code au **Chapitre 16**.

---

##  1. Ce que `NkRef` fait (Comportement observé)

*Date de l'observation : 14 septembre 2026*
# Evaluation Utilisateur : NKRef

**Date :** 14 septembre 2026

---

## Ce que l'application fait 

* **Gestion du canevas et navigation :**
  * Pan / Déplacement de la vue (Bouton milieu du pavé/souris ou Touche Espace + glisser).
  * Zoom centré sur le curseur .
  * Recentrage rapide sur le point d'origine (` au Début`).
  *  j'ai essayé ceci mais je n'ai remarque aucune modification , il s'agirait peut etre d'une reorganisation(`Pack` via `Ctrl+P`).

* **Intégration et manipulation d'images :**
  * Import/Collage rapide d'images depuis le presse-papiers avec drag and drop
  * Redimensionnement de l'image
  * Découpage/Sélection rectangulaire   (`Ctrl+glisser`) mais je ne vois pas ce changement quand je  l'effectue.
  

* **Annotation et dessin (Mode Crayon) :**
  * Activation/Désactivation rapide du mode dessin (Touche `D`).
  * Palette de couleurs prédéfinies (Orange, Pétrole, Rouge, Vert, Bleu, Blanc, Noir).
  * Réglage continu de l'épaisseur des traits (Slider).
  * Gestion de l'historique de dessin (`Annuler le dernier trait`, `Effacer tous les traits`).

* **Comportement de la fenêtre :**
  * Mode "Toujours au-dessus" / Épinglage (`T`)  mais j'ai as vu les modifications apres avoir tester.
  * Réglage de la transparence globale de la fenêtre (Slider d'opacité) ca marche tres bien .
  * Mode de déplacement dynamique de l'application via le fond de planche (`Glisser le fond = fenetre`).

---

## Ce que j'aurais voulu qu'elle fasse 

* **Outils de dessin avancés :**
  * Sélecteur de couleur personnalisé (Roue RVB / Pipette) au lieu de simples préréglages.
  * Gomme ciblée (par trait ou par zone) au lieu d'une annulation purement séquentielle.
  * Primitives géométriques de base (flèches, cercles, rectangles d'annotation) la on pourrait choisir les formes selon nos voulus.

* **Manipulation d'images & Organisation :**
  * Gestion de l'opacité par image (pas  uniquement sur la fenêtre entière de preference ).
  * Système de regroupement (*Group*) ou d'alignement automatique entre plusieurs images.

* **Sauvegarde et Persistance :**
  * Export de la planche complète (ou de la vue courante) sous forme d'image HD (PNG/JPEG).

* **Ergonomie & Raccourcis :**
  * Raccourci standard `Ctrl+Z` / `Ctrl+Y` pour l'historique d'annulation/rétablissement du dessin.
  * Indicateur visuel plus explicite de l'image actuellement sélectionnée et de ses propriétés.

---


---

> **Note pour le Chapitre 16 :** Ce document devra être relu et comparé aux spécifications techniques réelles du code source de `NkRef` lors du Chapitre 16.

<
```

