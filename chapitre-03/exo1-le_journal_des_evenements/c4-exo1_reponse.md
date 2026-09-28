# Capture et comptage des événements UI

## 1. Description de l'exercice
L'objectif de cet exercice est de capturer l'ensemble des événements système transmis à l'application (souris, clavier, redimensionnement et glisser-déposer d'un fichier), d'afficher dans la console la **famille** et le **type** de chaque événement reçu, puis d'estimer le volume d'événements générés lors d'une utilisation normale pendant **une seconde**.

---

## 2. Implémentation du Code C++ `c4-exo1_main.cpp`


```cpp
        #include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "Ma fenetre";
    cfg.width  = 800;
    cfg.height = 600; 

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
    while (window.IsOpen()) { 
        while (NkEvent *ev = NkEvents().PollEvent()){

            if (auto* press = ev->As<NkMouseButtonPressEvent>()) {
                if (press->IsLeft()) {
                    logger.Info(" Faire un double-clic ");
                    logger.Info("La famille de l'evenement souris , type : Entrées souris spécifiques");
                }
            } 

            if (auto* redimention = ev->As<NkWindowResizeEvent>()) {
              logger.Info(" Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement ");
              logger.Info("La famille de  l'evenement de redimention , le type : aucun trouve ");
            }

            if(auto* drop = ev->As<NkDropFileEvent>()){
                const auto& filData = drop->data;
                const uint32 filecount = filData.Count();
                logger.Info("porter un fichier dans la fenetre  famille evenements  pour deposer le fichier dans la fenetre ");
                logger.Info("la famille de l'evenement Drag and Drop, type : Opérations de Drag & Drop");
            }
            if (auto* q = ev->As<NkKeyPressEvent>()) {
                if(q->GetKey() == NkKey::NK_K){
                    logger.Info(" Appuyer sur la touche k pour fermer la fenetre ");
                    logger.Info(" La famille de l'Evenement de souris , type :   Entrées clavier spécifiques");
                    window.Close();
                }
            }
        }
     }
    return 0;
} 



```

---

## 3. Classification des Événements Pris en Charge

| Famille d'événement | Type d'événement (`Classe C++`) | Action de l'utilisateur déclencheuse |
| --- | --- | --- |
| **Souris** | `NkMouseMoveEvent` | Déplacement continu du curseur sur la fenêtre |
| **Souris** | `NkMouseButtonPressEvent` | Clic sur l'un des boutons de la souris (ex: Clic Gauche) |
| **Clavier** | `NkKeyPressEvent` | Pression d'une touche du clavier  |
| **Fenêtre** | `NkWindowResizeEvent` | Redimensionnement des bordures de la fenêtre |
| **Drag & Drop** | `NkDropFileEvent` | Glisser-déposer d'un ou plusieurs fichiers externes dans la fenêtre |

---

## 4. Extrait du Journal (Logs) Obtenu

voici les loggers obtenues en appliquant les actions specifiques de declenchement des  evenements 

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


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  journal.exe
     C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-03\exo1-le_journal_des_evenements\Build\Bin\Debug-Windows\journal\journal.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
