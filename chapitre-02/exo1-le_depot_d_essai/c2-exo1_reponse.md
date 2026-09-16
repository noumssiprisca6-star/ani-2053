
# Compte-rendu : Chapitre 2 -> Exercice 1 - Création et gestion d'un dépôt d'essai

Ce document détaille les étapes réalisées pour initialiser un dépôt Git, créer trois fichiers avec leurs commits respectifs, et visualiser l'historique sous forme de graphe compact comme le demande l'enoncer

---

## 1. Initialisation du dépôt Git

Dans mon  dossier  (`chapitre-02/exo1-le_depot_d_essai`), le dépôt Git a été initialisé à l'aide de la commande :

```bash
git init

```

*Résultat :* Initialized empty Git repository in C:/Users/jouvence computer/Desktop/ex/ani-2053/chapitre-02/exo1-le_depot_d_essai/.git/

* **Un dépôt Git vide a été créé dans le dossier du projet.**

---

## 2. Création des fichiers et validation des commits

 J'ai créé Trois fichiers C++ (`.cpp`) et les ais ajoutés à l'historique à travers trois commits distincts.

### Étape 2.1 : Premier commit

Création et enregistrement du premier fichier :

```bash
git add .
git commit -m "ajout de mon premier fichier du depot pour l'exercice du chapitre 2"

```
* **J'ai fait ` git add .` et non `git add fichier1.cpp` afin d'ajouter mon fichier .md a mon premier commit**

### Étape 2.2 : Deuxième commit

Création et enregistrement du deuxième fichier :

```bash
git add fichier2.cpp
git commit -m "deuxieme commit"

```

### Étape 2.3 : Troisième commit

Création et enregistrement du troisième fichier :

```bash
git add fichier3.cpp
git commit -m "mon troisieme commit"

```

---

## 3. Visualisation de l'historique et du graphe

Pour afficher l'historique condensé à une ligne par commit ainsi que le graphe associé,  j'ai exécutée la commande suivante :

```bash
git log --oneline --graph

```

### Résultat obtenu dans le terminal :

```text
* 9a38f3d (HEAD -> master) mon troisieme commit
* aa48df4 deuxieme commit
* d30e0a6  mon premier commit

```

---