

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

suivant la configuration simple de jenga que j'ai en ma possession dans le dossier application dans Nkentseu

```python
import os
from Jenga import *
from Jenga.GlobalToolchains import RegisterJengaGlobalToolchains

with project ("main"):
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
```

========================== Jenga Workspace: Nkentseu ===========================

Location: C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu
Entry file: C:\Users\jouvence computer\Desktop\tout\Gap\Nkentseu\Nkentseu\Nkentseu.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Linux, macOS, Android, iOS, Web, HarmonyOS, XboxSeries, XboxOne
Target Architectures: x86_64, arm64, wasm32
Start project: Sandbox


Projects
------------------------------------------------------------
Name                            Kind          Language   Test   External
========================================================================
__Unitest__                     StaticLib     C++        No     No
NKPlatform_Tests                TestSuite     C++        Yes    Yes
NKPlatform                      StaticLib     C++        No     Yes
NKCore_Tests                    TestSuite     C++        Yes    Yes
NKCore                          StaticLib     C++        No     Yes
NKLogger                        StaticLib     C++        No     Yes
NKLogger_Tests                  TestSuite     C++        Yes    Yes
NKMath                          StaticLib     C++        No     Yes
NKMath_Tests                    TestSuite     C++        Yes    Yes
NKMemory_Tests                  TestSuite     C++        Yes    Yes
NKMemory                        StaticLib     C++        No     Yes
NKContainers                    StaticLib     C++        No     Yes
NKContainers_Tests              TestSuite     C++        Yes    Yes
NKImage_Tests                   TestSuite     C++        Yes    Yes
NKImage                         StaticLib     C++        No     Yes
NKFont_Tests                    TestSuite     C++        Yes    Yes
NKFont                          StaticLib     C++        No     Yes
NKAudio                         StaticLib     C++        No     Yes
NKAudio_Tests                   TestSuite     C++        Yes    Yes
NKMedia                         StaticLib     C++        No     Yes
NKTime_Tests                    TestSuite     C++        Yes    Yes
NKTime                          StaticLib     C++        No     Yes
NKStream_Tests                  TestSuite     C++        Yes    Yes
NKStream                        StaticLib     C++        No     Yes
NKThreading_Tests               TestSuite     C++        Yes    Yes
NKThreading                     StaticLib     C++        No     Yes
NKFileSystem                    StaticLib     C++        No     Yes
NKFileSystem_Tests              TestSuite     C++        Yes    Yes
NKReflection_Tests              TestSuite     C++        Yes    Yes
NKReflection                    StaticLib     C++        No     Yes
NKNetwork                       StaticLib     C++        No     Yes
NKNetwork_Tests                 TestSuite     C++        Yes    Yes
NKSerialization_Tests           TestSuite     C++        Yes    Yes
NKSerialization                 StaticLib     C++        No     Yes
NKGlad                          StaticLib     C          No     Yes
NKGLSlang                       StaticLib     C++        No     Yes
NKSPIRVCross                    StaticLib     C++        No     Yes
NKMbedTLS                       StaticLib     C          No     Yes
pybind11                        StaticLib     C++        No     Yes
NKEvent                         StaticLib     C++        No     Yes
NKEvent_Tests                   TestSuite     C++        Yes    Yes
NKWindow_Tests                  TestSuite     C++        Yes    Yes
NKWindow                        StaticLib     C++        No     Yes
NKSL                            StaticLib     C++        No     Yes
NKCanvas                        StaticLib     C++        No     Yes
NKCanvas_Tests                  TestSuite     C++        Yes    Yes
NKRHI_Tests                     TestSuite     C++        Yes    Yes
NKRHI                           StaticLib     C++        No     Yes
NKUI_Tests                      TestSuite     C++        Yes    Yes
NKUI                            StaticLib     C++        No     Yes
NKGui                           StaticLib     C++        No     Yes
NKEditorKit                     StaticLib     C++        No     Yes
NKCode                          WindowedApp   C++        No     Yes
NKImGuiIntegration              StaticLib     C++        No     Yes
NKUIIntegration                 StaticLib     C++        No     Yes
NKGuiIntegration                StaticLib     C++        No     Yes


+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
main                            ConsoleApp    C++        No     Yes
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


