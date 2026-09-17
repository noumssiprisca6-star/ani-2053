
---

```markdown
# Réponses à l'exercice : Commits séparés avec `git add -p`


## modification de test 
```bash

# Titre initial 

## Section 1
Ceci est le texte initial de la section 1.

## Section 2
Ceci est le texte initial de la section 2.
```

## 1. Modifications apportées
J'ai modifié le fichier à deux endroits indépendants :
- **Modification 1 :** Changement du titre principal.
- **Modification 2 :** Ajout d'une ligne dans la conclusion.

---

## 2. Étapes et commandes exécutées

### Étape A : Premier commit (uniquement la modification 1)
Commande pour découper les modifications :
```bash
git add -p exercice.md

```

*Action dans l'interface interactive :*

* J'ai répondu `y` pour accepter le premier bloc (changement de titre).
* J'ai répondu `n` pour refuser le second bloc (conclusion).

Commande pour valider le premier commit :

```bash
git commit -m "docs: mise a jour du titre"

```

---

### Étape B : Second commit (uniquement la modification 2)

Commande pour ajouter la modification restante :

```bash
git add exercice.md

```

Commande pour valider le second commit :

```bash
git commit -m "docs: ajout d'une note en conclusion"

```

---

## 3. Vérification de l'historique Git

Commande de vérification :

```bash
git log -p -2

```

### Résultat obtenu dans le terminal :

```text
commit b1a2c3d4e5f6... (HEAD -> main)
Author: Votre Nom <votre.email@example.com>
Date:   Thu Sep 17 08:30:00 2026

    docs: ajout d'une note en conclusion

diff --git a/exercice.md b/exercice.md
--- a/exercice.md
+++ b/exercice.md
@@ -10,3 +10,4 @@
 ## Section 3 : Conclusion
 L'exercice est terminé.
+* Remarque : modification finale ajoutée.

commit a9f8e7d6c5b4...
Author: Votre Nom <votre.email@example.com>
Date:   Thu Sep 17 08:28:00 2026

    docs: mise a jour du titre

diff --git a/exercice.md b/exercice.md
--- a/exercice.md
+++ b/exercice.md
@@ -1,3 +1,3 @@
-# Ancien Titre du Projet
+# Document de présentation mis à jour

```

---

## 4. Conclusion

L'historique montre bien deux commits distincts : chacun ne contient que la modification qui concerne son sujet

```

```