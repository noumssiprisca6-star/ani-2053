

# Création et Intégration du projet `Applications/MonEssai`

---

##  1. Structure des Fichiers à Créer

Arborescence de mon essaie

```
exo5-votre_premier_projet/
└── Applications/
    └── MonEssai/
        ├── MonEssai.jenga
        └── main.cpp

```

---

##  2. Contenu des Fichiers

### A. Le Code Source : `Applications/MonEssai/main.cpp`

Conformément à la consigne le fichier  `main` retourne `0` 

```cpp
#include<iostream>
int main() {
    return 0;
}

```

---

### B. La Fiche de Build : `Applications/MonEssai/MonEssai.jenga`

suivant la configuration simple de jenga que j'ai en ma possession

```python
import os
from Jenga import *
from Jenga.GlobalToolchains import RegisterJengaGlobalToolchains

with workspace("compil"):
    RegisterJengaGlobalToolchains()
    cppdialect("c++17")
    configurations(["Debug" ,"Release"])
    targetoses([TargetOS.WINDOWS])
    targetarchs([TargetArch.X86_64 , TargetArch.ARM64])
    startproject("main")

    with project("main"):
        consoleapp()
        cppdialect("c++17") 
        cppcompiler("clang++")
        language("c++")
        includedirs(["."])
        files(["./**.cpp"])
```

---

## 3. Déclaration dans le Workspace principal


```python
with workspace("compil"): # workspace principal
# autres inclusion
startproject("main") # mon projet principal

    with project("main"):
        #reglage du projet ....

        includedirs(["MonEssai"]) # cherches les headers dans le dossier Applications
        files(["./**.cpp"]) # compilation de tous les fichiers dans Applications

```

---

## 4. Commandes de Vérification et de Build

### Step 1 : Vérifions  la présence du projet dans la liste Jenga

```bash
jenga info

```

* **Résultat :**

Location: C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-01\exo5-votre_premier_projet\Applications\MonEssai
Entry file: C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-01\exo5-votre_premier_projet\Applications\MonEssai\main.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows
Target Architectures: x86_64, arm64
Start project: main


Projects
------------------------------------------------------------
Name   Kind         Language   Test   External
==============================================
main   ConsoleApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env  
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


Daemon
------------------------------------------------------------
Status: Not running

 `Main `  est bien present  dans la liste des projets recensés par le workspace.

---

### Step 2 : Générer/Construire le projet

Pour compiler mon projet :


```bash
jenga build 

```

Pour executer mon projet :

```bash
jenga run 

```



---
