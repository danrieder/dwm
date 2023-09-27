/* See LICENSE file for copyright and license details. */
/*
 * TODO: 
 *        patch in scratchpad?
 *        patch in xrdb?
 *        remove the quit function 
 */

/*
 *  Patches (in the order applied):
 *    vanitygaps  adds gaps, gap control, lots of layouts (I have not included all layouts)
 *    sticky      [Mod+s] toggles a window to persist as you move from tag to tag 
 *    swallow     swallow spawned window - ex: watch a video with mpv from the command line will replace window that called it
 *    fullscreen  [Mod+f] toggles a window fullscreen 
*/

/* Constants 
#define BROWSER "brave"
*/
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "monospace:size=12", "fontawesome:size=12" };
static const char *fonts[]          = { "JetBrainsMono Nerd Font:pixelsize=14:antialias=true:autohint=true", 
                                        "Font Awesome:size=14" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=14";
static const char col_gray1[]       = "#1a1b26";
static const char col_gray2[]       = "#1a1b26";
static const char col_gray3[]       = "#acb0d0";
static const char col_gray4[]       = "#a9b1d6";
static const char col_cyan[]        = "#444b6a";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },               /* Master left, slaves right */
	{ "TTT",      bstack },             /* Master on top, slaves below */ 

	{ "|M|",      centeredmaster },     /* Master center, slaves on the sides */
	{ ">M>",      centeredfloatingmaster }, /* Master floats */
	
	{ "[@]",      spiral },             /* Fibonacci */
	{ "[\\]",     dwindle },            /* Shrinking in size etc. */
  
	{ "H[]",      deck },               /* Master left, slaves in a pile on right */
  { "[M]",      monocle },            /* All windows in a pile */

	{ "><>",      NULL },               /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *web[]  = { "brave", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  /* Main Keys: st, demenu, browser, kill window, shutdown, */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = web } },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,		   spawn,		       {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY,			                  XK_BackSpace,	spawn,		   {.v = (const char*[]){ "sysact", NULL } } },
	{ MODKEY|ShiftMask,		          XK_BackSpace,	spawn,		   {.v = (const char*[]){ "sysact", NULL } } },
  /* stack layouts t,y,u,i, */
	{ MODKEY,			                  XK_t,		   setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,		          XK_t,		   setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			                  XK_y,		   setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,		          XK_y,		   setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			                  XK_u,		   setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,		          XK_u,		   setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			                  XK_i,		   setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		          XK_i,		   setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
  /* bar on and off */
  { MODKEY,                       XK_b,      togglebar,      {0} },
  /* move through the stack mod+j or mod+k */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  /* gap & window control / behavior */
	{ MODKEY,			                  XK_a,		   togglegaps,	   {0} },
	{ MODKEY|ShiftMask,		          XK_a,		   defaultgaps,	   {0} },
	{ MODKEY|Mod4Mask,              XK_z,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_x,      incrgaps,       {.i = -1 } },
	{ MODKEY,			                  XK_s,		   togglesticky,	 {0} }, 
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_f,      fullscreen,     {0} },
  /* tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  /* external progs and scripts */
	{ MODKEY,			XK_F4,		spawn,		SHCMD(TERMINAL " -e pulsemixer;") },
	{ MODKEY,			XK_F9,		spawn,		{.v = (const char*[]){ "mounter", NULL } } },
	{ MODKEY,			XK_F10,		spawn,		{.v = (const char*[]){ "unmounter", NULL } } },
//	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
//	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
//	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
//	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
//	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
//	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
//	{ MODKEY,                       XK_Tab,    view,           {0} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
//	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

