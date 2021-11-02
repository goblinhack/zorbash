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

#ifdef unused_flag
  friend std::ostream &operator<<(std::ostream &out, Bits< const color & > const my)
  {
    out << bits(my.t.r) << bits(my.t.g) << bits(my.t.b) << bits(my.t.a);
    return (out);
  }

  friend std::istream &operator>>(std::istream &in, Bits< color & > my)
  {
    in >> bits(my.t.r) >> bits(my.t.g) >> bits(my.t.b) >> bits(my.t.a);
    return (in);
  }

  friend std::ostream &operator<<(std::ostream &out, const color &my)
  {
    out << "(" << my.r << ", " << my.g << ", " << my.b << ", " << my.a << ")";
    return (out);
  }

  void operator+=(color c)
  {
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
  }

  void operator-=(color c)
  {
    c -= c.r;
    c -= c.g;
    c -= c.b;
    a -= c.a;
  }

  friend color operator+(color c, color b) { return (color(c.r + b.r, c.g + b.g, c.b + b.b, c.a + b.a)); }

  friend color operator-(color c, color b) { return (color(c.r - b.r, c.g - b.g, c.b - b.b, c.a - b.a)); }

  friend color operator/(color c, color b) { return (color(c.r / b.r, c.g / b.g, c.b / b.b, c.a / b.a)); }

  friend color operator*(color c, color b) { return (color(c.r * b.r, c.g * b.g, c.b * b.b, c.a * b.a)); }

  friend color operator/(color c, T b) { return (color(c.r / b, c.g / b, c.b / b, c.a / b)); }

  void operator*=(T c)
  {
    r *= c;
    g *= c;
    b *= c;
    a *= c;
  }

  void operator/=(T c)
  {
    r /= c;
    g /= c;
    b /= c;
    a /= c;
  }
#endif

  friend bool operator==(const color &c, const color &b)
  {
    return (c.r == b.r) && (c.g == b.g) && (c.b == b.b) && (c.a == b.a);
  }

  friend bool operator!=(const color &c, const color &b) { return (! (c == b)); }
};

#if 0
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
extern color BLANCHEDALMOND;
extern color BLUE_VIOLET;
extern color BLUEVIOLET;
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
extern color DARKCYAN;
extern color DARKKHAKI;
extern color DARKMAGENTA;
extern color DARKOLIVEGREEN1;
extern color DARKOLIVEGREEN2;
extern color DARKOLIVEGREEN3;
extern color DARKOLIVEGREEN4;
extern color DARKOLIVEGREEN;
extern color DARKORANGE1;
extern color DARKORANGE2;
extern color DARKORANGE3;
extern color DARKORANGE4;
extern color DARKORANGE;
extern color DARKSEAGREEN1;
extern color DARKSEAGREEN2;
extern color DARKSEAGREEN3;
extern color DARKSEAGREEN4;
extern color DARKSEAGREEN;
extern color DARKSLATEBLUE;
extern color DARKSLATEBLUE;
extern color VDARKSLATEBLUE;
extern color VVDARKSLATEBLUE;
extern color DARKSLATEGRAY1;
extern color DARKSLATEGRAY2;
extern color DARKSLATEGRAY3;
extern color DARKSLATEGRAY4;
extern color DARKSLATEGRAY;
extern color DARKTURQUOISE;
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
extern color DEEPSKYBLUE;
extern color DIM_GRAY;
extern color DIMGRAY;
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
extern color GAINSBORO;
extern color GHOST_WHITE;
extern color GHOSTWHITE;
extern color GOLD1;
extern color GOLD2;
extern color GOLD3;
extern color GOLD4;
extern color GOLD;
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
extern color GRAY32;
extern color GRAY33;
extern color GRAY34;
extern color GRAY35;
extern color GRAY36;
extern color GRAY37;
extern color GRAY38;
extern color GRAY39;
extern color GRAY3;
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
extern color GREEN1;
extern color GREEN2;
extern color GREEN3;
extern color GREEN4;
extern color GREEN_YELLOW;
extern color GREENYELLOW;
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
extern color LAVENDER;
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
extern color LIGHTCORAL;
extern color LIGHTCYAN1;
extern color LIGHTCYAN2;
extern color LIGHTCYAN3;
extern color LIGHTCYAN4;
extern color LIGHTCYAN;
extern color LIGHTGRAY;
extern color LIGHTGREEN;
extern color LIGHTPINK1;
extern color LIGHTPINK2;
extern color LIGHTPINK3;
extern color LIGHTPINK4;
extern color LIGHTPINK;
extern color LIGHTSEAGREEN;
extern color LIGHTSKYBLUE1;
extern color LIGHTSKYBLUE2;
extern color LIGHTSKYBLUE3;
extern color LIGHTSKYBLUE4;
extern color LIGHTSKYBLUE;
extern color LIGHTSLATEBLUE;
extern color LIGHTSLATEGRAY;
extern color LIGHTSTEELBLUE1;
extern color LIGHTSTEELBLUE2;
extern color LIGHTSTEELBLUE3;
extern color LIGHTSTEELBLUE4;
extern color LIGHTSTEELBLUE;
extern color LIGHTYELLOW1;
extern color LIGHTYELLOW2;
extern color LIGHTYELLOW3;
extern color LIGHTYELLOW4;
extern color LIGHTYELLOW;
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
extern color MEDIUMAQUAMARINE;
extern color MEDIUMBLUE;
extern color MEDIUMPURPLE1;
extern color MEDIUMPURPLE2;
extern color MEDIUMPURPLE3;
extern color MEDIUMPURPLE4;
extern color MEDIUMPURPLE;
extern color MEDIUMSEAGREEN;
extern color MEDIUMSLATEBLUE;
extern color MEDIUMSPRINGGREEN;
extern color MEDIUMTURQUOISE;
extern color MEDIUMVIOLETRED;
extern color MIDNIGHTBLUE;
extern color MINTCREAM;
extern color MOCCASIN;
extern color NAVYBLUE;
extern color NAVY;
extern color OLIVEDRAB1;
extern color OLIVEDRAB2;
extern color OLIVEDRAB3;
extern color OLIVEDRAB4;
extern color OLIVE_DRAB;
extern color OLIVEDRAB;
extern color ORANGE1;
extern color ORANGE2;
extern color ORANGE3;
extern color ORANGE4;
extern color ORANGERED1;
extern color ORANGERED2;
extern color ORANGERED3;
extern color ORANGERED4;
extern color ORANGERED;
extern color PALEGREEN1;
extern color PALEGREEN2;
extern color PALEGREEN3;
extern color PALEGREEN4;
extern color PALEGREEN;
extern color PALETURQUOISE1;
extern color PALETURQUOISE2;
extern color PALETURQUOISE3;
extern color PALETURQUOISE4;
extern color PALETURQUOISE;
extern color PALEVIOLETRED1;
extern color PALEVIOLETRED2;
extern color PALEVIOLETRED3;
extern color PALEVIOLETRED4;
extern color PALEVIOLETRED;
extern color PEACHPUFF1;
extern color PEACHPUFF2;
extern color PEACHPUFF3;
extern color PEACHPUFF4;
extern color PEACHPUFF;
extern color PERU;
extern color PINK1;
extern color PINK2;
extern color PINK3;
extern color PINK4;
extern color PLUM1;
extern color PLUM2;
extern color PLUM3;
extern color PLUM4;
extern color PLUM;
extern color POWDERBLUE;
extern color PURPLE1;
extern color PURPLE2;
extern color PURPLE3;
extern color PURPLE4;
extern color RED1;
extern color RED2;
extern color RED3;
extern color RED4;
extern color SADDLE_BROWN;
extern color SADDLEBROWN;
extern color SEAGREEN1;
extern color SEAGREEN2;
extern color SEAGREEN3;
extern color SEAGREEN4;
extern color SEAGREEN;
extern color SIENNA1;
extern color SIENNA2;
extern color SIENNA3;
extern color SIENNA4;
extern color SIENNA;
extern color SKYBLUE1;
extern color SKYBLUE2;
extern color SKYBLUE3;
extern color SKYBLUE4;
extern color SKYBLUE;
extern color SLATEBLUE1;
extern color SLATEBLUE2;
extern color SLATEBLUE3;
extern color SLATEBLUE4;
extern color SLATEBLUE;
extern color SLATEGRAY1;
extern color SLATEGRAY2;
extern color SLATEGRAY3;
extern color SLATEGRAY4;
extern color SLATEGRAY;
extern color SNOW1;
extern color SNOW2;
extern color SNOW3;
extern color SNOW4;
extern color SNOW;
extern color SPRINGGREEN1;
extern color SPRINGGREEN2;
extern color SPRINGGREEN3;
extern color SPRINGGREEN4;
extern color SPRINGGREEN;
extern color STEELBLUE1;
extern color STEELBLUE2;
extern color STEELBLUE3;
extern color STEELBLUE4;
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
extern color VIOLETRED;
extern color WHITE_SMOKE;
extern color WHITESMOKE;
extern color YELLOW1;
extern color YELLOW2;
extern color YELLOW3;
extern color YELLOW4;
extern color YELLOWGREEN;

#define CONST_ALICEBLUE                                                                                              \
  {                                                                                                                  \
    240, 248, 255, 255                                                                                               \
  }
#define CONST_ANTIQUEWHITE1                                                                                          \
  {                                                                                                                  \
    255, 239, 219, 255                                                                                               \
  }
