<pre>
                        _____                                     ______                            __    
                       / ___/ ____ _ ____   ____   ___   _____   / ____/____   ____   _____ ____   / /___ 
                       \__ \ / __ `// __ \ / __ \ / _ \ / ___/  / /    / __ \ / __ \ / ___// __ \ / // _ \
                      ___/ // /_/ // /_/ // /_/ //  __// /     / /___ / /_/ // / / /(__  )/ /_/ // //  __/
                     /____/ \__,_// .___// .___/ \___//_/      \____/ \____//_/ /_//____/ \____//_/ \___/ 
                                 /_/    /_/                                                                   
</pre>
# Sapper Console
## What is it?
Minesweeper has very simple rules. The playing field is divided into cells, some of which are mined. To win, you need to open all the cells without hitting the mines. Numbers are displayed in open cells, each digit is the number of mines in the number of cells. Using this information, you can determine in which cells mines are found. Potential mines can be flagged.
## Keyboard layout
W,A,S,D         - Movement </br>
Space, Enter    - Choose option </br>
F               - Set flag  </br>
ESC             - Leave programm  </br>

## How to play?
### Windows
Run <strong>sapper_win.exe</strong>
### Linux
Run <strong>sapper_linux</strong>

## Code Compilation
Report issue if you have some problems with game or files. You can compile code to make program more suitable for your device
### Windows
<code>g++ main.cpp -o sapper_win.exe -static-libstdc++ -static-libgcc</code>
### Ubuntu/Debian
1. Update your system</br>
<code>sudo apt-get update</code>
2. Install ncurses library </br>
<code>sudo apt-get install libncurses5-dev libncursesw5-dev</code>
3. Compile source code</br>
<code>g++ main.cpp -o sapper_linux -lncurses</code>
