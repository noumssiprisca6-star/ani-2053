
```markdown
# Compte-Rendu : Cycle de vie d'un fichier dans Git

## 1. État après modification d'un fichier

**Commande exécutée :**
```bash
git status

```

**Sortie de `git status` :**

```text
On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
	modified:   Test.cpp

no changes added to commit (use "git add" and/or "git commit -a")

```

---

## 2. État après l'ajout à la zone de transit (`git add`)

**Commandes exécutées :**

```bash
git add Test.cpp 
git status

```

**Sortie de `git status` :**

```text
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   Test.cpp

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../../chapitre-01/demo4-le_plan_du_million_de_lignes/c1-demo4_reponse.md
        modified:   ../../chapitre-01/exo13-la_deuxieme_machine/c1-exo13_reponse.md
        modified:   ../../chapitre-01/exo2-mesurer_avant_de_croire/c1-exo2_reponse.md
        modified:   ../../chapitre-01/exo7-le_temps_que_ca_prend/c1-exo7_reponse.md

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        c2-exo2_reponse.md

```
 * **inclusion de toutes les modifications**
 **Commandes exécutées :**
 ```bash
 git add .
 ```
 **Sortie de `git status` :**
 ```
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   Test.cpp
        new file:   c2-exo2_reponse.md

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../../chapitre-01/demo4-le_plan_du_million_de_lignes/c1-demo4_reponse.md
        modified:   ../../chapitre-01/exo13-la_deuxieme_machine/c1-exo13_reponse.md
        modified:   ../../chapitre-01/exo2-mesurer_avant_de_croire/c1-exo2_reponse.md
        modified:   ../../chapitre-01/exo7-le_temps_que_ca_prend/c1-exo7_reponse.md
```

 
---

## 3. État après la validation (`git commit`)

**Commandes exécutées :**

```bash
git commit -m "modification d'un fichier et verification des git status"
git status

```

**Sortie de `git status` :**

```text
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   ../../chapitre-01/demo4-le_plan_du_million_de_lignes/c1-demo4_reponse.md
        modified:   ../../chapitre-01/exo13-la_deuxieme_machine/c1-exo13_reponse.md
        modified:   ../../chapitre-01/exo2-mesurer_avant_de_croire/c1-exo2_reponse.md
        modified:   ../../chapitre-01/exo7-le_temps_que_ca_prend/c1-exo7_reponse.md
        modified:   c2-exo2_reponse.md


```

---

## 4. Analyse des changements entre chaque étape

1. **Entre la modification et le `git add` :**
* **Ce qui change :** Le fichier passe du statut *Changes not staged for commit* (non indexé, rouge) au statut *Changes to be committed* (indexé, vert).
* **Explication :** Git a placé la modification dans la zone de transit (*staging area*). Elle est désormais enregistrée dans l'index et prête à faire partie du prochain snapshot.




2. **Entre le `git add` et le `git commit` :**

* **Ce qui change** : Les fichiers cibles (Test.cpp et c2-exo2_reponse.md) quittent la zone de transit (Changes to be committed). La branche locale passe à Your branch is ahead of 'origin/main' by 1 commit.

* **Explication** : Git crée un nouvel objet commit contenant les fichiers présents dans la zone de transit et fait avancer le pointeur de la branche. Les fichiers restés hors de la zone de transit (les fichiers du chapitre-01) demeurent non indexés.

* **Comprehension** :
` git add (Préparer) `: Copie vos modifications dans la zone de transit (staging area). Elle vous permet de sélectionner précisément quels fichiers ou quelles modifications vous souhaitez inclure dans votre prochain enregistrement.
` git status (Observer)` : Permet d'inspecter l'état actuel de votre travail. Elle affiche les fichiers qui ont été modifiés, ceux qui sont prêts à être enregistrés (dans la zone de transit) et ceux qui ne sont pas encore suivis par Git.    


`git commit (Enregistrer)` : Valide et sauvegarde définitivement l'état des fichiers présents dans la zone de transit sous la forme d'un « instantané » dans l'historique de Git, accompagné d'un message explicatif.