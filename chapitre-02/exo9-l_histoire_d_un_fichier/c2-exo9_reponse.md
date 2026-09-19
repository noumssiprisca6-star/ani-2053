


#  Histoire d'un fichier du moteur : `NkAudioBackends.cpp` Dans NKentseu

* **Commande Executee**
```bash
git log --follow --numstat -- Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp
```


```bash

commit 9fc9f5f6b6fee59a8a43af4a1e91c342b9ecd910
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Mon Jul 13 17:08:43 2026 +0100

    fix(nkaudio): ROOT CAUSE du son ralenti/bruite/intermittent - mixBuffer sous-dimensionne vs buffer device REEL. WASAPI demande jusqu'a bufferFrames (mesure: 1056 frames a 48000) par reveil callback, mais l'engine dimensionnait mixBuffer sur config.bufferSize=256 -> AudioCallback clampait frameCount (256/1056=24%) -> buffer device rempli a 24%, 76% silence -> dropouts massifs percus comme 'ralenti + bruit + pas toujours correct'. Fix: (1) WASAPI GetBufferSize() renvoie la VRAIE taille (mBufferSize=bufferFrames) au lieu du 256 demande ; (2) AudioEngine::Initialize resynchronise config (sampleRate/channels/frames) sur le format REELLEMENT negocie par le device et (re)dimensionne mixBuffer a max(bufferSize, framesReels)*channels. Corrige aussi le cas taux/canaux device != demande (resample vers le mauvais taux). NkAudioPlayer affiche desormais le format device reel.

7       0       Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit bdda350a054705f217f0daf5a54ab02bcb9c56ef
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Thu Jul 9 16:53:52 2026 +0100

    style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
    
    Applique le .clang-format maison a tout l'arbre source C++ :
    - indentation par namespace (NamespaceIndentation: All)
    - public/private/protected indentes sous class (IndentAccessModifiers)
    - une ligne vide entre definitions (SeparateDefinitionBlocks)

commit 9fc9f5f6b6fee59a8a43af4a1e91c342b9ecd910
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Mon Jul 13 17:08:43 2026 +0100

    fix(nkaudio): ROOT CAUSE du son ralenti/bruite/intermittent - mixBuffer
 sous-dimensionne vs buffer device REEL. WASAPI demande jusqu'a bufferFrame
s (mesure: 1056 frames a 48000) par reveil callback, mais l'engine dimensio
nnait mixBuffer sur config.bufferSize=256 -> AudioCallback clampait frameCo
unt (256/1056=24%) -> buffer device rempli a 24%, 76% silence -> dropouts m
assifs percus comme 'ralenti + bruit + pas toujours correct'. Fix: (1) WASA
PI GetBufferSize() renvoie la VRAIE taille (mBufferSize=bufferFrames) au li
eu du 256 demande ; (2) AudioEngine::Initialize resynchronise config (sampl
eRate/channels/frames) sur le format REELLEMENT negocie par le device et (r
e)dimensionne mixBuffer a max(bufferSize, framesReels)*channels. Corrige au
ssi le cas taux/canaux device != demande (resample vers le mauvais taux). N
kAudioPlayer affiche desormais le format device reel.

7       0       Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit bdda350a054705f217f0daf5a54ab02bcb9c56ef
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Thu Jul 9 16:53:52 2026 +0100

    style: reformatage clang-format repo-wide (Kernel/Engine/Applications)
    
    Applique le .clang-format maison a tout l'arbre source C++ :
    - indentation par namespace (NamespaceIndentation: All)
    - public/private/protected indentes sous class (IndentAccessModifiers)
    - une ligne vide entre definitions (SeparateDefinitionBlocks)
    - une instruction par ligne, accolades attachees, tabs
    
    1748 fichiers (.h/.cpp/.inl/.mm). Verifie : NKGptTrain 25/25 et renderd
emo 28/28 buildent OK apres reformatage.

1258    1020    Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit d4fce7ee584ccee1f4fe53d4c7b07e75d4e59588
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Sat Jul 4 13:24:06 2026 +0100

    feat(render): grille infinie reutilisable + fix ombres GL (glClipContro
l/clipZ01) + fix freeze DX11 (ResizeBuffers/command list) + NkInput cross-p
latform + cap FPS/vsync + pool object-UBO dynamique + ombres instanciees ; 
consolidation WIP multi-modules (NKCode, Noge, ...) (#19)

9       2       Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit 15156667d93f51db4d3582ce546ad6f7f5c2a156
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Mon Jun 22 06:16:23 2026 +0100

    chore(runtime): audit NKMemory complet + fix portabilite NkHash LP64 (#
5)
    
    * fix(export): defaut statique + inline/enum sans dllimport (corrige -W
ignored-attributes en build consommateur monolithique)
    
    * chore(runtime): audit NKMemory complet du Runtime + fix portabilite N
kHash LP64
    
    Conversion de tout Kernel/Runtime vers NKMemory (zero new/delete/malloc
/free
    brut de notre code) en 3 vagues, build de verif par module :
    - NKImage (deja conforme), NKCamera, NKCollision, NKUI, NKECS, NKFont
    - NKRHI, NKRenderer (NkMaterial ctor prive -> placement-new sur NkAlloc
), NKAudio
      (OGG=stb_vorbis vendored laisse, frontiere deja NKMemory)
    - NKEvent (104 Clone() + deleter NkEventDelete via NkUniquePtr, + doubl
on
      NkEventSystem.h dans NKWindow), NKWindow
    
    Encapsulation des liberations memoire SYSTEME (X11/XCB/xkb) dans
    NKWindow/Platform/Common/NkSystemMemory.h (NkX11Free/NkXcbFree) : plus 
de
    XFree/free systeme nus, mais ils appellent toujours le free natif (jama
is NkFree).
    
    Fix portabilite pre-existant revele par le re-build multi-plateforme :
    NkHash specialise pour uint64_t (= unsigned long en LP64) ne couvrait p
as
    nkentseu::uint64 (= unsigned long long partout) sur Android/Web/Linux/H
armony
    -> spec SFINAE generique sur tous les types entiers dans NkFunctional.h
    (non-regressant Windows).
    
    Re-build verifie : NKAudio/NKEvent 5/5 plateformes, NKRHI 4/5, NKRender
er 3/5.
    Echecs NKRenderer Linux (macros X11 Bool dans headers NKSL) et NKRHI/NK
Renderer
    HarmonyOS (stub OH_NativeWindow) sont PRE-EXISTANTS, hors perimetre mem
oire.
    
    Inclut aussi le travail de session accumule (Mou, Guides, NkSpark, NKCa
nvas,
    Songoo, portage Linux).
    
    * docs(readme): README principal reecrit (etat reel du depot) + fix tou
s les warnings du build Mou
    
    - README: remplace le contenu obsolete/fictif (structure Modules/includ
e, modules
      NKGraphics/NKPhysics inexistants, focus NKMath) par l'etat REEL : cou
ches Kernel/
      Foundation-System-Runtime + Engine/Noge + Applications, statuts par m
odule, vraies
      commandes Jenga (--target/--platform/--linux-backend), apps reelles, 
scripts git.
    - NKCanvas OpenGL: macro NK_GL_AVAIL pour les gardes de procs GL (point
eurs sur desktop/
      glad, fonctions liees sur GLES Android/iOS/Web/Harmony) -> supprime -
Wpointer-bool-conversion
      (glUniform*/glFramebuffer*). NkOpenGLContext::RecreateSurface marque 
'override'.
    - MouConfig: gLogger init a nullptr (init paresseuse) au lieu de la mac
ro logger qui
      contient __func__ -> supprime -Wpredefined-identifier-outside-functio
n.
    - NkOGGVorbisCodec (stb_vorbis vendored): pragma local pour neutraliser
 la comparaison
      de pointeur tautologique sans toucher la logique.
    Resultat: build Mou 0 warning sur Windows ET Android.

25      24      Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit 1f26ef965a87aaca651cb57ed1c2d11230ecc5ec
Author: Rihen <rihen.universe@gmail.com>
Date:   Fri May 29 23:36:49 2026 +0100

    Session 2026-05-29 — D-NkImage, Android APK restauré, Harmony compile
    
    D — NkImage hérite de NKIResource (NKStream/NKIResource.h)
      * 9 overrides : LoadFromFile/Memory(2args)/Stream, SaveToFile/Memory/
Stream,
        IsValid, Unload. Retrait du =0 par défaut des LoadFromMemory(d,s,ch
annels)
        pour éviter ambiguïté 2-args vs 3-args.
      * NKImage.jenga : +NKStream src + dependson NKStream.
      * Cascade transitive : NKCanvas/NKCamera/NKEvent/NKRenderer compilent
 sans
        toucher leurs jengas (propagation includedirs via dependson).
    
    Hot-plug/DPI Phase 2 — 9 backends NKWindow livrés
      * XLib/XCB (XRandR + hot-plug), Wayland (wl_output multi), Cocoa/UIKi
t
        (NSScreen/UIScreen + observers), Android (AConfiguration + JNI),
        Emscripten (devicePixelRatio), HarmonyOS (OH_NativeDisplayManager_*
),
        Noop (factice). API NkWindow::EnumerateMonitors/GetCurrentMonitor/
        GetMonitorCount + events NkSystemDisplayEvent + NkWindowDpiEvent.
    
    Harmony — NKWindow + chaîne kernel compile pour --platform harmony
      * NkHarmonyGamepad : réécrit en stub aligné NkIGamepad (snapshot vide
).
      * NkHarmonyEventSystem.cpp stubbé (SDK header retiré + types obsolète
s).
      * NkHarmonyWindow.cpp : nativeWindow -> ohNativeWindow.
      * NKAudio : ALSA exclu PLATFORM_LINUX si HARMONYOS/ANDROID ; climits
        ajouté à NkOGGVorbisCodec (UINT_MAX).
      * NKCanvas/OpenGL : 17 sites WAYLAND||ANDROID reçoivent ||HARMONYOS ;
        macro NK_NATIVE_WIN(s) pour gérer s.nativeWindow vs s.ohNativeWindo
w.
    
    Cleanup
      * NkUIFontBridge.h:221-223 : 3 lignes PowerShell collées par accident
        en queue de fichier retirées.
      * NKImage/ROADMAP.md + NKWindow/ROADMAP.md actualisés.
    
    À reprendre prochaine session
      * Noge ECS includes obsolètes (NkGameObjectFactory.h, NkECSDefines.h)
.
      * Pong : refonte sur NKCanvas (chantier A) résorbera NkSafeArea inclu
de.
      * NkFont module : implémenter NKIResource (atlas-centric à évaluer).

4       1       Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit bcc7c99d438f0103944d5bb712bf7e958790d3a5
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Thu May 21 13:36:03 2026 +0100

    update

794     146     Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit d557314e707baf17e53029b9d9cae2c5164dd417
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Tue May 5 20:04:22 2026 +0100

    update

0       0       {Modules => Kernel}/Runtime/NKAudio/src/NKAudio/NkAudioBack
ends.cpp

commit f1e536a58890ac267b12ab7df1004d0a43270c48
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Wed Apr 29 10:39:16 2026 +0100

    refactor 001

1       1       Modules/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp

commit 8737e282dbcbeab52dc0e6fb2740904daaf09013
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Sun Apr 19 12:23:47 2026 +0100

    Begin clearing and restructured file

487     0       Modules/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp
(END)
```

