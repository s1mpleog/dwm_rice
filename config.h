/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const unsigned int gappih = 5;   /* horiz inner gap between windows */
static const unsigned int gappiv = 5;   /* vert inner gap between windows */
static const unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    5; /* vert outer gap between windows and screen edge */
static const int smartgaps =
    0; /* 1 means no outer gap when there is only one window */

static const int vertpad = 0; /* vertical padding of bar */
static const int sidepad = 0; /* horizontal padding of bar */

static const int user_bh =
    35; /* 2 is the default spacing around the bar's font */

static const unsigned int ulinepad =
    5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke =
    2; /* thickness / height of the underline */
static const unsigned int ulinevoffset =
    0; /* how far above the bottom of the bar the line should appear */
static const int ulineall =
    0; /* 1 to show underline on all tags, 0 for just the active ones */

// static const char *fonts[] = {
//     "Ubuntu Mono Nerd Font:size=11:style=Bold:antialias=true:autohint=true"};

static const char *fonts[] = {
    "CaskaydiaCove Nerd Font:size=11:style:Bold:antialias=true:autohint=true",
    "Font Awesome 6 Free:size=14:pixelsize=14"};
static const char dmenufont[] = "Ubuntu:size=10";

// static const char col_gray1[] =
//
//     "#282c34"; // Dark background, similar to Doom One
// static const char col_gray2[] = "#3c3836"; // Slightly lighter dark
// background static const char col_gray3[] =
//     "#bbc2cf"; // Muted gray for text/inactive elements
// static const char col_gray4[] =
//     "#ebdbb2"; // Light gray for selected/active text
// static const char col_cyan[] = "#46d9ff";
//
// static const char *colors[][3] = {
//     /*               fg         bg         border   */
//     [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
//     [SchemeSel] = {col_gray4, col_cyan, col_cyan},
// };
//
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#282828";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#51afef";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

#define FORCE_VSPLIT 1

/* tagging */
// static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8",
// "9"};

// static const char *tags[] = {
//     "󰙯 ", // Terminal
//     "󰨞 ", // Web browsing
//     "󰞇 ", // Coding/Development
//     "󰍛 ", // File Management
//     "󰕧 ", // Music/Video
// };

static const char *tags[] = {
    "󰊠 ", // System Maintenance (Emerge, Kernel Compilation)
    "󰍡 ", // Math/Study (YouTube, PDFs, Jupyter Notebook)
    "󰕄 ", // OpenGL/Game Dev (C++, OpenGL, SDL2)
    "󰓅 ", // Rust Projects (Cargo, Axum, WASM)
    "󰗚 ", // JavaScript Projects (Next.js, Node.js)
    "󰩎 ", // Networking (Wireshark, Curl, TShark)
};

static const char *tagsalt[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
static const int momentaryalttags =
    0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
    {"pavucontrol", NULL, NULL, 0, 1, -1},
    {"nwg-look", NULL, NULL, 0, 1, -1},
    {"Nwg-look", NULL, NULL, 0, 1, -1},
    {"mpv", NULL, NULL, 0, 1, -1},
    {"mpvk", NULL, NULL, 0, 1, -1},
    {"imv", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static int attachbelow =
    1; /* 1 means attach after the currently active window */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"

// static const Layout layouts[] = {
//     /* symbol     arrange function */
//     {"[]=", tile}, /* first entry is default */
//     {"[\\]=", gaplessgrid},
//     {"><>", NULL}, /* no layout function means floating behavior */
//     {"[M]", monocle},
// };

static const Layout layouts[] = {
    /* symbol     arrange function */
    {":::", tile}, // no comment
    {"[]=", gaplessgrid},
    {"[M]", monocle},
    {"|M|", centeredmaster},
    {"[@]", spiral}, /* first entry is default */
    {"[\\]", dwindle},
    {"H[]", deck},
    {"TTT", bstack},
    {"===", bstackhoriz},
    {"HHH", grid},
    {"###", nrowgrid},
    {"---", horizgrid},
    {">M>", centeredfloatingmaster},
    {"><>", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */

#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
// static const char *dmenucmd[] = {"dmenu_run", "-fn", dmenufont, "-nb",
//
//                                  col_gray1,   "-nf", col_gray3, "-sb",
//                                  col_cyan,    "-sf", col_gray4, NULL};

static const char *dmenucmd[] = {"dmenu_run",    "-fn", dmenufont,   "-nb",
                                 normbgcolor,    "-nf", normfgcolor, "-sb",
                                 selbordercolor, "-sf", selfgcolor,  NULL};
static const char *termcmd[] = {"alacritty", NULL};

#include "movestack.c"

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, SHCMD("~/.zen/zen/zen-bin")},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},

    {MODKEY, XK_n, togglealttag, {0}},

    {MODKEY, XK_Tab, toggleAttachBelow, {0}},

    {MODKEY, XK_d, spawn,
     SHCMD("rofi -show drun -theme ~/.config/rofi/config.rasi")},

    {MODKEY, XK_w, spawn, SHCMD("firefox")},

    {MODKEY | ShiftMask, XK_s, spawn, SHCMD("spotify")},

    {MODKEY | ShiftMask, XK_o, spawn, SHCMD("obsidian")},

    {MODKEY, XK_c, spawn, SHCMD("zedit")},

    {MODKEY, XK_t, spawn, SHCMD("thunar")},

    {MODKEY, XK_f, fullscreen, {0}},

    {MODKEY | ShiftMask, XK_j, movestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_k, movestack, {.i = -1}},

    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_h, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_l, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},

    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {MODKEY | ControlMask, XK_period, cyclelayout, {.i = +1}},

    {MODKEY | ShiftMask, XK_r, xrdb, {.v = NULL}},

    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    //{MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    //{MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    //{MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    // {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    // {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    // {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    // {ClkTagBar, 0, Button1, view, {0}},
    // {ClkTagBar, 0, Button3, toggleview, {0}},
    // {ClkTagBar, MODKEY, Button1, tag, {0}},
    // {ClkTagBar, MODKEY, Button3, toggletag, {0}},

    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},

    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    //{ClkClientWin, ControlMask, Button1, dragmfact, {0}},
    //{ClkClientWin, ControlMask, Button3, dragcfact, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    //{ClkTabBar, 0, Button1, focuswin, {0}},
    //  {ClkTabBar, 0, Button1, focuswin, {0}},
    {ClkTabPrev, 0, Button1, movestack, {.i = -1}},
    {ClkTabNext, 0, Button1, movestack, {.i = +1}},
    //  {ClkTabClose, 0, Button1, killclient, {0}},
};
