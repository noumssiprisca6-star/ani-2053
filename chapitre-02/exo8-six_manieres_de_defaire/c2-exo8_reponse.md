


# Réponses à l'exercice : Manipulations et annulations avec Git

>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git

## 1. Une modification non voulue
- **Provoquer la situation :** Modification accidentelle du fichier `main.cpp` j'ai effacer un commantaire `/*affiche*/`
- **D'abord enregistrer avec un `crtl+s`**  
- **Commande pour annuler la modification :**

```bash
git restore main.cpp
```
 

* **Vérification :**  mon commentaire est revenu
 

---

## 2. Un `add` de trop

* **Provoquer la situation :** Exécution de `git add main.cpp` par erreur.
* **Commande pour retirer le fichier de l'index :**
```bash
git restore --staged main.cpp

```


* **Vérification (`git status`) :** Le fichier apparaît à nouveau dans les modifications non indexées (*Changes not staged for commit*) , le fichier est toujours modifié mais n'est plus prêt à être commité.
```bash 
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        main.cpp

nothing added to commit but untracked files present (use "git add" to track)
```
---

## 3. Un commit de trop (en local)

* **Provoquer la situation :** Création d'un commit local inutile avec `git commit -m "un commit qui sera annule"`.
* **Commande pour annuler le commit tout en gardant les modifications :**
```bash
git reset HEAD~1

```


* **Vérification (`git log -1`) :** Le dernier commit est désormais le commit précédent.
* **Resultat**
```bash
commit abdd5a9548f63f10c8a9936d210cbfb5fe2f16fd (HEAD -> main, origin/main, origin/HEAD)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 15:19:42 2026 +0200

    mon troisieme commit
```

---

## 4. Un commit poussé qu'il faut annuler

* **Provoquer la situation :** Envoi d'un commit mauvais sur le dépôt distant avec `git push`.
* **Commande pour annuler proprement le commit poussé :**
```bash
git revert HEAD --no-edit
git push

```
```bash

**git revert HEAD --no-edit**

[main ff0c14a] Revert "erreur pousse"
 Date: Thu Sep 17 16:36:36 2026 +0200
 1 file changed, 7 deletions(-)
 delete mode 100644 exo1_modification/main.cpp

**git push**

Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 306 bytes | 306.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/noumssiprisca6-star/MonEssaie.git
   34228c2..ff0c14a  main -> main
 
```



* **Vérification (`git log -2`) :** Un nouveau commit d'annulation (*Revert "..."*) a été créé et poussé sur le serveur.
* **Resultat**
```bash
ommit 34228c2fcdc88863f7e8c01c768e3947cb974d0e
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 16:36:15 2026 +0200

    erreur pousse
```

---

## 5. Un travail en cours qu'il faut mettre de côté

* **Provoquer la situation :** Réalisation de modifications non finies dans un fichier.
* **Commande pour sauvegarder temporairement le travail :**
```bash
git stash

```
* **Resultat**
```bash
Saved working directory and index state WIP on main: ff0c14a Revert "erreur pousse"
```


* **Commande pour restaurer le travail mis de côté :**
```bash
git stash pop

```


* **Vérification (`git status`) :** Les modifications en cours sont revenues dans le répertoire de travail.
```bash 
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   main.cpp

Dropped refs/stash@{0} (13bff248b80f178f063292faa668ac7184447e71)
```

---

## 6. Un commit « perdu » à retrouver par le reflog

* **Provoquer la situation :** Suppression forcée du dernier commit avec `git reset --hard HEAD~1`.
* **Commande pour afficher l'historique complet des actions :**
```bash
git reset --hard HEAD~1

```
* **Resultat**
```bash
HEAD is now at ff0c14a Revert "erreur pousse"
```
* **Commande pour afficher l'historique complet des actions :**
```bash
git reflog
```
* **Resultat**
```bash
ff0c14a (HEAD -> main, origin/main, origin/HEAD) HEAD@{0}: reset: moving to HEAD~1
348fb63 HEAD@{1}: commit: commit perdu a retrouver
ff0c14a (HEAD -> main, origin/main, origin/HEAD) HEAD@{2}: reset: moving to HEAD
ff0c14a (HEAD -> main, origin/main, origin/HEAD) HEAD@{3}: revert: Revert "erreur pousse"
34228c2 HEAD@{4}: commit: erreur pousse
abdd5a9 HEAD@{5}: reset: moving to HEAD~1
ceae919 HEAD@{6}: commit: commit a annuler
abdd5a9 HEAD@{7}: commit: mon troisieme commit
5c267e5 HEAD@{8}: commit: deuxieme commit
8b3267f HEAD@{9}: commit: ajout de mon premier fichier du depot pour l'exercice du chapitre 2
5f5684a HEAD@{10}: clone: from https://github.com/noumssiprisca6-star/MonEssaie.git

```

* **Vérification (`git log -1`) :** Le commit effacé est de nouveau le commit le plus récent.

```bash
commit ff0c14a0c4599e44d79de9de3b07675b52c6c5c8 (HEAD -> main, origin/main, origin/HEAD)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 16:36:36 2026 +0200

    Revert "erreur pousse"
    
    This reverts commit 34228c2fcdc88863f7e8c01c768e3947cb974d0e.
```

verification si le commit effacer est revenu 
```bash
git reset --hard 34228c2fcdc88863f7e8c01c768e3947cb974d0e 
```
puis 
```bash
git log -1
```
* **Resultat**
```bash
commit 34228c2fcdc88863f7e8c01c768e3947cb974d0e (HEAD -> main)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 16:36:15 2026 +0200

erreur pousse
```
