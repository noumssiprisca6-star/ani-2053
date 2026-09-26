# Le presse papier pour des textes et des images 

## Code source : `c3-exo8_main.cpp`

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
    cfg.width  = 1280;
    cfg.height = 720;
    NkString contient ;
   NkClipboardImage image;  
   	NkVector<uint8> pixels;
   

    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
 
    while (window.IsOpen()) {
        while (NkEvent *ev = NkEvents().PollEvent()){
           
            if (auto* q = ev->As<NkKeyPressEvent>()) {
                if(q->GetKey() == NkKey::NK_K){

                    logger.Info(" Appuyer  sur la touche q  pour rendre le press papier est fonctionnel");
                    contient = window.GetClipboardText(); 
                    window.SetClipboardText(contient.ToUpper());
                }

                if(q->GetKey() == NkKey::NK_S){

                    logger.Info(" Appuyer sur la touche s pour rendre le press papier image  est actif");

                    window.GetClipboardImage(image);   
                   const usize totalBytes = image.pixels.Size();
                   // Parcours direct du vecteur de pixels (RGBA)
                    for (usize i = 0; i < totalBytes; i += 4) {
                        image.pixels[i]     = 255 - image.pixels[i];     // Rouge
                        image.pixels[i + 1] = 255 - image.pixels[i + 1]; // Vert
                        image.pixels[i + 2] = 255 - image.pixels[i + 2]; // Bleu
                        // image.pixels[i + 3] (Alpha) reste non pris 
                    }
                   
                }
                 

            }
            
            if(ev->Is<NkWindowCloseEvent>()){
                window.Close();
            }
        }
    }
   
    return 0;
} 
```


## Explication

>** const usize totalBytes = image.pixels.Size();**
1. **`image.pixels.Size()`** demande au tableau dynamique le nombre total d'octets qu'il contient.
2. **`usize`** est choisi pour stocker ce résultat car il s'agit d'une quantité mémoire / taille d'un tableau.
3. **`const`** verrouille la variable `totalBytes` : la taille de l'image ne varie pas pendant le traitement de la boucle, donc cette valeur est constante du début à la fin de l'opération. 
-  La boucle for se parcours en sautant toutes les sequences ou `i` est un multiple de trois 

---

## Explication du fonctionnement :

1. **Gestion des événements (`NKEvent`) :** Dans la boucle principale, nous utilisons `NkEvents().PollEvent()` pour traiter la file d'événements. À l'aide de `ev->As<NkKeyPressEvent>()`, nous détectons le moment où l'utilisateur appuie sur les touches `k` ou `s`.


2. **Presse-papiers Texte (`NkClipboardText::GetClipboardText` / `SetClipboardText`) :** Lors de l'appui sur `k`, apres avoir copier le texte lors de l'execution , le texte brut est extrait, transformé caractère par caractère en majuscule, puis réécrit directement dans le presse-papiers, il est visible directement dans celui ci et accessible avec la touche raccourcit du clavier `window + v`

- le fichier `presstext .png` ce trouvant dans le dossier `exo8-le_presse_papiers_dans_les_deux_sens` illustre bien cette suite d'evenement

**Resultat du logger**
```bash
r taire ces deux lignes.
[2026-09-26 22:08:50.294] [INF] [default] [c3-exo8_main.cpp:31 in nkmain] ->  Appuyer  sur la touche k pour rendre le press papier est fonctionnel
[2026-09-26 22:08:53.057] [INF] [default] [c3-exo8_main.cpp:31 in nkmain] ->  Appuyer  sur la touche k pour rendre le press papier est fonctionnel
[2026-09-26 22:08:55.755] [INF] [default] [c3-exo8_main.cpp:31 in nkmain] ->  Appuyer  sur la touche k pour rendre le press papier est fonctionnel
[2026-09-26 22:08:56.389] [INF] [default] [c3-exo8_main.cpp:31 in nkmain] ->  Appuyer  sur la touche k pour rendre le press papier est fonctionnel
```

3. **Presse-papiers Image 

(`NkClipboardImage::GetClipboardImage` / `SetClipboardImage`) :** Lors de l'appui sur `S`, le buffer de l'image stocké dans le presse-papiers est chargé sous forme d'une `NkClipboardImage`. On parcourt le tableau de pixels et inverse les canaux de couleurs ($255 - \text{valeur}$) avant de renvoyer l'image modifiée dans le presse-papiers.

- le fichier `pressimage.png` illustre parfaitement l'inversion de couleur, et  le fichier `pressactive.png` es obtenu apres le     `window + v ` pour observer le press papier

**Resultat du logger**

```bash
[NKLogger] niveau=info | console=debug | journal=C:\Users\jouvence computer\Desktop\ex\ani-2053\chapitre-03\exo8-le_presse_papiers_dans_les_deux_sens\logs\app.log
[NKLogger] trace/debug sont SOUS le niveau : NK_LOG_LEVEL=debug pour les voir ; NK_LOG_CONSOLE=1 pour tout mettre a l'ecran ; NK_LOG_QUIET=1 pour taire ces deux lignes.
[2026-09-26 22:04:15.192] [INF] [default] [c3-exo8_main.cpp:38 in nkmain] ->  Appuyer sur la touche s pour rendre le press papier image  est actif
[2026-09-26 22:04:19.761] [INF] [default] [c3-exo8_main.cpp:38 in nkmain] ->  Appuyer sur la touche s pour rendre le press papier image  est actif
[2026-09-26 22:04:21.839] [INF] [default] [c3-exo8_main.cpp:38 in nkmain] ->  Appuyer sur la touche s pour rendre le press papier image  est actif
```
> ** Je note egalement que la mise en place de mes reponses a cette exercices m'a demander une mise a jour de Nkentseu pour beneficier de toutes les modifications qui furent effectuer (creations et suppressions de nombreux fichiers et des ameliorations )** 




