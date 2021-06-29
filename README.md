# Boboassa's build of dwm the dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements

In order to build dwm you need the Xlib header files.


## Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    `make clean install`


## Running dwm

Add the following line to your .xinitrc to start dwm using startx:

    `exec dwm`

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    `DISPLAY=foo.bar:1 exec dwm`

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your `.xinitrc`:

```
    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm
```

## Configuration

The configuration of dwm is done by creating a custom `config.h`
and (re)compiling the source code.


## Applied patches

Patches are a way of adding functionality to the minimal standard build of dwm

- Barpadding
- Center
- Centeredwindowname
- Colorbar
- Cycleleyouts
- Statuspadding
- Vanitygaps
- Zoomswap


## Aknowledgements

Visit [suckless.org](https://dwm.suckless.org/) for more information on dwm
and other suckless programs.
