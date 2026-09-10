# Reponse a l'exercice 2

### Mes résultats
- Chez moi : 3944 fichiers sources et 1 623 115 lignes
- Dans le chapitre : 2641 fichiers et 1 193 385 lignes
- Donc j'ai 1303 fichiers et environ 429000 lignes en plus.

### Pourquoi j'ai plus que le chapitre



J'ai plus de fichiers et plus de lignes que le chapitre parce que ils inclut les  en-tetes , les dossiers build, les fichiers test :

1.  J'ai compté les fichiers avec l'extension .h et aussi les fichiers avec l'extension .cpp. Certains comptages ne prennent que les fichiers .cpp, moi j'ai pris les deux.

2.  Il y a des fichiers qui sont créés automatiquement par l'environnement de développement quand on compile. Ces fichiers ne sont pas écrits par nous mais ils sont comptés quand on fait la commande.

3.  Mon dossier contient aussi des dossiers comme build et .git et des bibliothèques externes. Ça ajoute beaucoup de fichiers.


### Les commandes utilises 
```powershell
- Pour le nombre de fichiers sources
"dir -Recurse -Include *.cpp ,*.h -File | Where-Object { $_.FullName -notmatch "\\build\\" }.Count"
- pour le nombres de lignes :
"dir -Recurse -Include *.cpp,*.h -File | Where-Object { $_.FullName -notmatch "\\build\\" } | Get-Content | Measure-Object -Line"