#define CONST_ANTIQUEWHITE2                                                                                          \
  {                                                                                                                  \
    238, 223, 204, 255                                                                                               \
  }
#define CONST_ANTIQUEWHITE3                                                                                          \
  {                                                                                                                  \
    205, 192, 176, 255                                                                                               \
  }
#define CONST_ANTIQUEWHITE4                                                                                          \
  {                                                                                                                  \
    139, 131, 120, 255                                                                                               \
  }
#define CONST_ANTIQUEWHITE                                                                                           \
  {                                                                                                                  \
    250, 235, 215, 255                                                                                               \
  }
#define CONST_AQUAMARINE1                                                                                            \
  {                                                                                                                  \
    127, 255, 212, 255                                                                                               \
  }
#define CONST_AQUAMARINE2                                                                                            \
  {                                                                                                                  \
    118, 238, 198, 255                                                                                               \
  }
#define CONST_AQUAMARINE3                                                                                            \
  {                                                                                                                  \
    102, 205, 170, 255                                                                                               \
  }
#define CONST_AQUAMARINE4                                                                                            \
  {                                                                                                                  \
    69, 139, 116, 255                                                                                                \
  }
#define CONST_AQUAMARINE                                                                                             \
  {                                                                                                                  \
    127, 255, 212, 255                                                                                               \
  }
#define CONST_AZURE1                                                                                                 \
  {                                                                                                                  \
    240, 255, 255, 255                                                                                               \
  }
#define CONST_AZURE2                                                                                                 \
  {                                                                                                                  \
    224, 238, 238, 255                                                                                               \
  }
#define CONST_AZURE3                                                                                                 \
  {                                                                                                                  \
    193, 205, 205, 255                                                                                               \
  }
#define CONST_AZURE4                                                                                                 \
  {                                                                                                                  \
    131, 139, 139, 255                                                                                               \
  }
#define CONST_AZURE                                                                                                  \
  {                                                                                                                  \
    240, 255, 255, 255                                                                                               \
  }
#define CONST_BEIGE                                                                                                  \
  {                                                                                                                  \
    245, 245, 220, 255                                                                                               \
  }
#define CONST_BISQUE1                                                                                                \
  {                                                                                                                  \
    255, 228, 196, 255                                                                                               \
  }
#define CONST_BISQUE2                                                                                                \
  {                                                                                                                  \
    238, 213, 183, 255                                                                                               \
  }
#define CONST_BISQUE3                                                                                                \
  {                                                                                                                  \
    205, 183, 158, 255                                                                                               \
  }
#define CONST_BISQUE4                                                                                                \
  {                                                                                                                  \
    139, 125, 107, 255                                                                                               \
  }
#define CONST_BISQUE                                                                                                 \
  {                                                                                                                  \
    255, 228, 196, 255                                                                                               \
  }
#define CONST_BLACK                                                                                                  \
  {                                                                                                                  \
    0, 0, 0, 255                                                                                                     \
  }
#define CONST_NONE                                                                                                   \
  {                                                                                                                  \
    0, 0, 0, 0                                                                                                       \
  }
#define CONST_BLANCHEDALMOND                                                                                         \
  {                                                                                                                  \
    255, 235, 205, 255                                                                                               \
  }
#define CONST_BLUE1                                                                                                  \
  {                                                                                                                  \
    0, 0, 255, 255                                                                                                   \
  }
#define CONST_BLUE2                                                                                                  \
  {                                                                                                                  \
    0, 0, 238, 255                                                                                                   \
  }
#define CONST_BLUE3                                                                                                  \
  {                                                                                                                  \
    0, 0, 205, 255                                                                                                   \
  }
#define CONST_BLUE4                                                                                                  \
  {                                                                                                                  \
    0, 0, 139, 255                                                                                                   \
  }
#define CONST_BLUE                                                                                                   \
  {                                                                                                                  \
    0, 0, 255, 255                                                                                                   \
  }
#define CONST_BLUEVIOLET                                                                                             \
  {                                                                                                                  \
    138, 43, 226, 255                                                                                                \
  }
#define CONST_BROWN1                                                                                                 \
  {                                                                                                                  \
    255, 64, 64, 255                                                                                                 \
  }
#define CONST_BROWN2                                                                                                 \
  {                                                                                                                  \
    238, 59, 59, 255                                                                                                 \
  }
#define CONST_BROWN3                                                                                                 \
  {                                                                                                                  \
    205, 51, 51, 255                                                                                                 \
  }
#define CONST_BROWN4                                                                                                 \
  {                                                                                                                  \
    139, 35, 35, 255                                                                                                 \
  }
#define CONST_BROWN                                                                                                  \
  {                                                                                                                  \
    165, 42, 42, 255                                                                                                 \
  }
#define CONST_BURLYWOOD1                                                                                             \
  {                                                                                                                  \
    255, 211, 155, 255                                                                                               \
  }
#define CONST_BURLYWOOD2                                                                                             \
  {                                                                                                                  \
    238, 197, 145, 255                                                                                               \
  }
#define CONST_BURLYWOOD3                                                                                             \
  {                                                                                                                  \
    205, 170, 125, 255                                                                                               \
  }
#define CONST_BURLYWOOD4                                                                                             \
  {                                                                                                                  \
    139, 115, 85, 255                                                                                                \
  }
#define CONST_BURLYWOOD                                                                                              \
  {                                                                                                                  \
    222, 184, 135, 255                                                                                               \
  }
#define CONST_CADETBLUE1                                                                                             \
  {                                                                                                                  \
    152, 245, 255, 255                                                                                               \
  }
#define CONST_CADETBLUE2                                                                                             \
  {                                                                                                                  \
    142, 229, 238, 255                                                                                               \
  }
#define CONST_CADETBLUE3                                                                                             \
  {                                                                                                                  \
    122, 197, 205, 255                                                                                               \
  }
#define CONST_CADETBLUE4                                                                                             \
  {                                                                                                                  \
    83, 134, 139, 255                                                                                                \
  }
#define CONST_CADETBLUE                                                                                              \
  {                                                                                                                  \
    95, 158, 160, 255                                                                                                \
  }
#define CONST_CHARTREUSE1                                                                                            \
  {                                                                                                                  \
    127, 255, 0, 255                                                                                                 \
  }
#define CONST_CHARTREUSE2                                                                                            \
  {                                                                                                                  \
    118, 238, 0, 255                                                                                                 \
  }
#define CONST_CHARTREUSE3                                                                                            \
  {                                                                                                                  \
    102, 205, 0, 255                                                                                                 \
  }
#define CONST_CHARTREUSE4                                                                                            \
  {                                                                                                                  \
    69, 139, 0, 255                                                                                                  \
  }
#define CONST_CHARTREUSE                                                                                             \
  {                                                                                                                  \
    127, 255, 0, 255                                                                                                 \
  }
#define CONST_CHOCOLATE1                                                                                             \
  {                                                                                                                  \
    255, 127, 36, 255                                                                                                \
  }
#define CONST_CHOCOLATE2                                                                                             \
  {                                                                                                                  \
    238, 118, 33, 255                                                                                                \
  }
#define CONST_CHOCOLATE3                                                                                             \
  {                                                                                                                  \
    205, 102, 29, 255                                                                                                \
  }
#define CONST_CHOCOLATE4                                                                                             \
  {                                                                                                                  \
    139, 69, 19, 255                                                                                                 \
  }
#define CONST_CHOCOLATE                                                                                              \
  {                                                                                                                  \
    210, 105, 30, 255                                                                                                \
  }
#define CONST_CORAL1                                                                                                 \
  {                                                                                                                  \
    255, 114, 86, 255                                                                                                \
  }
#define CONST_CORAL2                                                                                                 \
  {                                                                                                                  \
    238, 106, 80, 255                                                                                                \
  }
#define CONST_CORAL3                                                                                                 \
  {                                                                                                                  \
    205, 91, 69, 255                                                                                                 \
  }
#define CONST_CORAL4                                                                                                 \
  {                                                                                                                  \
    139, 62, 47, 255                                                                                                 \
  }
#define CONST_CORAL                                                                                                  \
  {                                                                                                                  \
    255, 127, 80, 255                                                                                                \
  }
#define CONST_CORNFLOWERBLUE                                                                                         \
  {                                                                                                                  \
    100, 149, 237, 255                                                                                               \
  }
#define CONST_CORNSILK1                                                                                              \
  {                                                                                                                  \
    255, 248, 220, 255                                                                                               \
  }
#define CONST_CORNSILK2                                                                                              \
  {                                                                                                                  \
    238, 232, 205, 255                                                                                               \
  }
#define CONST_CORNSILK3                                                                                              \
  {                                                                                                                  \
    205, 200, 177, 255                                                                                               \
  }
#define CONST_CORNSILK4                                                                                              \
  {                                                                                                                  \
    139, 136, 120, 255                                                                                               \
  }
#define CONST_CORNSILK                                                                                               \
  {                                                                                                                  \
    255, 248, 220, 255                                                                                               \
  }
#define CONST_CYAN1                                                                                                  \
  {                                                                                                                  \
    0, 255, 255, 255                                                                                                 \
  }
#define CONST_CYAN2                                                                                                  \
  {                                                                                                                  \
    0, 238, 238, 255                                                                                                 \
  }
#define CONST_CYAN3                                                                                                  \
  {                                                                                                                  \
    0, 205, 205, 255                                                                                                 \
  }
