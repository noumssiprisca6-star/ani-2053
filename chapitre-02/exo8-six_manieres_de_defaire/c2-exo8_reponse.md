Cet exercice est un excellent parcours pratique pour maîtriser la gestion des erreurs et la récupération sous Git. Il vous demande de créer **6 situations de problème classique**, puis de les corriger une par une.

---

### Explication simple des 6 situations

1. **Modification non voulue :** Vous modifiez un fichier par erreur et vous voulez revenir au dernier état propre du fichier (avant tout `git add`).
2. **Un `add` de trop :** Vous avez fait `git add` sur un fichier que vous ne vouliez pas préparer pour le commit. Il faut l'enlever de la zone de staging sans effacer vos modifications.
3. **Un commit de trop (en local) :** Vous avez fait un commit en local, mais vous voulez l'annuler (garder le code ou tout effacer) avant de l'avoir envoyé à distance.
4. **Un commit poussé qu'il faut annuler :** Le commit est déjà envoyé sur le serveur (`origin/main`). Il faut créer un commit d'annulation (*revert*) pour ne pas réécrire l'historique partagé.
5. **Un travail en cours à mettre de côté :** Vous devez changer de tâche d'urgence alors que votre travail actuel n'est pas prêt à être commité.
6. **Un commit "perdu" à retrouver :** Vous supprimez ou annulez un commit par erreur, puis vous utilisez l'historique système de Git (`reflog`) pour retrouver son identifiant (SHA) et le restaurer.

---

### Modèle de fichier `.md` de réponse


```markdown
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


* **Vérification (`git log -2`) :** Un nouveau commit d'annulation (*Revert "..."*) a été créé et poussé sur le serveur.

---

## 5. Un travail en cours qu'il faut mettre de côté

* **Provoquer la situation :** Réalisation de modifications non finies dans un fichier.
* **Commande pour sauvegarder temporairement le travail :**
```bash
git stash

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
git reflog

```


* **Commande pour restaurer le commit perdu :**
```bash
git reset --hard <SHA1_DU_COMMIT_PERDU>

```


* **Vérification (`git log -1`) :** Le commit effacé est de nouveau le commit le plus récent.

```

---

### Guide étape par étape pour réaliser l'exercice dans votre terminal

<Sequence>
  <Step title="1. Annuler une modification non voulue">
    1. Ouvrez un fichier (ex: `main.cpp`) et écrivez du texte n'importe où.
    2. Enregistrez le fichier, puis vérifiez avec `git status`.
    3. Pour annuler ces changements :
       ```bash
       git restore main.cpp
       ```
    4. Vérifiez avec `git status` : la modification a disparu.
  </Step>

  <Step title="2. Retirer un add de trop">
    1. Modifiez un fichier et préparez-le :
       ```bash
       git add main.cpp
       ```
    2. Pour le retirer de l'index sans perdre vos changements :
       ```bash
       git restore --staged main.cpp
       ```
    3. Vérifiez avec `git status` : le fichier est toujours modifié, mais il n'est plus prêt à être commité.
  </Step>

  <Step title="3. Annuler un commit local de trop">
    1. Ajoutez et commitez une modification :
       ```bash
       git add main.cpp
       git commit -m "docs: test commit en trop"
       ```
    2. Pour annuler ce commit et revenir en arrière :
       ```bash
       git reset HEAD~1
       ```
    3. Vérifiez avec `git log -1` : le commit "test commit en trop" a été supprimé de l'historique local.
  </Step>

  <Step title="4. Annuler un commit déjà poussé">
    1. Créez un commit et envoyez-le sur votre serveur :
       ```bash
       git add main.cpp
       git commit -m "docs: erreur poussee sur le serveur"
       git push
       ```
    2. Pour l'annuler proprement sur le serveur, créez un commit inverse :
       ```bash
       git revert HEAD --no-edit
       git push
       ```
    3. Vérifiez avec `git log` : vous verrez le commit initial suivi du commit d'annulation (*Revert*).
  </Step>

  <Step title="5. Mettre de côté du travail en cours (Stash)">
    1. Faites des modifications dans votre fichier sans les commiter.
    2. Masquez-les temporairement :
       ```bash
       git stash
       ```
    3. Constatez avec `git status` que votre dossier est propre.
    4. Récupérez vos modifications quand vous êtes prêt :
       ```bash
       git stash pop
       ```
  </Step>

  <Step title="6. Retrouver un commit perdu avec reflog">
    1. Faites un commit :
       ```bash
       git add main.cpp
       git commit -m "docs: commit important a effacer"
       ```
    2. Forcez sa suppression (simulation d'une fausse manipulation) :
       ```bash
       git reset --hard HEAD~1
       ```
    3. Affichez le journal de bord complet de Git pour retrouver le SHA du commit :
       ```bash
       git reflog
       ```
    4. Repérez la ligne qui correspond au commit effacé (ex: `e3f4a1b`) et restaurez-le :
       ```bash
       git reset --hard e3f4a1b
       ```
    5. Lancez `git log -1` : votre commit est de retour !
  </Step>
</Sequence>

<ElicitationsGroup message="Souhaitez-vous des précisions sur l'une des commandes ?">
  <Elicitation label="Différence entre git reset et git revert" query="Explique-moi la différence exacte entre git reset et git revert et quand utiliser l'un ou l'autre."/>
</ElicitationsGroup>

```