# 1. Tableau Récapitulatif des Tests

| N° Test | Propriété Désactivée (`false`) | Action Impossible / Restriction Constatée 
| :---: | :--- | :--- | 
| **1** | `bool centered` | Impossible de centrer la fenêtre sur l'écran |
| **2** | `bool resizable` | Impossible de redimensionner la fenêtre (étirer les bords) |
| **3** | `bool movable` | Impossible de déplacer la fenêtre en cliquant-glissant la barre de titre | 
| **4** | `bool closable` | Impossible de fermer la fenêtre via la croix rouge  | 
| **5** | `bool minimizable` | Impossible de réduire la fenêtre dans la barre des tâches |
| **6** | `bool maximizable` | Impossible d'agrandir la fenêtre pour couvrir tout l'écran | 
| **7** | `bool canFullscreen` | Impossible de passer en mode plein écran exclusif  |

---

## 2. Fiches Détaillées des Tests

### Test 1 — `centered = false`
* **Propriété désactivée :** `bool centered`
* **Action impossible :** Placer automatiquement la fenêtre au centre de l'écran au démarrage.
* **Ce qui reste possible :** Redimensionner, déplacer, réduire, agrandir et fermer la fenêtre.
* **Observation :**  La fenêtre s'ouvre à une position par défaut 

### Test 2 — `resizable = false`
* **Propriété désactivée :** `bool resizable`
* **Action impossible :** Modifier la largeur et la hauteur de la fenêtre en étirant les bordures ou les coins.
* **Ce qui reste possible :** Déplacer, fermer, réduire et basculer en plein écran.
* **Observation :** Le curseur de redimensionnement n'apparaît pas / Bords fixes.

### Test 3 — `movable = false`
* **Propriété désactivée :** `bool movable`
* **Action impossible :** Déplacer la fenêtre sur le bureau en la glissant avec la souris.
* **Ce qui reste possible :** Redimensionner, fermer, réduire et interagir avec les éléments internes.
* **Observation :** La fenêtre reste ancrée à sa position fixe.

### Test 4 — `closable = false`
* **Propriété désactivée :** `bool closable`
* **Action impossible :** Fermer la fenêtre en cliquant sur le bouton de fermeture ou via le raccourci de fermeture standard.
* **Ce qui reste possible :** Déplacer, redimensionner, réduire, agrandir.
* **Observation:** La croix `X` est grisée 

### Test 5 — `minimizable = false`
* **Propriété désactivée :** `bool minimizable`
* **Action impossible :** Réduire la fenêtre dans la barre des tâches.
* **Ce qui reste possible :** Fermer, déplacer, redimensionner et agrandir.
* **Observation :** Le bouton de réduction `_` est grisé 

### Test 6 — `maximizable = false`
* **Propriété désactivée :** `bool maximizable`
* **Action impossible :** Agrandir la fenêtre pour occuper tout l'espace de travail.
* **Ce qui reste possible :** Déplacer, redimensionner manuellement, réduire et fermer.
* **Observation:* Le bouton d'agrandissement `□` est grisé ou absent. 

### Test 7 — `canFullscreen = false`
* **Propriété désactivée :** `bool canFullscreen`
* **Action impossible :** Basculer en mode plein écran sans bordure ni barre de titre.
* **Ce qui reste possible :** Agrandir la fenêtre (maximized), la déplacer, la redimensionner et la fermer.
* **Observation :**raccourci plein écran ne produit aucun effet. 

---

>*Une fois les sept tests terminer , j'enleve la non integration d'une action en  mettant un true * 