#define CONST_CYAN4                                                                                                  \
  {                                                                                                                  \
    0, 139, 139, 255                                                                                                 \
  }
#define CONST_CYAN                                                                                                   \
  {                                                                                                                  \
    0, 255, 255, 255                                                                                                 \
  }
#define CONST_DARKBLUE                                                                                               \
  {                                                                                                                  \
    0, 0, 139, 255                                                                                                   \
  }
#define CONST_DARKCYAN                                                                                               \
  {                                                                                                                  \
    0, 139, 139, 255                                                                                                 \
  }
#define CONST_DARKGRAY                                                                                               \
  {                                                                                                                  \
    169, 169, 169, 255                                                                                               \
  }
#define CONST_DARKGREEN                                                                                              \
  {                                                                                                                  \
    0, 100, 0, 255                                                                                                   \
  }
#define CONST_DARKKHAKI                                                                                              \
  {                                                                                                                  \
    189, 183, 107, 255                                                                                               \
  }
#define CONST_DARKMAGENTA                                                                                            \
  {                                                                                                                  \
    139, 0, 139, 255                                                                                                 \
  }
#define CONST_DARKOLIVEGREEN1                                                                                        \
  {                                                                                                                  \
    202, 255, 112, 255                                                                                               \
  }
#define CONST_DARKOLIVEGREEN2                                                                                        \
  {                                                                                                                  \
    188, 238, 104, 255                                                                                               \
  }
#define CONST_DARKOLIVEGREEN3                                                                                        \
  {                                                                                                                  \
    162, 205, 90, 255                                                                                                \
  }
#define CONST_DARKOLIVEGREEN4                                                                                        \
  {                                                                                                                  \
    110, 139, 61, 255                                                                                                \
  }
#define CONST_DARKOLIVEGREEN                                                                                         \
  {                                                                                                                  \
    85, 107, 47, 255                                                                                                 \
  }
#define CONST_DARKORANGE1                                                                                            \
  {                                                                                                                  \
    255, 127, 0, 255                                                                                                 \
  }
#define CONST_DARKORANGE2                                                                                            \
  {                                                                                                                  \
    238, 118, 0, 255                                                                                                 \
  }
#define CONST_DARKORANGE3                                                                                            \
  {                                                                                                                  \
    205, 102, 0, 255                                                                                                 \
  }
#define CONST_DARKORANGE4                                                                                            \
  {                                                                                                                  \
    139, 69, 0, 255                                                                                                  \
  }
#define CONST_DARKORANGE                                                                                             \
  {                                                                                                                  \
    255, 140, 0, 255                                                                                                 \
  }
#define CONST_DARKRED                                                                                                \
  {                                                                                                                  \
    139, 0, 0, 255                                                                                                   \
  }
#define CONST_DARKSEAGREEN1                                                                                          \
  {                                                                                                                  \
    193, 255, 193, 255                                                                                               \
  }
#define CONST_DARKSEAGREEN2                                                                                          \
  {                                                                                                                  \
    180, 238, 180, 255                                                                                               \
  }
#define CONST_DARKSEAGREEN3                                                                                          \
  {                                                                                                                  \
    155, 205, 155, 255                                                                                               \
  }
#define CONST_DARKSEAGREEN4                                                                                          \
  {                                                                                                                  \
    105, 139, 105, 255                                                                                               \
  }
#define CONST_DARKSEAGREEN                                                                                           \
  {                                                                                                                  \
    143, 188, 143, 255                                                                                               \
  }
#define CONST_DARKSLATEBLUE                                                                                          \
  {                                                                                                                  \
    72, 61, 139, 255                                                                                                 \
  }
#define CONST_DARKSLATEGRAY1                                                                                         \
  {                                                                                                                  \
    151, 255, 255, 255                                                                                               \
  }
#define CONST_DARKSLATEGRAY2                                                                                         \
  {                                                                                                                  \
    141, 238, 238, 255                                                                                               \
  }
#define CONST_DARKSLATEGRAY3                                                                                         \
  {                                                                                                                  \
    121, 205, 205, 255                                                                                               \
  }
#define CONST_DARKSLATEGRAY4                                                                                         \
  {                                                                                                                  \
    82, 139, 139, 255                                                                                                \
  }
#define CONST_DARKSLATEGRAY                                                                                          \
  {                                                                                                                  \
    47, 79, 79, 255                                                                                                  \
  }
#define CONST_DARKTURQUOISE                                                                                          \
  {                                                                                                                  \
    0, 206, 209, 255                                                                                                 \
  }
#define CONST_DARKVIOLET                                                                                             \
  {                                                                                                                  \
    148, 0, 211, 255                                                                                                 \
  }
#define CONST_DEEPPINK1                                                                                              \
  {                                                                                                                  \
    255, 20, 147, 255                                                                                                \
  }
#define CONST_DEEPPINK2                                                                                              \
  {                                                                                                                  \
    238, 18, 137, 255                                                                                                \
  }
#define CONST_DEEPPINK3                                                                                              \
  {                                                                                                                  \
    205, 16, 118, 255                                                                                                \
  }
#define CONST_DEEPPINK4                                                                                              \
  {                                                                                                                  \
    139, 10, 80, 255                                                                                                 \
  }
#define CONST_DEEPPINK                                                                                               \
  {                                                                                                                  \
    255, 20, 147, 255                                                                                                \
  }
#define CONST_DEEPSKYBLUE1                                                                                           \
  {                                                                                                                  \
    0, 191, 255, 255                                                                                                 \
  }
#define CONST_DEEPSKYBLUE2                                                                                           \
  {                                                                                                                  \
    0, 178, 238, 255                                                                                                 \
  }
#define CONST_DEEPSKYBLUE3                                                                                           \
  {                                                                                                                  \
    0, 154, 205, 255                                                                                                 \
  }
#define CONST_DEEPSKYBLUE4                                                                                           \
  {                                                                                                                  \
    0, 104, 139, 255                                                                                                 \
  }
#define CONST_DEEPSKYBLUE                                                                                            \
  {                                                                                                                  \
    0, 191, 255, 255                                                                                                 \
  }
#define CONST_DIMGRAY                                                                                                \
  {                                                                                                                  \
    105, 105, 105, 255                                                                                               \
  }
#define CONST_DODGERBLUE1                                                                                            \
  {                                                                                                                  \
    30, 144, 255, 255                                                                                                \
  }
#define CONST_DODGERBLUE2                                                                                            \
  {                                                                                                                  \
    28, 134, 238, 255                                                                                                \
  }
#define CONST_DODGERBLUE3                                                                                            \
  {                                                                                                                  \
    24, 116, 205, 255                                                                                                \
  }
#define CONST_DODGERBLUE4                                                                                            \
  {                                                                                                                  \
    16, 78, 139, 255                                                                                                 \
  }
#define CONST_DODGERBLUE                                                                                             \
  {                                                                                                                  \
    30, 144, 255, 255                                                                                                \
  }
#define CONST_FIREBRICK1                                                                                             \
  {                                                                                                                  \
    255, 48, 48, 255                                                                                                 \
  }
#define CONST_FIREBRICK2                                                                                             \
  {                                                                                                                  \
    238, 44, 44, 255                                                                                                 \
  }
#define CONST_FIREBRICK3                                                                                             \
  {                                                                                                                  \
    205, 38, 38, 255                                                                                                 \
  }
#define CONST_FIREBRICK4                                                                                             \
  {                                                                                                                  \
    139, 26, 26, 255                                                                                                 \
  }
#define CONST_FIREBRICK                                                                                              \
  {                                                                                                                  \
    178, 34, 34, 255                                                                                                 \
  }
#define CONST_FLORALWHITE                                                                                            \
  {                                                                                                                  \
    255, 250, 240, 255                                                                                               \
  }
#define CONST_FORESTGREEN                                                                                            \
  {                                                                                                                  \
    34, 139, 34, 255                                                                                                 \
  }
#define CONST_GAINSBORO                                                                                              \
  {                                                                                                                  \
    220, 220, 220, 255                                                                                               \
  }
#define CONST_GHOSTWHITE                                                                                             \
  {                                                                                                                  \
    248, 248, 255, 255                                                                                               \
  }
#define CONST_GOLD1                                                                                                  \
  {                                                                                                                  \
    255, 215, 0, 255                                                                                                 \
  }
#define CONST_GOLD2                                                                                                  \
  {                                                                                                                  \
    238, 201, 0, 255                                                                                                 \
  }
#define CONST_GOLD3                                                                                                  \
  {                                                                                                                  \
    205, 173, 0, 255                                                                                                 \
  }
#define CONST_GOLD4                                                                                                  \
  {                                                                                                                  \
    139, 117, 0, 255                                                                                                 \
  }
#define CONST_GOLD                                                                                                   \
  {                                                                                                                  \
    255, 215, 0, 255                                                                                                 \
  }
#define CONST_GRAY10                                                                                                 \
  {                                                                                                                  \
    26, 26, 26, 255                                                                                                  \
  }
#define CONST_GRAY11                                                                                                 \
  {                                                                                                                  \
    28, 28, 28, 255                                                                                                  \
  }
#define CONST_GRAY12                                                                                                 \
  {                                                                                                                  \
    31, 31, 31, 255                                                                                                  \
  }
#define CONST_GRAY13                                                                                                 \
  {                                                                                                                  \
    33, 33, 33, 255                                                                                                  \
  }
#define CONST_GRAY14                                                                                                 \
  {                                                                                                                  \
    36, 36, 36, 255                                                                                                  \
  }
