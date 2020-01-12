//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_MY_COLOR_H_
#define _MY_MY_COLOR_H_

#include <map>
#include "c_plus_plus_serializer.h"

template<class T> class my_acolor
{
public:

    T r {};
    T g {};
    T b {};
    T a {};

    my_acolor (void) : r(0), g(0), b(0), a(0) { }

    my_acolor (T r, T g, unsigned char b) : r(r), g(g), b(b), a(255) { }

    my_acolor (T r, T g, double b) : r(r), g(g), b(b), a(1.0) { }

    my_acolor (T r, T g, T b, T a) : r(r), g(g), b(b), a(a) { }

    my_acolor (const my_acolor &c) : r(c.r), g(c.g), b(c.b), a(c.a) { }

    friend std::ostream& operator<<(std::ostream &out,
                                    Bits<const my_acolor & > const my)
    {
        out << bits(my.t.r) << bits(my.t.g) << bits(my.t.b) << bits(my.t.a);
        return (out);
    }

    friend std::istream& operator>>(std::istream &in, Bits<my_acolor &> my)
    {
        in >> bits(my.t.r) >> bits(my.t.g) >> bits(my.t.b) >> bits(my.t.a);
        return (in);
    }

    friend std::ostream& operator << (std::ostream &out, const my_acolor &my)
    {
        out << "(" << my.r << ", " << my.g << ", " << my.b << ", " << my.a << ")";
        return (out);
    }

    void operator+= (my_acolor c)
    {
        r += c.r; g += c.g; b += c.b; a += c.a;
    }

    void operator-= (my_acolor c)
    {
        c -= c.r; c -= c.g; c -= c.b; a -= c.a;
    }

    friend my_acolor operator+ (my_acolor c, my_acolor b)
    {
        return (my_acolor(c.r + b.r, c.g + b.g, c.b + b.b, c.a + b.a));
    }

    friend my_acolor operator- (my_acolor c, my_acolor b)
    {
        return (my_acolor(c.r - b.r, c.g - b.g, c.b - b.b, c.a - b.a));
    }

    friend my_acolor operator/ (my_acolor c, my_acolor b)
    {
        return (my_acolor(c.r / b.r, c.g / b.g, c.b / b.b, c.a / b.a));
    }

    friend my_acolor operator* (my_acolor c, my_acolor b)
    {
        return (my_acolor(c.r * b.r, c.g * b.g, c.b * b.b, c.a * b.a));
    }

    friend my_acolor operator/ (my_acolor c, T b)
    {
        return (my_acolor(c.r / b, c.g / b, c.b / b, c.a / b));
    }

    void operator*= (T c)
    {
        r *= c; g *= c; b *= c; a *= c;
    }

    void operator/= (T c)
    {
        r /= c; g /= c; b /= c; a /= c;
    }

    friend bool operator== (my_acolor c, my_acolor b)
    {
        return (c.r == b.r) && (c.g == b.g) && (c.b == b.b) && (c.a == b.a);
    }

    friend bool operator!= (my_acolor c, my_acolor b)
    {
        return (!(c==b));
    }
};

typedef my_acolor<unsigned char> color;
typedef my_acolor<double> colorf;

typedef std::map< std::string, color > colors;
extern colors color_map;

void color_init(void);
void color_fini(void);
void glcolor_save(void);
void glcolor_restore(void);
color string2color(const char **s);
color string2color(const wchar_t **s);
color string2color(std::string &s, int *len);
color string2color(std::string &s);
color string2color(std::wstring &s, int *len);
const char *string2colorname(const char **s);
std::string string2colorname(std::string &s);
color color_find(const char *s);
color color_to_mono(color a);