NKCamera                        StaticLib     C++        No     Yes
NKCamera_Tests                  TestSuite     C++        Yes    Yes
NKCollision_Tests               TestSuite     C++        Yes    Yes
NKCollision                     StaticLib     C++        No     Yes
NKPhysics_Tests                 TestSuite     C++        Yes    Yes
NKPhysics                       StaticLib     C++        No     Yes
NKNavigation_Tests              TestSuite     C++        Yes    Yes
NKNavigation                    StaticLib     C++        No     Yes
NKUIDemo_Tests                  TestSuite     C++        Yes    Yes
NewGeneration                   WindowedApp   C++        No     Yes
NkUICanvasOptimizedDemo_Tests   TestSuite     C++        Yes    Yes
gltftest                        WindowedApp   C++        No     Yes
Gamepad_Tests                   TestSuite     C++        Yes    Yes
NkDrawableDemo                  WindowedApp   C++        No     Yes
NkFDV2                          WindowedApp   C++        No     Yes
NkFontDemo_Tests                TestSuite     C++        Yes    Yes
NkCanvasDemo_Tests              TestSuite     C++        Yes    Yes
NkRHIDemoText                   WindowedApp   C++        No     Yes
cr2d_Tests                      TestSuite     C++        Yes    Yes
r2d01                           WindowedApp   C++        No     Yes
NkSWRasterPrimitives            WindowedApp   C++        No     Yes
cr2d                            WindowedApp   C++        No     Yes
NKUID                           WindowedApp   C++        No     Yes
NkSpriteDemo_Tests              TestSuite     C++        Yes    Yes
renderdemo                      WindowedApp   C++        No     Yes
NkRHIDemoFull_Tests             TestSuite     C++        Yes    Yes
NKUID_Tests                     TestSuite     C++        Yes    Yes
NkRHIInterpTest_Tests           TestSuite     C++        Yes    Yes
NewGeneration_Tests             TestSuite     C++        Yes    Yes
NkRHIDemoFullImage_Tests        TestSuite     C++        Yes    Yes
renderdemo_Tests                TestSuite     C++        Yes    Yes
r2d01_Tests                     TestSuite     C++        Yes    Yes
NkRHIDemoFullImage              WindowedApp   C++        No     Yes
firsttriangle                   WindowedApp   C++        No     Yes
NKRHIDemo                       WindowedApp   C++        No     Yes
NkRHIDemoFullSL                 WindowedApp   C++        No     Yes
NkRHIDemoFullSL_Tests           TestSuite     C++        Yes    Yes
NkRHIDemoFull                   WindowedApp   C++        No     Yes
NkCanvasDemo                    WindowedApp   C++        No     Yes
NkSWRasterPrimitives_Tests      TestSuite     C++        Yes    Yes
NkFontDemo                      WindowedApp   C++        No     Yes
firsttriangle_Tests             TestSuite     C++        Yes    Yes
gltftest_Tests                  TestSuite     C++        Yes    Yes
NkUICanvasDemo_Tests            TestSuite     C++        Yes    Yes
NKUIDemo                        WindowedApp   C++        No     Yes
FontLoad                        WindowedApp   C++        No     Yes
NkSpriteDemo                    WindowedApp   C++        No     Yes
NkUICanvasOptimizedDemo         WindowedApp   C++        No     Yes
NkUICanvasDemo                  WindowedApp   C++        No     Yes
Gamepad                         WindowedApp   C++        No     Yes
NkRHIInterpTest                 WindowedApp   C++        No     Yes
NkRHIDemoText_Tests             TestSuite     C++        Yes    Yes
NkDrawableDemo_Tests            TestSuite     C++        Yes    Yes
RendererRHI                     WindowedApp   C++        No     Yes
NkFDV2_Tests                    TestSuite     C++        Yes    Yes
NKRHIDemo_Tests                 TestSuite     C++        Yes    Yes
RendererRHI_Tests               TestSuite     C++        Yes    Yes
NkAudioDemo                     ConsoleApp    C++        No     Yes
NkCameraDemos                   WindowedApp   C++        No     Yes
SandboxNKFileSystem             ConsoleApp    C++        No     Yes
SandboxNKLogger                 ConsoleApp    C++        No     Yes
SandboxNKReflection             ConsoleApp    C++        No     Yes
SandboxNKNetwork                ConsoleApp    C++        No     Yes
NKRenderer                      StaticLib     C++        No     Yes
NKRenderer_Tests                TestSuite     C++        Yes    Yes
NKTensor                        StaticLib     C++        No     Yes
NKTensor_Tests                  TestSuite     C++        Yes    Yes
NKAutograd                      StaticLib     C++        No     Yes
NKAutograd_Tests                TestSuite     C++        Yes    Yes
NKNN                            StaticLib     C++        No     Yes
NKNN_Tests                      TestSuite     C++        Yes    Yes
NKOptim                         StaticLib     C++        No     Yes
NKOptim_Tests                   TestSuite     C++        Yes    Yes
NKData                          StaticLib     C++        No     Yes
NKData_Tests                    TestSuite     C++        Yes    Yes
NKTrain_Tests                   TestSuite     C++        Yes    Yes
NKTrain                         StaticLib     C++        No     Yes
NKInfer                         StaticLib     C++        No     Yes
NKInfer_Tests                   TestSuite     C++        Yes    Yes
NKRL_Tests                      TestSuite     C++        Yes    Yes
NKRL                            StaticLib     C++        No     Yes
NKAgent_Tests                   TestSuite     C++        Yes    Yes
NKAgent                         StaticLib     C++        No     Yes
NKEvolve_Tests                  TestSuite     C++        Yes    Yes
NKEvolve                        StaticLib     C++        No     Yes
NKCivilization                  StaticLib     C++        No     Yes
NKCivilization_Tests            TestSuite     C++        Yes    Yes
NKGen                           StaticLib     C++        No     Yes
NKGen_Tests                     TestSuite     C++        Yes    Yes
NKGpt                           StaticLib     C++        No     Yes
NKSpeech                        StaticLib     C++        No     Yes
NKTensorDemo                    ConsoleApp    C++        No     Yes
NkSLComputeCheck                ConsoleApp    C++        No     Yes
NkGpuProbe                      ConsoleApp    C++        No     Yes
NkComputeNkSL                   ConsoleApp    C++        No     Yes
NkTensorGpuTest                 ConsoleApp    C++        No     Yes
NKGpuBenchTest                  ConsoleApp    C++        No     Yes
NKConvBenchTest                 ConsoleApp    C++        No     Yes
NKConvResidentBench             ConsoleApp    C++        No     Yes
NKMlpResidentBench              ConsoleApp    C++        No     Yes
NKMnistGpuTrain                 ConsoleApp    C++        No     Yes
NKMnistCnnGpuTrain              ConsoleApp    C++        No     Yes
NKTransformerTest               ConsoleApp    C++        No     Yes
NKGptTrain                      ConsoleApp    C++        No     Yes
NKAutogradTest                  ConsoleApp    C++        No     Yes
NKNNTest                        ConsoleApp    C++        No     Yes
NKConvTest                      ConsoleApp    C++        No     Yes
NKDataTest                      ConsoleApp    C++        No     Yes
NKTrainTest                     ConsoleApp    C++        No     Yes
NKRnnCtcTest                    ConsoleApp    C++        No     Yes
NKASRTest                       ConsoleApp    C++        No     Yes
NKImageCodecTest                ConsoleApp    C++        No     Yes
NkEditableMeshDemo              ConsoleApp    C++        No     Yes
NkLocomotionDemo                ConsoleApp    C++        No     Yes
NkAssetIODemo                   ConsoleApp    C++        No     Yes
NkSVGImportDemo                 ConsoleApp    C++        No     Yes
NKMeshAITest                    ConsoleApp    C++        No     Yes
NkAnimPhysTest                  ConsoleApp    C++        No     Yes
NkMicRecord                     ConsoleApp    C++        No     Yes
NKSpeechTest                    ConsoleApp    C++        No     Yes
NKTTSTrain                      ConsoleApp    C++        No     Yes
NKSpeechFeatureDemo             ConsoleApp    C++        No     Yes
NKMediaTest                     ConsoleApp    C++        No     Yes
NkVideoReadTest                 ConsoleApp    C++        No     Yes
NkAudioPlayer                   WindowedApp   C++        No     Yes
NkVideoPlayer                   WindowedApp   C++        No     Yes
NKOpusRef                       ConsoleApp    C++        No     Yes
NKVideoTest                     ConsoleApp    C++        No     Yes
NKInferTest                     ConsoleApp    C++        No     Yes
NKRLTest                        ConsoleApp    C++        No     Yes
NKAgentTest                     ConsoleApp    C++        No     Yes
NkAgentEcsDemo                  ConsoleApp    C++        No     Yes
NKEvolveTest                    ConsoleApp    C++        No     Yes
NKCivilizationTest              ConsoleApp    C++        No     Yes
NKGenTest                       ConsoleApp    C++        No     Yes
NKVAETest                       ConsoleApp    C++        No     Yes
NKMnistVAETest                  ConsoleApp    C++        No     Yes
NKMnistConvVAETest              ConsoleApp    C++        No     Yes
NKConvVAETest                   ConsoleApp    C++        No     Yes
NKVoxelGenTest                  ConsoleApp    C++        No     Yes
NKObjectGenTest                 ConsoleApp    C++        No     Yes
NKGen3DTest                     ConsoleApp    C++        No     Yes
NKGenMeshTest                   ConsoleApp    C++        No     Yes
NKSmoothMeshTest                ConsoleApp    C++        No     Yes
NKMeshRenderTest                ConsoleApp    C++        No     Yes
Model                           WindowedApp   C++        No     Yes
Nyeck                           WindowedApp   C++        No     Yes
ChatChat-Kongossa               WindowedApp   C++        No     Yes
frog                            WindowedApp   C++        No     Yes
NkSLCheck                       ConsoleApp    C++        No     Yes
NKPA                            WindowedApp   C++        No     Yes
NKECS_Tests                     TestSuite     C++        Yes    Yes
NKECS                           StaticLib     C++        No     Yes
Noge                            StaticLib     C++        No     Yes
Noge_Tests                      TestSuite     C++        Yes    Yes
Nogee                           WindowedApp   C++        No     Yes
NKEditorKitDemo                 WindowedApp   C++        No     Yes
NkAnimaEditor                   WindowedApp   C++        No     Yes
ImGuiRef                        WindowedApp   C++        No     Yes
NKGuiDemo                       WindowedApp   C++        No     Yes
NKViewportDemo                  WindowedApp   C++        No     Yes
PV3DE                           WindowedApp   C++        No     Yes
Pong                            WindowedApp   C++        No     Yes
Nkoung                          WindowedApp   C++        No     Yes
Mou                             WindowedApp   C++        No     Yes
NkImeTest                       WindowedApp   C++        No     Yes
NkImageDemo                     WindowedApp   C++        No     Yes
RihenDefi                       WindowedApp   C++        No     Yes
NkAudioECSDemo                  ConsoleApp    C++        No     Yes
NkNetWorldDemo                  ConsoleApp    C++        No     Yes
NkNavDemo                       ConsoleApp    C++        No     Yes
NkNavCoreDemo                   ConsoleApp    C++        No     Yes
NkHotReloadDemo                 ConsoleApp    C++        No     Yes
NkUIHudDemo                     ConsoleApp    C++        No     Yes
Tuto03Scene                     WindowedApp   C++        No     Yes
Tuto02Renderer                  WindowedApp   C++        No     Yes
Tuto01Fenetre                   WindowedApp   C++        No     Yes
Tuto04Camera                    WindowedApp   C++        No     Yes
Tuto05Meshes                    WindowedApp   C++        No     Yes


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