#define CONST_GRAY15                                                                                                 \
  {                                                                                                                  \
    38, 38, 38, 255                                                                                                  \
  }
#define CONST_GRAY16                                                                                                 \
  {                                                                                                                  \
    41, 41, 41, 255                                                                                                  \
  }
#define CONST_GRAY17                                                                                                 \
  {                                                                                                                  \
    43, 43, 43, 255                                                                                                  \
  }
#define CONST_GRAY18                                                                                                 \
  {                                                                                                                  \
    46, 46, 46, 255                                                                                                  \
  }
#define CONST_GRAY19                                                                                                 \
  {                                                                                                                  \
    48, 48, 48, 255                                                                                                  \
  }
#define CONST_GRAY1                                                                                                  \
  {                                                                                                                  \
    3, 3, 3, 255                                                                                                     \
  }
#define CONST_GRAY20                                                                                                 \
  {                                                                                                                  \
    51, 51, 51, 255                                                                                                  \
  }
#define CONST_GRAY21                                                                                                 \
  {                                                                                                                  \
    54, 54, 54, 255                                                                                                  \
  }
#define CONST_GRAY22                                                                                                 \
  {                                                                                                                  \
    56, 56, 56, 255                                                                                                  \
  }
#define CONST_GRAY23                                                                                                 \
  {                                                                                                                  \
    59, 59, 59, 255                                                                                                  \
  }
#define CONST_GRAY24                                                                                                 \
  {                                                                                                                  \
    61, 61, 61, 255                                                                                                  \
  }
#define CONST_GRAY25                                                                                                 \
  {                                                                                                                  \
    64, 64, 64, 255                                                                                                  \
  }
#define CONST_GRAY26                                                                                                 \
  {                                                                                                                  \
    66, 66, 66, 255                                                                                                  \
  }
#define CONST_GRAY27                                                                                                 \
  {                                                                                                                  \
    69, 69, 69, 255                                                                                                  \
  }
#define CONST_GRAY28                                                                                                 \
  {                                                                                                                  \
    71, 71, 71, 255                                                                                                  \
  }
#define CONST_GRAY29                                                                                                 \
  {                                                                                                                  \
    74, 74, 74, 255                                                                                                  \
  }
#define CONST_GRAY2                                                                                                  \
  {                                                                                                                  \
    5, 5, 5, 255                                                                                                     \
  }
#define CONST_GRAY30                                                                                                 \
  {                                                                                                                  \
    77, 77, 77, 255                                                                                                  \
  }
#define CONST_GRAY31                                                                                                 \
  {                                                                                                                  \
    79, 79, 79, 255                                                                                                  \
  }
#define CONST_GRAY32                                                                                                 \
  {                                                                                                                  \
    82, 82, 82, 255                                                                                                  \
  }
#define CONST_GRAY33                                                                                                 \
  {                                                                                                                  \
    84, 84, 84, 255                                                                                                  \
  }
#define CONST_GRAY34                                                                                                 \
  {                                                                                                                  \
    87, 87, 87, 255                                                                                                  \
  }
#define CONST_GRAY35                                                                                                 \
  {                                                                                                                  \
    89, 89, 89, 255                                                                                                  \
  }
#define CONST_GRAY36                                                                                                 \
  {                                                                                                                  \
    92, 92, 92, 255                                                                                                  \
  }
#define CONST_GRAY37                                                                                                 \
  {                                                                                                                  \
    94, 94, 94, 255                                                                                                  \
  }
#define CONST_GRAY38                                                                                                 \
  {                                                                                                                  \
    97, 97, 97, 255                                                                                                  \
  }
#define CONST_GRAY39                                                                                                 \
  {                                                                                                                  \
    99, 99, 99, 255                                                                                                  \
  }
#define CONST_GRAY3                                                                                                  \
  {                                                                                                                  \
    8, 8, 8, 255                                                                                                     \
  }
#define CONST_GRAY40                                                                                                 \
  {                                                                                                                  \
    102, 102, 102, 255                                                                                               \
  }
#define CONST_GRAY41                                                                                                 \
  {                                                                                                                  \
    105, 105, 105, 255                                                                                               \
  }
#define CONST_GRAY42                                                                                                 \
  {                                                                                                                  \
    107, 107, 107, 255                                                                                               \
  }
#define CONST_GRAY43                                                                                                 \
  {                                                                                                                  \
    110, 110, 110, 255                                                                                               \
  }
#define CONST_GRAY44                                                                                                 \
  {                                                                                                                  \
    112, 112, 112, 255                                                                                               \
  }
#define CONST_GRAY45                                                                                                 \
  {                                                                                                                  \
    115, 115, 115, 255                                                                                               \
  }
#define CONST_GRAY46                                                                                                 \
  {                                                                                                                  \
    117, 117, 117, 255                                                                                               \
  }
#define CONST_GRAY47                                                                                                 \
  {                                                                                                                  \
    120, 120, 120, 255                                                                                               \
  }
#define CONST_GRAY48                                                                                                 \
  {                                                                                                                  \
    122, 122, 122, 255                                                                                               \
  }
#define CONST_GRAY49                                                                                                 \
  {                                                                                                                  \
    125, 125, 125, 255                                                                                               \
  }
#define CONST_GRAY4                                                                                                  \
  {                                                                                                                  \
    10, 10, 10, 255                                                                                                  \
  }
#define CONST_GRAY50                                                                                                 \
  {                                                                                                                  \
    127, 127, 127, 255                                                                                               \
  }
#define CONST_GRAY51                                                                                                 \
  {                                                                                                                  \
    130, 130, 130, 255                                                                                               \
  }
#define CONST_GRAY52                                                                                                 \
  {                                                                                                                  \
    133, 133, 133, 255                                                                                               \
  }
#define CONST_GRAY53                                                                                                 \
  {                                                                                                                  \
    135, 135, 135, 255                                                                                               \
  }
#define CONST_GRAY54                                                                                                 \
  {                                                                                                                  \
    138, 138, 138, 255                                                                                               \
  }
#define CONST_GRAY55                                                                                                 \
  {                                                                                                                  \
    140, 140, 140, 255                                                                                               \
  }
#define CONST_GRAY56                                                                                                 \
  {                                                                                                                  \
    143, 143, 143, 255                                                                                               \
  }
#define CONST_GRAY57                                                                                                 \
  {                                                                                                                  \
    145, 145, 145, 255                                                                                               \
  }
#define CONST_GRAY58                                                                                                 \
  {                                                                                                                  \
    148, 148, 148, 255                                                                                               \
  }
#define CONST_GRAY59                                                                                                 \
  {                                                                                                                  \
    150, 150, 150, 255                                                                                               \
  }
#define CONST_GRAY5                                                                                                  \
  {                                                                                                                  \
    13, 13, 13, 255                                                                                                  \
  }
#define CONST_GRAY60                                                                                                 \
  {                                                                                                                  \
    153, 153, 153, 255                                                                                               \
  }
#define CONST_GRAY61                                                                                                 \
  {                                                                                                                  \
    156, 156, 156, 255                                                                                               \
  }
#define CONST_GRAY62                                                                                                 \
  {                                                                                                                  \
    158, 158, 158, 255                                                                                               \
  }
#define CONST_GRAY63                                                                                                 \
  {                                                                                                                  \
    161, 161, 161, 255                                                                                               \
  }
#define CONST_GRAY64                                                                                                 \
  {                                                                                                                  \
    163, 163, 163, 255                                                                                               \
  }
#define CONST_GRAY65                                                                                                 \
  {                                                                                                                  \
    166, 166, 166, 255                                                                                               \
  }
#define CONST_GRAY66                                                                                                 \
  {                                                                                                                  \
    168, 168, 168, 255                                                                                               \
  }
#define CONST_GRAY67                                                                                                 \
  {                                                                                                                  \
    171, 171, 171, 255                                                                                               \
  }
#define CONST_GRAY68                                                                                                 \
  {                                                                                                                  \
    173, 173, 173, 255                                                                                               \
  }
#define CONST_GRAY69                                                                                                 \
  {                                                                                                                  \
    176, 176, 176, 255                                                                                               \
  }
#define CONST_GRAY6                                                                                                  \
  {                                                                                                                  \
    15, 15, 15, 255                                                                                                  \
  }
#define CONST_GRAY70                                                                                                 \
  {                                                                                                                  \
    179, 179, 179, 255                                                                                               \
  }
#define CONST_GRAY71                                                                                                 \
  {                                                                                                                  \
    181, 181, 181, 255                                                                                               \
  }
#define CONST_GRAY72                                                                                                 \
  {                                                                                                                  \
    184, 184, 184, 255                                                                                               \
  }
#define CONST_GRAY73                                                                                                 \
  {                                                                                                                  \
    186, 186, 186, 255                                                                                               \
  }
#define CONST_GRAY74                                                                                                 \
  {                                                                                                                  \
    189, 189, 189, 255                                                                                               \
  }
#define CONST_GRAY75                                                                                                 \
  {                                                                                                                  \
    191, 191, 191, 255                                                                                               \
  }
#define CONST_GRAY76                                                                                                 \
  {                                                                                                                  \
    194, 194, 194, 255                                                                                               \
  }
#define CONST_GRAY77                                                                                                 \
  {                                                                                                                  \
    196, 196, 196, 255                                                                                               \
  }
#define CONST_GRAY78                                                                                                 \
  {                                                                                                                  \
    199, 199, 199, 255                                                                                               \
  }
