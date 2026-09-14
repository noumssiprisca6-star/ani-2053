# Rapport d'Ergonomie : Première Utilisation de NkRef (Analyse Vidéo)

---

## 1. Informations et Enregistrement Vidéo

* **Outil testé :** NkRef
* **Contexte :** Premier test utilisateur (Session à aveugle, sans voir le code )
* **Lien de la vidéo d'enregistrement :**(Fichier volumineux ~930 Mo hébergé en ligne)*

---

## 2. Relevé des Hésitations (Défauts d'Ergonomie)

> **Note :** Chaque horodatage ci-dessous correspond à un moment précis où une hésitation, un temps d'arrêt ou un clic d'hésitation a été observé lors du visionnage.

| Horodatage (TC) | Fonctionnalité testée | Hésitation / Comportement observé | Problème d'ergonomie identifié |
| :---: | :--- | :--- | :--- |
| **00:45** | Réorganisation (`Pack` / `Ctrl+P`) | Activation du raccourci/bouton sans aucun changement visuel constaté sur le canevas. | Absence totale de retour visuel (feedback) ou fonction inopérante. |
| **01:50** | Découpage rectangulaire (`Ctrl+glisser`) | Tentative de découpage d'image, mais aucune modification ou zone de sélection n'apparaît. | Manque d'indicateur visuel de sélection ou raccourci non pris en compte. |
| **03:15** | Mode Épinglage / Toujours au-dessus (`T`) | Appui sur la touche `T`, attente de confirmation visuelle, aucun changement d'état apparent. | Absence d'indicateur d'état (ex: icône d'épingle activée/désactivée). |
| **04:40** | Choix de couleur de dessin | Recherche d'une teinte spécifique, arrêt sur la palette limitée à 7 couleurs prédéfinies. | Manque de liberté créative (absence de roue RVB ou de pipette). |
| **05:20** | Correction de dessin | Hésitation avant d'effacer tout le trait car seule l'annulation séquentielle est proposée. | Absence d'un outil Gomme ciblé ou par zone. |
| **06:10** | Annulation d'action | Tentative réflexe d'utiliser `Ctrl+Z`, sans succès immédiat pour le dessin. | Non-respect des raccourcis standards de l'industrie (`Ctrl+Z` / `Ctrl+Y`). |
| **07:30** | Réglage d'opacité | Utilisation du slider d'opacité globale en cherchant à ne rendre transparente qu'une seule image. | Absence de réglage d'opacité individuel par image. |
| **09:56** | Fin de session / Sauvegarde | Balayage de l'écran à la recherche d'un bouton d'exportation de la planche. | Absence de fonction d'exportation HD (PNG/JPEG). |

---

## 3. Synthèse des Défauts d'Ergonomie & Axes d'Amélioration

---

## 3. Synthèse et Axes d'Amélioration Prioritaires

### A. Feedback Visuel et Prise en Charge des Actions (Priorité Haute)
* **Problème :** Plusieurs fonctionnalités clés (`Pack / Ctrl+P`, `Découpage / Ctrl+glisser`, `Toujours au-dessus / T`) ne renvoient aucun indicateur visuel lors de leur activation pour mon cas 
* **Solution :** Ajouter des indicateurs d'état clairs (ex: surbrillance de l'image sélectionnée, icône d'épingle active, contour de zone lors du découpage).

### B. Enrichissement des Outils de Dessin et Retouche
* **Problème :** Les options actuelles restent très restrictives (7 couleurs fixes, annulation trait par trait uniquement).
* **Solution :** Intégrer un sélecteur de couleur complet (RVB/Pipette), un outil Gomme (par zone/trait) ainsi que des formes géométriques de base (flèches, rectangles, cercles).

### C. Gestion Individuelle des Éléments et Export
* **Problème :** L'opacité ne s'applique qu'à la fenêtre globale et il est impossible d'exporter le travail final.
* **Solution :** Permettre le contrôle de l'opacité et l'alignement/groupage par image individuelle, et intégrer une fonction d'exportation de la planche en haute définition.

### D. Standardisation des Raccourcis
* **Problème :** La prise en main est ralentie par l'absence de raccourcis conventionnels.
* **Solution :** Aligner la gestion de l'historique sur les standards universels  ca pourrait toujours etre necessaire(`Ctrl+Z` pour annuler, `Ctrl+Y` pour rétablir).
---

```
MA VIDEO PESE ENORMEMENT JE NE PEUT DONC PAS L'ENVOYER DIRECTEMENT ICI .
Monsieur y'auraitil un moyen de vous la transferer autrement que sur git ????

```
## 4. Conclusion

Ce premier visionnage à froid a permis d'isoler **5** points de friction majeurs. Ces ajustements permettront de rendre la prise en main de NkRef beaucoup plus intuitive  qu'elle ne l'est deja selon moi  ,. C'est extremement fascinant ce que vous avez cree monsieur .