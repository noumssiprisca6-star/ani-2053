
>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git

# Comparaison des Stratégies d'Intégration Git : Merge vs Rebase

Ce document présente la comparaison entre une intégration par **fusion (`git merge`)** et une intégration par **rejeu (`git rebase`)** sur un même dépôt d'essai, ainsi que l'analyse des graphes d'historique résultants.

---

## 1. Intégration par Fusion (`git merge`)

La fusion conserve la branche de travail séparée et crée un **commit de fusion** (*merge commit*) pour relier l'historique de la branche à la branche principale `main`.
modification de la ligne 4 du fichier `main.cpp` dans mon depot mon `MonEssaie`

### Commandes exécutées :
```bash
git checkout -b test-merge
# [Modification du fichier main.cpp ligne quatre , mofification de la sortie avec un remplacement de phrase]
git add main.cpp
git commit -m " ajout de la fonction merge"

git checkout main
git commit -m "mise a jour de la documentation"
git merge test-merge -m "Merge branch 'test-merge' into main"

```
* **Resultat**
```bash 
Updating fce2868..c0b2c46
Fast-forward (no commit created; -m option ignored)
 exo1_modification/main.cpp | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
 ```

---

## 2. Intégration par Rejeu (`git rebase`)

Le rejeu prend les commits de la branche de travail et les **réécrit au sommet** de la branche `main`. Il réaligne l'historique avant d'effectuer la fusion.

### Commandes exécutées :

```bash
git checkout -b test-rebase
# [Modification du fichier main.cpp ligne 5 ]
git add main.cpp
git commit -m " ajout de la fonction rebase"

git checkout main
git commit -m " nettoyage du code"

 * **le jeu de la branche sur main**

 ```bash
git checkout test-rebase
git rebase main
```
* **Resultat**
```bash
Successfully rebased and updated refs/heads/test-rebase.
```


# Intégration finale sur main (Fast-Forward)
```bash
git checkout main
git merge test-rebase
```

---

## 3. Comparaison des Graphes d'Historique

Commande d'affichage du graphe :

```bash
git log --graph --oneline --all

```

### Visualisation du Graphe :

```text
* afcc158 (HEAD -> main, test-rebase) ajout de la fonction rebase
* c0b2c46 (test-merge)  ajout de la fonction merge
* fce2868 ajout de la fonction merge
* 9fb64fc (origin/main, origin/HEAD) modification ligne 3 du repertoire 1 MonEssaie
* 2a326d7 conflit resolu
*   880732f  resolution du conflit
|\  
| * de87a31  modification par le premier depot
* | 30c8f05 modification par le second depot
|/  
* 34228c2 erreur pousse
* abdd5a9 mon troisieme commit
* 5c267e5 deuxieme commit
* 8b3267f ajout de mon premier fichier du depot pour l'exercice du chapitre 2
* 5f5684a Initial commit
```

---



## 3. Analyse des Différences

1. **Intégration par `git merge` :**
* Visible dans la partie inférieure du graphe (`880732f`).
* Conserve la trace visuelle de la branche parallèle (`de87a31` et `30c8f05`).
* Génère un commit de fusion explicite pour réunir les deux branches.


2. **Intégration par `git rebase` :**
* Visible dans la partie supérieure du graphe (`afcc158`).
* Supprime la bifurcation visuelle en réécrivant les commits au sommet de `main`.
* Produit un historique entièrement linéaire et continu.


### Tableau comparatif

| Critère | Intégration par Fusion (`git merge`) | Intégration par Rejeu (`git rebase`) |
| --- | --- | --- |
| **Structure du graphe** | **Non-linéaire** : Présence de boucles, de croisements (` | `) et de branches parallèles. |
| **Commit de fusion** | **Oui** : Crée un commit de fusion supplémentaire (ex: *Merge branch 'xxx' into main*). | **Non** : Aucun commit de fusion n'est créé, la branche est intégrée de façon transparente. |
| **Modification de l'historique** | **Non** : Conserve l'historique exact, chronologique et réel du travail de l'équipe. | **Oui** : Réécrit l'historique en replaçant vos commits au sommet de la branche cible. |
| **Gestion des conflits** | Résolus **une seule fois** dans le commit de fusion. | Résolus **commit par commit** au moment de rejouer la branche. |
| **Lisibilité (pour l'équipe)** | Devient **complexe et chargé** quand plusieurs personnes travaillent en même temps. | **Excellente et très propre** : Idéal pour auditer l'historique ou rechercher des bugs. |

---

* **Utiliser `git merge**` : Quand on veut garder la trace exacte et historique de la branche de travail.
* **Utiliser `git rebase**` : Quand on veut maintenir un historique propre, lisible et linéaire sur le projet.
---

## 4. Préférence Argumentée

**Choix : Je préfère lire le graphe issu du Rejeu (`git rebase`).**

**Arguments :**

1. **Suppression du « bruit » visuel :**
* **Sur le Merge (partie basse du graphe) :** On observe une boucle avec des lignes croisées (`|\` et `|/`) et la création de commits de fusion supplémentaires (*resolution du conflit*). Dans un projet d'équipe avec des dizaines de branches, ce système crée un effet « sac de nœuds » très difficile à relire.
* **Sur le Rebase (partie haute du graphe) :** Le résultat se résume à une **seule colonne d'étoiles (`*`) parfaitement alignées**. Il n'y a aucune bifurcation ni croisement de lignes.


2. **Gain de lisibilité et gain de place :**
* Avec `git rebase`, chaque modification apparaît de façon séquentielle, comme si le travail avait été réalisé de manière fluide les uns après les autres.
* L'historique ne contient **aucun commit de fusion parasite** (du type *Merge branch...*), ce qui simplifie le suivi des fonctionnalités et la recherche de bugs ultérieure.

 ainsi donc on a  :

* **Lisibilité optimale :** L'historique en ligne droite est beaucoup plus simple à suivre pour l'équipe, évitant le "sac de nœuds" visuel lorsque plusieurs développeurs travaillent en parallèle.
* **Historique propre :** Il n'y a pas de commits de fusion inutiles, ce qui facilite les recherches de bugs dans l'historique du projet.



> **Je préfère le Rebase** car il transforme un historique complexe et bifurqué en un **fil conducteur unique et linéaire**, rendant la lecture du dépôt immédiate et agréable pour toute l'équipe.