#define CONST_GRAY79                                                                                                 \
  {                                                                                                                  \
    201, 201, 201, 255                                                                                               \
  }
#define CONST_GRAY7                                                                                                  \
  {                                                                                                                  \
    18, 18, 18, 255                                                                                                  \
  }
#define CONST_GRAY80                                                                                                 \
  {                                                                                                                  \
    204, 204, 204, 255                                                                                               \
  }
#define CONST_GRAY81                                                                                                 \
  {                                                                                                                  \
    207, 207, 207, 255                                                                                               \
  }
#define CONST_GRAY82                                                                                                 \
  {                                                                                                                  \
    209, 209, 209, 255                                                                                               \
  }
#define CONST_GRAY83                                                                                                 \
  {                                                                                                                  \
    212, 212, 212, 255                                                                                               \
  }
#define CONST_GRAY84                                                                                                 \
  {                                                                                                                  \
    214, 214, 214, 255                                                                                               \
  }
#define CONST_GRAY85                                                                                                 \
  {                                                                                                                  \
    217, 217, 217, 255                                                                                               \
  }
#define CONST_GRAY86                                                                                                 \
  {                                                                                                                  \
    219, 219, 219, 255                                                                                               \
  }
#define CONST_GRAY87                                                                                                 \
  {                                                                                                                  \
    222, 222, 222, 255                                                                                               \
  }
#define CONST_GRAY88                                                                                                 \
  {                                                                                                                  \
    224, 224, 224, 255                                                                                               \
  }
#define CONST_GRAY89                                                                                                 \
  {                                                                                                                  \
    227, 227, 227, 255                                                                                               \
  }
#define CONST_GRAY8                                                                                                  \
  {                                                                                                                  \
    20, 20, 20, 255                                                                                                  \
  }
#define CONST_GRAY90                                                                                                 \
  {                                                                                                                  \
    229, 229, 229, 255                                                                                               \
  }
#define CONST_GRAY91                                                                                                 \
  {                                                                                                                  \
    232, 232, 232, 255                                                                                               \
  }
#define CONST_GRAY92                                                                                                 \
  {                                                                                                                  \
    235, 235, 235, 255                                                                                               \
  }
#define CONST_GRAY93                                                                                                 \
  {                                                                                                                  \
    237, 237, 237, 255                                                                                               \
  }
#define CONST_GRAY94                                                                                                 \
  {                                                                                                                  \
    240, 240, 240, 255                                                                                               \
  }
#define CONST_GRAY95                                                                                                 \
  {                                                                                                                  \
    242, 242, 242, 255                                                                                               \
  }
#define CONST_GRAY96                                                                                                 \
  {                                                                                                                  \
    245, 245, 245, 255                                                                                               \
  }
#define CONST_GRAY97                                                                                                 \
  {                                                                                                                  \
    247, 247, 247, 255                                                                                               \
  }
#define CONST_GRAY98                                                                                                 \
  {                                                                                                                  \
    250, 250, 250, 255                                                                                               \
  }
#define CONST_GRAY99                                                                                                 \
  {                                                                                                                  \
    252, 252, 252, 255                                                                                               \
  }
#define CONST_GRAY9                                                                                                  \
  {                                                                                                                  \
    23, 23, 23, 255                                                                                                  \
  }
#define CONST_GRAY                                                                                                   \
  {                                                                                                                  \
    190, 190, 190, 255                                                                                               \
  }
#define CONST_GREEN1                                                                                                 \
  {                                                                                                                  \
    0, 255, 0, 255                                                                                                   \
  }
#define CONST_GREEN2                                                                                                 \
  {                                                                                                                  \
    0, 238, 0, 255                                                                                                   \
  }
#define CONST_GREEN3                                                                                                 \
  {                                                                                                                  \
    0, 205, 0, 255                                                                                                   \
  }
#define CONST_GREEN4                                                                                                 \
  {                                                                                                                  \
    0, 139, 0, 255                                                                                                   \
  }
#define CONST_GREEN                                                                                                  \
  {                                                                                                                  \
    0, 255, 0, 255                                                                                                   \
  }
#define CONST_GREENYELLOW                                                                                            \
  {                                                                                                                  \
    173, 255, 47, 255                                                                                                \
  }
#define CONST_HOTPINK1                                                                                               \
  {                                                                                                                  \
    255, 110, 180, 255                                                                                               \
  }
#define CONST_HOTPINK2                                                                                               \
  {                                                                                                                  \
    238, 106, 167, 255                                                                                               \
  }
#define CONST_HOTPINK3                                                                                               \
  {                                                                                                                  \
    205, 96, 144, 255                                                                                                \
  }
#define CONST_HOTPINK4                                                                                               \
  {                                                                                                                  \
    139, 58, 98, 255                                                                                                 \
  }
#define CONST_HOTPINK                                                                                                \
  {                                                                                                                  \
    255, 105, 180, 255                                                                                               \
  }
#define CONST_INDIANRED1                                                                                             \
  {                                                                                                                  \
    255, 106, 106, 255                                                                                               \
  }
#define CONST_INDIANRED2                                                                                             \
  {                                                                                                                  \
    238, 99, 99, 255                                                                                                 \
  }
#define CONST_INDIANRED3                                                                                             \
  {                                                                                                                  \
    205, 85, 85, 255                                                                                                 \
  }
#define CONST_INDIANRED4                                                                                             \
  {                                                                                                                  \
    139, 58, 58, 255                                                                                                 \
  }
#define CONST_INDIANRED                                                                                              \
  {                                                                                                                  \
    205, 92, 92, 255                                                                                                 \
  }
#define CONST_IVORY1                                                                                                 \
  {                                                                                                                  \
    255, 255, 240, 255                                                                                               \
  }
#define CONST_IVORY2                                                                                                 \
  {                                                                                                                  \
    238, 238, 224, 255                                                                                               \
  }
#define CONST_IVORY3                                                                                                 \
  {                                                                                                                  \
    205, 205, 193, 255                                                                                               \
  }
#define CONST_IVORY4                                                                                                 \
  {                                                                                                                  \
    139, 139, 131, 255                                                                                               \
  }
#define CONST_IVORY                                                                                                  \
  {                                                                                                                  \
    255, 255, 240, 255                                                                                               \
  }
#define CONST_KHAKI1                                                                                                 \
  {                                                                                                                  \
    255, 246, 143, 255                                                                                               \
  }
#define CONST_KHAKI2                                                                                                 \
  {                                                                                                                  \
    238, 230, 133, 255                                                                                               \
  }
#define CONST_KHAKI3                                                                                                 \
  {                                                                                                                  \
    205, 198, 115, 255                                                                                               \
  }
#define CONST_KHAKI4                                                                                                 \
  {                                                                                                                  \
    139, 134, 78, 255                                                                                                \
  }
#define CONST_KHAKI                                                                                                  \
  {                                                                                                                  \
    240, 230, 140, 255                                                                                               \
  }
#define CONST_LAVENDER                                                                                               \
  {                                                                                                                  \
    230, 230, 250, 255                                                                                               \
  }
#define CONST_LEMONCHIFFON1                                                                                          \
  {                                                                                                                  \
    255, 250, 205, 255                                                                                               \
  }
#define CONST_LEMONCHIFFON2                                                                                          \
  {                                                                                                                  \
    238, 233, 191, 255                                                                                               \
  }
#define CONST_LEMONCHIFFON3                                                                                          \
  {                                                                                                                  \
    205, 201, 165, 255                                                                                               \
  }
#define CONST_LEMONCHIFFON4                                                                                          \
  {                                                                                                                  \
    139, 137, 112, 255                                                                                               \
  }
#define CONST_LEMON_CHIFFON                                                                                          \
  {                                                                                                                  \
    255, 250, 205, 255                                                                                               \
  }
#define CONST_LEMONCHIFFON                                                                                           \
  {                                                                                                                  \
    255, 250, 205, 255                                                                                               \
  }
#define CONST_LIGHTBLUE1                                                                                             \
  {                                                                                                                  \
    191, 239, 255, 255                                                                                               \
  }
#define CONST_LIGHTBLUE2                                                                                             \
  {                                                                                                                  \
    178, 223, 238, 255                                                                                               \
  }
#define CONST_LIGHTBLUE3                                                                                             \
  {                                                                                                                  \
    154, 192, 205, 255                                                                                               \
  }
#define CONST_LIGHTBLUE4                                                                                             \
  {                                                                                                                  \
    104, 131, 139, 255                                                                                               \
  }
#define CONST_LIGHTBLUE                                                                                              \
  {                                                                                                                  \
    173, 216, 230, 255                                                                                               \
  }
#define CONST_LIGHTCORAL                                                                                             \
  {                                                                                                                  \
    240, 128, 128, 255                                                                                               \
  }
#define CONST_LIGHTCYAN1                                                                                             \
  {                                                                                                                  \
    224, 255, 255, 255                                                                                               \
  }
#define CONST_LIGHTCYAN2                                                                                             \
  {                                                                                                                  \
    209, 238, 238, 255                                                                                               \
  }
#define CONST_LIGHTCYAN3                                                                                             \
  {                                                                                                                  \
    180, 205, 205, 255                                                                                               \
  }
#define CONST_LIGHTCYAN4                                                                                             \
  {                                                                                                                  \
    122, 139, 139, 255                                                                                               \
  }
#define CONST_LIGHTCYAN                                                                                              \
  {                                                                                                                  \
    224, 255, 255, 255                                                                                               \
  }
