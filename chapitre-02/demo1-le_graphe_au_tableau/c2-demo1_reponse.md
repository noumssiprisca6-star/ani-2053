
#   Exercice Graphe de Commits Git

>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git

## Étape 1 : Création du Dépôt et Premier Commit (Commit A)

**Actions exécutées :**
un nouveau depot appeler MonEssaie fut creer 
emplacement `ex/MonEssaie/mes_demos`
```bash

git add Doc.md
git commit -m " ajout d'une documentation descriptive a titrre d'essaie dasn mon nouveau depot appeler MonEssaie"

```

* **Mon Commit A (Hash réel) :** `0e2cfd3`
* **Message de commit :** ` ajout d'une documentation descriptive a titrre d'essaie dasn mon nouveau depot appeler MonEssai`

---

## Étape 2 : Création du Point de Divergence (Commit B)

**Commandes exécutées :**

```bash
git add test.cpp
git commit -m "initialisation du projet"

```

* **Mon Commit B (Hash réel) :** `a2d8464`
* **Message de commit :** `initialisation du projet`
* **Rôle dans mon exercice :** C'est le **point de divergence** à partir duquel la branche `feature` sera créée.

---

##  Étape 3 : Branche `feature` et Premier Travail (Commit D)

**Commandes exécutées :**

```bash
git checkout -b feature
git add test.cpp
git commit -m "ajout de la nouvelle fonctionnalite"

```

* **Mon Commit D (Hash réel) :** `e15be64` 
* **Message de commit :** ` ajout de la nouvelle fonctionnalite`
* **Branche actuelle :** `feature`

---

##  Étape 4 : Travail Parallèle sur `main` (Commit C)

**Commandes exécutées :**

```bash
git checkout main
git add Doc.md
git commit -m "correction de bug sur main"

```

* **Mon Commit C (Hash réel) :** `bbadd86`  
* **Message de commit :** `fix: correction de bug sur main`
* **Branche actuelle :** `main`

---

## Étape 5 : Fusion des Branches (Commit M - Merge Commit)

**Commandes exécutées :**

```bash
git merge feature -m "Merge branch 'feature' into main"

```
* **Resultat**
```bash
Merge made by the 'ort' strategy.
 mes_demos/test.cpp | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
 ```

* **Mon Commit M (Hash réel) :** `6962d2c`
* **Message de commit :** `Merge branch 'feature' into main`
* **Rôle dans l'exercice :** Commit de fusion réunissant `feature` dans `main`.

---

##  Étape 6 : Captures et Rendu Final

### 1. la sortie obtenu plus bas s'obtient avec la commande  `git log --graph --oneline --all` 


### 2. Mon Schéma "Tableau" (Représentation Visuelle)

```
    *   6962d2c (HEAD -> main) Merge Branch ^Leatureinto main
|\  
| * e15be64 (feature) ajout de la nouvelle foctionnalite
* | bbadd86 correction du bug sur main
|/  
* a2d8464 initialisation du projet
* 0e2cfd3 ajout d'une documentation descriptive a titre d'essaie dans mon nouveau depot appeler MonEssaie
* 89f463b suppression de la video
* e4ff8cf ajout d'une  video de 10Mo
* afcc158 (test-rebase) ajout de la fonction rebase
* c0b2c46 (test-merge)  ajout de la fonction merge
* fce2868 ajout de la fonction merge
* 9fb64fc (origin/main, origin/HEAD) modification ligne 3 du repertoire 1 MonEssaie
* 2a326d7 conflit resolu
*   880732f  resolution du conflit
|\  
| * de87a31  modification par le premier depot
:

```

---

### 3. Tableau de Correspondance Final



| Identifiant du Schéma | Votre Hash Réel | Message du Commit | Rôle dans le Graphe |
| --- | --- | --- | --- |
| **A** | `0e2cfd3` | `ajout d'une documentation descriptive...` | Commit de base avant divergence |
| **B** | `a2d8464` | `initialisation du projet` | **Point de divergence** |
| **C** | `bbadd86` | `correction du bug sur main` | Commit propre à la branche `main` |
| **D** | `e15be64` | `ajout de la nouvelle foctionnalite` | Commit propre à la branche `feature` |
| **M** | `6962d2c` | `Merge Branch ^Leatureinto main` | **Commit de fusion (Merge Commit)** |

---


>**Un point de divergence dans Git est le dernier commit commun partagé par deux branches avant qu'elles ne se séparent et n'évoluent indépendamment l'une de l'autre.**






