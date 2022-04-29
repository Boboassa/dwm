/* Commands for keybindings imported and used in config.h */

#define TERMINAL "st"
#define BROWSER "qutebrowser"
#define EDITOR "vim"

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = {
    "dmenu_run",
    "-m", dmenumon,
    "-fn", dmenufont,
    "-nb", background,
    "-nf", foreground,
    "-sb", selectedbg,
    "-sf", selectedfg,
    NULL };

// General stuff
static const char *termcmd[]     = { TERMINAL, NULL };
//static const char *editorcmd[]   = { TERMINAL, "-e", "editor",  NULL };
static const char *calcmd[]      = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "calcurse", NULL };

// Wiki interaction
static const char *wikicmd[]     = { TERMINAL, "-e", "vim", "-c", "WikiIndex",  NULL };
static const char *wikifzfedit[] = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "fzfwiki", NULL };
// Append
static const char *wikifzfapp[]  = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "fzfwiki", "-a", NULL };
// Readonly
static const char *wikifzfview[] = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "fzfwiki", "-v", NULL };

// Program launching
static const char *browsercmd[]  = { BROWSER, NULL };

// Volume control
static const char *volup[]       =          { "volume", "-i", NULL };
static const char *voldown[]     =        { "volume", "-d", NULL };
static const char *togglemute[]  =     { "volume", "-m", NULL };

// Notification dismiss
static const char *dunstdel[]    =       { "dunstctl", "close", NULL };
static const char *dunstdelall[] =    { "dunstctl", "close-all", NULL };
static const char *dunstmute[]   =      { "dunstctl", "set-paused", "toggle", NULL };

// Backlight control
static const char *blup[] =    { "backlight", "-i", NULL };
static const char *bldown[] =  { "backlight", "-d", NULL };
//static const char *backlightreset[] = { "backlight", "-r", NULL };

static const char *launchmenu[] =     { "launch", "-o", NULL };
