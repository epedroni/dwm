/* See LICENSE file for copyright and license details. */

/* XF86 keys */
#define VOLDOWN	0x1008FF11   /* Volume control down        */
#define VOLMUTE	0x1008FF12   /* Mute sound from the system */
#define VOLUP	0x1008FF13   /* Volume control up          */
#define BLUP	0x1008FF02   /* Monitor brightness up	   */
#define BLDOWN	0x1008FF03   /* Monitor brightness down    */
#define SEARCH  0x1008FF1D

/* appearance */
static const char font[]            = "DVIcons:size=8";

#define NUMCOLORS 5                      // need at least 3
static const char colors[NUMCOLORS][ColLast][8] = {
   // border   foreground  background
   { "#3b3b3b", "#404040", "#111111" },  // 0 = normal
   { "#689dff", "#386dff", "#111111" },  // 1 = selected
   { "#ffffff", "#ffca38", "#111111" },  // 2 = urgent/warning
   { "#ffffff", "#ff3838", "#111111" },  // 3 = error
   { "#ffffff", "#999999", "#111111" },  // 4 = statusbar
};
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = False;    /* False means bottom bar */
static const Bool showtitle         = False;    /* True means titles are shown on bar */

/*   Display modes of the tab bar: never shown, always shown, shown only in  */
/*   monocle mode in presence of several windows.                            */
/*   A mode can be disabled by moving it after the showtab_nmodes end marker */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab            = showtab_auto; /* Default tab bar show mode  */
static const Bool toptab            = True;         /* False means bottom tab bar */

/* Productivity lock timeout in seconds - when the productivity lock is enabled, it is */
/* impossible to change view and toggle tags for the duration of the timeout */
static const long ptimeout = 1800;

/* tags                        web       chat      work      office    media     win7      gp        gp        gp    */
static const char *tags[] = { "\uE372", "\uE21B", "\uE3A9", "\uE0F2", "\uE140", "\uE343", "\uE027", "\uE027", "\uE027" };
/*
web: E372
media: E140
office: E0F2
file manager: E235
chat: E21B
work: E3A9
win7: E343
gp: E027
*/

/* default layout per tags */
/* The first element is for all-tag view, following i-th element corresponds to */
/* tags[i]. Layout is referred using the layouts array index.*/
/* tags                                      all    web    chat   work   office media  win7   gp     gp     gp */
static int def_layouts[1 + LENGTH(tags)] = { 0,     0,     0,     0,     2,     0,     2,     0,     0,     0 };

/* rules */
static const Rule rules[] = {
    /* class        instance      title            tags mask     isfloating   monitor */
    /* WM_CLASS     WM_CLASS      WM_NAME                                             */
  //{  NULL,        NULL,         NULL,            0,            False,        -1 },
    {  "Surf",      "surf",       NULL,            1 << 0,       False,        -1 },
    {  "Chromium",  "chromium",   NULL,            1 << 0,       False,        -1 },
    {  "Firefox",   "Navigator",  NULL,            1 << 0,       False,        -1 },
    
    {  "Thunderbird", "Mail",     NULL,            1 << 1,       False,        -1 },
    {  "Chromium",  "crx_knipolnnllmklapflnccelgolnpehhpl", NULL, 1 << 1, False, -1},
    {  "Slack",  "slack", NULL, 1 << 1, False, -1},

    {  "Eclipse",   "Eclipse",    NULL,            1 << 2,       False,        -1 },
    {  "jetbrains-idea", "sun-awt-X11-XFramePeer", NULL, 1 << 2, False,        -1 },
    
    {  "TeXstudio", "texstudio",  NULL,            1 << 3,       False,        -1 },
    {  "Abiword",   "abiword",    NULL,            1 << 3,       False,        -1 },
    {  "Gnumeric",  "gnumeric",   NULL,            1 << 3,       False,        -1 },
    
    {  "Deadbeef",  "deadbeef",   NULL,            1 << 4,       False,        -1 },
    {  "Vlc",       "vlc",        NULL,            1 << 4,       False,        -1 },
};

/* layout(s) */
static const float mfact      = 0.55;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;     /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
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
static const char *dmenucmd[]     = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG],"-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]      = { "xterm", NULL };
static const char *browsercmd[]   = { "chromium", NULL };
static const char *emailcmd[]     = { "thunderbird", NULL };
static const char *playercmd[]    = { "deadbeef", NULL };
static const char *editorcmd[]    = { "gedit", NULL };
static const char *scrotcmd[]     = { "scrot", "/home/eddy/screenshots/%Y-%m-%d-%H:%M:%S.png", NULL };
static const char *lockcmd[]      = { "i3lock", "-c", "000000", NULL };

static const char *lowervolumecmd[]  = { "amixer", "-q", "set", "Master", "2dB-", NULL };
static const char *raisevolumecmd[]  = { "amixer", "-q", "set", "Master", "2dB+", NULL };
static const char *mutevolumecmd[]   = { "amixer", "-q", "set", "Master", "toggle", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_t,      spawn,          {.v = browsercmd } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = playercmd } },
    { MODKEY|ShiftMask,             XK_o,      spawn,          {.v = emailcmd } },
    { MODKEY|ShiftMask,             XK_i,      spawn,          {.v = editorcmd } },
    { MODKEY,                       XK_p,      spawn,          {.v = lockcmd } },
    { 0,		                    XK_Print,  spawn,	       {.v = scrotcmd } },
    
    { 0,                            SEARCH,    prodlock,	   {0} },
    
    { MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_j,      incnmaster,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY|ShiftMask,             XK_l    ,  setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    
    { MODKEY,                       XK_e,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_w,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    
    TAGKEYS(                        XK_n,                      0) // web
    TAGKEYS(                        XK_b,                      1) // chat
    TAGKEYS(                        XK_a,                      2) // work
    TAGKEYS(                        XK_s,                      3) // office
    TAGKEYS(                        XK_m,                      4) // media
    TAGKEYS(                        XK_v,                      5) // win7
    TAGKEYS(                        XK_1,                      6) // gp
    TAGKEYS(                        XK_2,                      7) // gp
    TAGKEYS(                        XK_3,                      8) // gp
    
    { 0,                            VOLUP,     spawn,          {.v = raisevolumecmd } },
    { 0,                            VOLDOWN,   spawn,          {.v = lowervolumecmd } },
    { 0,                            VOLMUTE,   spawn,          {.v = mutevolumecmd } },
    
    { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
    { MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    /*{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },*/
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    //{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    /*{ ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },*/
};

