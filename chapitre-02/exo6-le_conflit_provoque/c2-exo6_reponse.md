

# Compte-Rendu : Gestion des Conflits Git


## Le necessaire pour l'exercice suivant la demande

**Prérequis :** Avoir un dépôt Git distant  sur gitHub . 
>TOUTES LES MODIFICATIONS EFFECTUER SUR CETTE EXERCICE ONT ETE CREE SUR MON NOUVEAU DEPOT MONESSAI : https://github.com/noumssiprisca6-star/MonEssaie.git
 j'ai donc deux depot mon essaie pour cette exercice dans deux repertoires distincts . un dans le dossier MonEssaie et l'autre dans un dossier SecondRep

 **Préparation des deux répertoires:** Clonnage.
Dans deux dossiers differents

##  **Modification  du repertoire 1 et envoi sur le depot distinct:**
 Terminal A  dans le MonEssaie 
1. Accéder  au dossier : `cd MonEssaie/ cd exo1_modification`
2. Modification de  la ligne 3 du fichier `Fichier1.cpp` (on va ecrire a la ligne 3 `std::cout <<"creation des conflits "<<std::endl;`)
3. Validation et pousse des changements :

```bash
git add Fichier1.cpp
git commit -m "Modification par le premier depot"
git push 

```

 **Resultat  du push.**
```bash
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean
PS C:\Users\jouvence computer\Desktop\ex\MonEssaie\exo1_modification> git push                                       
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 4 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 412 bytes | 412.00 KiB/s, done.
Total 4 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/noumssiprisca6-star/MonEssaie.git
   34228c2..de87a31  main -> main
```


  ## Refus du Push (Répertoire B)

Modification de la même ligne 3 dans le second clone `cd SecondRep` sans avoir récupéré les changements de `cd MonEssaie`, puis tentative de push.

1. Accédez au second dossier : `cd SecondRep/cd MonEssaie/cd exo1_modification` 

2. Modification de  **la même ligne 1** du fichier `Fichier1.cpp` (ex: écrivez *"Ligne modifiée par B"*).
3. Validation de  la modification localement :

```bash
git add Fichier1.cpp
git commit -m "Modification par  le second depot"

```

 * **je tente de  pousser : `git push `**
 * **Le push est refusé par Git **
* **Resultat**
```bash
To https://github.com/noumssiprisca6-star/MonEssaie.git
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'https://github.com/noumssiprisca6-star/MonEssaie.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
```

> Git signale un conflit de fusion (*Auto-merging failed*).


## . Déclenchement du Conflit

Tentative d'intégration des changements distants dans `SecondRep qui est le dossier du second repertoire` via un `pull`.

**Commande exécutée :**

```bash
git pull 


1. Ouverture du  `Fichier1.cpp`. observations des balises de conflit :

```text
int main(){
<<<<<<< HEAD
    std::cout <<"creation des conflits "<<std::endl;
=======
    std::cout<<"creation des conflits "<<std::endl;
>>>>>>> de87a3105394697e4feee2304a61f1b37ef8b393
    return 0;
}

```
##  Résolution du Conflit et Push Final

2. Suppression les balises (`<<<<<<<`, `=======`, `>>>>>>>`) et choix de combinez les deux modifications par leur acceptation respectves
3. Validation de  la résolution et pousse :

```bash
git add Fichier1.cpp
git commit -m "Resolution du conflit "
git push 

```

4. **le message final du push réussi.**

```bash
[main 880732f]  resolution du conflit
PS C:\Users\jouvence computer\Desktop\ex\SecondRep\MonEssaie\exo1_modification> git push
Enumerating objects: 14, done.
Counting objects: 100% (14/14), done.
Delta compression using up to 4 threads
Compressing objects: 100% (8/8), done.
Writing objects: 100% (8/8), 808 bytes | 404.00 KiB/s, done.
Total 8 (delta 5), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (5/5), completed with 2 local objects.
To https://github.com/noumssiprisca6-star/MonEssaie.git
   de87a31..880732f  main -> main
   ```

---

