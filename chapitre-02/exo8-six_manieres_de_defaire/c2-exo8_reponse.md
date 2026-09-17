


# Réponses à l'exercice : Manipulations et annulations avec Git

## 1. Une modification non voulue
- **Provoquer la situation :** Modification accidentelle du fichier `main.cpp` j'ai effacer un commantaire `/*affiche*/`
- **D'abord enregistrer avec un `crtl+s`**  
- **Commande pour annuler la modification :**

```bash
git restore main.cpp
```
 

* **Vérification :** Le répertoire de travail est redevenu propre et mon commentaire est revenu
 

---

## 2. Un `add` de trop

* **Provoquer la situation :** Exécution de `git add main.cpp` par erreur.
* **Commande pour retirer le fichier de l'index :**
```bash
git restore --staged main.cpp

```


* **Vérification (`git status`) :** Le fichier apparaît à nouveau dans les modifications non indexées (*Changes not staged for commit*).

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
commit f99e57f7a65e6bd2437820f5a720b06fea31f3b8 (HEAD -> main, origin/main, origin/HEAD)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 11:26:31 2026 +0200

    modification
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
PS C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-02\exo8-six_manieres_de_defaire> git revert HEAD --no-edit
[main 542c9a1] Revert "erreur de pousse"
 Date: Thu Sep 17 12:42:03 2026 +0200
 1 file changed, 7 deletions(-)
 delete mode 100644 chapitre-02/exo8-six_manieres_de_defaire/main.cpp

**git push**

 [main 542c9a1] Revert "erreur de pousse"
 Date: Thu Sep 17 12:42:03 2026 +0200
 1 file changed, 7 deletions(-)
 delete mode 100644 chapitre-02/exo8-six_manieres_de_defaire/main.cpp
PS C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-02\exo8-six_manieres_de_defaire> git push
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 312 bytes | 312.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/noumssiprisca6-star/ani-2053.git
   2994b43..542c9a1  main -> main
```



* **Vérification (`git log -2`) :** Un nouveau commit d'annulation (*Revert "..."*) a été créé et poussé sur le serveur.
* **Resultat**
```bash
commit 542c9a1c7ea19eb28a834df78aed95d5cb6de3d4 (HEAD -> main, origin/main, origin/HEAD)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 12:42:03 2026 +0200

    Revert "erreur de pousse"
    
    This reverts commit 2994b4317620a0fe6384a41a52349d5405e90a45.

commit 2994b4317620a0fe6384a41a52349d5405e90a45
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 12:40:59 2026 +0200

    erreur de pousse
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
Saved working directory and index state WIP on main: 542c9a1 Revert "erreur de pousse"
```


* **Commande pour restaurer le travail mis de côté :**
```bash
git stash pop

```


* **Vérification (`git status`) :** Les modifications en cours sont revenues dans le répertoire de travail.

---

## 6. Un commit « perdu » à retrouver par le reflog

* **Provoquer la situation :** Suppression forcée du dernier commit avec `git reset --hard HEAD~1`.
* **Commande pour afficher l'historique complet des actions :**
```bash
git reset --hard HEAD~1

