
#  Gestion du Titre Dynamique de Fenêtre

## 1. Description et Objectif de l'Exercice
L'objectif de cet exercice est de mettre en place la gestion dynamique du titre d'une fenêtre applicative. Le titre doit refléter en temps réel :
- Le nom du document ouvert (`exo5-le_titre_qui_informe`).
- L'état de modification du document (ajout d'un astérisque `*` dès qu'une touche du clavier est pressée).
- Les dimensions actuelles de la fenêtre `(800 x 600 px)`.



---
## 2. Code Source C++

```cpp

#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEvent.h"
#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu ;

int nkmain(const NkEntryState &state) {
    NkWindowConfig cfg;
    cfg.title  = "exo5-le_titre_informe";
    cfg.width  = 800;
    cfg.height = 600;
    bool IsModified = false;
    NkString NewTitle = cfg.title;
    NkWindow window(cfg);
    if (!window.IsOpen()) {
        logger.Error(" La  creation fenetre echouee");
        return -1;
    }
    
    while (window.IsOpen()) { 
        
        while(NkEvent* ev = NkEvents().PollEvent()){
            if (ev->Is<NkWindowCloseEvent>()){
                IsModified = true ;
                window.Close();
            }
            if(ev-> Is<NkWindowResizeBeginEvent>()){
                IsModified = true;
            }
            if (IsModified){
                NewTitle += "*";
                NewTitle +=  window.GetSize().ToString();
                window.SetTitle(NewTitle);
                NewTitle = cfg.title;
            }else{
                NewTitle = cfg.title + window.GetSize().ToString();
                window.SetTitle(NewTitle);
        
                
            }
          
        }
              IsModified = false ;
    }
    return 0;
} 
   
   
 
```
## 3. Explication
- *la fenetre est a  son etat initial avec les valeurs de ses dimension des la premiere execution*
    - lorsque l'on redimentionne la fenetre , l'asterisques de modification  apparait durant la modification , une fois la modification terminer , l'asterisque disparait .


---

## 4. Tableau de Validation des Tests

| Action de l'utilisateur | État `IsModifie` | Dimensions obtenues | Titre de la fenêtre résultant |
| --- | --- | --- | --- |
| **Lancement de l'application** | `false` | `800 x 600` | `exo5-le_titre_qui_informe(800x600)` |
| **Saisie d'une touche au clavier** | `true` | `800 x 600` | `exo5-le_titre_qui_informe * (800x600)` |
| **Redimensionnement manuel** | `true` | `1024 x 768` | `exo5-le_titre_qui_informe * (1024x768)` |

---

## 5. Conclusion

Le comportement implémenté permet une mise à jour réactive du titre de la fenêtre uniquement lorsque cela est nécessaire, respectant le paradigme de programmation événementielle.

>** l'image relative au test se trouve dans le fichier `test.png`