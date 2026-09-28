#  L'Architecture Multi-Backend de NKWindow


## 1. Arborescence du Module NKWindow

Le module sépare l'interface de (`NKWindow.h`) des implémentations spécifiques logées dans le dossier `platform` qui se trouve dans le dossier `Kernel/Runtime/NKWindow `:

```text
NKWindow/
├── include/
│   └── NKWindow/
│       ├── NKWindow.h           
│       ├── NKWindowConfig.h     
│       ├── NKMain.h             
│       ├── NkSurface.h         
│       └── Platform/            
│           ├── Win32/
│           ├── Cocoa/
|           ├── Linux/
|           ├── Common/
│           ├── XLib/
│           ├── XCB/
│           ├── Wayland/
│           ├── Android/
│           ├── UIKit/
│           ├── Emscripten/
│           ├── HarmonyOS/
│           ├── UWP/
│           ├── Xbox/
│           └── Noop/
└── src/                         

```

---



## 2. Nombre de fichiers et de lignes du module

la commande ci apres fut  executer dans la racine du module `NKWindow` pour compter le nombre de fichier 

```bash
(Get-ChildItem -Recurse -File -Include *.cpp, *.c, *.h, *.hpp).Count

```

la commande pour compter le nombre de ligne 
```bash
(Get-ChildItem -Recurse -File -Include *.cpp, *.c, *.h, *.hpp | Get-Content | Measure-Object -Line).Lines
```
**RESULTAT**

```bash
PS C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow> (Get-ChildItem -Recurse -File -Include *.cpp, *.c, *.h, *.hpp).Count
113
PS C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow> (Get-ChildItem -Recurse -File -Include *.cpp, *.c, *.h, *.hpp | Get-Content | Measure-Object -Line).Lines
28422
```

* **Nombre de fichiers source (`.h`, `.cpp`) :** ** 113 fichiers**
* **Nombre total de lignes de code :** **28422 lignes**

*(Mesure effectuée en comptant l'ensemble des en-têtes du dossier `include/NKWindow/` et des fichiers d'implémentation dans `src/`).*

---


## 3. Liste et Decompte des backends de plateformes 

La commandes executees pour avoir la liste des dossiers contenant backends


**Resultat de la commande d'analyse des backends**1
```bash
Get-ChildItem -Directory -Recurse | ForEach-Object { $_.FullName }

```


```
PS C:\Users\jouvence computer\Desktop\tGet-ChildItem -Directory -Recurse | ForEach-Object { $_.FullName }
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\pch
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\tests
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Core
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\EntryPoints
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Cocoa
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Common
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Emscripten
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\HarmonyOS
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Linux
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Noop
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UIKit
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\UWP
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Wayland
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Xbox
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XCB
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\XLib
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com\nkentseu
C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Android\java\com\nkentseu\window
PS C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Kernel\Runtime\NKWindow> 
```


## 2. Les 12 Backends 

En regardant  directement le sous-dossier `include/NKWindow/Platform/` ainsi que les blocs de compilation conditionnelle   au niveau des plateformes specifiques de NKWindowData pour la definition des structure  `#if defined(...)` dans `NkWindow.h`, on dénombre **12 dossiers / cibles de plateforme distinctes** :

1. **Win32** (`NkWin32Window.h` / Windows Desktop)


2. **Cocoa** (`NkCocoaWindow.h` / macOS)


3. **XLib** (`NkXLibWindow.h` / Linux X11)


4. **XCB** (`NkXCBWindow.h` / Linux X11 alternatif)


5. **Wayland** (`NkWaylandWindow.h` / Linux moderne)


6. **Android** (`NkAndroidWindow.h` / Android Native Activity)


7. **UIKit** (`NkUIKitWindow.h` / iOS & iPadOS)


8. **Emscripten** (`NkEmscriptenWindow.h` / WebAssembly)


9. **HarmonyOS** (`NkHarmonyWindow.h` / OS Huawei)


10. **UWP** (`NkUWPWindow.h` / Universal Windows Platform)


11. **Xbox** (`NkXboxWindow.h` / Console Xbox)


12. **Noop** (`NkNoopWindow.h` / Mode Headless sans affichage)

13. Linux

Total mesuré : **12 backends/plateformes matérielles et logicielles** implémentés dans l'arborescence.



### Comparaison des implémentations côté à côté
**Commandes executees pour afficher l'implemetation de Win32 et  XLib** 

- **Pour Win32**

```bash
Get-ChildItem -Path "src\NKWindow\Platform\Win32" -Recurse -File
```