```
* **Resultat**
```bash
HEAD is now at 542c9a1 Revert "erreur de pousse"
```
* **Commande pour afficher l'historique complet des actions :**
```bash
git reflog
```
* **Resultat**
```bash
542c9a1 (HEAD -> main, origin/main, origin/HEAD) HEAD@{0}: reset: moving to HEAD~1
58c6d55 HEAD@{1}: commit: commit perdu a retrouver
542c9a1 (HEAD -> main, origin/main, origin/HEAD) HEAD@{2}: reset: moving to HEAD
542c9a1 (HEAD -> main, origin/main, origin/HEAD) HEAD@{3}: revert: Revert "erreur de pousse"
2994b43 HEAD@{4}: commit: erreur de pousse
f99e57f HEAD@{5}: reset: moving to HEAD~1
5e7031d HEAD@{6}: commit: un commit qui sera annule
f99e57f HEAD@{7}: commit: modification
773403b HEAD@{8}: commit: finalisation de l'exercice sur la creation de branche
61e8f2c (test-taille) HEAD@{9}: merge test-taille: Fast-forward
f77224a HEAD@{10}: checkout: moving from test-taille to main
61e8f2c (test-taille) HEAD@{11}: commit: ajout du fichier .md
cc5adb1 HEAD@{12}: commit: la taille par branche mesurer
80c7d0e HEAD@{13}: commit: Mon troisieme et dernier ajout : les commentaires
42637cf HEAD@{14}: commit: mon deuxieme ajout : une fonction entiere pour gerer l'addition
de076a3 HEAD@{15}: commit: mon premier ajout : la fonction principale main
f77224a HEAD@{16}: checkout: moving from main to test-taille
f77224a HEAD@{17}: commit: le commit partiel
defb6ba HEAD@{18}: commit: le commit partiel
2503e8b HEAD@{19}: commit: fichier: mis a jour du titre
42570c4 HEAD@{20}: commit: document initial
785e1ae HEAD@{21}: commit: modifications du message de git
8486071 HEAD@{22}: commit: inspiration du commit de nkentseu.
43ac04f HEAD@{23}: commit: inspiration du commit de nkentseu
3a8d618 HEAD@{24}: commit: Les trois endroits
86af1b4 HEAD@{25}: commit: les trois endroits
0e20e92 HEAD@{26}: commit: modification d'un fichier et verification des git status
8c359d3 HEAD@{27}: commit: sans oublier le md
90c2966 HEAD@{28}: reset: moving to HEAD~1
ec26723 HEAD@{29}: commit: Reinitialisation du dossier exo1
90c2966 HEAD@{30}: reset: moving to origin/main
90c2966 HEAD@{31}: reset: moving to origin/main
90c2966 HEAD@{32}: commit: je ne dois pas oublier mon fichier .md
e61fd1e HEAD@{33}: commit: mon toisiemecommit
ed4c864 HEAD@{34}: commit: mon deuxieme commit
3f8ca77 HEAD@{35}: commit: mon premier commit
9148e6e HEAD@{36}: reset: moving to HEAD~1
e96c8c2 HEAD@{37}: commit: mon premier commit
9148e6e HEAD@{38}: commit: reconstitution
14c95d7 HEAD@{39}: commit: la deuxiemme machine
5997d29 HEAD@{40}: commit: les temps
2231882 HEAD@{41}: commit: les explications
4b1e901 HEAD@{42}: commit: NKREF
dde9df0 HEAD@{43}: commit: les tests
6820bb4 HEAD@{44}: commit: erreur dans nkmath
58debb1 HEAD@{45}: commit: les dependances dans NKCanvas
fb42b18 HEAD@{46}: commit: Remarques sur NKRef
d4d6e90 HEAD@{47}: commit: mon observation
2198d6f HEAD@{48}: commit: le temps de construction
4ee6dcc HEAD@{49}: commit: annotations exercices 4
59034ce HEAD@{50}: commit: les dependances
f74f744 HEAD@{51}: commit: dependson et links
5ae0ebe HEAD@{52}: commit: les deux erreurs de dependances
e96d930 HEAD@{53}: commit: amelioration de mon premier projet pour l'exercice 5.
bc96d81 HEAD@{54}: commit: amelioration de mon premier projet pour l'exercice 5
fb0311e HEAD@{55}: commit: amelioration de mon premier projet pour l'exercice 5
7291d24 HEAD@{56}: commit: mon premier essai
14b124d HEAD@{57}: commit: mon arborescence NKMath
ca327df HEAD@{58}: commit: mon arborescence NKMath
4e63e3f HEAD@{59}: commit: mon arborescence
ba429b7 HEAD@{60}: commit: mon arborescence
7cc3e35 HEAD@{61}: commit: mon programme
f32c53e HEAD@{62}: commit: mesurer avant de croire
4993d33 HEAD@{63}: commit: ma reponse modifie
e027c06 HEAD@{64}: commit: ma reponse
f89faa3 HEAD@{65}: clone: from https://github.com/noumssiprisca6-star/ani-2053.git
(END)

```

* **Vérification (`git log -1`) :** Le commit effacé est de nouveau le commit le plus récent.

```bash
commit 17507ed18dc50d1ac59f8195252138fd09ceae4a (HEAD -> main)
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 13:32:50 2026 +0200

    commit de retour

