
```markdown
#  Rapport d'Expérimentation : Mesure et Analyse du Cache de Build Jenga

> **Projet :** temps`  
> **Outil de Build :** Jenga  
> **Objectif :** Comparer les temps d'exécution entre une construction complète à froid  et une seconde construction sans modification , puis analyser le mécanisme d'optimisation sous-jacent.

---



## 1. le contenu du fichier Timing .cpp

 ```cpp
#include<iostream>
#include<string>

    class Animal{
        protected :
        std::string Nom ;
        public:
        Animal(std::string nom): Nom(nom){}
        void Marcher (){
        std::cout<<"marche vite"<<std::endl;}
    };
    
    
    int main(){
        Animal animal ("rex");
        animal.Marcher();
        return 0;
    }
    
 ```


## 2. Protocole & Relevé des Chronomètres

### Protocole
1. Nettoyage complet des objets et binaires intermédiaires.
2. Exécution de la **première construction** .
3. Exécution immédiate d'une **seconde construction** sans modifier aucun fichier du projet.


```bash
# 1. Nettoyage initial /
jenga clean

# 2. Commande pour la  construction complète (à froid)
jenga build

# 3. Commande pour la construction immédiate (à chaud)
 jenga build




```



### Construction à froid : Nombre de seconde (1.08s)

```

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.4.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. temps [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: temps                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: Timing.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\temps\temps.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.06s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1.08s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```

 ###  Construction à chaud ou immediate : Nombre de secondes (0.95s)


```

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.4.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. temps [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: temps                                                           Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: Timing.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\temps\temps.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 0.95s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           0.95s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

---
```

### Relevé des Mesures

 * **Passage 1** : Construction Complete (1.08s)
 * **Passage 2** : Reconstruction Immediate (0.95s)

> **Écart observé :** La seconde construction est quasi-instantanée (gain de temps est extremement reduit ).

---

## 3. Explication de l'Écart : Le Système de Build Incrémental avec Jenga

L'écart massif de durée entre les deux exécutions s'explique par les mécanismes d'**évaluation paresseuse (*Lazy Evaluation*)** et d'**analyse du DAG (*Directed Acyclic Graph*)** intégrés à Jenga.

### A. La première construction (Build à Froid)

Lors du premier passage :


1. **Pleine charge E/S et Processeur :** Le compilateur traduit l'intégralité des fichiers sources `.cpp` en fichiers objets `.o` puis les rassemble via l'éditeur de liens.
2. **Génération de l'empreinte (*Fingerprinting*) :** Jenga calcule et enregistre les signatures de chaque fichier ainsi que l'arbre des dépendances d'en-têtes (`.h`) .


### B. La seconde construction (Build à Chaud )

Lors du second passage immédiat :

1. **Vérification des dépendances  :** Jenga parcourt le graphe de build et compare l'état actuel des fichiers avec les empreintes enregistrées lors du premier passage.
2. **Détection d'absence de modifications :**
* Aucun fichier source (`.cpp`) ni en-tête (`.h`) n'a été modifié.
* Aucune option de compilation ni fichier `.jenga` n'a changé.
3. **hypothese pas une declaration   :** Jenga détermine que tous les artefacts de sortie (`.o`, `.lib`, `.exe`) sont à jour. Il empeche ainsi complètement l'appel aux toolchains/compilateurs pour une reconstruction immediate a la seconde pret  apres la premiere construction (`cl.exe`, `clang++`, etc.)



---



```