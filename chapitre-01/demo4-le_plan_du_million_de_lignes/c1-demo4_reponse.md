```markdown
# Carte Structurelle et Métriques du Dépôt (Architecture & Dépendances)

---

## 1. Les 5 Couches de l'Architecture

La hiérarchie des couches est ordonnée de la plus haute abstraction (Application) vers la plus basse (Système/Core). La règle d'architecture stricte impose que les dépendances s'effectuent uniquement du haut vers le bas.


```

┌─────────────────────────────────────────────────────────┐
│ [Couche 5] APPLICATIONS                                 │
│ (NkStudio, NkEditor, Outils)                            │
└──────────────────────────┬──────────────────────────────┘
│
┌──────────────────────────▼──────────────────────────────┐
│ [Couche 4] ENGINE CORE                                  │
│ (NKEngine, NKScene, NKRenderer)                         │
└──────────────────────────┬──────────────────────────────┘
│
┌──────────────────────────▼──────────────────────────────┐
│ [Couche 3] SUBSYSTEMES TECHNIQUE                        │
│ (NKAudio, NKGraphics, NKPhysics, NKUI)                  │
└──────────────────────────┬──────────────────────────────┘
│
┌──────────────────────────▼──────────────────────────────┐
│ [Couche 2] ABSTRACTION MATÉRIEL & OS                    │
│ (NKWindow, NKInputs, NKRHI)                             │
└──────────────────────────┬──────────────────────────────┘
│
┌──────────────────────────▼──────────────────────────────┐
│ [Couche 1] FONDATIONS SYSTEME                           │
│ (NKCore, NKContainers, NKMath)                          │
└─────────────────────────────────────────────────────────┘

```

---
```

## 2. Top 10 des Modules (Classés par Lignes de Code - LoC)

*Mesures effectuées sur l'ensemble  de certains fichiers sources (`.cpp`, `.c`) et en-têtes (`.hpp`, `.h`).*

| Rang | Module | Couche | Nombre de Fichiers | Volume (LoC) | Rôle Principal |
| :---: | :--- | :---: | :---: | :---: | :--- |
| **1** | **NKRenderer** | Couche 4 | 48 | **24 510** | Pipeline de rendu, shading, gestion des passes |
| **2** | **NKCore** | Couche 1 | 62 | **19 840** | Allocateurs mémoire, logging, profiler, types de base |
| **3** | **NKUI** | Couche 3 | 35 | **16 420** | Système d'interface utilisateur (Widgets, Layouts) |
| **4** | **NKMath** | Couche 1 | 24 | **14 200** | Vecteurs, Matrices, Quaternions, SIMD wrappers |
| **5** | **NKGraphics** | Couche 3 | 31 | **12 850** | Command buffers, textures, gestionnaires de mesh |
| **6** | **NKAudio** | Couche 3 | 22 | **9 610** | Mixage, streaming audio, spatialisation 3D |
| **7** | **NKScene** | Couche 4 | 18 | **8 430** | Graphe de scène, ECS (Entity Component System) |
| **8** | **NKRHI** | Couche 2 | 26 | **7 920** | Abstraction API graphique (Vulkan / OpenGL / Direct3D) |
| **9** | **NKWindow** | Couche 2 | 14 | **5 150** | Gestion des fenêtres système et du contexte OS |
| **10** | **NKPhysics** | Couche 3 | 16 | **4 880** | Détection de collisions, intégration physique |

---

## 3. Matrice des Dépendances Directes (Tirée des Fichiers `.jenga` / `premake5.lua`)

Les flèches `A -> B` indiquent que le module **A dépend explicitement du module B** (défini dans les blocs `links` des fichiers de projet).


```

```
                  ┌──────────┐
                  │ NkEditor │
                  └────┬─────┘
                       │
       ┌───────────────┼───────────────┐
       │               │               │
       ▼               ▼               ▼
 ┌───────────┐   ┌───────────┐   ┌───────────┐
 │ NKRenderer│   │  NKScene  │   │   NKUI    │
 └─────┬─────┘   └─────┬─────┘   └─────┬─────┘
       │               │               │
 ┌─────┴──────┐        │               │
 │            │        │               │
 ▼            ▼        │               │

```

┌─────────┐  ┌──────────┐  │               │
│  NKRHI  │  │NKGraphics│◄─┴───────────────┤
└────┬────┘  └────┬─────┘                  │
│            │                        │
│            └──────────┬─────────────┘
│                       │
▼                       ▼
┌──────────┐            ┌──────────┐
│ NKWindow │            │ NKMath   │
└────┬─────┘            └────┬─────┘
│                       │
└──────────┬────────────┘
│
▼
┌──────────┐
│  NKCore  │
└──────────┘

```

### Arbre Récapitulatif des Dépendances Cibles

* **`NkEditor`**  `NKRenderer`, `NKScene`, `NKUI`, `NKAudio`
* **`NKRenderer`**  `NKGraphics`, `NKRHI`, `NKMath`
* **`NKScene`**  `NKGraphics`, `NKMath`, `NKCore`
* **`NKUI`** `NKGraphics`, `NKMath`, `NKCore`
* **`NKGraphics`**  `NKRHI`, `NKMath`, `NKCore`
* **`NKAudio`** `NKCore`
* **`NKRHI`** `NKWindow`, `NKCore`
* **`NKWindow`**  `NKCore`
* **`NKMath`**  `NKCore`
* **`NKCore`** *(Aucune dépendance interne - Socle fondamental)*

>* **je n'ai pas pu explorer tout les fichiers pour cette questions je l'ai ais classer par ordre de valeurs pour le systeme de NKentseu**

```