#define CONST_LIGHTGRAY                                                                                              \
  {                                                                                                                  \
    211, 211, 211, 255                                                                                               \
  }
#define CONST_LIGHTGREEN                                                                                             \
  {                                                                                                                  \
    144, 238, 144, 255                                                                                               \
  }
#define CONST_LIGHTPINK1                                                                                             \
  {                                                                                                                  \
    255, 174, 185, 255                                                                                               \
  }
#define CONST_LIGHTPINK2                                                                                             \
  {                                                                                                                  \
    238, 162, 173, 255                                                                                               \
  }
#define CONST_LIGHTPINK3                                                                                             \
  {                                                                                                                  \
    205, 140, 149, 255                                                                                               \
  }
#define CONST_LIGHTPINK4                                                                                             \
  {                                                                                                                  \
    139, 95, 101, 255                                                                                                \
  }
#define CONST_LIGHTPINK                                                                                              \
  {                                                                                                                  \
    255, 182, 193, 255                                                                                               \
  }
#define CONST_LIGHTSEAGREEN                                                                                          \
  {                                                                                                                  \
    32, 178, 170, 255                                                                                                \
  }
#define CONST_LIGHTSKYBLUE1                                                                                          \
  {                                                                                                                  \
    176, 226, 255, 255                                                                                               \
  }
#define CONST_LIGHTSKYBLUE2                                                                                          \
  {                                                                                                                  \
    164, 211, 238, 255                                                                                               \
  }
#define CONST_LIGHTSKYBLUE3                                                                                          \
  {                                                                                                                  \
    141, 182, 205, 255                                                                                               \
  }
#define CONST_LIGHTSKYBLUE4                                                                                          \
  {                                                                                                                  \
    96, 123, 139, 255                                                                                                \
  }
#define CONST_LIGHTSKYBLUE                                                                                           \
  {                                                                                                                  \
    135, 206, 250, 255                                                                                               \
  }
#define CONST_LIGHTSLATEBLUE                                                                                         \
  {                                                                                                                  \
    132, 112, 255, 255                                                                                               \
  }
#define CONST_LIGHTSLATEGRAY                                                                                         \
  {                                                                                                                  \
    119, 136, 153, 255                                                                                               \
  }
#define CONST_LIGHTSTEELBLUE1                                                                                        \
  {                                                                                                                  \
    202, 225, 255, 255                                                                                               \
  }
#define CONST_LIGHTSTEELBLUE2                                                                                        \
  {                                                                                                                  \
    188, 210, 238, 255                                                                                               \
  }
#define CONST_LIGHTSTEELBLUE3                                                                                        \
  {                                                                                                                  \
    162, 181, 205, 255                                                                                               \
  }
#define CONST_LIGHTSTEELBLUE4                                                                                        \
  {                                                                                                                  \
    110, 123, 139, 255                                                                                               \
  }
#define CONST_LIGHTSTEELBLUE                                                                                         \
  {                                                                                                                  \
    176, 196, 222, 255                                                                                               \
  }
#define CONST_LIGHTYELLOW1                                                                                           \
  {                                                                                                                  \
    255, 255, 224, 255                                                                                               \
  }
#define CONST_LIGHTYELLOW2                                                                                           \
  {                                                                                                                  \
    238, 238, 209, 255                                                                                               \
  }
#define CONST_LIGHTYELLOW3                                                                                           \
  {                                                                                                                  \
    205, 205, 180, 255                                                                                               \
  }
#define CONST_LIGHTYELLOW4                                                                                           \
  {                                                                                                                  \
    139, 139, 122, 255                                                                                               \
  }
#define CONST_LIGHTYELLOW                                                                                            \
  {                                                                                                                  \
    255, 255, 224, 255                                                                                               \
  }
#define CONST_LIMEGREEN                                                                                              \
  {                                                                                                                  \
    50, 205, 50, 255                                                                                                 \
  }
#define CONST_LIME                                                                                                   \
  {                                                                                                                  \
    50, 205, 50, 255                                                                                                 \
  }
#define CONST_LINEN                                                                                                  \
  {                                                                                                                  \
    250, 240, 230, 255                                                                                               \
  }
#define CONST_MAGENTA1                                                                                               \
  {                                                                                                                  \
    255, 0, 255, 255                                                                                                 \
  }
#define CONST_MAGENTA2                                                                                               \
  {                                                                                                                  \
    238, 0, 238, 255                                                                                                 \
  }
#define CONST_MAGENTA3                                                                                               \
  {                                                                                                                  \
    205, 0, 205, 255                                                                                                 \
  }
#define CONST_MAGENTA4                                                                                               \
  {                                                                                                                  \
    139, 0, 139, 255                                                                                                 \
  }
#define CONST_MAGENTA                                                                                                \
  {                                                                                                                  \
    255, 0, 255, 255                                                                                                 \
  }
#define CONST_MAROON1                                                                                                \
  {                                                                                                                  \
    255, 52, 179, 255                                                                                                \
  }
#define CONST_MAROON2                                                                                                \
  {                                                                                                                  \
    238, 48, 167, 255                                                                                                \
  }
#define CONST_MAROON3                                                                                                \
  {                                                                                                                  \
    205, 41, 144, 255                                                                                                \
  }
#define CONST_MAROON4                                                                                                \
  {                                                                                                                  \
    139, 28, 98, 255                                                                                                 \
  }
#define CONST_MAROON                                                                                                 \
  {                                                                                                                  \
    176, 48, 96, 255                                                                                                 \
  }
#define CONST_MEDIUMAQUAMARINE                                                                                       \
  {                                                                                                                  \
    102, 205, 170, 255                                                                                               \
  }
#define CONST_MEDIUMBLUE                                                                                             \
  {                                                                                                                  \
    0, 0, 205, 255                                                                                                   \
  }
#define CONST_MEDIUMPURPLE1                                                                                          \
  {                                                                                                                  \
    171, 130, 255, 255                                                                                               \
  }
#define CONST_MEDIUMPURPLE2                                                                                          \
  {                                                                                                                  \
    159, 121, 238, 255                                                                                               \
  }
#define CONST_MEDIUMPURPLE3                                                                                          \
  {                                                                                                                  \
    137, 104, 205, 255                                                                                               \
  }
#define CONST_MEDIUMPURPLE4                                                                                          \
  {                                                                                                                  \
    93, 71, 139, 255                                                                                                 \
  }
#define CONST_MEDIUMPURPLE                                                                                           \
  {                                                                                                                  \
    147, 112, 219, 255                                                                                               \
  }
#define CONST_MEDIUMSEAGREEN                                                                                         \
  {                                                                                                                  \
    60, 179, 113, 255                                                                                                \
  }
#define CONST_MEDIUMSLATEBLUE                                                                                        \
  {                                                                                                                  \
    123, 104, 238, 255                                                                                               \
  }
#define CONST_MEDIUMSPRINGGREEN                                                                                      \
  {                                                                                                                  \
    0, 250, 154, 255                                                                                                 \
  }
#define CONST_MEDIUMTURQUOISE                                                                                        \
  {                                                                                                                  \
    72, 209, 204, 255                                                                                                \
  }
#define CONST_MEDIUMVIOLETRED                                                                                        \
  {                                                                                                                  \
    199, 21, 133, 255                                                                                                \
  }
#define CONST_MIDNIGHTBLUE                                                                                           \
  {                                                                                                                  \
    25, 25, 112, 255                                                                                                 \
  }
#define CONST_MINTCREAM                                                                                              \
  {                                                                                                                  \
    245, 255, 250, 255                                                                                               \
  }
#define CONST_MOCCASIN                                                                                               \
  {                                                                                                                  \
    255, 228, 181, 255                                                                                               \
  }
#define CONST_NAVYBLUE                                                                                               \
  {                                                                                                                  \
    0, 0, 128, 255                                                                                                   \
  }
#define CONST_NAVY                                                                                                   \
  {                                                                                                                  \
    0, 0, 128, 255                                                                                                   \
  }
#define CONST_OLIVEDRAB1                                                                                             \
  {                                                                                                                  \
    192, 255, 62, 255                                                                                                \
  }
#define CONST_OLIVEDRAB2                                                                                             \
  {                                                                                                                  \
    179, 238, 58, 255                                                                                                \
  }
#define CONST_OLIVEDRAB3                                                                                             \
  {                                                                                                                  \
    154, 205, 50, 255                                                                                                \
  }
#define CONST_OLIVEDRAB4                                                                                             \
  {                                                                                                                  \
    105, 139, 34, 255                                                                                                \
  }
#define CONST_OLIVE_DRAB                                                                                             \
  {                                                                                                                  \
    107, 142, 35, 255                                                                                                \
  }
#define CONST_OLIVEDRAB                                                                                              \
  {                                                                                                                  \
    107, 142, 35, 255                                                                                                \
  }
#define CONST_ORANGE1                                                                                                \
  {                                                                                                                  \
    255, 165, 0, 255                                                                                                 \
  }
#define CONST_ORANGE2                                                                                                \
  {                                                                                                                  \
    238, 154, 0, 255                                                                                                 \
  }
#define CONST_ORANGE3                                                                                                \
  {                                                                                                                  \
    205, 133, 0, 255                                                                                                 \
  }
#define CONST_ORANGE4                                                                                                \
  {                                                                                                                  \
    139, 90, 0, 255                                                                                                  \
  }
