1. **Introduction & Fichier modèle:** 1 min.
Présenter le rôle du fichier `jenga.json` et `.jenga` dans l'écosystème de build Jenga.


2. **Déclarations du module:** 3 min.
Détailler la structure du JSON : nom, type de cible, sources et dépendances.


3. **Filtrage & Conditionnement:** 3 min.
Expliquer la séparation selon la plateforme, la configuration et l'architecture.


4. **Délégation du Build:** 3 min.
Montrer comment Jenga génère le projet bas niveau et passe la main au compilateur cible.


---

# Plan de Présentation : Définition et Structure d'un fichier `.jenga`



---

## 1. Modèle de fichier `jenga.json` réel

Voici l'exemple concret à projeter à la classe pour illustrer  le projet  MonEssai ecrit dans le dossier Apllications de Nkentseu afin de l'integrer au worspace 

```json
{
    "include": [
        "**/*.py",
        "**/*.jenga"
    ],
    "exclude": [
        "Build/**",
        "Externals/**",
        ".vscode/**",
        "**/__pycache__",
        "**/node_modules"
    ],
    "pythonVersion": "3.8",
    "reportMissingImports": "warning",
    "reportUndefinedVariable": "warning",
    "reportWildcardImportFromLibrary": "none",
    "extraPaths": [
        "C:/Users/jouvence computer/Desktop/tout/Gap/Jenga/Jenga",
        ".jenga-typings"
    ],
    "_jengaIdeConfigVersion": "87be2a277f774510"
}

```

## 1.2 . Modèle de fichier `.jenga` réel de mon projet NewProjet dans ani-2053

```python
import os
from Jenga import *
from Jenga.GlobalToolchains import RegisterJengaGlobalToolchains

with workspace("compile"):
    RegisterJengaGlobalToolchains()
    cppdialect("c++17")
    configurations(["Debug" ,"Release"])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64 , TargetArch.ARM64])
    startproject("NewProject")

    

    with include ("Calculateur/Calcul.jenga"):
        pass
    with include ("Affichage/Affiche.jenga"):
        pass
    with project("NewProject"):
        consoleapp()
        cppdialect("c++17") 
        cppcompiler("clang++")
        language("c++")
        includedirs(["."])
        files(["./**.cpp"])
        dependson(["Calcul","afficher"])
        links(["Calcul", "afficher"])

    with filter("config: Debug"):
        optimize("OFF")
        symbols(True)
        defines(["DEBUG", "_DEBUG"])

    with filter("config:Release"):
        optimize("Speed")
        symbols(False)
        defines(["NODEBUG"])
       
```
---

## 2. Deroulé de la présentation (10 minutes)

### Min 0:00 - 0:02 : CE QUE LE FICHIER DÉCLARE

* **L'identité du module :** Prenons un module quelquonque disons  (`"name": "NKAudio"`).
* **Le type d'artefact :**  Le champ `"type": "StaticLib"` stipule explicitement que ce module compile sous forme de bibliothèque statique (`.lib` sur Windows, `.a` sur Linux/macOS).
* **Les ressources :** Les fichiers sources et en-têtes via les masques (`files`), ainsi que les répertoires d'inclusion (`include_dirs`).

### Min 0:02 - 0:05 : CE QUE LE FICHIER FILTRE

* **Par Plateforme (`platforms`) :** Séparation du code et des dépendances système (ex: `winmm.lib` sur Windows vs `asound` sur Linux).
* **Par Configuration (`configurations`) :** Profils `Debug` (symboles de débogage activés, pas d'optimisation) vs `Release` (optimisation maximale).
* **Par Architecture/Compilateur :** Injection conditionnelle de macros (`defines`) selon l'environnement de destination.

### Min 0:05 - 0:08 : CE QUE LE FICHIER DÉLÈGUE

* **Au générateur de build  :** `.jenga` ne compile pas directement les fichiers `.cpp`. Il sert de fichier de meta-configuration 
* **Au compilateur (MSVC / Clang / GCC) :** La résolution des drapeaux d'optimisation, l'assemblage final de la bibliothèque statique.
* **Au système d'exploitation :** La gestion des chemins de fichiers de sortie.

* **les codes**: 
pour la compilation :

```bash
jenga build ou jenga build --target nomdumoduleprecis 
```
avec les configuration Debug et Release
```bash
jenga build --config Debug  et  jenga build  --config Release
```
 pour l'execution 
 ```bash
 jenga run
 ```
 pour nettoyer l'editeur de code 

 ```bash
 jenga clean
 ```
 IL existe une multitude de commande de manipulation du programme python Jenga utiliser pour faciliter la compilation de nombreux projet c++ . C'est une innovation de haut niveau


### Min 0:08 - 0:10 : QUESTIONS / RÉPONSES

* Valider auprès du professeur/classe la réponse exacte sur la déclaration de la bibliothèque statique (`"type": "StaticLib"`).