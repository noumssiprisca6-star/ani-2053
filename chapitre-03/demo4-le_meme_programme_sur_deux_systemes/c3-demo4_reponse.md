
#  Portabilité Multiplateforme & Analyse des Changements Implicites (NKEngine)

Cet exercice démontre le rôle d'abstraction du moteur : exécuter le même code source (ou binaire cross-compilé) sur deux systèmes d'exploitation différents et observer les variations gérées automatiquement par l'OS et l'environnement d'exécution.

---

## 1. Code Source Unique (`c3-demo4_main.cpp`)

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { 
         while (NkEvent* ev = NkEvents().PollEvent()) {

            // Fermeture de la fenêtre
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            }
        }
    }
    return 0;
} 

```
**Resultat sur Window 

```bash
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. environnement [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: environnement                                                   Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: c3-demo4_main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\environnement\environnement.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 4.14s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           4.16s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-03\demo4-le_meme_programme_sur_deux_systemes> jenga run

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  environnement.exe
     C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-03\demo4-le_meme_programme_sur_deux_systemes\Build\Bin\Debug-Windows\environnement\environnement.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (7.46s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
>**Obtenu avec la configuration dans le fichier `demo4-le_meme_programme_sur_deux_systemes`**

` targetoses([TargetOS.WINDOWS])`

---

## 3. Relevé des variations observées (sans modification de code)

Lors de la bascule d'exécution entre **Windows (Win32)** et **Linux (X11 / Wayland)** ou **macOS (Cocoa)**, les éléments suivants changent automatiquement sous le capot :

| Élément | Système A : Windows 11 | Système B : Linux (Ubuntu/X11) |
| --- | --- | --- |
| **Backend de Fenêtrage** | Interfaçage natif `NKWindowWin32` (`CreateWindowExW`) | Interfaçage natif `NKWindowX11` (`XCreateWindow`) ou `Wayland` |
| **Type de Handle Natif** | Pointer vers `HWND` | Identifiant `Window` (XID) / `wl_surface*` |
| **Gestion du DPI Scale** | Déclaratif via l'API Manifest / `SetProcessDpiAwareness` | Déterminé par Xft.dpi ou le compositeur Wayland |
| **Format du Framebuffer** | Format de pixels DirectX / BGRA | Format de pixels GLX / EGL / RGBA |
| **Décoration de Fenêtre** | Barre de titre native Windows avec bouton réduire/agrandir/fermer à droite | Décoration côté serveur (SSD) ou client (CSD) avec boutons à droite ou à gauche |
| **Gestion des Chemins d'Accès** | Séparateur système `\` (Backslash) | Séparateur système `/` (Slash) |

---




## 4. Ce que le moteur de build (Jenga) affiche et génère


| Élément | Sur votre console (Windows) | Ce qui change sous Linux |
| --- | --- | --- |
| **Toolchain** | `clang-mingw` | `gcc` ou `clang` natif |
| **Target OS** | `Windows x86_64` | `Linux x86_64` |
| **Dossier de sortie** | `Build\Bin\Debug-Windows\` | `Build/Bin/Debug-Linux/` |
| **Format du fichier** | `environnement.exe` (**PE / Portable Executable**) | `environnement` (**ELF / Executable and Linkable Format**, sans extension) |

---

## 5. Ce qui change au niveau du Système et de l'Exécution

Sans avoir modifié une seule ligne de code C++, les comportements suivants changent automatiquement :

### A. Système de fichiers et Chemins

* **Windows :** Utilise des antislashs `\` et des lettres de lecteur (ex: `C:\Users\jouvence computer\...`). Il est **insensible à la casse** (`Main.cpp` et `main.cpp` désignent le même fichier).
* **Linux :** Utilise des slashs `/` à partir de la racine (ex: `/home/jouvence/...`). Il est **strictement sensible à la casse** (`Fichier.txt` $\neq$ `fichier.txt`).

### B. Variables d'environnement système

Si votre programme affiche ou lit des variables d'environnement :

* **Windows :** Lit `USERNAME`, `USERPROFILE`, `TEMP`, `PATH` (séparé par `;`).
* **Linux :** Lit `USER`, `HOME`, `/tmp`, `PATH` (séparé par `:`).

### C. Gestion de la Console et Fin de Ligne

* **Windows :** La fin de ligne texte par défaut est `CRLF` (`\r\n`). Les couleurs console dépendent du terminal (PowerShell / Windows Terminal / `cmd`).
* **Linux :** La fin de ligne texte est `LF` (`\n`). Les séquences d'échappement ANSI pour les couleurs et la gestion du curseur sont gérées nativement par le shell (`bash`/`zsh`).

### D. Rendu Graphique / Fenêtrage (via NkentseuKit / NKWindow)

Si votre programme ouvre une fenêtre graphique :

* **Windows :** La fenêtre est créée via l'API Win32 (`CreateWindowEx`), gérée par le compositeur Windows Desktop Window Manager (DWM).
* **Linux :** La fenêtre est créée via le protocole **X11** (Xlib/XCB) ou **Wayland**, et la décoration de fenêtre (barre de titre, boutons réduire/fermer) dépend du gestionnaire de bureau (GNOME, KDE, XFCE).

---

## 45 Conclusion

L'application n'a requis aucun `#ifdef` conditionnel dans le code utilisateur. Le module de fenêtre absorbe entièrement les spécificités de chaque OS pour exposer une interface **homogène, prédictive et portable**.
> **Compte-rendu des différences observées (Windows vs Linux) :**
> 1. **Format du binaire :** Passions d'un binaire `PE` (.exe) sous Windows à un binaire `ELF` (sans extension) sous Linux.
> 2. **Représentation des chemins :** passage de la notation Windows (`C:\Users\...`) à la hiérarchie POSIX (`/home/...`).
> 3. **Gestion de la casse :** le système de fichiers Linux applique la sensibilité à la casse sur tous les accès fichiers.
> 4. **Sous-systèmes d'OS :** l'exécutable fait appel aux API système natives `Win32` sous Windows et aux appels système `POSIX / X11 / Wayland` sous Linux sans modification du code source.
> 