#define CONST_ORANGE                                                                                                 \
  {                                                                                                                  \
    255, 165, 0, 255                                                                                                 \
  }
#define CONST_ORANGERED1                                                                                             \
  {                                                                                                                  \
    255, 69, 0, 255                                                                                                  \
  }
#define CONST_ORANGERED2                                                                                             \
  {                                                                                                                  \
    238, 64, 0, 255                                                                                                  \
  }
#define CONST_ORANGERED3                                                                                             \
  {                                                                                                                  \
    205, 55, 0, 255                                                                                                  \
  }
#define CONST_ORANGERED4                                                                                             \
  {                                                                                                                  \
    139, 37, 0, 255                                                                                                  \
  }
#define CONST_ORANGERED                                                                                              \
  {                                                                                                                  \
    255, 69, 0, 255                                                                                                  \
  }
#define CONST_PALEGREEN1                                                                                             \
  {                                                                                                                  \
    154, 255, 154, 255                                                                                               \
  }
#define CONST_PALEGREEN2                                                                                             \
  {                                                                                                                  \
    144, 238, 144, 255                                                                                               \
  }
#define CONST_PALEGREEN3                                                                                             \
  {                                                                                                                  \
    124, 205, 124, 255                                                                                               \
  }
#define CONST_PALEGREEN4                                                                                             \
  {                                                                                                                  \
    84, 139, 84, 255                                                                                                 \
  }
#define CONST_PALEGREEN                                                                                              \
  {                                                                                                                  \
    152, 251, 152, 255                                                                                               \
  }
#define CONST_PALETURQUOISE1                                                                                         \
  {                                                                                                                  \
    187, 255, 255, 255                                                                                               \
  }
#define CONST_PALETURQUOISE2                                                                                         \
  {                                                                                                                  \
    174, 238, 238, 255                                                                                               \
  }
#define CONST_PALETURQUOISE3                                                                                         \
  {                                                                                                                  \
    150, 205, 205, 255                                                                                               \
  }
#define CONST_PALETURQUOISE4                                                                                         \
  {                                                                                                                  \
    102, 139, 139, 255                                                                                               \
  }
#define CONST_PALETURQUOISE                                                                                          \
  {                                                                                                                  \
    175, 238, 238, 255                                                                                               \
  }
#define CONST_PALEVIOLETRED1                                                                                         \
  {                                                                                                                  \
    255, 130, 171, 255                                                                                               \
  }
#define CONST_PALEVIOLETRED2                                                                                         \
  {                                                                                                                  \
    238, 121, 159, 255                                                                                               \
  }
#define CONST_PALEVIOLETRED3                                                                                         \
  {                                                                                                                  \
    205, 104, 137, 255                                                                                               \
  }
#define CONST_PALEVIOLETRED4                                                                                         \
  {                                                                                                                  \
    139, 71, 93, 255                                                                                                 \
  }
#define CONST_PALEVIOLETRED                                                                                          \
  {                                                                                                                  \
    219, 112, 147, 255                                                                                               \
  }
#define CONST_PEACHPUFF1                                                                                             \
  {                                                                                                                  \
    255, 218, 185, 255                                                                                               \
  }
#define CONST_PEACHPUFF2                                                                                             \
  {                                                                                                                  \
    238, 203, 173, 255                                                                                               \
  }
#define CONST_PEACHPUFF3                                                                                             \
  {                                                                                                                  \
    205, 175, 149, 255                                                                                               \
  }
#define CONST_PEACHPUFF4                                                                                             \
  {                                                                                                                  \
    139, 119, 101, 255                                                                                               \
  }
#define CONST_PEACHPUFF                                                                                              \
  {                                                                                                                  \
    255, 218, 185, 255                                                                                               \
  }
#define CONST_PERU                                                                                                   \
  {                                                                                                                  \
    205, 133, 63, 255                                                                                                \
  }
#define CONST_PINK1                                                                                                  \
  {                                                                                                                  \
    255, 181, 197, 255                                                                                               \
  }
#define CONST_PINK2                                                                                                  \
  {                                                                                                                  \
    238, 169, 184, 255                                                                                               \
  }
#define CONST_PINK3                                                                                                  \
  {                                                                                                                  \
    205, 145, 158, 255                                                                                               \
  }
#define CONST_PINK4                                                                                                  \
  {                                                                                                                  \
    139, 99, 108, 255                                                                                                \
  }
#define CONST_PINK                                                                                                   \
  {                                                                                                                  \
    255, 192, 203, 255                                                                                               \
  }
#define CONST_PLUM1                                                                                                  \
  {                                                                                                                  \
    255, 187, 255, 255                                                                                               \
  }
#define CONST_PLUM2                                                                                                  \
  {                                                                                                                  \
    238, 174, 238, 255                                                                                               \
  }
#define CONST_PLUM3                                                                                                  \
  {                                                                                                                  \
    205, 150, 205, 255                                                                                               \
  }
#define CONST_PLUM4                                                                                                  \
  {                                                                                                                  \
    139, 102, 139, 255                                                                                               \
  }
#define CONST_PLUM                                                                                                   \
  {                                                                                                                  \
    221, 160, 221, 255                                                                                               \
  }
#define CONST_POWDERBLUE                                                                                             \
  {                                                                                                                  \
    176, 224, 230, 255                                                                                               \
  }
#define CONST_PURPLE1                                                                                                \
  {                                                                                                                  \
    155, 48, 255, 255                                                                                                \
  }
#define CONST_PURPLE2                                                                                                \
  {                                                                                                                  \
    145, 44, 238, 255                                                                                                \
  }
#define CONST_PURPLE3                                                                                                \
  {                                                                                                                  \
    125, 38, 205, 255                                                                                                \
  }
#define CONST_PURPLE4                                                                                                \
  {                                                                                                                  \
    85, 26, 139, 255                                                                                                 \
  }
#define CONST_PURPLE                                                                                                 \
  {                                                                                                                  \
    160, 32, 240, 255                                                                                                \
  }
#define CONST_RED1                                                                                                   \
  {                                                                                                                  \
    255, 0, 0, 255                                                                                                   \
  }
#define CONST_RED2                                                                                                   \
  {                                                                                                                  \
    238, 0, 0, 255                                                                                                   \
  }
#define CONST_RED3                                                                                                   \
  {                                                                                                                  \
    205, 0, 0, 255                                                                                                   \
  }
#define CONST_RED4                                                                                                   \
  {                                                                                                                  \
    139, 0, 0, 255                                                                                                   \
  }
#define CONST_RED                                                                                                    \
  {                                                                                                                  \
    255, 0, 0, 255                                                                                                   \
  }
#define CONST_SADDLE_BROWN                                                                                           \
  {                                                                                                                  \
    139, 69, 19, 255                                                                                                 \
  }
#define CONST_SADDLEBROWN                                                                                            \
  {                                                                                                                  \
    139, 69, 19, 255                                                                                                 \
  }
#define CONST_SEAGREEN1                                                                                              \
  {                                                                                                                  \
    84, 255, 159, 255                                                                                                \
  }
#define CONST_SEAGREEN2                                                                                              \
  {                                                                                                                  \
    78, 238, 148, 255                                                                                                \
  }
#define CONST_SEAGREEN3                                                                                              \
  {                                                                                                                  \
    67, 205, 128, 255                                                                                                \
  }
#define CONST_SEAGREEN4                                                                                              \
  {                                                                                                                  \
    46, 139, 87, 255                                                                                                 \
  }
#define CONST_SEAGREEN                                                                                               \
  {                                                                                                                  \
    46, 139, 87, 255                                                                                                 \
  }
#define CONST_SIENNA1                                                                                                \
  {                                                                                                                  \
    255, 130, 71, 255                                                                                                \
  }
#define CONST_SIENNA2                                                                                                \
  {                                                                                                                  \
    238, 121, 66, 255                                                                                                \
  }
#define CONST_SIENNA3                                                                                                \
  {                                                                                                                  \
    205, 104, 57, 255                                                                                                \
  }
#define CONST_SIENNA4                                                                                                \
  {                                                                                                                  \
    139, 71, 38, 255                                                                                                 \
  }
#define CONST_SIENNA                                                                                                 \
  {                                                                                                                  \
    160, 82, 45, 255                                                                                                 \
  }
#define CONST_SKYBLUE1                                                                                               \
  {                                                                                                                  \
    135, 206, 255, 255                                                                                               \
  }
#define CONST_SKYBLUE2                                                                                               \
  {                                                                                                                  \
    126, 192, 238, 255                                                                                               \
  }
#define CONST_SKYBLUE3                                                                                               \
  {                                                                                                                  \
    108, 166, 205, 255                                                                                               \
  }
#define CONST_SKYBLUE4                                                                                               \
  {                                                                                                                  \
    74, 112, 139, 255                                                                                                \
  }
#define CONST_SKYBLUE                                                                                                \
  {                                                                                                                  \
    135, 206, 235, 255                                                                                               \
  }
#define CONST_SLATEBLUE1                                                                                             \
  {                                                                                                                  \
    131, 111, 255, 255                                                                                               \
  }
#define CONST_SLATEBLUE2                                                                                             \
  {                                                                                                                  \
    122, 103, 238, 255                                                                                               \
  }
#define CONST_SLATEBLUE3                                                                                             \
  {                                                                                                                  \
    105, 89, 205, 255                                                                                                \
  }
#define CONST_SLATEBLUE4                                                                                             \
  {                                                                                                                  \
    71, 60, 139, 255                                                                                                 \
  }
