/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 0, .realgap = 0, .gappx = 4};

static const unsigned int snap      = 32;       /* snap pixel */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
 static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "JetBrains Mono:size=12" }; 
/* static const char *fonts[]          = { "Switzer:size=12" }; */ 
static const char dmenufont[]       = "JetBrains Mono:size=12";

static const char col_bgnorm[]       = "#1d2021";
static const char col_bgsel[]        = "#d79921";

static const char col_bordnorm[]       = "#504945";
static const char col_bordsel[]        = "#d79921";

static const char col_fg[]       = "#ebdbb2";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg, col_bgnorm, col_bordnorm },
	[SchemeSel]  = { col_bgnorm, col_bgsel,  col_bordsel  },
  [SchemeTitle] = {col_bgsel, col_bgnorm, col_bgnorm},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Alacritty",NULL,       NULL,       1 << 0,            0,          -1 },
	{ NULL,   "brave-browser",NULL,       1 << 2,            0,           -1 },
	{ NULL,       NULL,   "YouTube Music",1 << 1,            0,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 3,            0,          -1 },
	{ "obs",      NULL,       NULL,       1 << 4,            0,          -1 },
	{ "discord",  NULL,       NULL,       1 << 0,            0,           1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-p", "search ", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bgnorm, "-nf", col_fg, "-sb", col_bgsel, "-sf", col_bgnorm, NULL };
static const char *termcmd[]  = { "alacritty"};
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          SHCMD("discord --enable-gpu-rasterization") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD("pcmanfm") },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("caprine") },
	{ MODKEY,                       XK_a,      spawn,          SHCMD("gtk-launch ytm.desktop") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("brave") },
	{ MODKEY,                       XK_g,      spawn,          SHCMD("gimp") },
	{ MODKEY,                       XK_m,      spawn,          SHCMD("pavucontrol") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("sh /home/piotr/.config/dmenu/scripts/powermenu.sh") },
	{ MODKEY|ControlMask,           XK_Delete, spawn,          SHCMD("alacritty -e htop") },
	{0,                             XK_Print,  spawn,          SHCMD("flameshot gui") },

	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.025} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.025} },

	{ MODKEY,                       XK_Tab,    view,           {0} },

	{ MODKEY,                       XK_q,      killclient,     {0} },

	{ MODKEY,                       XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -4 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +4 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	/* TAGKEYS(                        XK_6,                      5) */
	/* TAGKEYS(                        XK_7,                      6) */
	/* TAGKEYS(                        XK_8,                      7) */
	/* TAGKEYS(                        XK_9,                      8) */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

	{ ClkTagBar,            0,              Button4,        viewprev,       {0} },
	{ ClkTagBar,            0,              Button5,        viewnext,       {0} },
};
