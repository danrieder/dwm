# Daniel's dwm build

[dwm](https://dwm.suckless.org/) is a tiling window manager for X by [suckless.org](https://suckless.org/).  
- dwm is customized through editing its source code, which makes it extremely fast and secure - it does not process any input data which isn't known at compile time, except window titles and status text read from the root window's name. You don't have to learn Lua/sh/ruby or some weird configuration file format (like X resource files), beside C, to customize it for your needs: you only have to learn C (at least in order to edit the header file).
- Because dwm is customized through editing its source code, it's pointless to make binary packages of it. This keeps its userbase small and elitist. No novices asking stupid questions. There are some distributions that provide binary packages though.  

## Keybindings:

- See config.h for a full list of key binds.

## Patches:

- [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/): add gaps, and additional layouts.
- [sticky](https://dwm.suckless.org/patches/sticky/): (<kbd>super+s</kbd>) toggles a window to perisist as you change tags. 
- [swallow](https://dwm.suckless.org/patches/swallow/): spawned window takes the place of window that spawned it (ex: playing a video with mpv). 
- [fullscreen](https://dwm.suckless.org/patches/fullscreen/): (<kbd>super+f</kbd>) make a window fullscreen and keep focus.

## Installation:

```bash
git clone https://github.com/danrieder/dwm.git
cd dwm
sudo make install
```
