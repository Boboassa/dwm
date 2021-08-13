/* Commands for keybindings imported and used in config.h */

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

static const char *termcmd[]  =       { "st", NULL };

static const char *volup[] =          { "volume", "-i", NULL };
static const char *voldown[] =        { "volume", "-d", NULL };
static const char *togglemute[] =     { "volume", "-m", NULL };

static const char *backlightup[] =    { "backlight", "-i", NULL };
static const char *backlightdown[] =  { "backlight", "-d", NULL };
//static const char *backlightreset[] = { "backlight", "-r", NULL };

//static const char *launchmenu[] =     { "fzfmenu", NULL };
