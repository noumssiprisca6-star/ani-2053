



---

#  Démonstration : Gestion et Résolution d'un Conflit Git

>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git

**Objectif :** Provoquer volontairement un conflit de fusion, analyser les marqueurs Git, reconstruire le code proprement et valider la résolution en conservant une démarche calme et structurée.

---
## Petite simulation de presentation
bonjour a tou je me nomme `NOUMSSI TIATSAP` et aujourd'hui nous allons resoudre un petit conflit provoquer volontairement sur deux branches distinctes de mon depot . Restons concentrer

## 1. Provocation du Conflit

1. **Modification sur  la branche `main` la ligne 3 du fichier test.cpp dans le dossier mes_demos :**

 ```bash
   git checkout main
   git add test.cpp
   git commit -m "modification du message sur main"

```

2. **Modification contradictoire sur `feature` ligne 3 du fichier test.cpp dans le dossier mes_demos:**
```bash
git checkout feature
git add test.cpp
git commit -m "modification du message sur feature"

```


3. **Déclenchement du conflit lors de la fusion :**
```bash
git checkout main
git merge feature

```


> **Résultat :** `Auto-merging mes_demos/test.cpp
CONFLICT (content): Merge conflict in mes_demos/test.cpp
Automatic merge failed; fix conflicts and then commit the result.`



---

## 2. Lecture des Marqueurs de Conflit
Bon l'enonce demande de lire a voix haute , mes mots tels qu'il sont ecrit represente mes paroles dans ce cas 

Contenu du fichier `test.cpp` généré par Git :

```bash
<<<<<<< HEAD
    std::cout <<"creation d'un conflit et resolution de celui ci dans le calme et l'assurance "<<std::endl;
=======
    std::cout <<" testons"<<std::endl;
>>>>>>> feature
    return 0 ;
}
```

### Explication des balises :

* **`<<<<<<< HEAD`** : Début du bloc en conflit sur la branche courante (`main`).
* **`=======`** : Séparateur entre les deux versions concurrentes.
* **`>>>>>>> feature`** : Fin du bloc en conflit provenant de la branche fusionnée (`feature`).

---

## 3. Décision et Reconstruction Manuale

* **Décision :** Conservation de la version de la branche `main` (modification actuelle) tout en intégrant une note explicative .
* **Fichier reconstruit (`test.cpp`) :**

```cpp

std::cout <<"Version officielle de main - intégrée avec feature"<<std::endl;

```


---

## 4. Validation et Vérification

1. **Enregistrement de la résolution :**
```bash
git add test.cpp
git commit -m "resolution du conflit sur test.cpp"

```


2. **Vérification de l'état du dépôt :**
```bash
git status

```


> **Résultat  :** 
On branch main Your branch is ahead of 'origin/main' by 3 commits.
(use "git push" to publish your local commits)
nothing to commit, working tree clean`

---
* **MERCI POUR VOTRE ECOUTE ET ATTENTION**
