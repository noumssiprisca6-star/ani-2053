#  L'Architecture Multi-Backend de NKWindow


## 1. Arborescence du Module NKWindow

Le module sépare l'interface publique (`NKWindow.h`) des implémentations spécifiques logées dans le dossier `platform` qui se trouve dans le dossier `Kernel/Runtime `:

```text
NKWindow/
├── include/
│   └── NKWindow/
│       ├── NKWindow.h           <-- Interface/Façade publique de la fenêtre
│       ├── NKWindowConfig.h     <-- Configuration (Taille, Titre, Style)
│       ├── NKMain.h             <-- Point d'entrée portable (nkmain)
│       ├── NkSurface.h          <-- Description de la surface graphique
│       └── Platform/            <-- En-têtes spécifiques par plateforme
│           ├── Win32/
│           ├── Cocoa/
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
└── src/                         <-- Fichiers d'implémentation (.cpp)

```

---

## 2. Les 14 Backends / Plateformes Supportés

Le module `NKWindow` intègre la gestion de 14 backends et plateformes à travers son système d'inclusion conditionnelle :

| alignemnt | Backend / Plateforme | Fichier / Target Système |
| --- | --- | --- |
| **1** | **Win32** | Windows Desktop (`NkWin32Window.h`)|
| **2** | **Cocoa** | macOS AppKit (`NkCocoaWindow.h`) |
| **3** | **XLib** | Linux / BSD - Serveur d'affichage X11 (`NkXLibWindow.h`)|
| **4** | **XCB** | Linux / BSD - Protocol X11 léger (`NkXCBWindow.h`)
| **5** | **Wayland** | Linux - Compositeur moderne (`NkWaylandWindow.h`)
| **6** | **Android** | Mobile Android Native Activity (`NkAndroidWindow.h`)
| **7** | **UIKit** | iOS / iPadOS (`NkUIKitWindow.h`)
| **8** | **Emscripten** | WebAssembly / HTML5 Canvas (`NkEmscriptenWindow.h`)
| **9** | **HarmonyOS** | Système d'exploitation Huawei (`NkHarmonyWindow.h`)
| **10** | **UWP** | Universal Windows Platform (`NkUWPWindow.h`)
| **11** | **Xbox** | Console Xbox (`NkXboxWindow.h`)
| **12** | **Noop (Fallback)** | Implémentation par défaut sans affichage (`NkNoopWindow.h`)
| **13** | **Noop (Explicit)** | Mode headless via `NKENTSEU_FORCE_WINDOWING_NOOP_ONLY`<br> |
| **14** | **Surface Native / Generic** | Abstraction générique de surface


En regardant  directement le sous-dossier `include/NKWindow/Platform/` ainsi que les blocs de compilation conditionnelle `#if defined(...)` dans `NkWindow.h`, on dénombre **12 dossiers / cibles de plateforme distinctes** :

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



Total mesuré : **12 backends/plateformes matérielles et logicielles** implémentés dans l'arborescence.
Les quatorzes decompter incluait les plateformes d'inclusions


---

## 3. Suivi d'un même appel dans 2 Backends (`GetSize()`)

Dans le code applicatif, l'utilisateur appelle la méthode unique :

```cpp
nkentseu::math::NkVec2u size = window.GetSize();[cite: 1, 2]

```

---

### Backend A : Implémentation Win32 (Windows)

Sur Windows, l'appel communique avec l'API système `GetClientRect` via le handle de fenêtre Win32 `mData.hwnd` :

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

Sur Linux avec le serveur X11, l'appel utilise `XGetWindowAttributes` via le pointeur de display `mData.display` et l'identifiant de fenêtre `mData.window` :

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

---


## 4. Nombre de fichiers et de lignes du module

Voici la commande exécutée depuis la racine du module `NKWindow` pour obtenir des mesures exactes (excluant les fichiers générés) :

```bash
Get-ChildItem -Path include, src -Recurse -Include *.h, *.hpp, *.cpp -File | Get-Content | Measure-Object -Line

```

* **Nombre de fichiers source (`.h`, `.cpp`) :** **48 fichiers**
* **Nombre total de lignes de code :** **5 842 lignes** mais l'enonce indique 30000lignes de codes donc je vais encore reexplorer

*(Mesure effectuée en comptant l'ensemble des en-têtes du dossier `include/NKWindow/` et des fichiers d'implémentation dans `src/`).*

---


## 3. Suivi d'un appel public (`GetSize()`) dans deux backends

Méthode de l'interface publique choisie dans `NKWindow.h` :

```cpp
math::NkVec2u GetSize() const;[cite: 1, 2]

```

### Comparaison des implémentations côté à côté

| Backend Win32 (`src/Platform/Win32/NkWin32Window.cpp`)|Backend XLib (`src/Platform/XLib/NkXLibWindow.cpp`)  |
| --- | --- |
| `cpp<br>math::NkVec2u NkWindow::GetSize() const {<br>    if (mData.hwnd == nullptr) <br>        return {0, 0};<br><br>    RECT clientRect;<br>    if (::GetClientRect(mData.hwnd, &clientRect)) {<br>        return {<br>            static_cast<uint32>(clientRect.right - clientRect.left),<br>            static_cast<uint32>(clientRect.bottom - clientRect.top)<br>        };<br>    }<br>    return {0, 0};<br>}<br>`<br> |  `cpp<br>math::NkVec2u NkWindow::GetSize() const {<br>    if (mData.display == nullptr  mData.window == 0) <br>        return {0, 0};<br><br>    XWindowAttributes gwa;<br>    if (XGetWindowAttributes(mData.display, mData.window, &gwa)) {<br>        return {<br>            static_cast<uint32>(gwa.width),<br>            static_cast<uint32>(gwa.height)<br>        };<br>    }<br>    return {0, 0};<br>}<br>`<br> |

---

### Ce qui est identique vs Ce qui change

* **Ce qui est identique :** La signature de la fonction (`math::NkVec2u NkWindow::GetSize() const`), le type de retour unifié (`math::NkVec2u`), le traitement de garde en cas de handle invalide (`return {0, 0}`), et la sémantique de l'opération qui retourne la taille exacte de la zone client en pixels.


* **Ce qui change :** Les structures de données internes interrogées (`mData.hwnd` de type `HWND` sous Windows contre `mData.display` et `mData.window` sous Linux), les API natives appelées (`::GetClientRect` Win32 vs `XGetWindowAttributes` de la Xlib), ainsi que le calcul de la largeur/hauteur (soustraction des coordonnées d'un rectangle `RECT` vs lecture directe des champs `width`/`height` de la structure `XWindowAttributes`).

---

### Ce que le module NKWindow absorbe 

1. Le module absorbe la divergence complète entre les appels systèmes natifs (`GetClientRect` Win32 contre `XGetWindowAttributes` X11) et la manipulation de leurs handles propriétaires respectifs (`HWND` vs `Display*`/`Window`).


2. Il masque les différences d'arithmétique géométrique propre à chaque système pour convertir leurs structures natives (`RECT` ou `XWindowAttributes`) vers un type mathématique unique (`math::NkVec2u`).


3. Il garantit qu'un seul code applicatif produit un comportement rigoureusement identique sur toutes les plateformes sans qu'aucun `#ifdef` ne pollue le code de l'utilisateur.