
# Démonstration : Destruction par `git reset --hard` et Récupération via `git reflog`

**Objectif  :** Simuler la perte définitive d'un travail suite à un `reset --hard`, constater la disparition du commit et du fichier sur le disque, puis restaurer l'intégralité du dépôt grâce au journal d'actions `git reflog`.

---
>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git
---

## 1. Phase 1 : Création du Travail et Sauvegarde

Création d'un fichier contenant du code important et enregistrement dans l'historique Git. `cd MonEssaie/cd mes_demos`

```bash
git add important.cpp
git commit -m " ajout du travail super important"

```

* **Vérification dans l'historique (`git log --oneline -n 2`) :**
> Le commit est bien enregistré au sommet de la branche avec son hash (`8e1243b `).



---

## 2. Phase 2 : Destruction Volontaire par `reset --hard`

Retour forcé au commit précédent (`HEAD~1`), effaçant les modifications dans la zone de travail et dans l'index.

```bash
git reset --hard HEAD~1

```

### Constat de la perte devant la classe :

1. **Dans l'explorateur de fichiers / terminal :** Le fichier `important.cpp` a totalement disparu .
2. **Dans l'historique (`git log --oneline`) :** Le commit ` ajout du travail super important` n'apparaît plus du tout dans la liste.

> *À ce stade, pour un utilisateur , le travail semble définitivement perdu.*

---

## 3. Phase 3 : Investigation avec `git reflog`

Git conserve un journal secret de tous les mouvements du pointeur `HEAD`. On l'interroge pour retrouver le commit "disparu".

```bash
git reflog

```

**Résultat affiché dans le terminal :**

```bash
c569085 (HEAD -> main) HEAD@{0}: reset: moving to HEAD~1
8e1243b HEAD@{1}: commit: ajout du travail super important
c569085 (HEAD -> main) HEAD@{2}: commit (merge): resolution du conflit sur test .cpp
13601be HEAD@{3}: checkout: moving from feature to main
042ed95 (feature) HEAD@{4}: commit: modification du message sur feature
e15be64 HEAD@{5}: checkout: moving from main to feature
13601be HEAD@{6}: commit: modification du message sur main
45fb5e9 (origin/main, origin/HEAD) HEAD@{7}: checkout: moving from main to main
45fb5e9 (origin/main, origin/HEAD) HEAD@{8}: commit (merge): resolution es conflits
6962d2c HEAD@{9}: checkout: moving from main to main
6962d2c HEAD@{10}: checkout: moving from main to main
6962d2c HEAD@{11}: merge feature: Merge made by the 'ort' strategy.
bbadd86 HEAD@{12}: commit: correction du bug sur main
a2d8464 HEAD@{13}: checkout: moving from feature to main
e15be64 HEAD@{14}: commit: ajout de la nouvelle foctionnalite
a2d8464 HEAD@{15}: checkout: moving from main to feature
a2d8464 HEAD@{16}: commit: initialisation du projet

```

* **Analyse :** La ligne `HEAD@{1}` conserve l'empreinte du commit supprimé sous l'identifiant **`8e1243b `**.

---

## 4. Phase 4 : Restauration et Annulation de la Destruction

On repositionne la branche `main` sur le hash du commit retrouvé dans le `reflog`.

```bash
git reset --hard 8e1243b

```

### Constat de la récupération :

1. **Vérification du fichier :**
 * **Resultat**
 ```bash
 HEAD is now at 8e1243b  ajout du travail super important
 ```


>  Le fichier est de retour sur le disque avec l'intégralité de son contenu , je peux de nouveau l'apercevoir dans l'hitorique de fichier et dans mon explorateur sur vscode


2. **Vérification de l'historique :**
```bash
git log --oneline 

```
* **Resultat**
```bash
8e1243b (HEAD -> main)  ajout du travail super important
c569085 resolution du conflit sur test .cpp
042ed95 (feature) modification du message sur feature
13601be modification du message sur main
```

>  Le commit réapparaît à sa place dans l'arbre Git.



---

##  Bilan 

* **`git reset --hard`** détruit le travail présent dans l'arbre de travail et masque le commit dans l'historique standard `git log`.
* **`git reflog`** est le journal de secours ultime : il enregistre **chaque déplacement de HEAD**. Tant que Git n'a pas nettoyé sa mémoire cache , aucun commit validé n'est réellement perdu ce qui est tres encourageant pour la suite du travail .