```bash
Répertoire: C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkent
seu\Kernel\Runtime\NKWindow\src\NKWindow\Platform\Win32
```
 **Resultat**

```
Mode                 LastWriteTime         Length Name                    
----                 -------------         ------ ----                    
-a----        21/07/2026     23:51           8847 NkWin32DropTarget.h     
-a----        26/09/2026     19:53          36490 NkWin32EventSystem.cpp  
-a----        21/07/2026     23:51            776 NkWin32EventSystem.h    
-a----        26/09/2026     19:53          30144 NkWin32Gamepad.h        
-a----        26/09/2026     19:53          77447 NkWin32Window.cpp       
-a----        26/09/2026     19:53           4711 NkWin32Window.h   

```
- **Pour XLib**

```bash
Get-ChildItem -Path "src\NKWindow\Platform\XLib" -Recurse -File
```

**Resultat**
```

Mode                 LastWriteTime         Length Name                    
----                 -------------         ------ ----                    
-a----        21/07/2026     23:51          11004 NkXLibDropTarget.h      
-a----        21/07/2026     23:51          13319 NkXLibEventSystem.cpp   
-a----        21/07/2026     23:51            806 NkXLibEventSystem.h     
-a----        26/09/2026     19:53          43826 NkXLibWindow.cpp        
-a----        21/07/2026     23:51           1351 NkXLibWindow.h          
```


 
### Backend A : Implémentation Win32 (Windows)

Sous Windows   

```cpp
math::NkVec2u NkWindow::GetSize() const {
    if (mData.hwnd == nullptr) return {0, 0};

    RECT clientRect;
    if (::GetClientRect(mData.hwnd, &clientRect)) {
        return {
            static_cast<uint32>(clientRect.right - clientRect.left),
            static_cast<uint32>(clientRect.bottom - clientRect.top)
        };
    }
    return {0, 0};
}

```

---

### Backend B : Implémentation XLib (Linux X11)

Sous Linux (X11)
`(lignes 431 à 442) `:  
```cpp
math::NkVec2u NkWindow::GetSize() const {
    if (mData.display == nullptr || mData.window == 0) return {0, 0};

    XWindowAttributes gwa;
    if (XGetWindowAttributes(mData.display, mData.window, &gwa)) {
        return {
            static_cast<uint32>(gwa.width),
            static_cast<uint32>(gwa.height)
        };
    }
    return {0, 0};
}

```

## 3. Ce qui est identique vs Ce qui change 

### Ce qui est identique

* **Le même objectif** : Les deux fonctions cherchent à obtenir la taille exacte (largeur et hauteur) de la fenêtre.
* **La même signature** : Elles ont le même nom, ne prennent aucun paramètre et renvoient exactement le même type de donnée (`math::NkVec2u`).
* **La même logique étape par étape** :
  1. Vérifier si la fenêtre existe (sinon, renvoyer `{0, 0}`).
  2. Demander les dimensions au système.
  3. Convertir ces dimensions en nombres entiers positifs (`uint32`) pour les renvoyer.
  4. En cas de problème, renvoyer `{0, 0}`.

---

### Ce qui change

* **Le système d'exploitation ciblé** :
  * **Sous Windows (Win32)** : On utilise la structure `RECT` et la fonction `GetClientRect`. La taille se calcule en soustrayant les bords : `droite - gauche` et `bas - haut`.
  * **Sous Linux (X11 / XLib)** : On utilise la structure `XWindowAttributes` et la fonction `XGetWindowAttributes`. Linux donne directement la largeur (`width`) et la hauteur (`height`).
* **Les informations stockées dans `mData`** :
  * Sur Windows, une seule information suffit : l'identifiant de la fenêtre (`mData.hwnd`).
  * Sur Linux, il en faut deux : la connexion au serveur graphique (`mData.display`) et l'identifiant de la fenêtre (`mData.window`).

---


### Ce que le module NKWindow absorbe 

1. **Il masque les fonctions de chaque système** :  nous n'avons  pas besoin de savoir si le programme tourne sous Windows ou Linux, ni d'utiliser les commandes lourdes de chaque système (`GetClientRect` ou `XGetWindowAttributes`).
2. **Il simplifie le calcul de la taille** : Quel que soit le système, il fait les calculs pour vous et vous donne directement le résultat dans le même format simple (`math::NkVec2u`).
3. **Un seul code pour tous les systèmes** : nous pouvons ecrire le code une seule fois, et il marche partout de la même façon.