extern color ALICE_BLUE;
extern color ALICEBLUE;
extern color ANTIQUEWHITE1;
extern color ANTIQUEWHITE2;
extern color ANTIQUEWHITE3;
extern color ANTIQUEWHITE4;
extern color ANTIQUE_WHITE;
extern color ANTIQUEWHITE;
extern color AQUAMARINE1;
extern color AQUAMARINE2;
extern color AQUAMARINE3;
extern color AQUAMARINE4;
extern color AQUAMARINE;
extern color AZURE1;
extern color AZURE2;
extern color AZURE3;
extern color AZURE4;
extern color AZURE;
extern color BEIGE;
extern color BISQUE1;
extern color BISQUE2;
extern color BISQUE3;
extern color BISQUE4;
extern color BISQUE;
extern color BLACK;
extern color COLOR_NONE;
extern color BLANCHED_ALMOND;
extern color BLANCHEDALMOND;
extern color BLUE1;
extern color BLUE2;
extern color BLUE3;
extern color BLUE4;
extern color BLUE;
extern color BLUE_VIOLET;
extern color BLUEVIOLET;
extern color BROWN1;
extern color BROWN2;
extern color BROWN3;
extern color BROWN4;
extern color BROWN;
extern color BURLYWOOD1;
extern color BURLYWOOD2;
extern color BURLYWOOD3;
extern color BURLYWOOD4;
extern color BURLYWOOD;
extern color CADETBLUE1;
extern color CADETBLUE2;
extern color CADETBLUE3;
extern color CADETBLUE4;
extern color CADET_BLUE;
extern color CADETBLUE;
extern color CHARTREUSE1;
extern color CHARTREUSE2;
extern color CHARTREUSE3;
extern color CHARTREUSE4;
extern color CHARTREUSE;
extern color CHOCOLATE1;
extern color CHOCOLATE2;
extern color CHOCOLATE3;
extern color CHOCOLATE4;
extern color CHOCOLATE;
extern color CORAL1;
extern color CORAL2;
extern color CORAL3;
extern color CORAL4;
extern color CORAL;
extern color CORNFLOWER_BLUE;
extern color CORNFLOWERBLUE;
extern color CORNSILK1;
extern color CORNSILK2;
extern color CORNSILK3;
extern color CORNSILK4;
extern color CORNSILK;
extern color CYAN1;
extern color CYAN2;
extern color CYAN3;
extern color CYAN4;
extern color CYAN;
extern color DARK_BLUE;
extern color DARKBLUE;
extern color DARK_CYAN;
extern color DARKCYAN;
extern color DARKGOLDENROD1;
extern color DARKGOLDENROD2;
extern color DARKGOLDENROD3;
extern color DARKGOLDENROD4;
extern color DARK_GOLDENROD;
extern color DARKGOLDENROD;
extern color DARK_GRAY;
extern color DARKGRAY;
extern color DARK_GREEN;
extern color DARKGREEN;
extern color DARK_GREY;
extern color DARKGREY;
extern color DARK_KHAKI;
extern color DARKKHAKI;
extern color DARK_MAGENTA;
extern color DARKMAGENTA;
extern color DARKOLIVEGREEN1;
extern color DARKOLIVEGREEN2;
extern color DARKOLIVEGREEN3;
extern color DARKOLIVEGREEN4;
extern color DARK_OLIVE_GREEN;
extern color DARKOLIVEGREEN;
extern color DARKORANGE1;
extern color DARKORANGE2;
extern color DARKORANGE3;
extern color DARKORANGE4;
extern color DARK_ORANGE;
extern color DARKORANGE;
extern color DARKORCHID1;
extern color DARKORCHID2;
extern color DARKORCHID3;
extern color DARKORCHID4;
extern color DARK_ORCHID;
extern color DARKORCHID;
extern color DARK_RED;
extern color DARKRED;
extern color DARK_SALMON;
extern color DARKSALMON;
extern color DARKSEAGREEN1;
extern color DARKSEAGREEN2;
extern color DARKSEAGREEN3;
extern color DARKSEAGREEN4;
extern color DARK_SEA_GREEN;
extern color DARKSEAGREEN;
extern color DARK_SLATE_BLUE;
extern color DARKSLATEBLUE;
extern color DARKSLATEBLUE;
extern color VDARKSLATEBLUE;
extern color VVDARKSLATEBLUE;
extern color DARKSLATEGRAY1;
extern color DARKSLATEGRAY2;
extern color DARKSLATEGRAY3;
extern color DARKSLATEGRAY4;
extern color DARK_SLATE_GRAY;
extern color DARKSLATEGRAY;
extern color DARK_SLATE_GREY;
extern color DARKSLATEGREY;
extern color DARK_TURQUOISE;
extern color DARKTURQUOISE;
extern color DARK_VIOLET;
extern color DARKVIOLET;
extern color DEEPPINK1;
extern color DEEPPINK2;
extern color DEEPPINK3;
extern color DEEPPINK4;
extern color DEEP_PINK;
extern color DEEPPINK;
extern color DEEPSKYBLUE1;
extern color DEEPSKYBLUE2;
extern color DEEPSKYBLUE3;
extern color DEEPSKYBLUE4;
extern color DEEP_SKY_BLUE;
extern color DEEPSKYBLUE;
extern color DIM_GRAY;
extern color DIMGRAY;
extern color DIM_GREY;
extern color DIMGREY;
extern color DODGERBLUE1;
extern color DODGERBLUE2;
extern color DODGERBLUE3;
extern color DODGERBLUE4;
extern color DODGER_BLUE;
extern color DODGERBLUE;
extern color FIREBRICK1;
extern color FIREBRICK2;
extern color FIREBRICK3;
extern color FIREBRICK4;
extern color FIREBRICK;
extern color FLORAL_WHITE;
extern color FLORALWHITE;
extern color FOREST_GREEN;
extern color FORESTGREEN;
extern color GAINSBORO;
extern color GHOST_WHITE;
extern color GHOSTWHITE;
extern color GOLD1;
extern color GOLD2;
extern color GOLD3;
extern color GOLD4;
extern color GOLDENROD1;
extern color GOLDENROD2;
extern color GOLDENROD3;
extern color GOLDENROD4;
extern color GOLDENROD;
extern color GOLD;
extern color GRAY10;
extern color GRAY11;
extern color GRAY12;
extern color GRAY13;
extern color GRAY14;
extern color GRAY15;
extern color GRAY16;
extern color GRAY17;
extern color GRAY18;
extern color GRAY19;
extern color GRAY1;
extern color GRAY20;
extern color GRAY21;
extern color GRAY22;
extern color GRAY23;
extern color GRAY24;
extern color GRAY25;
extern color GRAY26;
extern color GRAY27;
extern color GRAY28;
extern color GRAY29;
extern color GRAY2;
extern color GRAY30;
extern color GRAY31;
extern color GRAY32;
extern color GRAY33;
extern color GRAY34;
extern color GRAY35;
extern color GRAY36;
extern color GRAY37;
extern color GRAY38;
extern color GRAY39;
extern color GRAY3;
extern color GRAY40;
extern color GRAY41;
extern color GRAY42;
extern color GRAY43;
extern color GRAY44;
extern color GRAY45;
extern color GRAY46;
extern color GRAY47;
extern color GRAY48;
extern color GRAY49;
extern color GRAY4;
extern color GRAY50;
extern color GRAY51;
extern color GRAY52;
extern color GRAY53;
extern color GRAY54;
extern color GRAY55;
extern color GRAY56;
extern color GRAY57;
extern color GRAY58;
extern color GRAY59;
extern color GRAY5;
extern color GRAY60;
extern color GRAY61;
extern color GRAY62;
extern color GRAY63;
extern color GRAY64;
extern color GRAY65;
extern color GRAY66;
extern color GRAY67;
extern color GRAY68;
extern color GRAY69;
extern color GRAY6;
extern color GRAY70;
extern color GRAY71;
extern color GRAY72;
extern color GRAY73;
extern color GRAY74;
extern color GRAY75;
extern color GRAY76;
extern color GRAY77;
extern color GRAY78;
extern color GRAY79;
extern color GRAY7;
extern color GRAY80;
extern color GRAY81;
extern color GRAY82;
extern color GRAY83;
extern color GRAY84;
extern color GRAY85;
extern color GRAY86;
extern color GRAY87;
extern color GRAY88;
extern color GRAY89;
extern color GRAY8;
extern color GRAY90;
extern color GRAY91;
extern color GRAY92;
extern color GRAY93;
extern color GRAY94;
extern color GRAY95;
extern color GRAY96;
extern color GRAY97;
extern color GRAY98;
extern color GRAY99;
extern color GRAY9;
extern color GRAY;
extern color GREEN1;
extern color GREEN2;
extern color GREEN3;
extern color GREEN4;
extern color GREEN;
extern color GREEN_YELLOW;
extern color GREENYELLOW;
extern color GREY10;
extern color GREY11;
extern color GREY12;
extern color GREY13;
extern color GREY14;
extern color GREY15;
extern color GREY16;
extern color GREY17;
extern color GREY18;
extern color GREY19;
extern color GREY1;
extern color GREY20;
extern color GREY21;
extern color GREY22;
extern color GREY23;
extern color GREY24;
extern color GREY25;
extern color GREY26;
extern color GREY27;
extern color GREY28;
extern color GREY29;
extern color GREY2;
extern color GREY30;
extern color GREY31;
extern color GREY32;
extern color GREY33;
extern color GREY34;
extern color GREY35;
extern color GREY36;
extern color GREY37;
extern color GREY38;
extern color GREY39;
extern color GREY3;
extern color GREY40;
extern color GREY41;
extern color GREY42;
extern color GREY43;
extern color GREY44;
extern color GREY45;
extern color GREY46;
extern color GREY47;
extern color GREY48;
extern color GREY49;
extern color GREY4;
extern color GREY50;
extern color GREY51;
extern color GREY52;
extern color GREY53;
extern color GREY54;
extern color GREY55;
extern color GREY56;
extern color GREY57;
extern color GREY58;
extern color GREY59;
extern color GREY5;
extern color GREY60;
extern color GREY61;
extern color GREY62;
extern color GREY63;
extern color GREY64;
extern color GREY65;
extern color GREY66;
extern color GREY67;
extern color GREY68;
extern color GREY69;
extern color GREY6;
extern color GREY70;
extern color GREY71;
extern color GREY72;
extern color GREY73;
extern color GREY74;
extern color GREY75;
extern color GREY76;
extern color GREY77;
extern color GREY78;
extern color GREY79;
extern color GREY7;
extern color GREY80;
extern color GREY81;
extern color GREY82;
extern color GREY83;
extern color GREY84;
extern color GREY85;
extern color GREY86;
extern color GREY87;
extern color GREY88;
extern color GREY89;
extern color GREY8;
extern color GREY90;
extern color GREY91;
extern color GREY92;
extern color GREY93;
extern color GREY94;
extern color GREY95;
extern color GREY96;
extern color GREY97;
extern color GREY98;
extern color GREY99;
extern color GREY9;
extern color GREY;
extern color HONEYDEW1;
extern color HONEYDEW2;
extern color HONEYDEW3;
extern color HONEYDEW4;
extern color HONEYDEW;
extern color HOTPINK1;
extern color HOTPINK2;
extern color HOTPINK3;
extern color HOTPINK4;
extern color HOT_PINK;
extern color HOTPINK;
extern color INDIANRED1;
extern color INDIANRED2;
extern color INDIANRED3;
extern color INDIANRED4;
extern color INDIAN_RED;
extern color INDIANRED;
extern color IVORY1;
extern color IVORY2;
extern color IVORY3;
extern color IVORY4;
extern color IVORY;
extern color KHAKI1;
extern color KHAKI2;
extern color KHAKI3;
extern color KHAKI4;
extern color KHAKI;
extern color LAVENDERBLUSH1;
extern color LAVENDERBLUSH2;
extern color LAVENDERBLUSH3;
extern color LAVENDERBLUSH4;
extern color LAVENDER_BLUSH;
extern color LAVENDERBLUSH;
extern color LAVENDER;
extern color LAWN_GREEN;
extern color LAWNGREEN;
extern color LEMONCHIFFON1;
extern color LEMONCHIFFON2;
extern color LEMONCHIFFON3;
extern color LEMONCHIFFON4;
extern color LEMON_CHIFFON;
extern color LEMONCHIFFON;
extern color LIGHTBLUE1;
extern color LIGHTBLUE2;
extern color LIGHTBLUE3;
extern color LIGHTBLUE4;
extern color LIGHT_BLUE;
extern color LIGHTBLUE;
extern color LIGHT_CORAL;
extern color LIGHTCORAL;
extern color LIGHTCYAN1;
extern color LIGHTCYAN2;
extern color LIGHTCYAN3;
extern color LIGHTCYAN4;
extern color LIGHT_CYAN;
extern color LIGHTCYAN;
extern color LIGHTGOLDENROD1;
extern color LIGHTGOLDENROD2;
extern color LIGHTGOLDENROD3;
extern color LIGHTGOLDENROD4;
extern color LIGHT_GOLDENROD;
extern color LIGHTGOLDENROD;
extern color LIGHT_GOLDENROD_YELLOW;
extern color LIGHTGOLDENRODYELLOW;
extern color LIGHT_GRAY;
extern color LIGHTGRAY;
extern color LIGHT_GREEN;
extern color LIGHTGREEN;
extern color LIGHT_GREY;
extern color LIGHTGREY;
extern color LIGHTPINK1;
extern color LIGHTPINK2;
extern color LIGHTPINK3;
extern color LIGHTPINK4;
extern color LIGHT_PINK;
extern color LIGHTPINK;
extern color LIGHTSALMON1;
extern color LIGHTSALMON2;
extern color LIGHTSALMON3;
extern color LIGHTSALMON4;
extern color LIGHT_SALMON;
extern color LIGHTSALMON;
extern color LIGHT_SEA_GREEN;
extern color LIGHTSEAGREEN;
extern color LIGHTSKYBLUE1;
extern color LIGHTSKYBLUE2;
extern color LIGHTSKYBLUE3;
extern color LIGHTSKYBLUE4;
extern color LIGHT_SKY_BLUE;
extern color LIGHTSKYBLUE;
extern color LIGHT_SLATE_BLUE;
extern color LIGHTSLATEBLUE;
extern color LIGHT_SLATE_GRAY;
extern color LIGHTSLATEGRAY;
extern color LIGHT_SLATE_GREY;
extern color LIGHTSLATEGREY;
extern color LIGHTSTEELBLUE1;
extern color LIGHTSTEELBLUE2;
extern color LIGHTSTEELBLUE3;
extern color LIGHTSTEELBLUE4;
extern color LIGHT_STEEL_BLUE;
extern color LIGHTSTEELBLUE;
extern color LIGHTYELLOW1;
extern color LIGHTYELLOW2;
extern color LIGHTYELLOW3;
extern color LIGHTYELLOW4;
extern color LIGHT_YELLOW;
extern color LIGHTYELLOW;
extern color LIME_GREEN;
extern color LIMEGREEN;
extern color LIME;
extern color LINEN;
extern color MAGENTA1;
extern color MAGENTA2;
extern color MAGENTA3;
extern color MAGENTA4;
extern color MAGENTA;
extern color MAROON1;
extern color MAROON2;
extern color MAROON3;
extern color MAROON4;
extern color MAROON;
extern color MEDIUM_AQUAMARINE;
extern color MEDIUMAQUAMARINE;
extern color MEDIUM_BLUE;
extern color MEDIUMBLUE;
extern color MEDIUMORCHID1;
extern color MEDIUMORCHID2;
extern color MEDIUMORCHID3;
extern color MEDIUMORCHID4;
extern color MEDIUM_ORCHID;
extern color MEDIUMORCHID;
extern color MEDIUMPURPLE1;
extern color MEDIUMPURPLE2;
extern color MEDIUMPURPLE3;
extern color MEDIUMPURPLE4;
extern color MEDIUM_PURPLE;
extern color MEDIUMPURPLE;
extern color MEDIUM_SEA_GREEN;
extern color MEDIUMSEAGREEN;
extern color MEDIUM_SLATE_BLUE;
extern color MEDIUMSLATEBLUE;
extern color MEDIUM_SPRING_GREEN;
extern color MEDIUMSPRINGGREEN;
extern color MEDIUM_TURQUOISE;
extern color MEDIUMTURQUOISE;
extern color MEDIUM_VIOLET_RED;
extern color MEDIUMVIOLETRED;
extern color MIDNIGHT_BLUE;
extern color MIDNIGHTBLUE;
extern color MINT_CREAM;
extern color MINTCREAM;
extern color MISTYROSE1;
extern color MISTYROSE2;
extern color MISTYROSE3;
extern color MISTYROSE4;
extern color MISTY_ROSE;
extern color MISTYROSE;
extern color MOCCASIN;
extern color NAVAJOWHITE1;
extern color NAVAJOWHITE2;
extern color NAVAJOWHITE3;
extern color NAVAJOWHITE4;
extern color NAVAJO_WHITE;
extern color NAVAJOWHITE;
extern color NAVY_BLUE;
extern color NAVYBLUE;
extern color NAVY;
extern color OLD_LACE;
extern color OLDLACE;
extern color OLIVEDRAB1;
extern color OLIVEDRAB2;
extern color OLIVEDRAB3;
extern color OLIVEDRAB4;
extern color OLIVE_DRAB;
extern color OLIVEDRAB;
extern color LIGHT_ORANGE;
extern color ORANGE1;
extern color ORANGE2;
extern color ORANGE3;
extern color ORANGE4;
extern color ORANGE;
extern color ORANGERED1;
extern color ORANGERED2;
extern color ORANGERED3;
extern color ORANGERED4;
extern color ORANGE_RED;
extern color ORANGERED;
extern color ORCHID1;
extern color ORCHID2;
extern color ORCHID3;
extern color ORCHID4;
extern color ORCHID;
extern color PALE_GOLDENROD;
extern color PALEGOLDENROD;
extern color PALEGREEN1;
extern color PALEGREEN2;
extern color PALEGREEN3;
extern color PALEGREEN4;
extern color PALE_GREEN;
extern color PALEGREEN;
extern color PALETURQUOISE1;
extern color PALETURQUOISE2;
extern color PALETURQUOISE3;
extern color PALETURQUOISE4;
extern color PALE_TURQUOISE;
extern color PALETURQUOISE;
extern color PALEVIOLETRED1;
extern color PALEVIOLETRED2;
extern color PALEVIOLETRED3;
extern color PALEVIOLETRED4;
extern color PALE_VIOLET_RED;
extern color PALEVIOLETRED;
extern color PAPAYA_WHIP;
extern color PAPAYAWHIP;
extern color PEACHPUFF1;
extern color PEACHPUFF2;
extern color PEACHPUFF3;
extern color PEACHPUFF4;
extern color PEACH_PUFF;
extern color PEACHPUFF;
extern color PERU;
extern color PINK1;
extern color PINK2;
extern color PINK3;
extern color PINK4;
extern color PINK;
extern color PLUM1;
extern color PLUM2;
extern color PLUM3;
extern color PLUM4;
extern color PLUM;
extern color POWDER_BLUE;
extern color POWDERBLUE;
extern color PURPLE1;
extern color PURPLE2;
extern color PURPLE3;
extern color PURPLE4;
extern color PURPLE;
extern color RED1;
extern color RED2;
extern color RED3;
extern color RED4;
extern color RED;
extern color ROSYBROWN1;
extern color ROSYBROWN2;
extern color ROSYBROWN3;
extern color ROSYBROWN4;
extern color ROSY_BROWN;
extern color ROSYBROWN;
extern color ROYALBLUE1;
extern color ROYALBLUE2;
extern color ROYALBLUE3;
extern color ROYALBLUE4;
extern color ROYAL_BLUE;
extern color ROYALBLUE;
extern color SADDLE_BROWN;
extern color SADDLEBROWN;
extern color SALMON1;
extern color SALMON2;
extern color SALMON3;
extern color SALMON4;
extern color SALMON;
extern color SANDY_BROWN;
extern color SANDYBROWN;
extern color SEAGREEN1;
extern color SEAGREEN2;
extern color SEAGREEN3;
extern color SEAGREEN4;
extern color SEA_GREEN;
extern color SEAGREEN;
extern color SEASHELL1;
extern color SEASHELL2;
extern color SEASHELL3;
extern color SEASHELL4;
extern color SEASHELL;
extern color SIENNA1;
extern color SIENNA2;
extern color SIENNA3;
extern color SIENNA4;
extern color SIENNA;
extern color SKYBLUE1;
extern color SKYBLUE2;
extern color SKYBLUE3;
extern color SKYBLUE4;
extern color SKY_BLUE;
extern color SKYBLUE;
extern color SLATEBLUE1;
extern color SLATEBLUE2;
extern color SLATEBLUE3;
extern color SLATEBLUE4;
extern color SLATE_BLUE;
extern color SLATEBLUE;
extern color SLATEGRAY1;
extern color SLATEGRAY2;
extern color SLATEGRAY3;
extern color SLATEGRAY4;
extern color SLATE_GRAY;
extern color SLATEGRAY;
extern color SLATE_GREY;
extern color SLATEGREY;
extern color SNOW1;
extern color SNOW2;
extern color SNOW3;
extern color SNOW4;
extern color SNOW;
extern color SPRINGGREEN1;
extern color SPRINGGREEN2;
extern color SPRINGGREEN3;
extern color SPRINGGREEN4;
extern color SPRING_GREEN;
extern color SPRINGGREEN;
extern color STEELBLUE1;
extern color STEELBLUE2;
extern color STEELBLUE3;
extern color STEELBLUE4;
extern color STEEL_BLUE;
extern color STEELBLUE;
extern color TAN1;
extern color TAN2;
extern color TAN3;
extern color TAN4;
extern color TAN;
extern color THISTLE1;
extern color THISTLE2;
extern color THISTLE3;
extern color THISTLE4;
extern color THISTLE;
extern color TOMATO1;
extern color TOMATO2;
extern color TOMATO3;
extern color TOMATO4;
extern color TOMATO;
extern color TURQUOISE1;
extern color TURQUOISE2;
extern color TURQUOISE3;
extern color TURQUOISE4;
extern color TURQUOISE;
extern color VIOLET;
extern color VIOLETRED1;
extern color VIOLETRED2;
extern color VIOLETRED3;
extern color VIOLETRED4;
extern color VIOLET_RED;
extern color VIOLETRED;
extern color WHEAT1;
extern color WHEAT2;
extern color WHEAT3;
extern color WHEAT4;
extern color WHEAT;
extern color WHITE;
extern color WHITE_SMOKE;
extern color WHITESMOKE;
extern color YELLOW1;
extern color YELLOW2;
extern color YELLOW3;
extern color YELLOW4;
extern color YELLOW_GREEN;
extern color YELLOWGREEN;
extern color YELLOW;

