### Requirements:
Ensure you have [Raylib](https://www.raylib.com/b) and [GCC](https://gcc.gnu.org/install/) installed on your system

I recommend installing gcc via your package manager or with MinGW

For Arch Linux:
```
pacman -S gcc raylib
```

For Windows:\
[GCC install guide for Windows](https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j)\
For Raylib, just go to the website linked at the top and click Download. 

### Running:
Run the bash script with: 
```
bash build.bash 
```
or compile directly:
```
g++ -lraylib main.cpp -o sands
./sands
```

if "./sands" doesn't work then run the following command:
```
chmod +x ./sands
```

