
> * **Ce fichier .md reponds  aux 5 questions suivantes:**

1. **Comment nommer les branches ?**
Définir une convention claire (ex: `nom/type-fonctionnalite`) pour savoir qui fait quoi sans se mélanger.
2. **Que doit contenir un commit ?**
Expliquer qu'un commit doit être propre (code qui compile), petit (une seule tâche), avec un message clair.
3. **Qui relit quoi (Revue de code) ?**
Définir le processus d'approbation avant de fusionner sur `main` (ex: au moins 1 camarade doit relire et valider la Pull Request).
4. **Ce qui est strictement interdit**
Lister les mauvaises pratiques (ex: pusher directement sur `main`, faire un `push --force`, envoyer des fichiers exécutables `.exe` ou temporaires).
5. **Que faire si la branche principale (`main`) est cassée ?**
Rédiger la procédure d'urgence étape par étape pour réparer le problème ou annuler le commit fautif sans tout perdre (utilisation de `git revert`).

---

# Charte et Règles Git du Projet

*Guide de travail collaboratif pour une équipe (4 étudiants)*



## 1. Convention de Nommage des Branches
* La branche `main` est la branche de production : elle doit **toujours être stable et compilable**.
* **Interdiction de travailler directement sur `main`.**
* **Structure d'un nom de branche :** `<prenom>/<type>-<description-courte>`
  * `feat` : Nouvelle fonctionnalité (ex: `prisca/feat-menu-principal`)
  * `fix` : Correction d'un bug (ex: `alex/fix-erreur-compilation`)
  * `docs` : Ajout ou modification de documentation (ex: `jean/docs-update-readme`)

---

## 2. Règles sur le Contenu et la Qualité des Commits
* **Commit Atomique :** Un commit ne doit contenir que des modifications liées à une seule tâche.
* **Code Compilable :** Il est interdit de commiter du code qui ne compile pas localement.
* **Format du message de commit :** ` <type>: <description au présent/impératif>`
  * *Exemple valide :* `feat: ajouter la verification des saisies utilisateur`
  * *Exemple interdit :* `update`, `bugfix`, `wip`

* **Explication du choix de format** :
 
 Que signifie chaque partie du format <type>: <description> ?
- **<type>** : Indique la catégorie du changement pour comprendre immédiatement le rôle du commit. Les types les plus courants sont :

- **feat (feature)** : Ajout d'une nouvelle fonctionnalité (ex: feat: ajouter la gestion des utilisateurs).

- **fix**: Correction d'un bug (ex: fix: corriger l'affichage du menu).

- **docs :** Modification de la documentation (ex: docs: mise a jour du README).

- **refactor :** Reconstitution du code sans changer son comportement ni ajouter de bug (ex: refactor: simplifier la fonction de calcul).

- **style :** Modifications purement cosmétiques qui ne changent pas le sens du code (espaces, indentation, point-virgule manquant).

- **test :** Ajout ou modification de tests automatisés.

- **<description> :** Explique brièvement ce que fait la modification. Elle doit être rédigée au présent ou à l'impératif (ex: "ajouter" ou "ajoute" au lieu de "j'ai ajouté").
---

## 3. Processus de Revue de Code (Code Review)
* **Pull Request (PR) Obligatoire :** Toute intégration sur `main` se fait via une demande de fusion.
* **Binôme de Relecture :** Chaque PR doit être relue et approuvée par **au moins 1 autre membre du groupe** avant d'être fusionnée.
* **Rotation :** Les relecteurs changent régulièrement pour que toute l'équipe garde une vision globale du projet.
* **Validation :** L'auteur de la PR effectue la fusion uniquement après l'obtention du bouton green/approval d'un camarade.

---

## 4. Pratiques Strictement Interdites 
1. **Push direct sur `main` :** Aucun commit direct n'est toléré sur la branche principale.
2. **Push forcé (`git push --force`) :** Strictement interdit sur `main` et sur toutes les branches partagées.
3. **Commit de fichiers boursouflés ou binaires :** Ne jamais commiter de fichiers exécutables (`.exe`, `.out`), de dossiers de build ou d'outils temporaires. Utiliser le `.gitignore`.

---

## 5. Procédure d'Urgence : Réparation de la Branche `main` 

Si la branche `main` ne compile plus ou contient un bug critique suite à une fusion :

1. **Alerte immédiate :** Signaler le problème sur le canal de communication de l'équipe (Discord/WhatsApp).
2. **Gel des fusions :** Toutes les Pull Requests en cours sont mises en pause.
3. **Identification et Correction :**
   * L'auteur du dernier commit fusionné prend la responsabilité du correctif.
   * Si le fix prend **moins de 15 minutes** : créer une branche d'urgence `<prenom>/hotfix-reparation-main`, corriger et fusionner en priorité.
   * Si le fix prend **plus de 15 minutes** : annuler le commit problématique directement via la commande :
```bash
     git revert <hash_du_commit_fautif>
     git push 
```
4. **Relance :** Une fois `main` de nouveau stable et validée par l'équipe, le travail normal reprend.
   

> **DE FACON PLUS PRECISE**


### Pour réparer la branche `main` sans impacter le travail des 3 autres membres du groupe, il existe **deux procédures exactes** selon le temps nécessaire pour corriger le problème.

---

### Option 1 : L'annulation propre (Recommandée si la réparation prend > 15 min)
Elle permet de remettre `main` dans un état stable immédiatement en annulant la fusion qui a tout cassé.

1. **Identifier le commit fautif:** Étape 1.
Affichez les derniers commits pour repérer l'identifiant (hash) de la fusion qui a cassé `main` :

```bash
git log --oneline -n 5

```

*(Exemple de résultat : `a1b2c3d Merge branch 'prisca/feat-menu' into main` $\rightarrow$ le hash est **`a1b2c3d`**).*


2. **Annuler le commit sur main:** Étape 2.
Pour annuler un commit de fusion (merge commit), il faut taper :

```bash
git revert -m 1 <hash_du_commit>

```

*Note : Si le commit à annuler est un commit classique (pas un merge), tapez simplement :* `git revert <hash_du_commit>`.


3. **Pousser la réparation sur GitHub:** 
Étape 3.
Validez et envoyez la correction sur le serveur distant :

```bash
git push 

```

*Vérification : La branche `main` recompile de nouveau pour tout le groupe.*


---

### Option 2 : Le correctif d'urgence en branche (Si la réparation prend < 15 min)

Si nous savons exactement d'où vient l'erreur et qu'elle se corrige en deux lignes de code, ne  **jamais** travailler  directement sur `main`.

1. **Créer une branche de correctif:** Étape 1.
Placez-vous sur `main` à jour et créez une branche dédiée :

```bash
git checkout main
git pull origin main
git checkout -b <votre_prenom>/hotfix-reparer-main

```


2. **Corriger et valider le code:** Étape 2.
Correction  du  bug dans l' éditeur, vérifiez que le projet **compile parfaitement**, puis commitez :

```bash
git add .
git commit -m "fix: reparation de la compilation sur main"
git push origin <votre_prenom>/hotfix-reparer-main

```


3. **Fusionner en priorité:** Étape 3.
Ouvrez une Pull Request d'urgence sur GitHub, demandez à un camarade de valider rapidement, puis fusionnez sur `main`.

>**CECI CONCERNE TOUS LES MEMBRES DU GROUPE SANS EXEPTION**
>**POUR UNE MEILLEURE COLLABORATION SUR GITHUB IL FAUT TOUJOURS S'ASSURER DE TOUJOURS RESPECTER LA CHARTE DE GIT.**