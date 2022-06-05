//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_MY_COLOR_HPP_
#define _MY_MY_COLOR_HPP_

#include <string>

class color
{
public:
  unsigned char r {};
  unsigned char g {};
  unsigned char b {};
  unsigned char a {};

  color(void) : r(0), g(0), b(0), a(0) {}

  color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}

  color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

  color(const color &c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

  friend color operator+(color c, color b) { return (color(c.r + b.r, c.g + b.g, c.b + b.b, c.a + b.a)); }

  friend color operator-(color c, color b) { return (color(c.r - b.r, c.g - b.g, c.b - b.b, c.a - b.a)); }

  friend color operator/(color c, color b) { return (color(c.r / b.r, c.g / b.g, c.b / b.b, c.a / b.a)); }

  friend color operator*(color c, color b) { return (color(c.r * b.r, c.g * b.g, c.b * b.b, c.a * b.a)); }

  friend color operator/(color c, unsigned char b) { return (color(c.r / b, c.g / b, c.b / b, c.a / b)); }

  void operator*=(unsigned char c)
  {
    r *= c;
    g *= c;
    b *= c;
    a *= c;
  }

  void operator/=(unsigned char c)
  {
    r /= c;
    g /= c;
    b /= c;
    a /= c;
  }

  friend bool operator==(const color &c, const color &b)
  {
    return (c.r == b.r) && (c.g == b.g) && (c.b == b.b) && (c.a == b.a);
  }

  friend bool operator!=(const color &c, const color &b) { return (! (c == b)); }
};

