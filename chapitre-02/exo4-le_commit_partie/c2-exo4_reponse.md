
# Réponses à l'exercice : Commits séparés avec `git add -p`


## modification de test 


# Titre mis a jour du projet 

## Section 1
Ceci est le texte initial de la section 1.

## Section 2
Ceci est le texte initial de la section 2.
ajout d'une remarque finale


## 1. Modifications apportées
J'ai modifié le fichier à deux endroits indépendants :
- **Modification 1 :** Changement du titre principal.
- **Modification 2 :** Ajout d'une ligne dans la conclusion.

---

## 2. Étapes et commandes exécutées

### Étape A : Premier commit (uniquement la modification 1)

Commande pour découper les modifications :
```bash
git add -p c2-exo4_reponse.md.

```
* **REsultat**
```bash
PS C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-02\exo4-le_commit_partie> git commit -m "document initial"
[main 42570c4] document initial
 1 file changed, 117 insertions(+)
 create mode 100644 chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
PS C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-02\exo4-le_commit_partie> git add -p c2-exo4_reponse.md
diff --git a/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md b/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
index 2976f25..26d11dd 100644
--- a/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
+++ b/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
@@ -6,16 +6,17 @@
 
 ```

*Action dans l'interface interactive :*

* J'ai répondu `y` pour accepter le premier bloc .
* **Resultat**
```bash
## 1. Modifications apportées
 J'ai modifié le fichier à deux endroits indépendants :
(1/1) Stage this hunk [y,n,q,a,d,s,e,p,?]? y
<stdin>:13: trailing whitespace.
# Titre mis a jour du projet 
warning: 1 line adds whitespace errors.
```

* J'ai répondu `n` pour refuser le second bloc (conclusion).

Commande pour valider le premier commit :

```bash
git commit -m "fichier: mis a jour du titre"

```

* **Resultat**

```bash
[main 2503e8b] fichier: mis a jour du titre
 1 file changed, 4 insertions(+), 3 deletions(-)
```
---

### Étape B : Second commit (uniquement la modification 2)

Commande pour ajouter la modification restante :

```bash
git add c2-exo4-le_commit_partie.md

```

Commande pour valider le second commit :

```bash
git commit -m "fichier : ajout de la remarque finale"

```

---

## 3. Vérification de l'historique Git

Commande de vérification :

```bash
git log -p -2

```

### Résultat obtenu dans le terminal :


```text
index 2976f25..26d11dd 100644
--- a/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
+++ b/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
@@ -6,16 +6,17 @@
 
 
 ## modification de test 
-```bash
 
-
commit 42570c4d5319df387f453cb0cf31d202ba2dbb07
Author: noumssiprisca6-star <noumssiprisca6@gmail.com>
Date:   Thu Sep 17 09:44:22 2026 +0200

    document initial

diff --git a/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md b/chapitre-02/exo4-le_commit_part
ie/c2-exo4_reponse.md
new file mode 100644
index 0000000..2976f25
--- /dev/null
+++ b/chapitre-02/exo4-le_commit_partie/c2-exo4_reponse.md
@@ -0,0 +1,117 @@
+
+---
+
+
+```text
+commit b1a2c3d4e5f6... (HEAD -> main)
+Author: Votre Nom <votre.email@example.com>
+Date:   Thu Sep 17 08:30:00 2026
+
+    docs: ajout d'une note en conclusion
+
+diff --git a/exercice.md b/exercice.md
+--- a/exercice.md
++++ b/exercice.md
+@@ -10,3 +10,4 @@
+ ## Section 3 : Conclusion
+ L'exercice est terminé.
++* Remarque : modification finale ajoutée.
+
+commit a9f8e7d6c5b4...
+Author: Votre Nom <votre.email@example.com>
+Date:   Thu Sep 17 08:28:00 2026
+
+    docs: mise a jour du titre
+
+diff --git a/exercice.md b/exercice.md
+--- a/exercice.md
++++ b/exercice.md
+@@ -1,3 +1,3 @@
+-# Ancien Titre du Projet
++# Document de présentation mis à jour
+
+```
+
+---
+
+## 4. Conclusion
+
+L'historique montre bien deux commits distincts : chacun ne contient que la modification qui conce
rne son sujet
+
+```
+
+```

```

---

## 4. Conclusion

L'historique montre bien deux commits pour mes deux modification : chacun contient la modification qui concerne son sujet