**Fichier étudié :** `Kernel/Runtime/NKAudio/src/NKAudio/NkAudioBackends.cpp`  
**Projet :** Moteur de jeu `nkentseu`  
**Auteur principal :** M.Teuguia /le teguis

---

## 1. Création du Fichier

* **Date :** 19 Avril 2026
* **Commit :** `8737e282dbcbeab52dc0e6fb2740904daaf09013`
* **Message de commit :** `Begin clearing and restructured file`
* **Ce qui s'est passé :** Le fichier a été créé lors d'une phase de restructuration du module Audio (`NKAudio`). Dès sa création, M.teuguia  y a écrit 487 lignes de code d'apres ce que je vois  pour mettre en place la gestion des sorties sonores  dans le depot .

---

## 2. Les 3 Moments Clés de son Évolution

### Moment 1 : Déploiement et expansion majeure du code
* **Date :** 21 Mai 2026
* **Commit :** `bcc7c99d438f0103944d5bb712bf7e958790d3a5` 
* **Changement :** +794 lignes ajoutées, -146 lignes supprimées.
* **Explication  :** C'est le plus gros pic de modification du fichier selon moi . l'auteur  a ajouté une très grande partie de la logique de manipulation son et des pilotes audio pour rendre le module fonctionnel sur différentes plateformes certainement.

