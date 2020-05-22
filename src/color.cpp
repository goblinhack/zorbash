//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <strings.h> // do not remove
#include <string.h> // do not remove
#include "my_main.h"
#include "my_gl.h"
#include "my_string.h"
#include <strings.h> // do not remove, strcasecmp

color COLOR_NONE;
color ALICE_BLUE;
color ALICEBLUE;
color ANTIQUEWHITE1;
color ANTIQUEWHITE2;
color ANTIQUEWHITE3;
color ANTIQUEWHITE4;
color ANTIQUE_WHITE;
color ANTIQUEWHITE;
color AQUAMARINE1;
color AQUAMARINE2;
color AQUAMARINE3;
color AQUAMARINE4;
color AQUAMARINE;
color AZURE1;
color AZURE2;
color AZURE3;
color AZURE4;
color AZURE;
color BEIGE;
color BISQUE1;
color BISQUE2;
color BISQUE3;
color BISQUE4;
color BISQUE;
color BLACK;
color BLANCHED_ALMOND;
color BLANCHEDALMOND;
color BLUE1;
color BLUE2;
color BLUE3;
color BLUE4;
color BLUE;
color BLUE_VIOLET;
color BLUEVIOLET;
color BROWN1;
color BROWN2;
color BROWN3;
color BROWN4;
color BROWN;
color BURLYWOOD1;
color BURLYWOOD2;
color BURLYWOOD3;
color BURLYWOOD4;
color BURLYWOOD;
color CADETBLUE1;
color CADETBLUE2;
color CADETBLUE3;
color CADETBLUE4;
color CADET_BLUE;
color CADETBLUE;
color CHARTREUSE1;
color CHARTREUSE2;
color CHARTREUSE3;
color CHARTREUSE4;
color CHARTREUSE;
color CHOCOLATE1;
color CHOCOLATE2;
color CHOCOLATE3;
color CHOCOLATE4;
color CHOCOLATE;
color CORAL1;
color CORAL2;
color CORAL3;
color CORAL4;
color CORAL;
color CORNFLOWER_BLUE;
color CORNFLOWERBLUE;
color CORNSILK1;
color CORNSILK2;
color CORNSILK3;
color CORNSILK4;
color CORNSILK;
color CYAN1;
color CYAN2;
color CYAN3;
color CYAN4;
color CYAN;
color DARK_BLUE;
color DARKBLUE;
color DARK_CYAN;
color DARKCYAN;
color DARKGOLDENROD1;
color DARKGOLDENROD2;
color DARKGOLDENROD3;
color DARKGOLDENROD4;
color DARK_GOLDENROD;
color DARKGOLDENROD;
color DARK_GRAY;
color DARKGRAY;
color DARK_GREEN;
color DARKGREEN;
color DARK_GREY;
color DARKGREY;
color DARK_KHAKI;
color DARKKHAKI;
color DARK_MAGENTA;
color DARKMAGENTA;
color DARKOLIVEGREEN1;
color DARKOLIVEGREEN2;
color DARKOLIVEGREEN3;
color DARKOLIVEGREEN4;
color DARK_OLIVE_GREEN;
color DARKOLIVEGREEN;
color DARKORANGE1;
color DARKORANGE2;
color DARKORANGE3;
color DARKORANGE4;
color DARK_ORANGE;
color DARKORANGE;
color DARKORCHID1;
color DARKORCHID2;
color DARKORCHID3;
color DARKORCHID4;
color DARK_ORCHID;
color DARKORCHID;
color DARK_RED;
color DARKRED;
color DARK_SALMON;
color DARKSALMON;
color DARKSEAGREEN1;
color DARKSEAGREEN2;
color DARKSEAGREEN3;
color DARKSEAGREEN4;
color DARK_SEA_GREEN;
color DARKSEAGREEN;
color DARK_SLATE_BLUE;
color DARKSLATEBLUE;
color VDARKSLATEBLUE;
color VVDARKSLATEBLUE;
color DARKSLATEGRAY1;
color DARKSLATEGRAY2;
color DARKSLATEGRAY3;
color DARKSLATEGRAY4;
color DARK_SLATE_GRAY;
color DARKSLATEGRAY;
color DARK_SLATE_GREY;
color DARKSLATEGREY;
color DARK_TURQUOISE;
color DARKTURQUOISE;
color DARK_VIOLET;
color DARKVIOLET;
color DEEPPINK1;
color DEEPPINK2;
color DEEPPINK3;
color DEEPPINK4;
color DEEP_PINK;
color DEEPPINK;
color DEEPSKYBLUE1;
color DEEPSKYBLUE2;
color DEEPSKYBLUE3;
color DEEPSKYBLUE4;
color DEEP_SKY_BLUE;
color DEEPSKYBLUE;
color DIM_GRAY;
color DIMGRAY;
color DIM_GREY;
color DIMGREY;
color DODGERBLUE1;
color DODGERBLUE2;
color DODGERBLUE3;
color DODGERBLUE4;
color DODGER_BLUE;
color DODGERBLUE;
color FIREBRICK1;
color FIREBRICK2;
color FIREBRICK3;
color FIREBRICK4;
color FIREBRICK;
color FLORAL_WHITE;
color FLORALWHITE;
color FOREST_GREEN;
color FORESTGREEN;
color GAINSBORO;
color GHOST_WHITE;
color GHOSTWHITE;
color GOLD1;
color GOLD2;
color GOLD3;
color GOLD4;
color GOLDENROD1;
color GOLDENROD2;
color GOLDENROD3;
color GOLDENROD4;
color GOLDENROD;
color GOLD;
color GRAY10;
color GRAY11;
color GRAY12;
color GRAY13;
color GRAY14;
color GRAY15;
color GRAY16;
color GRAY17;
color GRAY18;
color GRAY19;
color GRAY1;
color GRAY20;
color GRAY21;
color GRAY22;
color GRAY23;
color GRAY24;
color GRAY25;
color GRAY26;
color GRAY27;
color GRAY28;
color GRAY29;
color GRAY2;
color GRAY30;
color GRAY31;
color GRAY32;
color GRAY33;
color GRAY34;
color GRAY35;
color GRAY36;
color GRAY37;
color GRAY38;
color GRAY39;
color GRAY3;
color GRAY40;
color GRAY41;
color GRAY42;
color GRAY43;
color GRAY44;
color GRAY45;
color GRAY46;
color GRAY47;
color GRAY48;
color GRAY49;
color GRAY4;
color GRAY50;
color GRAY51;
color GRAY52;
color GRAY53;
color GRAY54;
color GRAY55;
color GRAY56;
color GRAY57;
color GRAY58;
color GRAY59;
color GRAY5;
color GRAY60;
color GRAY61;
color GRAY62;
color GRAY63;
color GRAY64;
color GRAY65;
color GRAY66;
color GRAY67;
color GRAY68;
color GRAY69;
color GRAY6;
color GRAY70;
color GRAY71;
color GRAY72;
color GRAY73;
color GRAY74;
color GRAY75;
color GRAY76;
color GRAY77;
color GRAY78;
color GRAY79;
color GRAY7;
color GRAY80;
color GRAY81;
color GRAY82;
color GRAY83;
color GRAY84;
color GRAY85;
color GRAY86;
color GRAY87;
color GRAY88;
color GRAY89;
color GRAY8;
color GRAY90;
color GRAY91;
color GRAY92;
color GRAY93;
color GRAY94;
color GRAY95;
color GRAY96;
color GRAY97;
color GRAY98;
color GRAY99;
color GRAY9;
color GRAY;
color GREEN1;
color GREEN2;
color GREEN3;
color GREEN4;
color GREEN;
color GREEN_YELLOW;
color GREENYELLOW;
color GREY10;
color GREY11;
color GREY12;
color GREY13;
color GREY14;
color GREY15;
color GREY16;
color GREY17;
color GREY18;
color GREY19;
color GREY1;
color GREY20;
color GREY21;
color GREY22;
color GREY23;
color GREY24;
color GREY25;
color GREY26;
color GREY27;
color GREY28;
color GREY29;
color GREY2;
color GREY30;
color GREY31;
color GREY32;
color GREY33;
color GREY34;
color GREY35;
color GREY36;
color GREY37;
color GREY38;
color GREY39;
color GREY3;
color GREY40;
color GREY41;
color GREY42;
color GREY43;
color GREY44;
color GREY45;
color GREY46;
color GREY47;
color GREY48;
color GREY49;
color GREY4;
color GREY50;
color GREY51;
color GREY52;
color GREY53;
color GREY54;
color GREY55;
color GREY56;
color GREY57;
color GREY58;
color GREY59;
color GREY5;
color GREY60;
color GREY61;
color GREY62;
color GREY63;
color GREY64;
color GREY65;
color GREY66;
color GREY67;
color GREY68;
color GREY69;
color GREY6;
color GREY70;
color GREY71;
color GREY72;
color GREY73;
color GREY74;
color GREY75;
color GREY76;
color GREY77;
color GREY78;
color GREY79;
color GREY7;
color GREY80;
color GREY81;
color GREY82;
color GREY83;
color GREY84;
color GREY85;
color GREY86;
color GREY87;
color GREY88;
color GREY89;
color GREY8;
color GREY90;
color GREY91;
color GREY92;
color GREY93;
color GREY94;
color GREY95;
color GREY96;
color GREY97;
color GREY98;
color GREY99;
color GREY9;
color GREY;
color HONEYDEW1;
color HONEYDEW2;
color HONEYDEW3;
color HONEYDEW4;
color HONEYDEW;
color HOTPINK1;
color HOTPINK2;
color HOTPINK3;
color HOTPINK4;
color HOT_PINK;
color HOTPINK;
color INDIANRED1;
color INDIANRED2;
color INDIANRED3;
color INDIANRED4;
color INDIAN_RED;
color INDIANRED;
color IVORY1;
color IVORY2;
color IVORY3;
color IVORY4;
color IVORY;
color KHAKI1;
color KHAKI2;
color KHAKI3;
color KHAKI4;
color KHAKI;
color LAVENDERBLUSH1;
color LAVENDERBLUSH2;
color LAVENDERBLUSH3;
color LAVENDERBLUSH4;
color LAVENDER_BLUSH;
color LAVENDERBLUSH;
color LAVENDER;
color LAWN_GREEN;
color LAWNGREEN;
color LEMONCHIFFON1;
color LEMONCHIFFON2;
color LEMONCHIFFON3;
color LEMONCHIFFON4;
color LEMON_CHIFFON;
color LEMONCHIFFON;
color LIGHTBLUE1;
color LIGHTBLUE2;
color LIGHTBLUE3;
color LIGHTBLUE4;
color LIGHT_BLUE;
color LIGHTBLUE;
color LIGHT_CORAL;
color LIGHTCORAL;
color LIGHTCYAN1;
color LIGHTCYAN2;
color LIGHTCYAN3;
color LIGHTCYAN4;
color LIGHT_CYAN;
color LIGHTCYAN;
color LIGHTGOLDENROD1;
color LIGHTGOLDENROD2;
color LIGHTGOLDENROD3;
color LIGHTGOLDENROD4;
color LIGHT_GOLDENROD;
color LIGHTGOLDENROD;
color LIGHT_GOLDENROD_YELLOW;
color LIGHTGOLDENRODYELLOW;
color LIGHT_GRAY;
color LIGHTGRAY;
color LIGHT_GREEN;
color LIGHTGREEN;
color LIGHT_GREY;
color LIGHTGREY;
color LIGHTPINK1;
color LIGHTPINK2;
color LIGHTPINK3;
color LIGHTPINK4;
color LIGHT_PINK;
color LIGHTPINK;
color LIGHTSALMON1;
color LIGHTSALMON2;
color LIGHTSALMON3;
color LIGHTSALMON4;
color LIGHT_SALMON;
color LIGHTSALMON;
color LIGHT_SEA_GREEN;
color LIGHTSEAGREEN;
color LIGHTSKYBLUE1;
color LIGHTSKYBLUE2;
color LIGHTSKYBLUE3;
color LIGHTSKYBLUE4;
color LIGHT_SKY_BLUE;
color LIGHTSKYBLUE;
color LIGHT_SLATE_BLUE;
color LIGHTSLATEBLUE;
color LIGHT_SLATE_GRAY;
color LIGHTSLATEGRAY;
color LIGHT_SLATE_GREY;
color LIGHTSLATEGREY;
color LIGHTSTEELBLUE1;
color LIGHTSTEELBLUE2;
color LIGHTSTEELBLUE3;
color LIGHTSTEELBLUE4;
color LIGHT_STEEL_BLUE;
color LIGHTSTEELBLUE;
color LIGHTYELLOW1;
color LIGHTYELLOW2;
color LIGHTYELLOW3;
color LIGHTYELLOW4;
color LIGHT_YELLOW;
color LIGHTYELLOW;
color LIME_GREEN;
color LIMEGREEN;
color LIME;
color LINEN;
color MAGENTA1;
color MAGENTA2;
color MAGENTA3;
color MAGENTA4;
color MAGENTA;
color MAROON1;
color MAROON2;
color MAROON3;
color MAROON4;
color MAROON;
color MEDIUM_AQUAMARINE;
color MEDIUMAQUAMARINE;
color MEDIUM_BLUE;
color MEDIUMBLUE;
color MEDIUMORCHID1;
color MEDIUMORCHID2;
color MEDIUMORCHID3;
color MEDIUMORCHID4;
color MEDIUM_ORCHID;
color MEDIUMORCHID;
color MEDIUMPURPLE1;
color MEDIUMPURPLE2;
color MEDIUMPURPLE3;
color MEDIUMPURPLE4;
color MEDIUM_PURPLE;
color MEDIUMPURPLE;
color MEDIUM_SEA_GREEN;
color MEDIUMSEAGREEN;
color MEDIUM_SLATE_BLUE;
color MEDIUMSLATEBLUE;
color MEDIUM_SPRING_GREEN;
color MEDIUMSPRINGGREEN;
color MEDIUM_TURQUOISE;
color MEDIUMTURQUOISE;
color MEDIUM_VIOLET_RED;
color MEDIUMVIOLETRED;
color MIDNIGHT_BLUE;
color MIDNIGHTBLUE;
color MINT_CREAM;
color MINTCREAM;
color MISTYROSE1;
color MISTYROSE2;
color MISTYROSE3;
color MISTYROSE4;
color MISTY_ROSE;
color MISTYROSE;
color MOCCASIN;
color NAVAJOWHITE1;
color NAVAJOWHITE2;
color NAVAJOWHITE3;
color NAVAJOWHITE4;
color NAVAJO_WHITE;
color NAVAJOWHITE;
color NAVY_BLUE;
color NAVYBLUE;
color NAVY;
color OLD_LACE;
color OLDLACE;
color OLIVEDRAB1;
color OLIVEDRAB2;
color OLIVEDRAB3;
color OLIVEDRAB4;
color OLIVE_DRAB;
color OLIVEDRAB;
color LIGHT_ORANGE;
color ORANGE1;
color ORANGE2;
color ORANGE3;
color ORANGE4;
color ORANGE;
color ORANGERED1;
color ORANGERED2;
color ORANGERED3;
color ORANGERED4;
color ORANGE_RED;
color ORANGERED;
color ORCHID1;
color ORCHID2;
color ORCHID3;
color ORCHID4;
color ORCHID;
color PALE_GOLDENROD;
color PALEGOLDENROD;
color PALEGREEN1;
color PALEGREEN2;
color PALEGREEN3;
color PALEGREEN4;
color PALE_GREEN;
color PALEGREEN;
color PALETURQUOISE1;
color PALETURQUOISE2;
color PALETURQUOISE3;
color PALETURQUOISE4;
color PALE_TURQUOISE;
color PALETURQUOISE;
color PALEVIOLETRED1;
color PALEVIOLETRED2;
color PALEVIOLETRED3;
color PALEVIOLETRED4;
color PALE_VIOLET_RED;
color PALEVIOLETRED;
color PAPAYA_WHIP;
color PAPAYAWHIP;
color PEACHPUFF1;
color PEACHPUFF2;
color PEACHPUFF3;
color PEACHPUFF4;
color PEACH_PUFF;
color PEACHPUFF;
color PERU;
color PINK1;
color PINK2;
color PINK3;
color PINK4;
color PINK;
color PLUM1;
color PLUM2;
color PLUM3;
color PLUM4;
color PLUM;
color POWDER_BLUE;
color POWDERBLUE;
color PURPLE1;
color PURPLE2;
color PURPLE3;
color PURPLE4;
color PURPLE;
color RED1;
color RED2;
color RED3;
color RED4;
color RED;
color ROSYBROWN1;
color ROSYBROWN2;
color ROSYBROWN3;
color ROSYBROWN4;
color ROSY_BROWN;
color ROSYBROWN;
color ROYALBLUE1;
color ROYALBLUE2;
color ROYALBLUE3;
color ROYALBLUE4;
color ROYAL_BLUE;
color ROYALBLUE;
color SADDLE_BROWN;
color SADDLEBROWN;
color SALMON1;
color SALMON2;
color SALMON3;
color SALMON4;
color SALMON;
color SANDY_BROWN;
color SANDYBROWN;
color SEAGREEN1;
color SEAGREEN2;
color SEAGREEN3;
color SEAGREEN4;
color SEA_GREEN;
color SEAGREEN;
color SEASHELL1;
color SEASHELL2;
color SEASHELL3;
color SEASHELL4;
color SEASHELL;
color SIENNA1;
color SIENNA2;
color SIENNA3;
color SIENNA4;
color SIENNA;
color SKYBLUE1;
color SKYBLUE2;
color SKYBLUE3;
color SKYBLUE4;
color SKY_BLUE;
color SKYBLUE;
color SLATEBLUE1;
color SLATEBLUE2;
color SLATEBLUE3;
color SLATEBLUE4;
color SLATE_BLUE;
color SLATEBLUE;
color SLATEGRAY1;
color SLATEGRAY2;
color SLATEGRAY3;
color SLATEGRAY4;
color SLATE_GRAY;
color SLATEGRAY;
color SLATE_GREY;
color SLATEGREY;
color SNOW1;
color SNOW2;
color SNOW3;
color SNOW4;
color SNOW;
color SPRINGGREEN1;
color SPRINGGREEN2;
color SPRINGGREEN3;
color SPRINGGREEN4;
color SPRING_GREEN;
color SPRINGGREEN;
color STEELBLUE1;
color STEELBLUE2;
color STEELBLUE3;
color STEELBLUE4;
color STEEL_BLUE;
color STEELBLUE;
color TAN1;
color TAN2;
color TAN3;
color TAN4;
color TAN;
color THISTLE1;
color THISTLE2;
color THISTLE3;
color THISTLE4;
color THISTLE;
color TOMATO1;
color TOMATO2;
color TOMATO3;
color TOMATO4;
color TOMATO;
color TURQUOISE1;
color TURQUOISE2;
color TURQUOISE3;
color TURQUOISE4;
color TURQUOISE;
color VIOLET;
color VIOLETRED1;
color VIOLETRED2;
color VIOLETRED3;
color VIOLETRED4;
color VIOLET_RED;
color VIOLETRED;
color WHEAT1;
color WHEAT2;
color WHEAT3;
color WHEAT4;
color WHEAT;
color WHITE;
color WHITE_SMOKE;
color WHITESMOKE;
color YELLOW1;
color YELLOW2;
color YELLOW3;
color YELLOW4;
color YELLOW_GREEN;
color YELLOWGREEN;
color YELLOW;
color INK;