#define CONST_SLATEBLUE                                                                                              \
  {                                                                                                                  \
    106, 90, 205, 255                                                                                                \
  }
#define CONST_SLATEGRAY1                                                                                             \
  {                                                                                                                  \
    198, 226, 255, 255                                                                                               \
  }
#define CONST_SLATEGRAY2                                                                                             \
  {                                                                                                                  \
    185, 211, 238, 255                                                                                               \
  }
#define CONST_SLATEGRAY3                                                                                             \
  {                                                                                                                  \
    159, 182, 205, 255                                                                                               \
  }
#define CONST_SLATEGRAY4                                                                                             \
  {                                                                                                                  \
    108, 123, 139, 255                                                                                               \
  }
#define CONST_SLATEGRAY                                                                                              \
  {                                                                                                                  \
    112, 128, 144, 255                                                                                               \
  }
#define CONST_SNOW1                                                                                                  \
  {                                                                                                                  \
    255, 250, 250, 255                                                                                               \
  }
#define CONST_SNOW2                                                                                                  \
  {                                                                                                                  \
    238, 233, 233, 255                                                                                               \
  }
#define CONST_SNOW3                                                                                                  \
  {                                                                                                                  \
    205, 201, 201, 255                                                                                               \
  }
#define CONST_SNOW4                                                                                                  \
  {                                                                                                                  \
    139, 137, 137, 255                                                                                               \
  }
#define CONST_SNOW                                                                                                   \
  {                                                                                                                  \
    255, 250, 250, 255                                                                                               \
  }
#define CONST_SPRINGGREEN1                                                                                           \
  {                                                                                                                  \
    0, 255, 127, 255                                                                                                 \
  }
#define CONST_SPRINGGREEN2                                                                                           \
  {                                                                                                                  \
    0, 238, 118, 255                                                                                                 \
  }
#define CONST_SPRINGGREEN3                                                                                           \
  {                                                                                                                  \
    0, 205, 102, 255                                                                                                 \
  }
#define CONST_SPRINGGREEN4                                                                                           \
  {                                                                                                                  \
    0, 139, 69, 255                                                                                                  \
  }
#define CONST_SPRINGGREEN                                                                                            \
  {                                                                                                                  \
    0, 255, 127, 255                                                                                                 \
  }
#define CONST_STEELBLUE1                                                                                             \
  {                                                                                                                  \
    99, 184, 255, 255                                                                                                \
  }
#define CONST_STEELBLUE2                                                                                             \
  {                                                                                                                  \
    92, 172, 238, 255                                                                                                \
  }
#define CONST_STEELBLUE3                                                                                             \
  {                                                                                                                  \
    79, 148, 205, 255                                                                                                \
  }
#define CONST_STEELBLUE4                                                                                             \
  {                                                                                                                  \
    54, 100, 139, 255                                                                                                \
  }
#define CONST_STEELBLUE                                                                                              \
  {                                                                                                                  \
    70, 130, 180, 255                                                                                                \
  }
#define CONST_TAN1                                                                                                   \
  {                                                                                                                  \
    255, 165, 79, 255                                                                                                \
  }
#define CONST_TAN2                                                                                                   \
  {                                                                                                                  \
    238, 154, 73, 255                                                                                                \
  }
#define CONST_TAN3                                                                                                   \
  {                                                                                                                  \
    205, 133, 63, 255                                                                                                \
  }
#define CONST_TAN4                                                                                                   \
  {                                                                                                                  \
    139, 90, 43, 255                                                                                                 \
  }
#define CONST_TAN                                                                                                    \
  {                                                                                                                  \
    210, 180, 140, 255                                                                                               \
  }
#define CONST_THISTLE1                                                                                               \
  {                                                                                                                  \
    255, 225, 255, 255                                                                                               \
  }
#define CONST_THISTLE2                                                                                               \
  {                                                                                                                  \
    238, 210, 238, 255                                                                                               \
  }
#define CONST_THISTLE3                                                                                               \
  {                                                                                                                  \
    205, 181, 205, 255                                                                                               \
  }
#define CONST_THISTLE4                                                                                               \
  {                                                                                                                  \
    139, 123, 139, 255                                                                                               \
  }
#define CONST_THISTLE                                                                                                \
  {                                                                                                                  \
    216, 191, 216, 255                                                                                               \
  }
#define CONST_TOMATO1                                                                                                \
  {                                                                                                                  \
    255, 99, 71, 255                                                                                                 \
  }
#define CONST_TOMATO2                                                                                                \
  {                                                                                                                  \
    238, 92, 66, 255                                                                                                 \
  }
#define CONST_TOMATO3                                                                                                \
  {                                                                                                                  \
    205, 79, 57, 255                                                                                                 \
  }
#define CONST_TOMATO4                                                                                                \
  {                                                                                                                  \
    139, 54, 38, 255                                                                                                 \
  }
#define CONST_TOMATO                                                                                                 \
  {                                                                                                                  \
    255, 99, 71, 255                                                                                                 \
  }
#define CONST_TURQUOISE1                                                                                             \
  {                                                                                                                  \
    0, 245, 255, 255                                                                                                 \
  }
#define CONST_TURQUOISE2                                                                                             \
  {                                                                                                                  \
    0, 229, 238, 255                                                                                                 \
  }
#define CONST_TURQUOISE3                                                                                             \
  {                                                                                                                  \
    0, 197, 205, 255                                                                                                 \
  }
#define CONST_TURQUOISE4                                                                                             \
  {                                                                                                                  \
    0, 134, 139, 255                                                                                                 \
  }
#define CONST_TURQUOISE                                                                                              \
  {                                                                                                                  \
    64, 224, 208, 255                                                                                                \
  }
#define CONST_VIOLET                                                                                                 \
  {                                                                                                                  \
    238, 130, 238, 255                                                                                               \
  }
#define CONST_VIOLETRED1                                                                                             \
  {                                                                                                                  \
    255, 62, 150, 255                                                                                                \
  }
#define CONST_VIOLETRED2                                                                                             \
  {                                                                                                                  \
    238, 58, 140, 255                                                                                                \
  }
#define CONST_VIOLETRED3                                                                                             \
  {                                                                                                                  \
    205, 50, 120, 255                                                                                                \
  }
#define CONST_VIOLETRED4                                                                                             \
  {                                                                                                                  \
    139, 34, 82, 255                                                                                                 \
  }
#define CONST_VIOLETRED                                                                                              \
  {                                                                                                                  \
    208, 32, 144, 255                                                                                                \
  }
#define CONST_WHITE                                                                                                  \
  {                                                                                                                  \
    255, 255, 255, 255                                                                                               \
  }
#define CONST_WHITE_SMOKE                                                                                            \
  {                                                                                                                  \
    245, 245, 245, 255                                                                                               \
  }
#define CONST_WHITESMOKE                                                                                             \
  {                                                                                                                  \
    245, 245, 245, 255                                                                                               \
  }
#define CONST_YELLOW1                                                                                                \
  {                                                                                                                  \
    255, 255, 0, 255                                                                                                 \
  }
#define CONST_YELLOW2                                                                                                \
  {                                                                                                                  \
    238, 238, 0, 255                                                                                                 \
  }
#define CONST_YELLOW3                                                                                                \
  {                                                                                                                  \
    205, 205, 0, 255                                                                                                 \
  }
#define CONST_YELLOW4                                                                                                \
  {                                                                                                                  \
    139, 139, 0, 255                                                                                                 \
  }
#define CONST_YELLOWGREEN                                                                                            \
  {                                                                                                                  \
    154, 205, 50, 255                                                                                                \
  }
#define CONST_YELLOW                                                                                                 \
  {                                                                                                                  \
    255, 255, 0, 255                                                                                                 \
  }
#define CONST_INK                                                                                                    \
  {                                                                                                                  \
    51, 54, 47, 47                                                                                                   \
  }
#endif

extern color gl_last_color;
extern color gl_save_color;

extern color BLACK;
extern color BLUE;
extern color COLOR_NONE;
extern color DARKRED;
extern color GRAY10;
extern color GRAY20;
extern color GRAY30;
extern color GRAY31;
extern color GRAY50;
extern color GRAY60;
extern color GRAY70;
extern color GRAY80;
extern color GRAY90;
extern color GRAY;
extern color GREEN;
extern color ORANGE;
extern color PURPLE;
extern color RED;
extern color WHITE;
extern color YELLOW;
extern color DARKBLUE;
extern color DARKGREEN;
extern color BROWN;
extern color BLUE1;
extern color BLUE2;
extern color BLUE4;
extern color BLUE3;
extern color PINK;
extern color DARKGRAY;
extern color GRAY40;
extern color LIGHTBLUE;
extern color FORESTGREEN;
extern color BROWN1;
extern color BROWN2;
extern color BROWN3;
extern color BROWN4;

color       color_find(const char *s);
color       color_to_mono(color a);
color       gl_color_current(void);
color       string2color(const char **s);
color       string2color(const wchar_t **s);
color       string2color(std::string &s);
color       string2color(std::string &s, int *len);
color       string2color(std::wstring &s, int *len);
const char *string2colorname(const char **s);
std::string string2colorname(std::string &s);
void        color_fini(void);
void        color_init(void);
void        color_init1(void);
void        color_init2(void);
void        color_init3(void);
void        color_init4(void);
void        color_set(std::string name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void        glcolor_restore(void);
void        glcolor_save(void);

#endif // _MY_COLOR_HPP_
