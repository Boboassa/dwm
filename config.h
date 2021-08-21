/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 15;       /* vertical gap above the bar */
static const int sidepad            = 15;       /* horizontal gap on the left and right of the bar */
static const int horizpadbar        = 15;       /* horizontal internal padding for statusbar */
static const int vertpadbar         = 10;       /* vertical internal padding for statusbar */
static const char *fonts[]          = { "Hurmit Nerd Font:style=medium:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "Hurmit Nerd Font:style=medium:pixelsize=16";

// color theme, included from ~/.cache/themes/ in config.mk
#include "dwm-color.h"

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "sp-term", "-g", "25x10", NULL };
const char *spcmd2[] = {"st", "-n", "sp-pass", "-g", "90x25", NULL };
const char *spcmd3[] = {"mpv", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"sp-term",      spcmd1},
	{"sp-pass",      spcmd2},
	{"mpv",       spcmd3},
};


/* tagging: refer to https://github.com/bakkeby/patches/wiki/tagicons */
static const char *tags[NUMTAGS] = { NULL };  /* left for compatibility reasons, i.e. code that checks LENGTH(tags) */
static char *tagicons[][NUMTAGS] = {
	[IconsDefault]        = { "" },
    /* name                    term.       docs        note        globe       circle      circle      circle      message     music    */
	[IconsVacant]         = { "\uE795 ₁", "\uF899 ₂", "\uF89D ₃", "\uF0AC ₄", "\uF10C ₅", "\uF10C ₆", "\uF10C ₇", "\uF869 ₈", "\uF886 ₉" },
	[IconsOccupied]       = { "\uE795 ₁", "\uF899 ₂", "\uF89D ₃", "\uF0AC ₄", "\uF10C ₅", "\uF10C ₆", "\uF10C ₇", "\uF869 ₈", "\uF886 ₉" },
	[IconsSubscript]      = { "\uE795 ₁", "\uF899 ₂", "\uF89D ₃", "\uF0AC ₄", "\uF10C ₅", "\uF10C ₆", "\uF10C ₇", "\uF869 ₈", "\uF886 ₉" },
    [IconsNumbers]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
     * class          instance       title   tags mask   switchtotag iscentered isfloating  monitor */
    { "float",        NULL,          NULL,   0,          0,          1,         1,          -1 },
	{ "Zathura",      NULL,          NULL,   1 << 2,     0,          0,         0,          -1 },
	{ "qutebrowser",  NULL,          NULL,   1 << 3,     0,          0,         0,          -1 },
	{ "discord",      NULL,          NULL,   1 << 7,     0,          0,         0,          -1 },
	{ NULL,		      "sp-term",	 NULL,   SPTAG(0),   0,          1,         1,          -1 },
	{ NULL,		      "sp-pass",	 NULL,   SPTAG(1),   0,          1,         1,          -1 },
	{ NULL,		      "mpv",         NULL,   SPTAG(2),   0,          1,         1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	// symbol        arrange function        note/icon description
	{ "\uFC61",      tile },                 /* first entry is default */
	// { "<M>",        monocle },
	{ "\uF966",      spiral },               /* arrow rotate right */
	{ "\uF964",      dwindle },              /* arrow rotate left  */
	// { "H[]",      deck },
	{ "\uF9A9",      bstack },               /* tree blocks        */
	{ "\uF85B",      bstackhoriz },          /* horizontal lines   */
	// { "HHH",      grid },
	{ "\uF53A",      nrowgrid },             /* 3x3 grid           */
	// { "---",      horizgrid },
	// { ":::",      gaplessgrid },
	{ "\uFB1D",      centeredmaster },       /* arrows vert line   */
	// { ">M>",      centeredfloatingmaster },
	//{ "\uFA73",      NULL },  /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions MODIFIED FROM THE DEFAULT DWM BUILD
Mod + [1-9]                  Add tag number to currently focussed tags      view
Mod + Shift + [1-9]          Focus only the selected tag              toggleview
Mod + Ctrl  + [1-9]          Move current window to selected tag             tag
Mod + Ctrl  + Shift + [1-9]  Toggle empty tags                         toggletag
*/
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      toggleview,  {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,         {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      view,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,   {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Include commands for keybindings */
#include "commands.h"

/* Include special function key codes */
#include <X11/XF86keysym.h>

static Key keys[] = {
/* modifier                  key        function        argument           */
/* templates                                                               */
//{ MODKEY,                    XK_F1,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F2,      spawn,         SHCMD("<++>") },
//{ MODKEY,                    XK_F3,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F4,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F5,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F6,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F7,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F8,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F9,      spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F10,     spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F11,     spawn,         {.v = <++> } },
//{ MODKEY,                    XK_F12,     spawn,         {.v = <++> } },

//{ MODKEY,                    XK_grave,   spawn,         {.v = <++> } },
TAGKEYS(                     XK_1,                      0)
TAGKEYS(                     XK_2,                      1)
TAGKEYS(                     XK_3,                      2)
TAGKEYS(                     XK_4,                      3)
TAGKEYS(                     XK_5,                      4)
TAGKEYS(                     XK_6,                      5)
TAGKEYS(                     XK_7,                      6)
TAGKEYS(                     XK_8,                      7)
TAGKEYS(                     XK_9,                      8)
{ MODKEY,                    XK_0,            view,            {.ui = ~0 } },
{ MODKEY|ShiftMask,          XK_0,            tag,             {.ui = ~0 } },
{ MODKEY,                    XK_minus,        spawn,           {.v = 0 } },
{ MODKEY,                    XK_equal,        spawn,           {.v = 0 } },
{ MODKEY,                    XK_BackSpace,    spawn,           {.v = 0 } },

{ MODKEY,                    XK_Tab,          view,           {0} },
{ MODKEY,                    XK_q,            spawn,          {0} },
{ MODKEY|ShiftMask,          XK_q,            quit,           {0} },
{ MODKEY,                    XK_w,            spawn,          {.v = wikicmd} },
//{ MODKEY,                    XK_e,            spawn,          {.v = <++> } },
//{ MODKEY,                    XK_r,            setlayout,      {.v = &layouts[5]} },
{ MODKEY,                    XK_t,            setlayout,      {.v = &layouts[0]} },
{ MODKEY,                    XK_y,            togglescratch,  {.ui = 0 } },
{ MODKEY,                    XK_u,            togglescratch,  {.ui = 1 } },
{ MODKEY,                    XK_i,            incnmaster,     {.i = +1 } },
//{ MODKEY,                    XK_o,            spawn,          {.v = <++> } },
//{ MODKEY,                    XK_p,            spawn,          {.v = dmenucmd } },
//{ MODKEY,                    XK_bracketleft,  spawn,          SHCMD("<++>") },
//{ MODKEY,                    XK_bracketright, spawn,          SHCMD("<++>") },
//{ MODKEY,                    XK_backslash,    spawn,          SHCMD("<++>") },

{ MODKEY,                    XK_a,            cyclelayout,    {.i = +1 } },
//{ MODKEY|ShiftMask,          XK_a,            seticonset,     {.i = 0 } },
{ MODKEY,                    XK_s,            spawn,          {.v = browsercmd } },
{ MODKEY,                    XK_d,            incnmaster,     {.i = -1 } },
//{ MODKEY,                    XK_f,            setlayout,      {.v = &layouts[1]} },
//{ MODKEY,                    XK_g,            setlayout,      {.v = &layouts[2]} },
{ MODKEY,                    XK_h,            setmfact,       {.f = -0.05} },
{ MODKEY,                    XK_j,            focusstack,     {.i = +1 } },
{ MODKEY,                    XK_k,            focusstack,     {.i = -1 } },
{ MODKEY,                    XK_l,            setmfact,       {.f = +0.05} },
//{ MODKEY,                    XK_semicolon,    spawn,          {.v = <++> } },
//{ MODKEY,                    XK_apostrophe,   spawn,          {.v = <++> } },
{ MODKEY,                    XK_Return,       spawn,            {.v = termcmd } },
{ MODKEY|ShiftMask,          XK_Return,       spawn,          {.v = termcmd } },
{ MODKEY,                    XK_Return,       zoom,           {0} },

//{ MODKEY,                    XK_z,            spawn,          {.v = <++> } },
{ MODKEY,                    XK_x,            togglescratch,  {.ui = 2 } },
{ MODKEY,                    XK_c,            spawn,          {.v = calcmd} },
{ MODKEY|ShiftMask,          XK_c,            killclient,     {0} },
//{ MODKEY,                    XK_v,            spawn,          {.v = <++> } },
{ MODKEY,                    XK_b,            togglebar,      {0} },
//{ MODKEY|ShiftMask,          XK_b,            seticonset,     {.i = 1 } },
{ MODKEY,                    XK_n,            spawn,          {.v = diarycmd } },
//{ MODKEY,                    XK_m,            setlayout,      {.v = &layouts[6]} },
{ MODKEY,                    XK_comma,        focusmon,       {.i = -1 } },
{ MODKEY|ShiftMask,          XK_comma,        tagmon,         {.i = -1 } },
{ MODKEY,                    XK_period,       focusmon,       {.i = +1 } },
{ MODKEY|ShiftMask,          XK_period,       tagmon,         {.i = +1 } },

{ MODKEY,                    XK_space,        setlayout,      {0} },
{ MODKEY|ShiftMask,          XK_space,        togglefloating, {0} },

{ MODKEY|Mod4Mask,           XK_u,            incrgaps,       {.i = +1 } },
{ MODKEY|Mod4Mask|ShiftMask, XK_u,            incrgaps,       {.i = -1 } },
//{ MODKEY|Mod4Mask,           XK_i,            incrigaps,      {.i = +1 } },
//{ MODKEY|Mod4Mask|ShiftMask, XK_i,            incrigaps,      {.i = -1 } },
//{ MODKEY|Mod4Mask,           XK_o,            incrogaps,      {.i = +1 } },
//{ MODKEY|Mod4Mask|ShiftMask, XK_o,            incrogaps,      {.i = -1 } },
//{ MODKEY|Mod4Mask,           XK_6,            incrihgaps,     {.i = +1 } },
//{ MODKEY|Mod4Mask|ShiftMask, XK_6,            incrihgaps,     {.i = -1 } },
//{ MODKEY|Mod4Mask,           XK_7,            incrivgaps,     {.i = +1 } },
//{ MODKEY|Mod4Mask|ShiftMask, XK_7,            incrivgaps,     {.i = -1 } },
//{ MODKEY|Mod4Mask,           XK_8,            incrohgaps,     {.i = +1 } },
//{ MODKEY|Mod4Mask|ShiftMask, XK_8,            incrohgaps,     {.i = -1 } },
//{ MODKEY|Mod4Mask,           XK_9,            incrovgaps,     {.i = +1 } },
//{ MODKEY|Mod4Mask|ShiftMask, XK_9,            incrovgaps,     {.i = -1 } },
{ MODKEY|Mod4Mask,           XK_0,            togglegaps,     {0} },
{ MODKEY|Mod4Mask|ShiftMask, XK_0,            defaultgaps,    {0} },

{ 0,            XF86XK_AudioMute,             spawn,    {.v = togglemute } },
{ 0,            XF86XK_AudioLowerVolume,      spawn,    {.v = voldown } },
{ 0,            XF86XK_AudioRaiseVolume,      spawn,    {.v = volup } },
{ 0,            XF86XK_MonBrightnessUp,       spawn,    {.v = backlightup } },
{ 0,            XF86XK_MonBrightnessDown,     spawn,    {.v = backlightdown } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */

static Button buttons[] = {
/* click           event mask   button     function        argument */
{ ClkLtSymbol,     0,           Button1,   setlayout,      {0} },
{ ClkLtSymbol,     0,           Button3,   setlayout,      {.v = &layouts[2]} },
{ ClkWinTitle,     0,           Button2,   zoom,           {0} },
{ ClkStatusText,   0,           Button2,   spawn,          {.v = termcmd } },
{ ClkClientWin,    MODKEY,      Button1,   movemouse,      {0} },
{ ClkClientWin,    MODKEY,      Button2,   togglefloating, {0} },
{ ClkClientWin,    MODKEY,      Button3,   resizemouse,    {0} },
{ ClkTagBar,       0,           Button1,   view,           {0} },
{ ClkTagBar,       0,           Button3,   toggleview,     {0} },
{ ClkTagBar,       MODKEY,      Button1,   tag,            {0} },
{ ClkTagBar,       MODKEY,      Button3,   toggletag,      {0} },
{ ClkTagBar,       0,           Button4,   cycleiconset,   {.i = +1 } },
{ ClkTagBar,       0,           Button5,   cycleiconset,   {.i = -1 } },
};