---

###  Moment 2 : Reformatage et nettoyage automatique
* **Date :** 9 Juillet 2026
* **Commit :** ` bdda350a054705f217f0daf5a54ab02bcb9c56ef`
* **Message de commit :** `style: reformatage clang-format repo-wide`
* **Changement :** +1258 lignes, -1020 lignes.
* **Explication :** Le code n'a pas changé de comportement, mais son apparence a été nettoyée sur l'ensemble du moteur avec l'outil `clang-format`. L'objectif était de respecter des règles de présentation strictes (alignement des accolades, des espaces et des namespaces ,etc.).

---

###  Moment 3 : Correction du bogue audio ("Root Cause" WASAPI)
* **Date :** 13 Juillet 2026
* **Commit :** `9fc9f5f6b6fee59a8a43af4a1e91c342b9ecd910`
* **Message de commit :** `fix(nkaudio): ROOT CAUSE du son ralenti/bruite/intermittent...`
* **Changement :** Correction ciblée du problème d'échantillonnage sous Windows (WASAPI).
* **Explication  :** L'auteur a identifié et résolu un bogue critique où le son grésillait ou tournait au ralenti. La mémoire tampon (*buffer*) réservée par le moteur était trop petite par rapport à ce que la carte son demandait vraiment (256 frames au lieu de 1056).