colors color_map;

static void color_set (std::string name,
                       color *c,
                       uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{_
    c->r = r;
    c->g = g;
    c->b = b;
    c->a = a;

    auto result = color_map.insert(std::make_pair(name, *c));
    if (result.second == false) {
        ERR("color insert name [%s] failed", name.c_str());
    }
}

void color_init (void)
{_
    color_set("yellow1", &YELLOW1, 255, 255, 0, 255);
    color_set("yellow2", &YELLOW2, 238, 238, 0, 255);
    color_set("yellow3", &YELLOW3, 205, 205, 0, 255);
    color_set("yellow4", &YELLOW4, 139, 139, 0, 255);
    color_set("yellow_green", &YELLOW_GREEN, 154, 205, 50, 255);
    color_set("yellowgreen", &YELLOWGREEN, 154, 205, 50, 255);
    color_set("yellow", &YELLOW, 255, 255, 0, 255);
    color_set("ink", &INK, 54, 47, 47, 255);
}

void color_fini (void)
{_
    color_map.clear();
}

color gl_save_color(255, 255, 255, 255);
color gl_last_color(255, 255, 255, 255);

void glcolor_save (void)
{_
    gl_save_color = gl_last_color;
}

void glcolor_restore (void)
{_
    color s = gl_last_color = gl_save_color;

    glColor4ub(s.r, s.g, s.b, s.a);
}

color string2color (const char **s)
{_
    static char tmp[MAXSHORTSTR];
    static const char *eo_tmp = tmp + sizeof(tmp);
    const char *c = *s;
    char *t = tmp;

    while (t < eo_tmp) {
        if ((*c == '\0') || (*c == '$')) {
            break;
        }

        *t++ = *c++;
    }

    if (c == eo_tmp) {
        return (WHITE);
    }

    *t++ = '\0';
    *s += (t - tmp);

    if (!strcasecmp(tmp, "reset")) {
        return (RESET_TEXT_COLOR);
    }

    auto result = color_map.find(std::string(tmp));

    if (result == color_map.end()) {
        LOG("unknown color [%s]", tmp);
        return (WHITE);
    }

    return (result->second);
}

color string2color (const wchar_t **s)
{_
    static wchar_t tmp[MAXSHORTSTR];
    static const wchar_t *eo_tmp = tmp + MAXSHORTSTR - 1;
    const wchar_t *c = *s;
    wchar_t *t = tmp;

    while (t < eo_tmp) {
        if ((*c == '\0') || (*c == '$')) {
            break;
        }

        *t++ = *c++;
    }

    if (c == eo_tmp) {
        return (WHITE);
    }

    *t++ = '\0';
    *s += (t - tmp);

    if (!wcscmp(tmp, L"reset")) {
        return (RESET_TEXT_COLOR);
    }

    std::string f = wstring_to_string(std::wstring(tmp));
    auto result = color_map.find(f);

    if (result == color_map.end()) {
        LOG("unknown color [%s]", f.c_str());
        return (WHITE);
    }

    return (result->second);
}

color string2color (std::string &s, int *len)
{_
    auto iter = s.begin();
    std::string out;

    while (iter != s.end()) {
        auto c = *iter;

        if ((c == '\0') || (c == '$')) {
            break;
        }

        out += c;
        iter++;
    }

    if (len) {
        *len = iter - s.begin();
    }

    if (out == "reset") {
        return (RESET_TEXT_COLOR);
    }

    auto result = color_map.find(out);

    if (result == color_map.end()) {
        LOG("unknown color [%s]", out.c_str());
        return (WHITE);
    }

    return (result->second);
}

color string2color (std::string &s)
{
    auto iter = s.begin();
    std::string out;

    while (iter != s.end()) {
        auto c = *iter;

        if ((c == '\0') || (c == '$')) {
            break;
        }

        out += c;
        iter++;
    }

    if (out == "reset") {
        return (RESET_TEXT_COLOR);
    }

    auto result = color_map.find(out);

    if (result == color_map.end()) {
        LOG("unknown color [%s]", out.c_str());
        return (WHITE);
    }

    return (result->second);
}

color string2color (std::wstring &s, int *len)
{_
    auto v = wstring_to_string(s);
    return (string2color(v, len));
}

const char *string2colorname (const char **s)
{_
    static char tmp[MAXSHORTSTR];
    static const char *eo_tmp = tmp + MAXSHORTSTR - 1;
    const char *c = *s;
    char *t = tmp;

    while (t < eo_tmp) {
        if ((*c == '\0') || (*c == '$')) {
            break;
        }

        *t++ = *c++;
    }

    if (c == eo_tmp) {
        return (0);
    }

    *t++ = '\0';
    *s += (t - tmp);

    if (!strcasecmp(tmp, "reset")) {
        return (RESET_TEXT_COLOR_STR);
    }

    auto result = color_map.find(std::string(tmp));

    if (result == color_map.end()) {
        LOG("unknown color [%s]", tmp);
        return ("");
    }

    return (tmp);
}

std::string string2colorname (std::string &s)
{_
    auto iter = s.begin();
    std::string out;

    if (s == "") {
        return ("white");
    }

    while (iter != s.end()) {
        auto c = *iter;

        if ((c == '\0') || (c == '$')) {
            break;
        }

        out += c;
        iter++;
    }

    if (out == "reset") {
        return (RESET_TEXT_COLOR_STR);
    }

    auto result = color_map.find(out);

    if (result == color_map.end()) {
        LOG("unknown color [%s]", out.c_str());
        return ("");
    }

    return (out);
}

color color_find (const char *s)
{_
    if (!s) {
        return (WHITE);
    }

    if (!strcmp(s, "")) {
        return (WHITE);
    }

    auto result = color_map.find(std::string(s));

    if (result == color_map.end()) {
        LOG("unknown color [%s]", s);
        return (WHITE);
    }

    return (result->second);
}

color color_to_mono (color a)
{_
    float avg = (a.r + a.g + a.b) / 3.0;

    a.r = avg;
    a.g = avg;
    a.b = avg;

    return (a);
}
