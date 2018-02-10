/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Inconsolata:size=12" };
static const char dmenufont[]       = "Inconsolata:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask     isfloating   monitor */
	{ "mpv",         NULL,       NULL,       0,            1,           -1 },
	{ "ffplay",      NULL,       NULL,       0,            1,           -1 },
	{ "VISUAL",      NULL,       NULL,       0,            1,           -1 },
	{ NULL,          NULL,       "QEMU",     0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { "termcmd", NULL};
static const char *permcmd[]    = { "termcmd", "perm", NULL };

/* apps */
static const char *emacscmd[]   = { "emacscmd", NULL };
static const char *temacscmd[]  = { "emacscmd", "tabbed", NULL };
static const char *htopcmd[]    = { "htopcmd", NULL };
static const char *logcmd[]     = { "logcmd", NULL };
static const char *muttcmd[]    = { "muttcmd", NULL };
static const char *nyxcmd[]     = { "nyxcmd", NULL };
static const char *torrentcmd[] = { "torrentcmd", NULL };
static const char *viscmd[]     = { "viscmd", NULL };
static const char *tviscmd[]    = { "viscmd", "tabbed", NULL };
static const char *ytcmd[]      = { "ytcmd", NULL };
static const char *tytcmd[]     = { "ytcmd", "tabbed", NULL };
static const char *webcmd[]     = { "firefox", NULL };

/* volume */
static const char *voldowncmd[] = { "voldown", NULL };
static const char *volupcmd[]   = { "volup", NULL };
static const char *mutecmd[]    = { "volmute", NULL };

/* backlight */
static const char *blupcmd[]    = { "blup", NULL };
static const char *bldowncmd[]  = { "bldown", NULL };

/* misc. */
static const char *shutdowncmd[]= { "shutdown", NULL };

#include <X11/XF86keysym.h> /* volume keys, etc. */
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_Return, spawn,          {.v = permcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_e,      spawn,          {.v = emacscmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = temacscmd } },
	{ MODKEY|ShiftMask,             XK_h,      spawn,          {.v = htopcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = logcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = muttcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = nyxcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = torrentcmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = viscmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = tviscmd } },
	{ MODKEY,                       XK_f,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_y,      spawn,          {.v = ytcmd } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = tytcmd } },

	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = voldowncmd } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volupcmd } },

	{ 0,              XF86XK_MonBrightnessUp,  spawn,          {.v = blupcmd } },
	{ 0,              XF86XK_MonBrightnessDown,spawn,          {.v = bldowncmd } },
	{ 0,              XF86XK_AudioMute,        spawn,          {.v = mutecmd } },

	{ MODKEY,                       XK_F4,     spawn,          {.v = shutdowncmd } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)

	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
};