---

## 3. Ce que les messages disent des raisons des changements

L'historique montre une évolution très naturelle pour un moteur de jeu en développement :
1. **Une phase de démarrage (Avril - Mai) :** On écrit le code rapidement pour que le son fonctionne ( avec `Begin clearing`, `update` dans les description des commits).
2. **Une phase de propreté (Début Juillet) :** On uniformise le style de tout le projet pour le rendre lisible et facile à maintenir (`style: reformatage`).
3. **Une phase de correction fine (Mi-Juillet) :** On corrige les bogues matériels complexes précis découverts lors des tests (`fix(nkaudio)`).

---

### RESUME DE CE QUE J'EN RETIENT

1. *"J'ai choisi le fichier `NkAudioBackends.cpp` qui gère le son dans le moteur `nkentseu`."*
2. *"En faisant `git log --follow --numstat`, j'ai découvert qu'il est né le 19 avril 2026, qu'il a subi un gros reformatage de style le 9 juillet, et qu'un bogue important de son ralenti a été corrigé le 13 juillet."*
3. *"Les messages de commit montrent qu'on est passé d'une phase de création rapide à une phase de nettoyage puis de correction de bogues matériels."*

## 4. Conclusion

Le fichier `NkAudioBackends.cpp` est une pièce centrale du moteur audio. Son histoire montre le passage d'un code brut en cours de création à un composant stabilisé, nettoyé et corrigé pour fonctionner correctement avec la carte son de l'ordinateur.


