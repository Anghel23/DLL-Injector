# 🔥 DLL Injector

Acest proiect este un injector DLL simplu, utilizat pentru a încărca o bibliotecă DLL într-un proces țintă. Este dezvoltat ca parte a lucrării de licență și demonstrează utilizarea tehnicilor de injecție la nivel user-mode.

## ⚙️ Tehnologii utilizate
- **C++**
- **WinAPI** (OpenProcess, VirtualAllocEx, WriteProcessMemory, CreateRemoteThread)

## 🚀 Funcționalitate
Injectorul alocă memorie în procesul țintă, scrie calea DLL-ului în memoria acestuia și apelează `LoadLibraryA` pentru a-l încărca.

## 📥 Instalare și compilare
### **1. Clonare repository**
```bash
 git clone https://github.com/username/DLL_Injector.git
 cd DLL_Injector
```

### **2. Compilare**
Compilarea se poate face folosind `cl.exe` (Visual Studio Developer Command Prompt):
```bash
cl /EHsc DLL_Injector.cpp /link kernel32.lib user32.lib
```

Sau utilizând `g++` cu MinGW:
```bash
g++ -o DLL_Injector.exe DLL_Injector.cpp -static -lKernel32
```

## 🛠️ Utilizare
```bash
DLL_Injector.exe <pid> <path-to-DLL>
```
Exemplu:
```bash
DLL_Injector.exe 1234 C:\path\to\your.dll
```

## ⚠️ Notă
- Necesită privilegii administrative pentru a injecta DLL-ul în anumite procese.
- Este destinat **doar pentru cercetare și testare**.

## 📜 Licență
Acest proiect este disponibil sub licență MIT.

📌 **Proiect creat ca parte a lucrării de licență.**