```

 `main `  est bien present  dans la liste des projets recensés par le workspace.
 comme suit : 

    
 main                            ConsoleApp    C++        No     Yes

---

### Step 2 : Générer/Construire le projet

Pour compiler mon projet :


```bash
jenga build 
 ```

* **Resultat** : construction belle et bien reussi

```
╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: main                                                            Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\main\main.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 1.13s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKCore                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 5 source file(s)
✓   [1/5] Compiled: NkLimits.cpp
✓   [2/5] Compiled: NkAssert.cpp
✓   [3/5] Compiled: NkTraits.cpp
✓   [4/5] Compiled: NkBits.cpp
✓   [5/5] Compiled: NkPlatform.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKCore.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.38s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMemory                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 14 source file(s)
✓   [1/14] Compiled: NkContainerAllocator.cpp
✓   [2/14] Compiled: NkFunction.cpp
✓   [3/14] Compiled: NkGc.cpp
✓   [4/14] Compiled: NkFunctionSIMD.cpp
✓   [5/14] Compiled: NkGlobalOperators.cpp
✓   [6/14] Compiled: NkHash.cpp
✓   [7/14] Compiled: NkMemory.cpp
✓   [8/14] Compiled: NkMultiLevelAllocator.cpp
✓   [9/14] Compiled: NkProfiler.cpp
✓   [10/14] Compiled: NkPoolAllocator.cpp
✓   [11/14] Compiled: NkTracker.cpp
✓   [12/14] Compiled: NkTag.cpp
✓   [13/14] Compiled: NkUtils.cpp
✓   [14/14] Compiled: NkAllocator.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMemory.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 3.59s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘
```


---