extern color gl_save_color;
extern color gl_last_color;

static inline color gl_color_current (void)
{
    return (gl_last_color);
}

extern color COLOR_NONE;

#define CONST_ALICEBLUE { 240, 248, 255, 255 }
#define CONST_ANTIQUEWHITE1 { 255, 239, 219, 255 }
#define CONST_ANTIQUEWHITE2 { 238, 223, 204, 255 }
#define CONST_ANTIQUEWHITE3 { 205, 192, 176, 255 }
#define CONST_ANTIQUEWHITE4 { 139, 131, 120, 255 }
#define CONST_ANTIQUEWHITE { 250, 235, 215, 255 }
#define CONST_AQUAMARINE1 { 127, 255, 212, 255 }
#define CONST_AQUAMARINE2 { 118, 238, 198, 255 }
#define CONST_AQUAMARINE3 { 102, 205, 170, 255 }
#define CONST_AQUAMARINE4 { 69, 139, 116, 255 }
#define CONST_AQUAMARINE { 127, 255, 212, 255 }
#define CONST_AZURE1 { 240, 255, 255, 255 }
#define CONST_AZURE2 { 224, 238, 238, 255 }
#define CONST_AZURE3 { 193, 205, 205, 255 }
#define CONST_AZURE4 { 131, 139, 139, 255 }
#define CONST_AZURE { 240, 255, 255, 255 }
#define CONST_BEIGE { 245, 245, 220, 255 }
#define CONST_BISQUE1 { 255, 228, 196, 255 }
#define CONST_BISQUE2 { 238, 213, 183, 255 }
#define CONST_BISQUE3 { 205, 183, 158, 255 }
#define CONST_BISQUE4 { 139, 125, 107, 255 }
#define CONST_BISQUE { 255, 228, 196, 255 }
#define CONST_BLACK { 0, 0, 0, 255 }
#define CONST_NONE { 0, 0, 0, 0 }
#define CONST_BLANCHEDALMOND { 255, 235, 205, 255 }
#define CONST_BLUE1 { 0, 0, 255, 255 }
#define CONST_BLUE2 { 0, 0, 238, 255 }
#define CONST_BLUE3 { 0, 0, 205, 255 }
#define CONST_BLUE4 { 0, 0, 139, 255 }
#define CONST_BLUE { 0, 0, 255, 255 }
#define CONST_BLUEVIOLET { 138, 43, 226, 255 }
#define CONST_BROWN1 { 255, 64, 64, 255 }
#define CONST_BROWN2 { 238, 59, 59, 255 }
#define CONST_BROWN3 { 205, 51, 51, 255 }
#define CONST_BROWN4 { 139, 35, 35, 255 }
#define CONST_BROWN { 165, 42, 42, 255 }
#define CONST_BURLYWOOD1 { 255, 211, 155, 255 }
#define CONST_BURLYWOOD2 { 238, 197, 145, 255 }
#define CONST_BURLYWOOD3 { 205, 170, 125, 255 }
#define CONST_BURLYWOOD4 { 139, 115, 85, 255 }
#define CONST_BURLYWOOD { 222, 184, 135, 255 }
#define CONST_CADETBLUE1 { 152, 245, 255, 255 }
#define CONST_CADETBLUE2 { 142, 229, 238, 255 }
#define CONST_CADETBLUE3 { 122, 197, 205, 255 }
#define CONST_CADETBLUE4 { 83, 134, 139, 255 }
#define CONST_CADETBLUE { 95, 158, 160, 255 }
#define CONST_CHARTREUSE1 { 127, 255, 0, 255 }
#define CONST_CHARTREUSE2 { 118, 238, 0, 255 }
#define CONST_CHARTREUSE3 { 102, 205, 0, 255 }
#define CONST_CHARTREUSE4 { 69, 139, 0, 255 }
#define CONST_CHARTREUSE { 127, 255, 0, 255 }
#define CONST_CHOCOLATE1 { 255, 127, 36, 255 }
#define CONST_CHOCOLATE2 { 238, 118, 33, 255 }
#define CONST_CHOCOLATE3 { 205, 102, 29, 255 }
#define CONST_CHOCOLATE4 { 139, 69, 19, 255 }
#define CONST_CHOCOLATE { 210, 105, 30, 255 }
#define CONST_CORAL1 { 255, 114, 86, 255 }
#define CONST_CORAL2 { 238, 106, 80, 255 }
#define CONST_CORAL3 { 205, 91, 69, 255 }
#define CONST_CORAL4 { 139, 62, 47, 255 }
#define CONST_CORAL { 255, 127, 80, 255 }
#define CONST_CORNFLOWERBLUE { 100, 149, 237, 255 }
#define CONST_CORNSILK1 { 255, 248, 220, 255 }
#define CONST_CORNSILK2 { 238, 232, 205, 255 }
#define CONST_CORNSILK3 { 205, 200, 177, 255 }
#define CONST_CORNSILK4 { 139, 136, 120, 255 }
#define CONST_CORNSILK { 255, 248, 220, 255 }
#define CONST_CYAN1 { 0, 255, 255, 255 }
#define CONST_CYAN2 { 0, 238, 238, 255 }
#define CONST_CYAN3 { 0, 205, 205, 255 }
#define CONST_CYAN4 { 0, 139, 139, 255 }
#define CONST_CYAN { 0, 255, 255, 255 }
#define CONST_DARKBLUE { 0, 0, 139, 255 }
#define CONST_DARKCYAN { 0, 139, 139, 255 }
#define CONST_DARKGOLDENROD1 { 255, 185, 15, 255 }
#define CONST_DARKGOLDENROD2 { 238, 173, 14, 255 }
#define CONST_DARKGOLDENROD3 { 205, 149, 12, 255 }
#define CONST_DARKGOLDENROD4 { 139, 101, 8, 255 }
#define CONST_DARKGOLDENROD { 184, 134, 11, 255 }
#define CONST_DARKGRAY { 169, 169, 169, 255 }
#define CONST_DARKGREEN { 0, 100, 0, 255 }
#define CONST_DARKGREY { 169, 169, 169, 255 }
#define CONST_DARKKHAKI { 189, 183, 107, 255 }
#define CONST_DARKMAGENTA { 139, 0, 139, 255 }
#define CONST_DARKOLIVEGREEN1 { 202, 255, 112, 255 }
#define CONST_DARKOLIVEGREEN2 { 188, 238, 104, 255 }
#define CONST_DARKOLIVEGREEN3 { 162, 205, 90, 255 }
#define CONST_DARKOLIVEGREEN4 { 110, 139, 61, 255 }
#define CONST_DARKOLIVEGREEN { 85, 107, 47, 255 }
#define CONST_DARKORANGE1 { 255, 127, 0, 255 }
#define CONST_DARKORANGE2 { 238, 118, 0, 255 }
#define CONST_DARKORANGE3 { 205, 102, 0, 255 }
#define CONST_DARKORANGE4 { 139, 69, 0, 255 }
#define CONST_DARKORANGE { 255, 140, 0, 255 }
#define CONST_DARKORCHID1 { 191, 62, 255, 255 }
#define CONST_DARKORCHID2 { 178, 58, 238, 255 }
#define CONST_DARKORCHID3 { 154, 50, 205, 255 }
#define CONST_DARKORCHID4 { 104, 34, 139, 255 }
#define CONST_DARKORCHID { 153, 50, 204, 255 }
#define CONST_DARKRED { 139, 0, 0, 255 }
#define CONST_DARKSALMON { 233, 150, 122, 255 }
#define CONST_DARKSEAGREEN1 { 193, 255, 193, 255 }
#define CONST_DARKSEAGREEN2 { 180, 238, 180, 255 }
#define CONST_DARKSEAGREEN3 { 155, 205, 155, 255 }
#define CONST_DARKSEAGREEN4 { 105, 139, 105, 255 }
#define CONST_DARKSEAGREEN { 143, 188, 143, 255 }
#define CONST_DARKSLATEBLUE { 72, 61, 139, 255 }
#define CONST_DARKSLATEGRAY1 { 151, 255, 255, 255 }
#define CONST_DARKSLATEGRAY2 { 141, 238, 238, 255 }
#define CONST_DARKSLATEGRAY3 { 121, 205, 205, 255 }
#define CONST_DARKSLATEGRAY4 { 82, 139, 139, 255 }
#define CONST_DARKSLATEGRAY { 47, 79, 79, 255 }
#define CONST_DARKSLATEGREY { 47, 79, 79, 255 }
#define CONST_DARKTURQUOISE { 0, 206, 209, 255 }
#define CONST_DARKVIOLET { 148, 0, 211, 255 }
#define CONST_DEEPPINK1 { 255, 20, 147, 255 }
#define CONST_DEEPPINK2 { 238, 18, 137, 255 }
#define CONST_DEEPPINK3 { 205, 16, 118, 255 }
#define CONST_DEEPPINK4 { 139, 10, 80, 255 }
#define CONST_DEEPPINK { 255, 20, 147, 255 }
#define CONST_DEEPSKYBLUE1 { 0, 191, 255, 255 }
#define CONST_DEEPSKYBLUE2 { 0, 178, 238, 255 }
#define CONST_DEEPSKYBLUE3 { 0, 154, 205, 255 }
#define CONST_DEEPSKYBLUE4 { 0, 104, 139, 255 }
#define CONST_DEEPSKYBLUE { 0, 191, 255, 255 }
#define CONST_DIMGRAY { 105, 105, 105, 255 }
#define CONST_DIMGREY { 105, 105, 105, 255 }
#define CONST_DODGERBLUE1 { 30, 144, 255, 255 }
#define CONST_DODGERBLUE2 { 28, 134, 238, 255 }
#define CONST_DODGERBLUE3 { 24, 116, 205, 255 }
#define CONST_DODGERBLUE4 { 16, 78, 139, 255 }
#define CONST_DODGERBLUE { 30, 144, 255, 255 }
#define CONST_FIREBRICK1 { 255, 48, 48, 255 }
#define CONST_FIREBRICK2 { 238, 44, 44, 255 }
#define CONST_FIREBRICK3 { 205, 38, 38, 255 }
#define CONST_FIREBRICK4 { 139, 26, 26, 255 }
#define CONST_FIREBRICK { 178, 34, 34, 255 }
#define CONST_FLORALWHITE { 255, 250, 240, 255 }
#define CONST_FORESTGREEN { 34, 139, 34, 255 }
#define CONST_GAINSBORO { 220, 220, 220, 255 }
#define CONST_GHOSTWHITE { 248, 248, 255, 255 }
#define CONST_GOLD1 { 255, 215, 0, 255 }
#define CONST_GOLD2 { 238, 201, 0, 255 }
#define CONST_GOLD3 { 205, 173, 0, 255 }
#define CONST_GOLD4 { 139, 117, 0, 255 }
#define CONST_GOLDENROD1 { 255, 193, 37, 255 }
#define CONST_GOLDENROD2 { 238, 180, 34, 255 }
#define CONST_GOLDENROD3 { 205, 155, 29, 255 }
#define CONST_GOLDENROD4 { 139, 105, 20, 255 }
#define CONST_GOLDENROD { 218, 165, 32, 255 }
#define CONST_GOLD { 255, 215, 0, 255 }
#define CONST_GRAY10 { 26, 26, 26, 255 }
#define CONST_GRAY11 { 28, 28, 28, 255 }
#define CONST_GRAY12 { 31, 31, 31, 255 }
#define CONST_GRAY13 { 33, 33, 33, 255 }
#define CONST_GRAY14 { 36, 36, 36, 255 }
#define CONST_GRAY15 { 38, 38, 38, 255 }
#define CONST_GRAY16 { 41, 41, 41, 255 }
#define CONST_GRAY17 { 43, 43, 43, 255 }
#define CONST_GRAY18 { 46, 46, 46, 255 }
#define CONST_GRAY19 { 48, 48, 48, 255 }
#define CONST_GRAY1 { 3, 3, 3, 255 }
#define CONST_GRAY20 { 51, 51, 51, 255 }
#define CONST_GRAY21 { 54, 54, 54, 255 }
#define CONST_GRAY22 { 56, 56, 56, 255 }
#define CONST_GRAY23 { 59, 59, 59, 255 }
#define CONST_GRAY24 { 61, 61, 61, 255 }
#define CONST_GRAY25 { 64, 64, 64, 255 }
#define CONST_GRAY26 { 66, 66, 66, 255 }
#define CONST_GRAY27 { 69, 69, 69, 255 }
#define CONST_GRAY28 { 71, 71, 71, 255 }
#define CONST_GRAY29 { 74, 74, 74, 255 }
#define CONST_GRAY2 { 5, 5, 5, 255 }
#define CONST_GRAY30 { 77, 77, 77, 255 }
#define CONST_GRAY31 { 79, 79, 79, 255 }
#define CONST_GRAY32 { 82, 82, 82, 255 }
#define CONST_GRAY33 { 84, 84, 84, 255 }
#define CONST_GRAY34 { 87, 87, 87, 255 }
#define CONST_GRAY35 { 89, 89, 89, 255 }
#define CONST_GRAY36 { 92, 92, 92, 255 }
#define CONST_GRAY37 { 94, 94, 94, 255 }
#define CONST_GRAY38 { 97, 97, 97, 255 }
#define CONST_GRAY39 { 99, 99, 99, 255 }
#define CONST_GRAY3 { 8, 8, 8, 255 }
#define CONST_GRAY40 { 102, 102, 102, 255 }
#define CONST_GRAY41 { 105, 105, 105, 255 }
#define CONST_GRAY42 { 107, 107, 107, 255 }
#define CONST_GRAY43 { 110, 110, 110, 255 }
#define CONST_GRAY44 { 112, 112, 112, 255 }
#define CONST_GRAY45 { 115, 115, 115, 255 }
#define CONST_GRAY46 { 117, 117, 117, 255 }
#define CONST_GRAY47 { 120, 120, 120, 255 }
#define CONST_GRAY48 { 122, 122, 122, 255 }
#define CONST_GRAY49 { 125, 125, 125, 255 }
#define CONST_GRAY4 { 10, 10, 10, 255 }
#define CONST_GRAY50 { 127, 127, 127, 255 }
#define CONST_GRAY51 { 130, 130, 130, 255 }
#define CONST_GRAY52 { 133, 133, 133, 255 }
#define CONST_GRAY53 { 135, 135, 135, 255 }
#define CONST_GRAY54 { 138, 138, 138, 255 }
#define CONST_GRAY55 { 140, 140, 140, 255 }
#define CONST_GRAY56 { 143, 143, 143, 255 }
#define CONST_GRAY57 { 145, 145, 145, 255 }
#define CONST_GRAY58 { 148, 148, 148, 255 }
#define CONST_GRAY59 { 150, 150, 150, 255 }
#define CONST_GRAY5 { 13, 13, 13, 255 }
#define CONST_GRAY60 { 153, 153, 153, 255 }
#define CONST_GRAY61 { 156, 156, 156, 255 }
#define CONST_GRAY62 { 158, 158, 158, 255 }
#define CONST_GRAY63 { 161, 161, 161, 255 }
#define CONST_GRAY64 { 163, 163, 163, 255 }
#define CONST_GRAY65 { 166, 166, 166, 255 }
#define CONST_GRAY66 { 168, 168, 168, 255 }
#define CONST_GRAY67 { 171, 171, 171, 255 }
#define CONST_GRAY68 { 173, 173, 173, 255 }
#define CONST_GRAY69 { 176, 176, 176, 255 }
#define CONST_GRAY6 { 15, 15, 15, 255 }
#define CONST_GRAY70 { 179, 179, 179, 255 }
#define CONST_GRAY71 { 181, 181, 181, 255 }
#define CONST_GRAY72 { 184, 184, 184, 255 }
#define CONST_GRAY73 { 186, 186, 186, 255 }
#define CONST_GRAY74 { 189, 189, 189, 255 }
#define CONST_GRAY75 { 191, 191, 191, 255 }
#define CONST_GRAY76 { 194, 194, 194, 255 }
#define CONST_GRAY77 { 196, 196, 196, 255 }
#define CONST_GRAY78 { 199, 199, 199, 255 }
#define CONST_GRAY79 { 201, 201, 201, 255 }
#define CONST_GRAY7 { 18, 18, 18, 255 }
#define CONST_GRAY80 { 204, 204, 204, 255 }
#define CONST_GRAY81 { 207, 207, 207, 255 }
#define CONST_GRAY82 { 209, 209, 209, 255 }
#define CONST_GRAY83 { 212, 212, 212, 255 }
#define CONST_GRAY84 { 214, 214, 214, 255 }
#define CONST_GRAY85 { 217, 217, 217, 255 }
#define CONST_GRAY86 { 219, 219, 219, 255 }
#define CONST_GRAY87 { 222, 222, 222, 255 }
#define CONST_GRAY88 { 224, 224, 224, 255 }
#define CONST_GRAY89 { 227, 227, 227, 255 }
#define CONST_GRAY8 { 20, 20, 20, 255 }
#define CONST_GRAY90 { 229, 229, 229, 255 }
#define CONST_GRAY91 { 232, 232, 232, 255 }
#define CONST_GRAY92 { 235, 235, 235, 255 }
#define CONST_GRAY93 { 237, 237, 237, 255 }
#define CONST_GRAY94 { 240, 240, 240, 255 }
#define CONST_GRAY95 { 242, 242, 242, 255 }
#define CONST_GRAY96 { 245, 245, 245, 255 }
#define CONST_GRAY97 { 247, 247, 247, 255 }
#define CONST_GRAY98 { 250, 250, 250, 255 }
#define CONST_GRAY99 { 252, 252, 252, 255 }
#define CONST_GRAY9 { 23, 23, 23, 255 }
#define CONST_GRAY { 190, 190, 190, 255 }
#define CONST_GREEN1 { 0, 255, 0, 255 }
#define CONST_GREEN2 { 0, 238, 0, 255 }
#define CONST_GREEN3 { 0, 205, 0, 255 }
#define CONST_GREEN4 { 0, 139, 0, 255 }
#define CONST_GREEN { 0, 255, 0, 255 }
#define CONST_GREENYELLOW { 173, 255, 47, 255 }
#define CONST_GREY10 { 26, 26, 26, 255 }
#define CONST_GREY11 { 28, 28, 28, 255 }
#define CONST_GREY12 { 31, 31, 31, 255 }
#define CONST_GREY13 { 33, 33, 33, 255 }
#define CONST_GREY14 { 36, 36, 36, 255 }
#define CONST_GREY15 { 38, 38, 38, 255 }
#define CONST_GREY16 { 41, 41, 41, 255 }
#define CONST_GREY17 { 43, 43, 43, 255 }
#define CONST_GREY18 { 46, 46, 46, 255 }
#define CONST_GREY19 { 48, 48, 48, 255 }
#define CONST_GREY1 { 3, 3, 3, 255 }
#define CONST_GREY20 { 51, 51, 51, 255 }
#define CONST_GREY21 { 54, 54, 54, 255 }
#define CONST_GREY22 { 56, 56, 56, 255 }
#define CONST_GREY23 { 59, 59, 59, 255 }
#define CONST_GREY24 { 61, 61, 61, 255 }
#define CONST_GREY25 { 64, 64, 64, 255 }
#define CONST_GREY26 { 66, 66, 66, 255 }
#define CONST_GREY27 { 69, 69, 69, 255 }
#define CONST_GREY28 { 71, 71, 71, 255 }
#define CONST_GREY29 { 74, 74, 74, 255 }
#define CONST_GREY2 { 5, 5, 5, 255 }
#define CONST_GREY30 { 77, 77, 77, 255 }
#define CONST_GREY31 { 79, 79, 79, 255 }
#define CONST_GREY32 { 82, 82, 82, 255 }
#define CONST_GREY33 { 84, 84, 84, 255 }
#define CONST_GREY34 { 87, 87, 87, 255 }
#define CONST_GREY35 { 89, 89, 89, 255 }
#define CONST_GREY36 { 92, 92, 92, 255 }
#define CONST_GREY37 { 94, 94, 94, 255 }
#define CONST_GREY38 { 97, 97, 97, 255 }
#define CONST_GREY39 { 99, 99, 99, 255 }
#define CONST_GREY3 { 8, 8, 8, 255 }
#define CONST_GREY40 { 102, 102, 102, 255 }
#define CONST_GREY41 { 105, 105, 105, 255 }
#define CONST_GREY42 { 107, 107, 107, 255 }
#define CONST_GREY43 { 110, 110, 110, 255 }
#define CONST_GREY44 { 112, 112, 112, 255 }
#define CONST_GREY45 { 115, 115, 115, 255 }
#define CONST_GREY46 { 117, 117, 117, 255 }
#define CONST_GREY47 { 120, 120, 120, 255 }
#define CONST_GREY48 { 122, 122, 122, 255 }
#define CONST_GREY49 { 125, 125, 125, 255 }
#define CONST_GREY4 { 10, 10, 10, 255 }
#define CONST_GREY50 { 127, 127, 127, 255 }
#define CONST_GREY51 { 130, 130, 130, 255 }
#define CONST_GREY52 { 133, 133, 133, 255 }
#define CONST_GREY53 { 135, 135, 135, 255 }
#define CONST_GREY54 { 138, 138, 138, 255 }
#define CONST_GREY55 { 140, 140, 140, 255 }
#define CONST_GREY56 { 143, 143, 143, 255 }
#define CONST_GREY57 { 145, 145, 145, 255 }
#define CONST_GREY58 { 148, 148, 148, 255 }
#define CONST_GREY59 { 150, 150, 150, 255 }
#define CONST_GREY5 { 13, 13, 13, 255 }
#define CONST_GREY60 { 153, 153, 153, 255 }
#define CONST_GREY61 { 156, 156, 156, 255 }
#define CONST_GREY62 { 158, 158, 158, 255 }
#define CONST_GREY63 { 161, 161, 161, 255 }
#define CONST_GREY64 { 163, 163, 163, 255 }
#define CONST_GREY65 { 166, 166, 166, 255 }
#define CONST_GREY66 { 168, 168, 168, 255 }
#define CONST_GREY67 { 171, 171, 171, 255 }
#define CONST_GREY68 { 173, 173, 173, 255 }
#define CONST_GREY69 { 176, 176, 176, 255 }
#define CONST_GREY6 { 15, 15, 15, 255 }
#define CONST_GREY70 { 179, 179, 179, 255 }
#define CONST_GREY71 { 181, 181, 181, 255 }
#define CONST_GREY72 { 184, 184, 184, 255 }
#define CONST_GREY73 { 186, 186, 186, 255 }
#define CONST_GREY74 { 189, 189, 189, 255 }
#define CONST_GREY75 { 191, 191, 191, 255 }
#define CONST_GREY76 { 194, 194, 194, 255 }
#define CONST_GREY77 { 196, 196, 196, 255 }
#define CONST_GREY78 { 199, 199, 199, 255 }
#define CONST_GREY79 { 201, 201, 201, 255 }
#define CONST_GREY7 { 18, 18, 18, 255 }
#define CONST_GREY80 { 204, 204, 204, 255 }
#define CONST_GREY81 { 207, 207, 207, 255 }
#define CONST_GREY82 { 209, 209, 209, 255 }
#define CONST_GREY83 { 212, 212, 212, 255 }
#define CONST_GREY84 { 214, 214, 214, 255 }
#define CONST_GREY85 { 217, 217, 217, 255 }
#define CONST_GREY86 { 219, 219, 219, 255 }
#define CONST_GREY87 { 222, 222, 222, 255 }
#define CONST_GREY88 { 224, 224, 224, 255 }
#define CONST_GREY89 { 227, 227, 227, 255 }
#define CONST_GREY8 { 20, 20, 20, 255 }
#define CONST_GREY90 { 229, 229, 229, 255 }
#define CONST_GREY91 { 232, 232, 232, 255 }
#define CONST_GREY92 { 235, 235, 235, 255 }
#define CONST_GREY93 { 237, 237, 237, 255 }
#define CONST_GREY94 { 240, 240, 240, 255 }
#define CONST_GREY95 { 242, 242, 242, 255 }
#define CONST_GREY96 { 245, 245, 245, 255 }
#define CONST_GREY97 { 247, 247, 247, 255 }
#define CONST_GREY98 { 250, 250, 250, 255 }
#define CONST_GREY99 { 252, 252, 252, 255 }
#define CONST_GREY9 { 23, 23, 23, 255 }
#define CONST_GREY { 190, 190, 190, 255 }
#define CONST_HONEYDEW1 { 240, 255, 240, 255 }
#define CONST_HONEYDEW2 { 224, 238, 224, 255 }
#define CONST_HONEYDEW3 { 193, 205, 193, 255 }
#define CONST_HONEYDEW4 { 131, 139, 131, 255 }
#define CONST_HONEYDEW { 240, 255, 240, 255 }
#define CONST_HOTPINK1 { 255, 110, 180, 255 }
#define CONST_HOTPINK2 { 238, 106, 167, 255 }
#define CONST_HOTPINK3 { 205, 96, 144, 255 }
#define CONST_HOTPINK4 { 139, 58, 98, 255 }
#define CONST_HOTPINK { 255, 105, 180, 255 }
#define CONST_INDIANRED1 { 255, 106, 106, 255 }
#define CONST_INDIANRED2 { 238, 99, 99, 255 }
#define CONST_INDIANRED3 { 205, 85, 85, 255 }
#define CONST_INDIANRED4 { 139, 58, 58, 255 }
#define CONST_INDIANRED { 205, 92, 92, 255 }
#define CONST_IVORY1 { 255, 255, 240, 255 }
#define CONST_IVORY2 { 238, 238, 224, 255 }
#define CONST_IVORY3 { 205, 205, 193, 255 }
#define CONST_IVORY4 { 139, 139, 131, 255 }
#define CONST_IVORY { 255, 255, 240, 255 }
#define CONST_KHAKI1 { 255, 246, 143, 255 }
#define CONST_KHAKI2 { 238, 230, 133, 255 }
#define CONST_KHAKI3 { 205, 198, 115, 255 }
#define CONST_KHAKI4 { 139, 134, 78, 255 }
#define CONST_KHAKI { 240, 230, 140, 255 }
#define CONST_LAVENDERBLUSH1 { 255, 240, 245, 255 }
#define CONST_LAVENDERBLUSH2 { 238, 224, 229, 255 }
#define CONST_LAVENDERBLUSH3 { 205, 193, 197, 255 }
#define CONST_LAVENDERBLUSH4 { 139, 131, 134, 255 }
#define CONST_LAVENDER_BLUSH { 255, 240, 245, 255 }
#define CONST_LAVENDERBLUSH { 255, 240, 245, 255 }
#define CONST_LAVENDER { 230, 230, 250, 255 }
#define CONST_LAWN_GREEN { 124, 252, 0, 255 }
#define CONST_LAWNGREEN { 124, 252, 0, 255 }
#define CONST_LEMONCHIFFON1 { 255, 250, 205, 255 }
#define CONST_LEMONCHIFFON2 { 238, 233, 191, 255 }
#define CONST_LEMONCHIFFON3 { 205, 201, 165, 255 }
#define CONST_LEMONCHIFFON4 { 139, 137, 112, 255 }
#define CONST_LEMON_CHIFFON { 255, 250, 205, 255 }
#define CONST_LEMONCHIFFON { 255, 250, 205, 255 }
#define CONST_LIGHTBLUE1 { 191, 239, 255, 255 }
#define CONST_LIGHTBLUE2 { 178, 223, 238, 255 }
#define CONST_LIGHTBLUE3 { 154, 192, 205, 255 }
#define CONST_LIGHTBLUE4 { 104, 131, 139, 255 }
#define CONST_LIGHT_BLUE { 173, 216, 230, 255 }
#define CONST_LIGHTBLUE { 173, 216, 230, 255 }
#define CONST_LIGHT_CORAL { 240, 128, 128, 255 }
#define CONST_LIGHTCORAL { 240, 128, 128, 255 }
#define CONST_LIGHTCYAN1 { 224, 255, 255, 255 }
#define CONST_LIGHTCYAN2 { 209, 238, 238, 255 }
#define CONST_LIGHTCYAN3 { 180, 205, 205, 255 }
#define CONST_LIGHTCYAN4 { 122, 139, 139, 255 }
#define CONST_LIGHT_CYAN { 224, 255, 255, 255 }
#define CONST_LIGHTCYAN { 224, 255, 255, 255 }
#define CONST_LIGHTGOLDENROD1 { 255, 236, 139, 255 }
#define CONST_LIGHTGOLDENROD2 { 238, 220, 130, 255 }
#define CONST_LIGHTGOLDENROD3 { 205, 190, 112, 255 }
#define CONST_LIGHTGOLDENROD4 { 139, 129, 76, 255 }
#define CONST_LIGHT_GOLDENROD { 238, 221, 130, 255 }
#define CONST_LIGHTGOLDENROD { 238, 221, 130, 255 }
#define CONST_LIGHT_GOLDENROD_YELLOW { 250, 250, 210, 255 }
#define CONST_LIGHTGOLDENRODYELLOW { 250, 250, 210, 255 }
#define CONST_LIGHT_GRAY { 211, 211, 211, 255 }
#define CONST_LIGHTGRAY { 211, 211, 211, 255 }
#define CONST_LIGHT_GREEN { 144, 238, 144, 255 }
#define CONST_LIGHTGREEN { 144, 238, 144, 255 }
#define CONST_LIGHT_GREY { 211, 211, 211, 255 }
#define CONST_LIGHTGREY { 211, 211, 211, 255 }
#define CONST_LIGHTPINK1 { 255, 174, 185, 255 }
#define CONST_LIGHTPINK2 { 238, 162, 173, 255 }
#define CONST_LIGHTPINK3 { 205, 140, 149, 255 }
#define CONST_LIGHTPINK4 { 139, 95, 101, 255 }
#define CONST_LIGHT_PINK { 255, 182, 193, 255 }
#define CONST_LIGHTPINK { 255, 182, 193, 255 }
#define CONST_LIGHTSALMON1 { 255, 160, 122, 255 }
#define CONST_LIGHTSALMON2 { 238, 149, 114, 255 }
#define CONST_LIGHTSALMON3 { 205, 129, 98, 255 }
#define CONST_LIGHTSALMON4 { 139, 87, 66, 255 }
#define CONST_LIGHT_SALMON { 255, 160, 122, 255 }
#define CONST_LIGHTSALMON { 255, 160, 122, 255 }
#define CONST_LIGHT_SEA_GREEN { 32, 178, 170, 255 }
#define CONST_LIGHTSEAGREEN { 32, 178, 170, 255 }
#define CONST_LIGHTSKYBLUE1 { 176, 226, 255, 255 }
#define CONST_LIGHTSKYBLUE2 { 164, 211, 238, 255 }
#define CONST_LIGHTSKYBLUE3 { 141, 182, 205, 255 }
#define CONST_LIGHTSKYBLUE4 { 96, 123, 139, 255 }
#define CONST_LIGHT_SKY_BLUE { 135, 206, 250, 255 }
#define CONST_LIGHTSKYBLUE { 135, 206, 250, 255 }
#define CONST_LIGHT_SLATE_BLUE { 132, 112, 255, 255 }
#define CONST_LIGHTSLATEBLUE { 132, 112, 255, 255 }
#define CONST_LIGHT_SLATE_GRAY { 119, 136, 153, 255 }
#define CONST_LIGHTSLATEGRAY { 119, 136, 153, 255 }
#define CONST_LIGHT_SLATE_GREY { 119, 136, 153, 255 }
#define CONST_LIGHTSLATEGREY { 119, 136, 153, 255 }
#define CONST_LIGHTSTEELBLUE1 { 202, 225, 255, 255 }
#define CONST_LIGHTSTEELBLUE2 { 188, 210, 238, 255 }
#define CONST_LIGHTSTEELBLUE3 { 162, 181, 205, 255 }
#define CONST_LIGHTSTEELBLUE4 { 110, 123, 139, 255 }
#define CONST_LIGHT_STEEL_BLUE { 176, 196, 222, 255 }
#define CONST_LIGHTSTEELBLUE { 176, 196, 222, 255 }
#define CONST_LIGHTYELLOW1 { 255, 255, 224, 255 }
#define CONST_LIGHTYELLOW2 { 238, 238, 209, 255 }
#define CONST_LIGHTYELLOW3 { 205, 205, 180, 255 }
#define CONST_LIGHTYELLOW4 { 139, 139, 122, 255 }
#define CONST_LIGHT_YELLOW { 255, 255, 224, 255 }
#define CONST_LIGHTYELLOW { 255, 255, 224, 255 }
#define CONST_LIME_GREEN { 50, 205, 50, 255 }
#define CONST_LIMEGREEN { 50, 205, 50, 255 }
#define CONST_LIME { 50, 205, 50, 255 }
#define CONST_LINEN { 250, 240, 230, 255 }
#define CONST_MAGENTA1 { 255, 0, 255, 255 }
#define CONST_MAGENTA2 { 238, 0, 238, 255 }
#define CONST_MAGENTA3 { 205, 0, 205, 255 }
#define CONST_MAGENTA4 { 139, 0, 139, 255 }
#define CONST_MAGENTA { 255, 0, 255, 255 }
#define CONST_MAROON1 { 255, 52, 179, 255 }
#define CONST_MAROON2 { 238, 48, 167, 255 }
#define CONST_MAROON3 { 205, 41, 144, 255 }
#define CONST_MAROON4 { 139, 28, 98, 255 }
#define CONST_MAROON { 176, 48, 96, 255 }
#define CONST_MEDIUM_AQUAMARINE { 102, 205, 170, 255 }
#define CONST_MEDIUMAQUAMARINE { 102, 205, 170, 255 }
#define CONST_MEDIUM_BLUE { 0, 0, 205, 255 }
#define CONST_MEDIUMBLUE { 0, 0, 205, 255 }
#define CONST_MEDIUMORCHID1 { 224, 102, 255, 255 }
#define CONST_MEDIUMORCHID2 { 209, 95, 238, 255 }
#define CONST_MEDIUMORCHID3 { 180, 82, 205, 255 }
#define CONST_MEDIUMORCHID4 { 122, 55, 139, 255 }
#define CONST_MEDIUM_ORCHID { 186, 85, 211, 255 }
#define CONST_MEDIUMORCHID { 186, 85, 211, 255 }
#define CONST_MEDIUMPURPLE1 { 171, 130, 255, 255 }
#define CONST_MEDIUMPURPLE2 { 159, 121, 238, 255 }
#define CONST_MEDIUMPURPLE3 { 137, 104, 205, 255 }
#define CONST_MEDIUMPURPLE4 { 93, 71, 139, 255 }
#define CONST_MEDIUM_PURPLE { 147, 112, 219, 255 }
#define CONST_MEDIUMPURPLE { 147, 112, 219, 255 }
#define CONST_MEDIUM_SEA_GREEN { 60, 179, 113, 255 }
#define CONST_MEDIUMSEAGREEN { 60, 179, 113, 255 }
#define CONST_MEDIUM_SLATE_BLUE { 123, 104, 238, 255 }
#define CONST_MEDIUMSLATEBLUE { 123, 104, 238, 255 }
#define CONST_MEDIUM_SPRING_GREEN { 0, 250, 154, 255 }
#define CONST_MEDIUMSPRINGGREEN { 0, 250, 154, 255 }
#define CONST_MEDIUM_TURQUOISE { 72, 209, 204, 255 }
#define CONST_MEDIUMTURQUOISE { 72, 209, 204, 255 }
#define CONST_MEDIUM_VIOLET_RED { 199, 21, 133, 255 }
#define CONST_MEDIUMVIOLETRED { 199, 21, 133, 255 }
#define CONST_MIDNIGHT_BLUE { 25, 25, 112, 255 }
#define CONST_MIDNIGHTBLUE { 25, 25, 112, 255 }
#define CONST_MINT_CREAM { 245, 255, 250, 255 }
#define CONST_MINTCREAM { 245, 255, 250, 255 }
#define CONST_MISTYROSE1 { 255, 228, 225, 255 }
#define CONST_MISTYROSE2 { 238, 213, 210, 255 }
#define CONST_MISTYROSE3 { 205, 183, 181, 255 }
#define CONST_MISTYROSE4 { 139, 125, 123, 255 }
#define CONST_MISTY_ROSE { 255, 228, 225, 255 }
#define CONST_MISTYROSE { 255, 228, 225, 255 }
#define CONST_MOCCASIN { 255, 228, 181, 255 }
#define CONST_NAVAJOWHITE1 { 255, 222, 173, 255 }
#define CONST_NAVAJOWHITE2 { 238, 207, 161, 255 }
#define CONST_NAVAJOWHITE3 { 205, 179, 139, 255 }
#define CONST_NAVAJOWHITE4 { 139, 121, 94, 255 }
#define CONST_NAVAJO_WHITE { 255, 222, 173, 255 }
#define CONST_NAVAJOWHITE { 255, 222, 173, 255 }
#define CONST_NAVY_BLUE { 0, 0, 128, 255 }
#define CONST_NAVYBLUE { 0, 0, 128, 255 }
#define CONST_NAVY { 0, 0, 128, 255 }
#define CONST_OLD_LACE { 253, 245, 230, 255 }
#define CONST_OLDLACE { 253, 245, 230, 255 }
#define CONST_OLIVEDRAB1 { 192, 255, 62, 255 }
#define CONST_OLIVEDRAB2 { 179, 238, 58, 255 }
#define CONST_OLIVEDRAB3 { 154, 205, 50, 255 }
#define CONST_OLIVEDRAB4 { 105, 139, 34, 255 }
#define CONST_OLIVE_DRAB { 107, 142, 35, 255 }
#define CONST_OLIVEDRAB { 107, 142, 35, 255 }
#define CONST_LIGHT_ORANGE { 255, 200, 40, 255 }
#define CONST_ORANGE1 { 255, 165, 0, 255 }
#define CONST_ORANGE2 { 238, 154, 0, 255 }
#define CONST_ORANGE3 { 205, 133, 0, 255 }
#define CONST_ORANGE4 { 139, 90, 0, 255 }
#define CONST_ORANGE { 255, 165, 0, 255 }
#define CONST_ORANGERED1 { 255, 69, 0, 255 }
#define CONST_ORANGERED2 { 238, 64, 0, 255 }
#define CONST_ORANGERED3 { 205, 55, 0, 255 }
#define CONST_ORANGERED4 { 139, 37, 0, 255 }
#define CONST_ORANGE_RED { 255, 69, 0, 255 }
#define CONST_ORANGERED { 255, 69, 0, 255 }
#define CONST_ORCHID1 { 255, 131, 250, 255 }
#define CONST_ORCHID2 { 238, 122, 233, 255 }
#define CONST_ORCHID3 { 205, 105, 201, 255 }
#define CONST_ORCHID4 { 139, 71, 137, 255 }
#define CONST_ORCHID { 218, 112, 214, 255 }
#define CONST_PALE_GOLDENROD { 238, 232, 170, 255 }
#define CONST_PALEGOLDENROD { 238, 232, 170, 255 }
#define CONST_PALEGREEN1 { 154, 255, 154, 255 }
#define CONST_PALEGREEN2 { 144, 238, 144, 255 }
#define CONST_PALEGREEN3 { 124, 205, 124, 255 }
#define CONST_PALEGREEN4 { 84, 139, 84, 255 }
#define CONST_PALE_GREEN { 152, 251, 152, 255 }
#define CONST_PALEGREEN { 152, 251, 152, 255 }
#define CONST_PALETURQUOISE1 { 187, 255, 255, 255 }
#define CONST_PALETURQUOISE2 { 174, 238, 238, 255 }
#define CONST_PALETURQUOISE3 { 150, 205, 205, 255 }
#define CONST_PALETURQUOISE4 { 102, 139, 139, 255 }
#define CONST_PALE_TURQUOISE { 175, 238, 238, 255 }
#define CONST_PALETURQUOISE { 175, 238, 238, 255 }
#define CONST_PALEVIOLETRED1 { 255, 130, 171, 255 }
#define CONST_PALEVIOLETRED2 { 238, 121, 159, 255 }
#define CONST_PALEVIOLETRED3 { 205, 104, 137, 255 }
#define CONST_PALEVIOLETRED4 { 139, 71, 93, 255 }
#define CONST_PALE_VIOLET_RED { 219, 112, 147, 255 }
#define CONST_PALEVIOLETRED { 219, 112, 147, 255 }
#define CONST_PAPAYA_WHIP { 255, 239, 213, 255 }
#define CONST_PAPAYAWHIP { 255, 239, 213, 255 }
#define CONST_PEACHPUFF1 { 255, 218, 185, 255 }
#define CONST_PEACHPUFF2 { 238, 203, 173, 255 }
#define CONST_PEACHPUFF3 { 205, 175, 149, 255 }
#define CONST_PEACHPUFF4 { 139, 119, 101, 255 }
#define CONST_PEACH_PUFF { 255, 218, 185, 255 }
#define CONST_PEACHPUFF { 255, 218, 185, 255 }
#define CONST_PERU { 205, 133, 63, 255 }
#define CONST_PINK1 { 255, 181, 197, 255 }
#define CONST_PINK2 { 238, 169, 184, 255 }
#define CONST_PINK3 { 205, 145, 158, 255 }
#define CONST_PINK4 { 139, 99, 108, 255 }
#define CONST_PINK { 255, 192, 203, 255 }
#define CONST_PLUM1 { 255, 187, 255, 255 }
#define CONST_PLUM2 { 238, 174, 238, 255 }
#define CONST_PLUM3 { 205, 150, 205, 255 }
#define CONST_PLUM4 { 139, 102, 139, 255 }
#define CONST_PLUM { 221, 160, 221, 255 }
#define CONST_POWDER_BLUE { 176, 224, 230, 255 }
#define CONST_POWDERBLUE { 176, 224, 230, 255 }
#define CONST_PURPLE1 { 155, 48, 255, 255 }
#define CONST_PURPLE2 { 145, 44, 238, 255 }
#define CONST_PURPLE3 { 125, 38, 205, 255 }
#define CONST_PURPLE4 { 85, 26, 139, 255 }
#define CONST_PURPLE { 160, 32, 240, 255 }
#define CONST_RED1 { 255, 0, 0, 255 }
#define CONST_RED2 { 238, 0, 0, 255 }
#define CONST_RED3 { 205, 0, 0, 255 }
#define CONST_RED4 { 139, 0, 0, 255 }
#define CONST_RED { 255, 0, 0, 255 }
#define CONST_ROSYBROWN1 { 255, 193, 193, 255 }
#define CONST_ROSYBROWN2 { 238, 180, 180, 255 }
#define CONST_ROSYBROWN3 { 205, 155, 155, 255 }
#define CONST_ROSYBROWN4 { 139, 105, 105, 255 }
#define CONST_ROSY_BROWN { 188, 143, 143, 255 }
#define CONST_ROSYBROWN { 188, 143, 143, 255 }
#define CONST_ROYALBLUE1 { 72, 118, 255, 255 }
#define CONST_ROYALBLUE2 { 67, 110, 238, 255 }
#define CONST_ROYALBLUE3 { 58, 95, 205, 255 }
#define CONST_ROYALBLUE4 { 39, 64, 139, 255 }
#define CONST_ROYAL_BLUE { 65, 105, 225, 255 }
#define CONST_ROYALBLUE { 65, 105, 225, 255 }
#define CONST_SADDLE_BROWN { 139, 69, 19, 255 }
#define CONST_SADDLEBROWN { 139, 69, 19, 255 }
#define CONST_SALMON1 { 255, 140, 105, 255 }
#define CONST_SALMON2 { 238, 130, 98, 255 }
#define CONST_SALMON3 { 205, 112, 84, 255 }
#define CONST_SALMON4 { 139, 76, 57, 255 }
#define CONST_SALMON { 250, 128, 114, 255 }
#define CONST_SANDY_BROWN { 244, 164, 96, 255 }
#define CONST_SANDYBROWN { 244, 164, 96, 255 }
#define CONST_SEAGREEN1 { 84, 255, 159, 255 }
#define CONST_SEAGREEN2 { 78, 238, 148, 255 }
#define CONST_SEAGREEN3 { 67, 205, 128, 255 }
#define CONST_SEAGREEN4 { 46, 139, 87, 255 }
#define CONST_SEA_GREEN { 46, 139, 87, 255 }
#define CONST_SEAGREEN { 46, 139, 87, 255 }
#define CONST_SEASHELL1 { 255, 245, 238, 255 }
#define CONST_SEASHELL2 { 238, 229, 222, 255 }
#define CONST_SEASHELL3 { 205, 197, 191, 255 }
#define CONST_SEASHELL4 { 139, 134, 130, 255 }
#define CONST_SEASHELL { 255, 245, 238, 255 }
#define CONST_SIENNA1 { 255, 130, 71, 255 }
#define CONST_SIENNA2 { 238, 121, 66, 255 }
#define CONST_SIENNA3 { 205, 104, 57, 255 }
#define CONST_SIENNA4 { 139, 71, 38, 255 }
#define CONST_SIENNA { 160, 82, 45, 255 }
#define CONST_SKYBLUE1 { 135, 206, 255, 255 }
#define CONST_SKYBLUE2 { 126, 192, 238, 255 }
#define CONST_SKYBLUE3 { 108, 166, 205, 255 }
#define CONST_SKYBLUE4 { 74, 112, 139, 255 }
#define CONST_SKY_BLUE { 135, 206, 235, 255 }
#define CONST_SKYBLUE { 135, 206, 235, 255 }
#define CONST_SLATEBLUE1 { 131, 111, 255, 255 }
#define CONST_SLATEBLUE2 { 122, 103, 238, 255 }
#define CONST_SLATEBLUE3 { 105, 89, 205, 255 }
#define CONST_SLATEBLUE4 { 71, 60, 139, 255 }
#define CONST_SLATE_BLUE { 106, 90, 205, 255 }
#define CONST_SLATEBLUE { 106, 90, 205, 255 }
#define CONST_SLATEGRAY1 { 198, 226, 255, 255 }
#define CONST_SLATEGRAY2 { 185, 211, 238, 255 }
#define CONST_SLATEGRAY3 { 159, 182, 205, 255 }
#define CONST_SLATEGRAY4 { 108, 123, 139, 255 }
#define CONST_SLATE_GRAY { 112, 128, 144, 255 }
#define CONST_SLATEGRAY { 112, 128, 144, 255 }
#define CONST_SLATE_GREY { 112, 128, 144, 255 }
#define CONST_SLATEGREY { 112, 128, 144, 255 }
#define CONST_SNOW1 { 255, 250, 250, 255 }
#define CONST_SNOW2 { 238, 233, 233, 255 }
#define CONST_SNOW3 { 205, 201, 201, 255 }
#define CONST_SNOW4 { 139, 137, 137, 255 }
#define CONST_SNOW { 255, 250, 250, 255 }
#define CONST_SPRINGGREEN1 { 0, 255, 127, 255 }
#define CONST_SPRINGGREEN2 { 0, 238, 118, 255 }
#define CONST_SPRINGGREEN3 { 0, 205, 102, 255 }
#define CONST_SPRINGGREEN4 { 0, 139, 69, 255 }
#define CONST_SPRING_GREEN { 0, 255, 127, 255 }
#define CONST_SPRINGGREEN { 0, 255, 127, 255 }
#define CONST_STEELBLUE1 { 99, 184, 255, 255 }
#define CONST_STEELBLUE2 { 92, 172, 238, 255 }
#define CONST_STEELBLUE3 { 79, 148, 205, 255 }
#define CONST_STEELBLUE4 { 54, 100, 139, 255 }
#define CONST_STEEL_BLUE { 70, 130, 180, 255 }
#define CONST_STEELBLUE { 70, 130, 180, 255 }
#define CONST_TAN1 { 255, 165, 79, 255 }
#define CONST_TAN2 { 238, 154, 73, 255 }
#define CONST_TAN3 { 205, 133, 63, 255 }
#define CONST_TAN4 { 139, 90, 43, 255 }
#define CONST_TAN { 210, 180, 140, 255 }
#define CONST_THISTLE1 { 255, 225, 255, 255 }
#define CONST_THISTLE2 { 238, 210, 238, 255 }
#define CONST_THISTLE3 { 205, 181, 205, 255 }
#define CONST_THISTLE4 { 139, 123, 139, 255 }
#define CONST_THISTLE { 216, 191, 216, 255 }
#define CONST_TOMATO1 { 255, 99, 71, 255 }
#define CONST_TOMATO2 { 238, 92, 66, 255 }
#define CONST_TOMATO3 { 205, 79, 57, 255 }
#define CONST_TOMATO4 { 139, 54, 38, 255 }
#define CONST_TOMATO { 255, 99, 71, 255 }
#define CONST_TURQUOISE1 { 0, 245, 255, 255 }
#define CONST_TURQUOISE2 { 0, 229, 238, 255 }
#define CONST_TURQUOISE3 { 0, 197, 205, 255 }
#define CONST_TURQUOISE4 { 0, 134, 139, 255 }
#define CONST_TURQUOISE { 64, 224, 208, 255 }
#define CONST_VIOLET { 238, 130, 238, 255 }
#define CONST_VIOLETRED1 { 255, 62, 150, 255 }
#define CONST_VIOLETRED2 { 238, 58, 140, 255 }
#define CONST_VIOLETRED3 { 205, 50, 120, 255 }
#define CONST_VIOLETRED4 { 139, 34, 82, 255 }
#define CONST_VIOLET_RED { 208, 32, 144, 255 }
#define CONST_VIOLETRED { 208, 32, 144, 255 }
#define CONST_WHEAT1 { 255, 231, 186, 255 }
#define CONST_WHEAT2 { 238, 216, 174, 255 }
#define CONST_WHEAT3 { 205, 186, 150, 255 }
#define CONST_WHEAT4 { 139, 126, 102, 255 }
#define CONST_WHEAT { 245, 222, 179, 255 }
#define CONST_WHITE { 255, 255, 255, 255 }
#define CONST_WHITE_SMOKE { 245, 245, 245, 255 }
#define CONST_WHITESMOKE { 245, 245, 245, 255 }
#define CONST_YELLOW1 { 255, 255, 0, 255 }
#define CONST_YELLOW2 { 238, 238, 0, 255 }
#define CONST_YELLOW3 { 205, 205, 0, 255 }
#define CONST_YELLOW4 { 139, 139, 0, 255 }
#define CONST_YELLOW_GREEN { 154, 205, 50, 255 }
#define CONST_YELLOWGREEN { 154, 205, 50, 255 }
#define CONST_YELLOW { 255, 255, 0, 255 }
#define CONST_INK { 51, 54, 47, 47 }
#endif // _MY_COLOR_H_
