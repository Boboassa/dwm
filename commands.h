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

static const char *termcmd[]   = { TERMINAL, NULL };
static const char *editorcmd[] = { TERMINAL, "-e", "editor",  NULL };
static const char *wikicmd[]   = { TERMINAL, "-e", "vim", "-c", "VimwikiIndex",  NULL };
static const char *diaryedit[] = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "vwdiary", NULL };
static const char *diaryview[] = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "vwdiary", "-v", NULL };
static const char *calcmd[]    = { TERMINAL, "-c", "float", "-g", "85x30", "-e", "calcurse", NULL };

static const char *browsercmd[] = { BROWSER, NULL };

static const char *volup[] =          { "volume", "-i", NULL };
static const char *voldown[] =        { "volume", "-d", NULL };
static const char *togglemute[] =     { "volume", "-m", NULL };

static const char *backlightup[] =    { "backlight", "-i", NULL };
static const char *backlightdown[] =  { "backlight", "-d", NULL };
//static const char *backlightreset[] = { "backlight", "-r", NULL };

static const char *launchmenu[] =     { "launch", "-o", NULL };
