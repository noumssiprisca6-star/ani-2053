
# Compte-Rendu : Impact d'un fichier lourd sur l'historique Git

## 1. Expérience réalisée

L'objectif est d'observer l'impact sur la taille du dossier caché `.git` lorsqu'une vidéo volumineuse de 10 Mo (`ma_video.mp4`) est ajoutée puis supprimée dans l'historique.

### Commandes exécutées :

1. **Commit de la vidéo (10 Mo) :**
```bash
   git add ma_video.mp4
   git commit -m " ajout d une video de 10Mo"

```

2. **Suppression de la vidéo au commit suivant :**
```bash
git rm ma_video.mp4
git commit -m " suppression de la video"

```
* **Resultat**
```bash
[main 89f463b] suppression de la video
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 exo1_modification/ma_video.mp4
 ```


3. **Mesure de la taille du dossier `.git` :**

observation de la taille de mon dossier dans les proprietes



---

## 2. Résultat obtenu

* **Taille observée du dossier `.git` :** `9.33Mo`.
* **Taille precedente du dossier `.git`: **`42ko`.
* **Résultat dans le dossier de travail :** La vidéo `ma_video.mp4` a bien disparu du dossier visible `MonEssaie/exo1_modification`

---

## 3. Conclusion selon ma comprehension 

1. **Git conserve tout l'historique :** Bien que la vidéo ait été supprimée avec `git rm`, **son contenu reste stocké dans le dossier caché `.git**`.
2. **Explication :** Git doit pouvoir restaurer le projet à n'importe quel commit passé. Supprimer un fichier dans le commit présent ne le retire pas de l'historique.
3. **Bonne pratique :** Ne jamais commiter de fichiers média ou lourds directement dans Git. On utilise un fichier `.gitignore` pour les ignorer, ou l'extension **Git LFS** (*Large File Storage*).