extern color AQUAMARINE;
extern color AQUAMARINE1;
extern color AQUAMARINE2;
extern color AQUAMARINE3;
extern color AQUAMARINE4;
extern color AZURE;
extern color AZURE1;
extern color AZURE2;
extern color AZURE3;
extern color AZURE4;
extern color BEIGE;
extern color BISQUE;
extern color BISQUE1;
extern color BISQUE2;
extern color BISQUE3;
extern color BISQUE4;
extern color BLACK;
extern color BLANCHEDALMOND;
extern color BLUE;
extern color BLUE1;
extern color BLUE2;
extern color BLUE3;
extern color BLUE4;
extern color BLUE_VIOLET;
extern color BLUEVIOLET;
extern color BROWN;
extern color BROWN1;
extern color BROWN2;
extern color BROWN3;
extern color BROWN4;
extern color BURLYWOOD;
extern color BURLYWOOD1;
extern color BURLYWOOD2;
extern color BURLYWOOD3;
extern color BURLYWOOD4;
extern color CADET_BLUE;
extern color CADETBLUE;
extern color CADETBLUE1;
extern color CADETBLUE2;
extern color CADETBLUE3;
extern color CADETBLUE4;
extern color CHARTREUSE;
extern color CHARTREUSE1;
extern color CHARTREUSE2;
extern color CHARTREUSE3;
extern color CHARTREUSE4;
extern color CHOCOLATE;
extern color CHOCOLATE1;
extern color CHOCOLATE2;
extern color CHOCOLATE3;
extern color CHOCOLATE4;
extern color COLOR_NONE;
extern color CORAL;
extern color CORAL1;
extern color CORAL2;
extern color CORAL3;
extern color CORAL4;
extern color CORNFLOWER_BLUE;
extern color CORNFLOWERBLUE;
extern color CORNSILK;
extern color CORNSILK1;
extern color CORNSILK2;
extern color CORNSILK3;
extern color CORNSILK4;
extern color CYAN;
extern color CYAN1;
extern color CYAN2;
extern color CYAN3;
extern color CYAN4;
extern color DARKBLUE;
extern color DARKCYAN;
extern color DARKGRAY;
extern color DARKGREEN;
extern color DARKGREY;
extern color DARKKHAKI;
extern color DARKMAGENTA;
extern color DARKOLIVEGREEN;
extern color DARKOLIVEGREEN1;
extern color DARKOLIVEGREEN2;
extern color DARKOLIVEGREEN3;
extern color DARKOLIVEGREEN4;
extern color DARKORANGE;
extern color DARKORANGE1;
extern color DARKORANGE2;
extern color DARKORANGE3;
extern color DARKORANGE4;
extern color DARKRED;
extern color DARKSEAGREEN;
extern color DARKSEAGREEN1;
extern color DARKSEAGREEN2;
extern color DARKSEAGREEN3;
extern color DARKSEAGREEN4;
extern color DARKSLATEBLUE;
extern color DARKSLATEGRAY;
extern color DARKSLATEGRAY1;
extern color DARKSLATEGRAY2;
extern color DARKSLATEGRAY3;
extern color DARKSLATEGRAY4;
extern color DARKSLATEGREY;
extern color DARKSLATEGREY1;
extern color DARKSLATEGREY2;
extern color DARKSLATEGREY3;
extern color DARKSLATEGREY4;
extern color DARKTURQUOISE;
extern color DARKVIOLET;
extern color DEEPBLUE;
extern color DEEPBLUE2;
extern color DEEP_PINK;
extern color DEEPPINK;
extern color DEEPPINK1;
extern color DEEPPINK2;
extern color DEEPPINK3;
extern color DEEPPINK4;
extern color DEEPSKYBLUE;
extern color DEEPSKYBLUE1;
extern color DEEPSKYBLUE2;
extern color DEEPSKYBLUE3;
extern color DEEPSKYBLUE4;
extern color DIM_GRAY;
extern color DIMGRAY;
extern color DIM_GREY;
extern color DIMGREY;
extern color DODGER_BLUE;
extern color DODGERBLUE;
extern color DODGERBLUE1;
extern color DODGERBLUE2;
extern color DODGERBLUE3;
extern color DODGERBLUE4;
extern color FIREBRICK;
extern color FIREBRICK1;
extern color FIREBRICK2;
extern color FIREBRICK3;
extern color FIREBRICK4;
extern color FLORAL_WHITE;
extern color FLORALWHITE;
extern color FOREST_GREEN;
extern color FORESTGREEN;
extern color GAINSBORO;
extern color GHOST_WHITE;
extern color GHOSTWHITE;
extern color GOLD;
extern color GOLD1;
extern color GOLD2;
extern color GOLD3;
extern color GOLD4;
extern color GRAY;
extern color GRAY1;
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
extern color GRAY2;
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
extern color GRAY3;
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
extern color GRAY4;
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
extern color GRAY5;
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
extern color GRAY6;
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
extern color GRAY7;
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
extern color GRAY8;
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
extern color GRAY9;
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
extern color GREEN;
extern color GREEN1;
extern color GREEN2;
extern color GREEN3;
extern color GREEN4;
extern color GREEN_YELLOW;
extern color GREENYELLOW;
extern color GREY;
extern color GREY1;
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
extern color GREY2;
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
extern color GREY3;
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
extern color GREY4;
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
extern color GREY5;
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
extern color GREY6;
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
extern color GREY7;
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
extern color GREY8;
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
extern color GREY9;
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
extern color HOT_PINK;
extern color HOTPINK;
extern color HOTPINK1;
extern color HOTPINK2;
extern color HOTPINK3;
extern color HOTPINK4;
extern color INDIAN_RED;
extern color INDIANRED;
extern color INDIANRED1;
extern color INDIANRED2;
extern color INDIANRED3;
extern color INDIANRED4;
extern color IVORY;
extern color IVORY1;
extern color IVORY2;
extern color IVORY3;
extern color IVORY4;
extern color KHAKI;
extern color KHAKI1;
extern color KHAKI2;
extern color KHAKI3;
extern color KHAKI4;
extern color LAVA;
extern color LAVENDER;
extern color LEMON_CHIFFON;
extern color LEMONCHIFFON;
extern color LEMONCHIFFON;
extern color WATER;
extern color DEEPWATER;
extern color LEMONCHIFFON1;
extern color LEMONCHIFFON2;
extern color LEMONCHIFFON3;
extern color LEMONCHIFFON4;
extern color LIGHTBLUE;
extern color LIGHTBLUE1;
extern color LIGHTBLUE2;
extern color LIGHTBLUE3;
extern color LIGHTBLUE4;
extern color LIGHTCORAL;
extern color LIGHTCYAN;
extern color LIGHTCYAN1;
extern color LIGHTCYAN2;
extern color LIGHTCYAN3;
extern color LIGHTCYAN4;
extern color LIGHTGRAY;
extern color LIGHTGREEN;
extern color LIGHTGREY;
extern color LIGHTPINK;
extern color LIGHTPINK1;
extern color LIGHTPINK2;
extern color LIGHTPINK3;
extern color LIGHTPINK4;
extern color LIGHTSEAGREEN;
extern color LIGHTSKYBLUE;
extern color LIGHTSKYBLUE1;
extern color LIGHTSKYBLUE2;
extern color LIGHTSKYBLUE3;
extern color LIGHTSKYBLUE4;
extern color LIGHTSLATEBLUE;
extern color LIGHTSLATEGRAY;
extern color LIGHTSLATEGREY;
extern color LIGHTSTEELBLUE;
extern color LIGHTSTEELBLUE1;
extern color LIGHTSTEELBLUE2;
extern color LIGHTSTEELBLUE3;
extern color LIGHTSTEELBLUE4;
extern color LIGHTYELLOW;
extern color LIGHTYELLOW1;
extern color LIGHTYELLOW2;
extern color LIGHTYELLOW3;
extern color LIGHTYELLOW4;
extern color LIME;
extern color LIMEGREEN;
extern color LINEN;
extern color MAGENTA;
extern color MAGENTA1;
extern color MAGENTA2;
extern color MAGENTA3;
extern color MAGENTA4;
extern color MAROON;
extern color MAROON1;
extern color MAROON2;
extern color MAROON3;
extern color MAROON4;
extern color MEDIUMAQUAMARINE;
extern color MEDIUMBLUE;
extern color MEDIUMPURPLE;
extern color MEDIUMPURPLE1;
extern color MEDIUMPURPLE2;
extern color MEDIUMPURPLE3;
extern color MEDIUMPURPLE4;
extern color MEDIUMSEAGREEN;
extern color MEDIUMSLATEBLUE;
extern color MEDIUMSPRINGGREEN;
extern color MEDIUMTURQUOISE;
extern color MEDIUMVIOLETRED;
extern color MIDNIGHTBLUE;
extern color MINTCREAM;
extern color MOCCASIN;
extern color NAVY;
extern color NAVYBLUE;
extern color OLIVE_DRAB;
extern color OLIVEDRAB;
extern color OLIVEDRAB1;
extern color OLIVEDRAB2;
extern color OLIVEDRAB3;
extern color OLIVEDRAB4;
extern color ORANGE;
extern color ORANGE1;
extern color ORANGE2;
extern color ORANGE3;
extern color ORANGE4;
extern color ORANGERED;
extern color ORANGERED1;
extern color ORANGERED2;
extern color ORANGERED3;
extern color ORANGERED4;
extern color PALEBLUE;
extern color PALEBLUE2;
extern color PALEGREEN;
extern color PALEGREEN1;
extern color PALEGREEN2;
extern color PALEGREEN3;
extern color PALEGREEN4;
extern color PALETURQUOISE;
extern color PALETURQUOISE1;
extern color PALETURQUOISE2;
extern color PALETURQUOISE3;
extern color PALETURQUOISE4;
extern color PALEVIOLETRED;
extern color PALEVIOLETRED1;
extern color PALEVIOLETRED2;
extern color PALEVIOLETRED3;
extern color PALEVIOLETRED4;
extern color PEACHPUFF;
extern color PEACHPUFF1;
extern color PEACHPUFF2;
extern color PEACHPUFF3;
extern color PEACHPUFF4;
extern color PERU;
extern color PINK;
extern color PINK1;
extern color PINK2;
extern color PINK3;
extern color PINK4;
extern color PLUM;
extern color PLUM1;
extern color PLUM2;
extern color PLUM3;
extern color PLUM4;
extern color POWDERBLUE;
extern color PURPLE;
extern color PURPLE1;
extern color PURPLE2;
extern color PURPLE3;
extern color PURPLE4;
extern color RED;
extern color RED1;
extern color RED2;
extern color RED3;
extern color RED4;
extern color SADDLE_BROWN;
extern color SADDLEBROWN;
extern color SEAGREEN;
extern color SEAGREEN1;
extern color SEAGREEN2;
extern color SEAGREEN3;
extern color SEAGREEN4;
extern color SIENNA;
extern color SIENNA1;
extern color SIENNA2;
extern color SIENNA3;
extern color SIENNA4;
extern color SKYBLUE;
extern color SKYBLUE1;
extern color SKYBLUE2;
extern color SKYBLUE3;
extern color SKYBLUE4;
extern color SLATEBLUE;
extern color SLATEBLUE1;
extern color SLATEBLUE2;
extern color SLATEBLUE3;
extern color SLATEBLUE4;
extern color SLATEGRAY;
extern color SLATEGRAY1;
extern color SLATEGRAY2;
extern color SLATEGRAY3;
extern color SLATEGRAY4;
extern color SLATEGREY;
extern color SLATEGREY1;
extern color SLATEGREY2;
extern color SLATEGREY3;
extern color SLATEGREY4;
extern color SNOW;
extern color SNOW1;
extern color SNOW2;
extern color SNOW3;
extern color SNOW4;
extern color SPRINGGREEN;
extern color SPRINGGREEN1;
extern color SPRINGGREEN2;
extern color SPRINGGREEN3;
extern color SPRINGGREEN4;
extern color STEELBLUE;
extern color STEELBLUE1;
extern color STEELBLUE2;
extern color STEELBLUE3;
extern color STEELBLUE4;
extern color TAN;
extern color TAN1;
extern color TAN2;
extern color TAN3;
extern color TAN4;
extern color THISTLE;
extern color THISTLE1;
extern color THISTLE2;
extern color THISTLE3;
extern color THISTLE4;
extern color TOMATO;
extern color TOMATO1;
extern color TOMATO2;
extern color TOMATO3;
extern color TOMATO4;
extern color TURQUOISE;
extern color TURQUOISE1;
extern color TURQUOISE2;
extern color TURQUOISE3;
extern color TURQUOISE4;
extern color VDARKSLATEBLUE;
extern color VIOLET;
extern color VIOLETRED;
extern color VIOLETRED1;
extern color VIOLETRED2;
extern color VIOLETRED3;
extern color VIOLETRED4;
extern color VVDARKSLATEBLUE;
extern color WHITE;
extern color WHITE_SMOKE;
extern color WHITESMOKE;
extern color YELLOW;
extern color YELLOW1;
extern color YELLOW2;
extern color YELLOW3;
extern color YELLOW4;
extern color YELLOWGREEN;

extern color gl_last_color;
extern color gl_save_color;

color color_find(const char *s);
color color_to_mono(color a);
color gl_color_current(void);
color string2color(const char **s);
color string2color(const wchar_t **s);
color string2color(std::string &s);
color string2color(std::string &s, int *len);
color string2color(std::wstring &s, int *len);
color color_change_hue(const color &in, const float fHue);

const char *string2colorname(const char **s);

std::string string2colorname(std::string &s);

void color_fini(void);
void color_init(void);
void color_init1(void);
void color_init2(void);
void color_init3(void);
void color_init4(void);
void color_set(std::string name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void glcolor_restore(void);
void glcolor_save(void);

#endif // _MY_COLOR_HPP_
