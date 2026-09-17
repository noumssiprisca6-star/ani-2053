
# Réponses à l'exercice : Mesure de la taille du dépôt Git

## 1. Description de la procédure
L'objectif de cet exercice est de créer une nouvelle branche, d'y ajouter 3 commits, puis de mesurer l'évolution de la taille du dossier `.git` sur le disque.

---

## 2. Commandes exécutées et résultats

### Étape A : Création de la branche
Commande pour créer et basculer sur la nouvelle branche :
```bash
git checkout -b test-taille

```
* **Resultat**
```bash
Switched to a new branch 'test-taille'
```

* **Taille du dossier .git  sur le disque avant l'ajout des modifications** `1.66 mo`
---

### Étape B : Réalisation des 3 commits

J'ai apporté trois modifications successives en enregistrant un commit à chaque fois :

1. **Premier commit :**
```bash

git add GitTest.cpp
git commit -m " mon premier ajout : la fonction principale main"

```

* **Resultat**
```bash
[test-taille de076a3] mon premier ajout : la fonction principale main
 1 file changed, 5 insertions(+)
 create mode 100644 chapitre-02/exo5-la_branche_mesuree/GitTest.cpp
```


2. **Deuxième commit :**
```bash
e
git add GitTest.cpp
git commit -m "mon deuxieme ajout : une fonction entiere pour gerer l'addition"

```

* **Resultat**
```bash
[test-taille 42637cf] mon deuxieme ajout : une fonction entiere pour gerer l'addition
 1 file changed, 6 insertions(+), 1 deletion(-)
```


3. **Troisième commit :**
```bash
git add GitTest.cpp
git commit -m "Mon troisieme et dernier ajout : les commentaires"

```
* **Resultat**
```bash
[test-taille 80c7d0e] Mon troisieme et dernier ajout : les commentaires
 1 file changed, 1 insertion(+)
```



---

### Étape C : Mesure de la taille du dossier `.git`
 **Etape**

Ouvrir le dossier de projet dans l'Explorateur de fichiers.

Activez l'affichage des éléments cachés (sous Windows : onglet Affichage > cochez Éléments masqués).

Faires un clic droit sur le dossier .git > Propriétés.

Lisez la valeur indiquée à la ligne Taille sur le disque.


#### Résultat obtenu :

* **Taille initiale (avant commits) :** ~1.66mo
* **Taille finale (après 3 commits) :** ~1.67Mo

---

## 3. Explication du résultat

Créer des commits **ne fait pas gagner de la place** sur le disque, mais en **consomme davantage** (même si l'augmentation est très faible comme mon cas).

### Pourquoi le dépôt grossit-il ?

1. **Création de nouveaux objets Git :** À chaque commit, Git crée de nouveaux objets (fichiers *blob* pour le contenu modifié, fichiers *tree* pour la structure des dossiers, et objets *commit* pour les métadonnées . J'ai obtenu ces informations a travers des recherches approfondies).
2. **Conservation de l'historique :** Git n'écrase pas les anciennes versions de  fichiers. Il conserve la version précédente ET la nouvelle version pour v permettre de revenir en arrière à tout moment.


## Conclusion

La place occupée par le dossier `.git` augmente donc à chaque nouveau commit pour stocker l'historique complet des modifications.
et il ne faut pas oublier de revenir sur la branche principale avec 
```bash
git checkout main 
```
et  pour ajouter les modifications effectuer sur ma branche 
```bash
git merge test-taille
```
pour envoyer  sur github
``` bash
git push origin main
```