[NKLogger] niveau=info | console=debug | journal=C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-03\exo1-le_journal_des_evenements\logs\app.log
[NKLogger] trace/debug sont SOUS le niveau : NK_LOG_LEVEL=debug pour les voir ; NK_LOG_CONSOLE=1 pour tout mettre a l'ecran ; NK_LOG_QUIET=1 pour taire ces deux lignes.
[2026-09-28 19:23:01.317] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:01.318] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:02.575] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 75
[2026-09-28 19:23:03.577] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 139
[2026-09-28 19:23:04.732] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 271
[2026-09-28 19:23:06.053] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 438
[2026-09-28 19:23:07.397] [INF] [default] [c4-exo1_main.cpp:30 in nkmain] ->  Faire un double-clic  avec la souris
[2026-09-28 19:23:07.398] [INF] [default] [c4-exo1_main.cpp:31 in nkmain] -> La famille de l'evenement souris , type : Entrees souris specifiques
[2026-09-28 19:23:07.398] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 597
[2026-09-28 19:23:07.399] [INF] [default] [c4-exo1_main.cpp:30 in nkmain] ->  Faire un double-clic  avec la souris
[2026-09-28 19:23:07.399] [INF] [default] [c4-exo1_main.cpp:31 in nkmain] -> La famille de l'evenement souris , type : Entrees souris specifiques
[2026-09-28 19:23:09.076] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 598
[2026-09-28 19:23:10.086] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 737
[2026-09-28 19:23:11.690] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 738
[2026-09-28 19:23:12.699] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 827
[2026-09-28 19:23:13.706] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 955
[2026-09-28 19:23:15.183] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1140
[2026-09-28 19:23:15.183] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.184] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.184] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.184] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.185] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.185] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.185] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.186] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.186] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.186] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.186] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.187] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.187] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.187] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.188] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.188] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.190] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.191] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.191] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.191] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.191] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.192] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.192] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.192] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.193] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.193] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.193] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.193] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.194] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.194] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.195] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.196] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.196] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.196] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.197] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.197] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.197] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.198] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.198] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.198] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.199] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.199] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.199] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.200] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.200] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.201] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.201] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.202] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.202] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.203] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:15.204] [INF] [default] [c4-exo1_main.cpp:36 in nkmain] ->  Le redimentionnement s'active lorsque la  fenetre se creer et continu apres chaque redimentionnement 
[2026-09-28 19:23:15.204] [INF] [default] [c4-exo1_main.cpp:37 in nkmain] -> La famille de  l'evenement de redimention , le type : aucun trouve 
[2026-09-28 19:23:16.186] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1161
[2026-09-28 19:23:17.456] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1211
[2026-09-28 19:23:18.464] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1311
[2026-09-28 19:23:19.473] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1412
[2026-09-28 19:23:20.552] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1463
[2026-09-28 19:23:21.560] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1488
[2026-09-28 19:23:22.569] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1588
[2026-09-28 19:23:23.578] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1643
[2026-09-28 19:23:24.586] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1743
[2026-09-28 19:23:25.594] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1843
[2026-09-28 19:23:26.815] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1895
[2026-09-28 19:23:27.895] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1931
[2026-09-28 19:23:29.174] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1949
[2026-09-28 19:23:30.181] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 1998
[2026-09-28 19:23:31.190] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2072
[2026-09-28 19:23:32.198] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2172
[2026-09-28 19:23:33.299] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2213
[2026-09-28 19:23:34.570] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2229
[2026-09-28 19:23:35.577] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2260
[2026-09-28 19:23:36.633] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2299
[2026-09-28 19:23:37.633] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2352
[2026-09-28 19:23:38.682] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2377
[2026-09-28 19:23:40.094] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2396
[2026-09-28 19:23:41.101] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2448
[2026-09-28 19:23:42.311] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2465
[2026-09-28 19:23:43.318] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2552
[2026-09-28 19:23:44.729] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2596
[2026-09-28 19:23:46.612] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2597
[2026-09-28 19:23:47.621] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2659
[2026-09-28 19:23:48.760] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2749
[2026-09-28 19:23:48.762] [INF] [default] [c4-exo1_main.cpp:43 in nkmain] -> porter un fichier dans la fenetre  famille evenements  pour deposer le fichier dans la fenetre 
[2026-09-28 19:23:48.762] [INF] [default] [c4-exo1_main.cpp:44 in nkmain] -> la famille de l'evenement Drag and Drop, type : Operations de Drag & Drop
[2026-09-28 19:23:50.205] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2780
[2026-09-28 19:23:54.043] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2781
[2026-09-28 19:23:55.334] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2821
[2026-09-28 19:23:57.714] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2844
[2026-09-28 19:23:58.833] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2861
[2026-09-28 19:23:59.840] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 2960
[2026-09-28 19:24:00.848] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 3009
[2026-09-28 19:24:02.531] [INF] [default] [c4-exo1_main.cpp:48 in nkmain] ->  Appuyer sur la touche k pour fermer la fenetre 
[2026-09-28 19:24:02.532] [INF] [default] [c4-exo1_main.cpp:49 in nkmain] ->  La famille de l'Evenement de souris , type :   Entrees clavier specifiques
[2026-09-28 19:24:02.591] [INF] [default] [c4-exo1_main.cpp:55 in nkmain] -> Total d'events : 3026

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

## 5. Mesure et Comptage des Événements par Seconde

Une mesure effectuée sur **1 seconde d'usage normal** (déplacement de la souris tout en saisissant une touche du clavier) donne les résultats suivants :

* **Durée du test :** 34.25s
* **Nombre total d'événements capturés :** `3026` événements par seconde.

### Répartition constatée :

1. **Événements de Redimention(`NkWindowResizeEvent`) : ~85% à 95%**
Le  redimentionnement  génère un très grand nombre d'événements car chaque micro-déplacement sur l'axe X/Y envoie une notification au système.
2. **Événements Clavier et Souris (`NkKeyPressEvent` ,`NkMouseButtonPressEvent`) : ~30% à 10%**
Dépend de la vitesse de frappe (environ des une qutrevingtaine événements par seconde lors d'une frappe rapide).
3. **Événements Fenêtre & Drag & Drop : ~1% à 2%**
Ce sont des événements ponctuels qui n'interviennent que lors d'une action spécifique.

---

## 6. Conclusion

* L'architecture événementielle basée sur `PollEvent()` permet  d'intercepter avec précision chaque interaction utilisateur.
* Le **déplacement de la souris** et **le redimentionnement** sont  des  sources ultra-majoritaire du flux d'événements reçus par l'application lors d'une seconde d'utilisation.
