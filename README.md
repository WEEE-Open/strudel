# S.T.R.U.D.E.L.
*Salvavita Temporeggiatore per Rottami Umilissimi Dimenticati Estremamente Logori*
A `C` program that displays a random, team releated, assortment of words.
## Dependencies
The only dependency used is [Raylib](https://www.raylib.com/), it's just needed to be installed on the building device.

On debian based systems you can install the prerequirements (usually they are not needed on a full installation of linux)
``` bash
apt install build-essential git # for git and c compiler
apt install libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev # for graphics and stuff, usually not needed

```

To install `raylib` it's enough to run
``` bash
apt install libraylib-dev # for the full environment
apt install libraylib550 # for only the runtime
```

## Usage
To use the program it must be built as a normal `c` program, using `raylib` as one of the libraries
``` bash
gcc src/main -o build/main -lraylib # or other compiler
```

To run the program it's enough to run from the terminal the path to it, it will open a full-screen window and start to print words
``` bash
build/main
```
>  Note: if it gives an error that `/build` doesn't exist, it must be made
