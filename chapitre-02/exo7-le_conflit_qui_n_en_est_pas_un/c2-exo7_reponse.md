
# Démonstration : Fusion Automatique Git (Auto-Merge sans conflit)

Ce document illustre la capacité de Git à assembler automatiquement deux modifications distantes apportées sur le même fichier, mais à des emplacements différents.

---

## 1. Première modification et envoi (Clone A)

Modification apportée au **haut du fichier `Fichier3.cpp`**  ligne 3 dans ` MonEssaie/exo1_modification`, suivie de la validation et du push.

**Commande exécutée :**
```bash
git add .
git  commit -m "modification ligne 3 du repertoire 1 MonEssaie"
git push 

```

**Message affiché :**

```bash
[main 9fb64fc] modification ligne 3 du repertoire 1 MonEssaie
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\jouvence computer\Desktop\ex\MonEssaie\exo1_modification> git push
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 4 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 368 bytes | 368.00 KiB/s, done.
Total 4 (delta 3), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (3/3), completed with 3 local objects.
To https://github.com/noumssiprisca6-star/MonEssaie.git
   2a326d7..9fb64fc  main -> main

```

---

## 2. Seconde modification et refus initial (Clone B)

Modification apportée au **bas du fichier `Fichier3.cpp`** dans `SecondRep/MonEssaie/exo1_modifiaction` ligne 5 sans récupération préalable des changements de `  MonEssaie`.

**Commande de push exécutée :**

```bash
git add .
git commit -m "Modification du bas du fichier par  SecondRep "
git push 

```

**Message de refus affiché :**

```bash
[main ff2fe46] Modification du bas du fichier par  SecondRep
 1 file changed, 1 insertion(+), 1 deletion(-)
PS C:\Users\jouvence computer\Desktop\ex\SecondRep\MonEssaie\exo1_modification> git push
To https://github.com/noumssiprisca6-star/MonEssaie.git
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'https://github.com/noumssiprisca6-star/MonEssaie.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.

```

---

## 3. Fusion automatique par Git (Auto-Merge)

Exécution du `git pull` pour intégrer les modifications distantes de A dans B.

**Commande exécutée :**

```bash
git pull 

```

**Message de fusion automatique affiché :**

```bash
Merge branch 'main' of https://github.com/noumssiprisca6-star/MonEssaie
# Please enter a commit message to explain why this merge is necessary,
# especially if it merges an updated upstream into a topic branch.
#
# Lines starting with '#' will be ignored, and an empty message aborts
# the commit.
~                                                                                                                 
~                                                                                                                 
~                                                                                                                 
~                                                                                                                 
~                                                                                                                 
~                                                                                                                 
~                                                                                                                 
.git/MERGE_MSG [unix] (01:33 18/09/2026)                                                                  1,1 Tout
"~/Desktop/ex/SecondRep/MonEssaie/.git/MERGE_MSG" [unix] 6L, 298B                                         

```


**Commande exécutée :**
(Le : fait apparaître le curseur en bas à gauche, w signifie écrire/sauvegarder, et q signifie quitter).

```bash
PS C:\Users\jouvence computer\Desktop\ex\SecondRep\MonEssaie\exo1_modification> git pull
remote: Enumerating objects: 12, done.
remote: Counting objects: 100% (12/12), done.
remote: Compressing objects: 100% (4/4), done.
remote: Total 8 (delta 6), reused 6 (delta 4), pack-reused 0 (from 0)
Unpacking objects: 100% (8/8), 641 bytes | 13.00 KiB/s, done.
From https://github.com/noumssiprisca6-star/MonEssaie
   880732f..9fb64fc  main       -> origin/main
Merge made by the 'ort' strategy.
 exo1_modification/Fichier3.cpp | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```
---

## 4. Validation et Push final (Clone B sur SecondRep)

Envoi de la version combinée sur le dépôt distant.

**Commande exécutée :**

```bash
git push 

```

**Message de confirmation affiché :**

```bash
Enumerating objects: 19, done.
Counting objects: 100% (18/18), done.
Delta compression using up to 4 threads
Compressing objects: 100% (11/11), done.
Writing objects: 100% (11/11), 1.14 KiB | 291.00 KiB/s, done.
Total 11 (delta 7), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (7/7), completed with 3 local objects.
To https://github.com/noumssiprisca6-star/MonEssaie.git
   9fb64fc..ff48a8a  main -> main
```

---

## 5. Résultat 

Le fichier contient désormais les deux modifications assemblées :

 * **Commande**
 ```bash 
 git log --oneline -n 5
 ```

```bash
ff48a8a (HEAD -> main, origin/main, origin/HEAD) Merge branch 'main' of https://github.com/noumssiprisca6-star/MonEssaie
```


