# Build
```
MSYS2 32bit -> MSYS2 MSYS

pacman -S msys/gcc

cd conemu-msys2-32
windres -i ConEmuT.rc -o ConEmuT.res.o
gcc ConEmuT.res.o ConEmuT.cpp -o conemu-msys2-32.exe
```