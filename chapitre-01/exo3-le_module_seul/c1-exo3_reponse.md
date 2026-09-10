# ARBORESCENCE DE NKMath DANS NKENTSEU
  ┌─────────────────┐
  │     NKMath      │  5. Cible
  └────────┬────────┘
           ↑
  ┌────────┴────────┐
  │  NKContainers   │  4.
  └────────┬────────┘
           ↑
  ┌────────┴────────┐
  │    NKMemory     │  3.
  └────────┬────────┘
           ↑
  ┌────────┴────────┐
  │     NKCore      │  2.
  └────────┬────────┘
           ↑
  ┌────────┴────────┐
  │   NKPlatform    │  1. Base
  └─────────────────┘



## Nombre de projet 
 - Build  de  (5 projects) :
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)


## Description
- chaque fleche oriente vers le haut represente en faite la dependance :"depend de"
- NKPlateform est construit en premier  par consequent NKMath est construit   en  dernier et depends donc des quatres autres projets  