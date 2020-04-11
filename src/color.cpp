//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_gl.h"
#include "my_string.h"
#include <cstring>

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
    color_set("aliceblue", &ALICEBLUE, 240, 248, 255, 255);
    color_set("antiquewhite1", &ANTIQUEWHITE1, 255, 239, 219, 255);
    color_set("antiquewhite2", &ANTIQUEWHITE2, 238, 223, 204, 255);
    color_set("antiquewhite3", &ANTIQUEWHITE3, 205, 192, 176, 255);
    color_set("antiquewhite4", &ANTIQUEWHITE4, 139, 131, 120, 255);
    color_set("antiquewhite", &ANTIQUEWHITE, 250, 235, 215, 255);
    color_set("aquamarine1", &AQUAMARINE1, 127, 255, 212, 255);
    color_set("aquamarine2", &AQUAMARINE2, 118, 238, 198, 255);
    color_set("aquamarine3", &AQUAMARINE3, 102, 205, 170, 255);
    color_set("aquamarine4", &AQUAMARINE4, 69, 139, 116, 255);
    color_set("aquamarine", &AQUAMARINE, 127, 255, 212, 255);
    color_set("azure1", &AZURE1, 240, 255, 255, 255);
    color_set("azure2", &AZURE2, 224, 238, 238, 255);
    color_set("azure3", &AZURE3, 193, 205, 205, 255);
    color_set("azure4", &AZURE4, 131, 139, 139, 255);
    color_set("azure", &AZURE, 240, 255, 255, 255);
    color_set("beige", &BEIGE, 245, 245, 220, 255);
    color_set("bisque1", &BISQUE1, 255, 228, 196, 255);
    color_set("bisque2", &BISQUE2, 238, 213, 183, 255);
    color_set("bisque3", &BISQUE3, 205, 183, 158, 255);
    color_set("bisque4", &BISQUE4, 139, 125, 107, 255);
    color_set("bisque", &BISQUE, 255, 228, 196, 255);
    color_set("black", &BLACK, 0, 0, 0, 255);
    color_set("none", &COLOR_NONE, 0, 0, 0, 0);
    color_set("blanchedalmond", &BLANCHEDALMOND, 255, 235, 205, 255);
    color_set("blue1", &BLUE1, 0, 0, 255, 255);
    color_set("blue2", &BLUE2, 0, 0, 238, 255);
    color_set("blue3", &BLUE3, 0, 0, 205, 255);
    color_set("blue4", &BLUE4, 0, 0, 139, 255);
    color_set("blue", &BLUE, 0, 0, 255, 255);
    color_set("blueviolet", &BLUEVIOLET, 138, 43, 226, 255);
    color_set("brown1", &BROWN1, 255, 64, 64, 255);
    color_set("brown2", &BROWN2, 238, 59, 59, 255);
    color_set("brown3", &BROWN3, 205, 51, 51, 255);
    color_set("brown4", &BROWN4, 139, 35, 35, 255);
    color_set("brown", &BROWN, 165, 42, 42, 255);
    color_set("burlywood1", &BURLYWOOD1, 255, 211, 155, 255);
    color_set("burlywood2", &BURLYWOOD2, 238, 197, 145, 255);
    color_set("burlywood3", &BURLYWOOD3, 205, 170, 125, 255);
    color_set("burlywood4", &BURLYWOOD4, 139, 115, 85, 255);
    color_set("burlywood", &BURLYWOOD, 222, 184, 135, 255);
    color_set("cadetblue1", &CADETBLUE1, 152, 245, 255, 255);
    color_set("cadetblue2", &CADETBLUE2, 142, 229, 238, 255);
    color_set("cadetblue3", &CADETBLUE3, 122, 197, 205, 255);
    color_set("cadetblue4", &CADETBLUE4, 83, 134, 139, 255);
    color_set("cadetblue", &CADETBLUE, 95, 158, 160, 255);
    color_set("chartreuse1", &CHARTREUSE1, 127, 255, 0, 255);
    color_set("chartreuse2", &CHARTREUSE2, 118, 238, 0, 255);
    color_set("chartreuse3", &CHARTREUSE3, 102, 205, 0, 255);
    color_set("chartreuse4", &CHARTREUSE4, 69, 139, 0, 255);
    color_set("chartreuse", &CHARTREUSE, 127, 255, 0, 255);
    color_set("chocolate1", &CHOCOLATE1, 255, 127, 36, 255);
    color_set("chocolate2", &CHOCOLATE2, 238, 118, 33, 255);
    color_set("chocolate3", &CHOCOLATE3, 205, 102, 29, 255);
    color_set("chocolate4", &CHOCOLATE4, 139, 69, 19, 255);
    color_set("chocolate", &CHOCOLATE, 210, 105, 30, 255);
    color_set("coral1", &CORAL1, 255, 114, 86, 255);
    color_set("coral2", &CORAL2, 238, 106, 80, 255);
    color_set("coral3", &CORAL3, 205, 91, 69, 255);
    color_set("coral4", &CORAL4, 139, 62, 47, 255);
    color_set("coral", &CORAL, 255, 127, 80, 255);
    color_set("cornflowerblue", &CORNFLOWERBLUE, 100, 149, 237, 255);
    color_set("cornsilk1", &CORNSILK1, 255, 248, 220, 255);
    color_set("cornsilk2", &CORNSILK2, 238, 232, 205, 255);
    color_set("cornsilk3", &CORNSILK3, 205, 200, 177, 255);
    color_set("cornsilk4", &CORNSILK4, 139, 136, 120, 255);
    color_set("cornsilk", &CORNSILK, 255, 248, 220, 255);
    color_set("cyan1", &CYAN1, 0, 255, 255, 255);
    color_set("cyan2", &CYAN2, 0, 238, 238, 255);
    color_set("cyan3", &CYAN3, 0, 205, 205, 255);
    color_set("cyan4", &CYAN4, 0, 139, 139, 255);
    color_set("cyan", &CYAN, 0, 255, 255, 255);
    color_set("darkblue", &DARKBLUE, 0, 0, 139, 255);
    color_set("darkcyan", &DARKCYAN, 0, 139, 139, 255);
    color_set("darkgoldenrod1", &DARKGOLDENROD1, 255, 185, 15, 255);
    color_set("darkgoldenrod2", &DARKGOLDENROD2, 238, 173, 14, 255);
    color_set("darkgoldenrod3", &DARKGOLDENROD3, 205, 149, 12, 255);
    color_set("darkgoldenrod4", &DARKGOLDENROD4, 139, 101, 8, 255);
    color_set("darkgoldenrod", &DARKGOLDENROD, 184, 134, 11, 255);
    color_set("darkgray", &DARKGRAY, 169, 169, 169, 255);
    color_set("darkgreen", &DARKGREEN, 0, 100, 0, 255);
    color_set("darkgrey", &DARKGREY, 169, 169, 169, 255);
    color_set("darkkhaki", &DARKKHAKI, 189, 183, 107, 255);
    color_set("darkmagenta", &DARKMAGENTA, 139, 0, 139, 255);
    color_set("darkolivegreen1", &DARKOLIVEGREEN1, 202, 255, 112, 255);
    color_set("darkolivegreen2", &DARKOLIVEGREEN2, 188, 238, 104, 255);
    color_set("darkolivegreen3", &DARKOLIVEGREEN3, 162, 205, 90, 255);
    color_set("darkolivegreen4", &DARKOLIVEGREEN4, 110, 139, 61, 255);
    color_set("darkolivegreen", &DARKOLIVEGREEN, 85, 107, 47, 255);
    color_set("darkorange1", &DARKORANGE1, 255, 127, 0, 255);
    color_set("darkorange2", &DARKORANGE2, 238, 118, 0, 255);
    color_set("darkorange3", &DARKORANGE3, 205, 102, 0, 255);
    color_set("darkorange4", &DARKORANGE4, 139, 69, 0, 255);
    color_set("darkorange", &DARKORANGE, 255, 140, 0, 255);
    color_set("darkorchid1", &DARKORCHID1, 191, 62, 255, 255);
    color_set("darkorchid2", &DARKORCHID2, 178, 58, 238, 255);
    color_set("darkorchid3", &DARKORCHID3, 154, 50, 205, 255);
    color_set("darkorchid4", &DARKORCHID4, 104, 34, 139, 255);
    color_set("darkorchid", &DARKORCHID, 153, 50, 204, 255);
    color_set("darkred", &DARKRED, 139, 0, 0, 255);
    color_set("darksalmon", &DARKSALMON, 233, 150, 122, 255);
    color_set("darkseagreen1", &DARKSEAGREEN1, 193, 255, 193, 255);
    color_set("darkseagreen2", &DARKSEAGREEN2, 180, 238, 180, 255);
    color_set("darkseagreen3", &DARKSEAGREEN3, 155, 205, 155, 255);
    color_set("darkseagreen4", &DARKSEAGREEN4, 105, 139, 105, 255);
    color_set("darkseagreen", &DARKSEAGREEN, 143, 188, 143, 255);
    color_set("darkslateblue", &DARKSLATEBLUE, 72, 61, 139, 255);
    color_set("vdarkslateblue", &VDARKSLATEBLUE, 42, 31, 109, 255);
    color_set("vvdarkslateblue", &VVDARKSLATEBLUE, 32, 21, 99, 255);
    color_set("darkslategray1", &DARKSLATEGRAY1, 151, 255, 255, 255);
    color_set("darkslategray2", &DARKSLATEGRAY2, 141, 238, 238, 255);
    color_set("darkslategray3", &DARKSLATEGRAY3, 121, 205, 205, 255);
    color_set("darkslategray4", &DARKSLATEGRAY4, 82, 139, 139, 255);
    color_set("darkslategray", &DARKSLATEGRAY, 47, 79, 79, 255);
    color_set("darkslategrey", &DARKSLATEGREY, 47, 79, 79, 255);
    color_set("darkturquoise", &DARKTURQUOISE, 0, 206, 209, 255);
    color_set("darkviolet", &DARKVIOLET, 148, 0, 211, 255);
    color_set("deeppink1", &DEEPPINK1, 255, 20, 147, 255);
    color_set("deeppink2", &DEEPPINK2, 238, 18, 137, 255);
    color_set("deeppink3", &DEEPPINK3, 205, 16, 118, 255);
    color_set("deeppink4", &DEEPPINK4, 139, 10, 80, 255);
    color_set("deeppink", &DEEPPINK, 255, 20, 147, 255);
    color_set("deepskyblue1", &DEEPSKYBLUE1, 0, 191, 255, 255);
    color_set("deepskyblue2", &DEEPSKYBLUE2, 0, 178, 238, 255);
    color_set("deepskyblue3", &DEEPSKYBLUE3, 0, 154, 205, 255);
    color_set("deepskyblue4", &DEEPSKYBLUE4, 0, 104, 139, 255);
    color_set("deepskyblue", &DEEPSKYBLUE, 0, 191, 255, 255);
    color_set("dimgray", &DIMGRAY, 105, 105, 105, 255);
    color_set("dimgrey", &DIMGREY, 105, 105, 105, 255);
    color_set("dodgerblue1", &DODGERBLUE1, 30, 144, 255, 255);
    color_set("dodgerblue2", &DODGERBLUE2, 28, 134, 238, 255);
    color_set("dodgerblue3", &DODGERBLUE3, 24, 116, 205, 255);
    color_set("dodgerblue4", &DODGERBLUE4, 16, 78, 139, 255);
    color_set("dodgerblue", &DODGERBLUE, 30, 144, 255, 255);
    color_set("firebrick1", &FIREBRICK1, 255, 48, 48, 255);
    color_set("firebrick2", &FIREBRICK2, 238, 44, 44, 255);
    color_set("firebrick3", &FIREBRICK3, 205, 38, 38, 255);
    color_set("firebrick4", &FIREBRICK4, 139, 26, 26, 255);
    color_set("firebrick", &FIREBRICK, 178, 34, 34, 255);
    color_set("floralwhite", &FLORALWHITE, 255, 250, 240, 255);
    color_set("forestgreen", &FORESTGREEN, 34, 139, 34, 255);
    color_set("gainsboro", &GAINSBORO, 220, 220, 220, 255);
    color_set("ghostwhite", &GHOSTWHITE, 248, 248, 255, 255);
    color_set("gold1", &GOLD1, 255, 215, 0, 255);
    color_set("gold2", &GOLD2, 238, 201, 0, 255);
    color_set("gold3", &GOLD3, 205, 173, 0, 255);
    color_set("gold4", &GOLD4, 139, 117, 0, 255);
    color_set("goldenrod1", &GOLDENROD1, 255, 193, 37, 255);
    color_set("goldenrod2", &GOLDENROD2, 238, 180, 34, 255);
    color_set("goldenrod3", &GOLDENROD3, 205, 155, 29, 255);
    color_set("goldenrod4", &GOLDENROD4, 139, 105, 20, 255);
    color_set("goldenrod", &GOLDENROD, 218, 165, 32, 255);
    color_set("gold", &GOLD, 255, 215, 0, 255);
    color_set("gray10", &GRAY10, 26, 26, 26, 255);
    color_set("gray11", &GRAY11, 28, 28, 28, 255);
    color_set("gray12", &GRAY12, 31, 31, 31, 255);
    color_set("gray13", &GRAY13, 33, 33, 33, 255);
    color_set("gray14", &GRAY14, 36, 36, 36, 255);
    color_set("gray15", &GRAY15, 38, 38, 38, 255);
    color_set("gray16", &GRAY16, 41, 41, 41, 255);
    color_set("gray17", &GRAY17, 43, 43, 43, 255);
    color_set("gray18", &GRAY18, 46, 46, 46, 255);
    color_set("gray19", &GRAY19, 48, 48, 48, 255);
    color_set("gray1", &GRAY1, 3, 3, 3, 255);
    color_set("gray20", &GRAY20, 51, 51, 51, 255);
    color_set("gray21", &GRAY21, 54, 54, 54, 255);
    color_set("gray22", &GRAY22, 56, 56, 56, 255);
    color_set("gray23", &GRAY23, 59, 59, 59, 255);
    color_set("gray24", &GRAY24, 61, 61, 61, 255);
    color_set("gray25", &GRAY25, 64, 64, 64, 255);
    color_set("gray26", &GRAY26, 66, 66, 66, 255);
    color_set("gray27", &GRAY27, 69, 69, 69, 255);
    color_set("gray28", &GRAY28, 71, 71, 71, 255);
    color_set("gray29", &GRAY29, 74, 74, 74, 255);
    color_set("gray2", &GRAY2, 5, 5, 5, 255);
    color_set("gray30", &GRAY30, 77, 77, 77, 255);
    color_set("gray31", &GRAY31, 79, 79, 79, 255);
    color_set("gray32", &GRAY32, 82, 82, 82, 255);
    color_set("gray33", &GRAY33, 84, 84, 84, 255);
    color_set("gray34", &GRAY34, 87, 87, 87, 255);
    color_set("gray35", &GRAY35, 89, 89, 89, 255);
    color_set("gray36", &GRAY36, 92, 92, 92, 255);
    color_set("gray37", &GRAY37, 94, 94, 94, 255);
    color_set("gray38", &GRAY38, 97, 97, 97, 255);
    color_set("gray39", &GRAY39, 99, 99, 99, 255);
    color_set("gray3", &GRAY3, 8, 8, 8, 255);
    color_set("gray40", &GRAY40, 102, 102, 102, 255);
    color_set("gray41", &GRAY41, 105, 105, 105, 255);
    color_set("gray42", &GRAY42, 107, 107, 107, 255);
    color_set("gray43", &GRAY43, 110, 110, 110, 255);
    color_set("gray44", &GRAY44, 112, 112, 112, 255);
    color_set("gray45", &GRAY45, 115, 115, 115, 255);
    color_set("gray46", &GRAY46, 117, 117, 117, 255);
    color_set("gray47", &GRAY47, 120, 120, 120, 255);
    color_set("gray48", &GRAY48, 122, 122, 122, 255);
    color_set("gray49", &GRAY49, 125, 125, 125, 255);
    color_set("gray4", &GRAY4, 10, 10, 10, 255);
    color_set("gray50", &GRAY50, 127, 127, 127, 255);
    color_set("gray51", &GRAY51, 130, 130, 130, 255);
    color_set("gray52", &GRAY52, 133, 133, 133, 255);
    color_set("gray53", &GRAY53, 135, 135, 135, 255);
    color_set("gray54", &GRAY54, 138, 138, 138, 255);
    color_set("gray55", &GRAY55, 140, 140, 140, 255);
    color_set("gray56", &GRAY56, 143, 143, 143, 255);
    color_set("gray57", &GRAY57, 145, 145, 145, 255);
    color_set("gray58", &GRAY58, 148, 148, 148, 255);
    color_set("gray59", &GRAY59, 150, 150, 150, 255);
    color_set("gray5", &GRAY5, 13, 13, 13, 255);
    color_set("gray60", &GRAY60, 153, 153, 153, 255);
    color_set("gray61", &GRAY61, 156, 156, 156, 255);
    color_set("gray62", &GRAY62, 158, 158, 158, 255);
    color_set("gray63", &GRAY63, 161, 161, 161, 255);
    color_set("gray64", &GRAY64, 163, 163, 163, 255);
    color_set("gray65", &GRAY65, 166, 166, 166, 255);
    color_set("gray66", &GRAY66, 168, 168, 168, 255);
    color_set("gray67", &GRAY67, 171, 171, 171, 255);
    color_set("gray68", &GRAY68, 173, 173, 173, 255);
    color_set("gray69", &GRAY69, 176, 176, 176, 255);
    color_set("gray6", &GRAY6, 15, 15, 15, 255);
    color_set("gray70", &GRAY70, 179, 179, 179, 255);
    color_set("gray71", &GRAY71, 181, 181, 181, 255);
    color_set("gray72", &GRAY72, 184, 184, 184, 255);
    color_set("gray73", &GRAY73, 186, 186, 186, 255);
    color_set("gray74", &GRAY74, 189, 189, 189, 255);
    color_set("gray75", &GRAY75, 191, 191, 191, 255);
    color_set("gray76", &GRAY76, 194, 194, 194, 255);
    color_set("gray77", &GRAY77, 196, 196, 196, 255);
    color_set("gray78", &GRAY78, 199, 199, 199, 255);
    color_set("gray79", &GRAY79, 201, 201, 201, 255);
    color_set("gray7", &GRAY7, 18, 18, 18, 255);
    color_set("gray80", &GRAY80, 204, 204, 204, 255);
    color_set("gray81", &GRAY81, 207, 207, 207, 255);
    color_set("gray82", &GRAY82, 209, 209, 209, 255);
    color_set("gray83", &GRAY83, 212, 212, 212, 255);
    color_set("gray84", &GRAY84, 214, 214, 214, 255);
    color_set("gray85", &GRAY85, 217, 217, 217, 255);
    color_set("gray86", &GRAY86, 219, 219, 219, 255);
    color_set("gray87", &GRAY87, 222, 222, 222, 255);
    color_set("gray88", &GRAY88, 224, 224, 224, 255);
    color_set("gray89", &GRAY89, 227, 227, 227, 255);
    color_set("gray8", &GRAY8, 20, 20, 20, 255);
    color_set("gray90", &GRAY90, 229, 229, 229, 255);
    color_set("gray91", &GRAY91, 232, 232, 232, 255);
    color_set("gray92", &GRAY92, 235, 235, 235, 255);
    color_set("gray93", &GRAY93, 237, 237, 237, 255);
    color_set("gray94", &GRAY94, 240, 240, 240, 255);
    color_set("gray95", &GRAY95, 242, 242, 242, 255);
    color_set("gray96", &GRAY96, 245, 245, 245, 255);
    color_set("gray97", &GRAY97, 247, 247, 247, 255);
    color_set("gray98", &GRAY98, 250, 250, 250, 255);
    color_set("gray99", &GRAY99, 252, 252, 252, 255);
    color_set("gray9", &GRAY9, 23, 23, 23, 255);
    color_set("gray", &GRAY, 190, 190, 190, 255);
    color_set("green1", &GREEN1, 0, 255, 0, 255);
    color_set("green2", &GREEN2, 0, 238, 0, 255);
    color_set("green3", &GREEN3, 0, 205, 0, 255);
    color_set("green4", &GREEN4, 0, 139, 0, 255);
    color_set("green", &GREEN, 0, 255, 0, 255);
    color_set("greenyellow", &GREENYELLOW, 173, 255, 47, 255);
    color_set("grey10", &GREY10, 26, 26, 26, 255);
    color_set("grey11", &GREY11, 28, 28, 28, 255);
    color_set("grey12", &GREY12, 31, 31, 31, 255);
    color_set("grey13", &GREY13, 33, 33, 33, 255);
    color_set("grey14", &GREY14, 36, 36, 36, 255);
    color_set("grey15", &GREY15, 38, 38, 38, 255);
    color_set("grey16", &GREY16, 41, 41, 41, 255);
    color_set("grey17", &GREY17, 43, 43, 43, 255);
    color_set("grey18", &GREY18, 46, 46, 46, 255);
    color_set("grey19", &GREY19, 48, 48, 48, 255);
    color_set("grey1", &GREY1, 3, 3, 3, 255);
    color_set("grey20", &GREY20, 51, 51, 51, 255);
    color_set("grey21", &GREY21, 54, 54, 54, 255);
    color_set("grey22", &GREY22, 56, 56, 56, 255);
    color_set("grey23", &GREY23, 59, 59, 59, 255);
    color_set("grey24", &GREY24, 61, 61, 61, 255);
    color_set("grey25", &GREY25, 64, 64, 64, 255);
    color_set("grey26", &GREY26, 66, 66, 66, 255);
    color_set("grey27", &GREY27, 69, 69, 69, 255);
    color_set("grey28", &GREY28, 71, 71, 71, 255);
    color_set("grey29", &GREY29, 74, 74, 74, 255);
    color_set("grey2", &GREY2, 5, 5, 5, 255);
    color_set("grey30", &GREY30, 77, 77, 77, 255);
    color_set("grey31", &GREY31, 79, 79, 79, 255);
    color_set("grey32", &GREY32, 82, 82, 82, 255);
    color_set("grey33", &GREY33, 84, 84, 84, 255);
    color_set("grey34", &GREY34, 87, 87, 87, 255);
    color_set("grey35", &GREY35, 89, 89, 89, 255);
    color_set("grey36", &GREY36, 92, 92, 92, 255);
    color_set("grey37", &GREY37, 94, 94, 94, 255);
    color_set("grey38", &GREY38, 97, 97, 97, 255);
    color_set("grey39", &GREY39, 99, 99, 99, 255);
    color_set("grey3", &GREY3, 8, 8, 8, 255);
    color_set("grey40", &GREY40, 102, 102, 102, 255);
    color_set("grey41", &GREY41, 105, 105, 105, 255);
    color_set("grey42", &GREY42, 107, 107, 107, 255);
    color_set("grey43", &GREY43, 110, 110, 110, 255);
    color_set("grey44", &GREY44, 112, 112, 112, 255);
    color_set("grey45", &GREY45, 115, 115, 115, 255);
    color_set("grey46", &GREY46, 117, 117, 117, 255);
    color_set("grey47", &GREY47, 120, 120, 120, 255);
    color_set("grey48", &GREY48, 122, 122, 122, 255);
    color_set("grey49", &GREY49, 125, 125, 125, 255);
    color_set("grey4", &GREY4, 10, 10, 10, 255);
    color_set("grey50", &GREY50, 127, 127, 127, 255);
    color_set("grey51", &GREY51, 130, 130, 130, 255);
    color_set("grey52", &GREY52, 133, 133, 133, 255);
    color_set("grey53", &GREY53, 135, 135, 135, 255);
    color_set("grey54", &GREY54, 138, 138, 138, 255);
    color_set("grey55", &GREY55, 140, 140, 140, 255);
    color_set("grey56", &GREY56, 143, 143, 143, 255);
    color_set("grey57", &GREY57, 145, 145, 145, 255);
    color_set("grey58", &GREY58, 148, 148, 148, 255);
    color_set("grey59", &GREY59, 150, 150, 150, 255);
    color_set("grey5", &GREY5, 13, 13, 13, 255);
    color_set("grey60", &GREY60, 153, 153, 153, 255);
    color_set("grey61", &GREY61, 156, 156, 156, 255);
    color_set("grey62", &GREY62, 158, 158, 158, 255);
    color_set("grey63", &GREY63, 161, 161, 161, 255);
    color_set("grey64", &GREY64, 163, 163, 163, 255);
    color_set("grey65", &GREY65, 166, 166, 166, 255);
    color_set("grey66", &GREY66, 168, 168, 168, 255);
    color_set("grey67", &GREY67, 171, 171, 171, 255);
    color_set("grey68", &GREY68, 173, 173, 173, 255);
    color_set("grey69", &GREY69, 176, 176, 176, 255);
    color_set("grey6", &GREY6, 15, 15, 15, 255);
    color_set("grey70", &GREY70, 179, 179, 179, 255);
    color_set("grey71", &GREY71, 181, 181, 181, 255);
    color_set("grey72", &GREY72, 184, 184, 184, 255);
    color_set("grey73", &GREY73, 186, 186, 186, 255);
    color_set("grey74", &GREY74, 189, 189, 189, 255);
    color_set("grey75", &GREY75, 191, 191, 191, 255);
    color_set("grey76", &GREY76, 194, 194, 194, 255);
    color_set("grey77", &GREY77, 196, 196, 196, 255);
    color_set("grey78", &GREY78, 199, 199, 199, 255);
    color_set("grey79", &GREY79, 201, 201, 201, 255);
    color_set("grey7", &GREY7, 18, 18, 18, 255);
    color_set("grey80", &GREY80, 204, 204, 204, 255);
    color_set("grey81", &GREY81, 207, 207, 207, 255);
    color_set("grey82", &GREY82, 209, 209, 209, 255);
    color_set("grey83", &GREY83, 212, 212, 212, 255);
    color_set("grey84", &GREY84, 214, 214, 214, 255);
    color_set("grey85", &GREY85, 217, 217, 217, 255);
    color_set("grey86", &GREY86, 219, 219, 219, 255);
    color_set("grey87", &GREY87, 222, 222, 222, 255);
    color_set("grey88", &GREY88, 224, 224, 224, 255);
    color_set("grey89", &GREY89, 227, 227, 227, 255);
    color_set("grey8", &GREY8, 20, 20, 20, 255);
    color_set("grey90", &GREY90, 229, 229, 229, 255);
    color_set("grey91", &GREY91, 232, 232, 232, 255);
    color_set("grey92", &GREY92, 235, 235, 235, 255);
    color_set("grey93", &GREY93, 237, 237, 237, 255);
    color_set("grey94", &GREY94, 240, 240, 240, 255);
    color_set("grey95", &GREY95, 242, 242, 242, 255);
    color_set("grey96", &GREY96, 245, 245, 245, 255);
    color_set("grey97", &GREY97, 247, 247, 247, 255);
    color_set("grey98", &GREY98, 250, 250, 250, 255);
    color_set("grey99", &GREY99, 252, 252, 252, 255);
    color_set("grey9", &GREY9, 23, 23, 23, 255);
    color_set("grey", &GREY, 190, 190, 190, 255);
    color_set("honeydew1", &HONEYDEW1, 240, 255, 240, 255);
    color_set("honeydew2", &HONEYDEW2, 224, 238, 224, 255);
    color_set("honeydew3", &HONEYDEW3, 193, 205, 193, 255);
    color_set("honeydew4", &HONEYDEW4, 131, 139, 131, 255);
    color_set("honeydew", &HONEYDEW, 240, 255, 240, 255);
    color_set("hotpink1", &HOTPINK1, 255, 110, 180, 255);
    color_set("hotpink2", &HOTPINK2, 238, 106, 167, 255);
    color_set("hotpink3", &HOTPINK3, 205, 96, 144, 255);
    color_set("hotpink4", &HOTPINK4, 139, 58, 98, 255);
    color_set("hotpink", &HOTPINK, 255, 105, 180, 255);
    color_set("indianred1", &INDIANRED1, 255, 106, 106, 255);
    color_set("indianred2", &INDIANRED2, 238, 99, 99, 255);
    color_set("indianred3", &INDIANRED3, 205, 85, 85, 255);
    color_set("indianred4", &INDIANRED4, 139, 58, 58, 255);
    color_set("indianred", &INDIANRED, 205, 92, 92, 255);
    color_set("ivory1", &IVORY1, 255, 255, 240, 255);
    color_set("ivory2", &IVORY2, 238, 238, 224, 255);
    color_set("ivory3", &IVORY3, 205, 205, 193, 255);
    color_set("ivory4", &IVORY4, 139, 139, 131, 255);
    color_set("ivory", &IVORY, 255, 255, 240, 255);
    color_set("khaki1", &KHAKI1, 255, 246, 143, 255);
    color_set("khaki2", &KHAKI2, 238, 230, 133, 255);
    color_set("khaki3", &KHAKI3, 205, 198, 115, 255);
    color_set("khaki4", &KHAKI4, 139, 134, 78, 255);
    color_set("khaki", &KHAKI, 240, 230, 140, 255);
    color_set("lavenderblush1", &LAVENDERBLUSH1, 255, 240, 245, 255);
    color_set("lavenderblush2", &LAVENDERBLUSH2, 238, 224, 229, 255);
    color_set("lavenderblush3", &LAVENDERBLUSH3, 205, 193, 197, 255);
    color_set("lavenderblush4", &LAVENDERBLUSH4, 139, 131, 134, 255);
    color_set("lavender_blush", &LAVENDER_BLUSH, 255, 240, 245, 255);
    color_set("lavenderblush", &LAVENDERBLUSH, 255, 240, 245, 255);
    color_set("lavender", &LAVENDER, 230, 230, 250, 255);
    color_set("lawn_green", &LAWN_GREEN, 124, 252, 0, 255);
    color_set("lawngreen", &LAWNGREEN, 124, 252, 0, 255);
    color_set("lemonchiffon1", &LEMONCHIFFON1, 255, 250, 205, 255);
    color_set("lemonchiffon2", &LEMONCHIFFON2, 238, 233, 191, 255);
    color_set("lemonchiffon3", &LEMONCHIFFON3, 205, 201, 165, 255);
    color_set("lemonchiffon4", &LEMONCHIFFON4, 139, 137, 112, 255);
    color_set("lemon_chiffon", &LEMON_CHIFFON, 255, 250, 205, 255);
    color_set("lemonchiffon", &LEMONCHIFFON, 255, 250, 205, 255);
    color_set("lightblue1", &LIGHTBLUE1, 191, 239, 255, 255);
    color_set("lightblue2", &LIGHTBLUE2, 178, 223, 238, 255);
    color_set("lightblue3", &LIGHTBLUE3, 154, 192, 205, 255);
    color_set("lightblue4", &LIGHTBLUE4, 104, 131, 139, 255);
    color_set("light_blue", &LIGHT_BLUE, 173, 216, 230, 255);
    color_set("lightblue", &LIGHTBLUE, 173, 216, 230, 255);
    color_set("light_coral", &LIGHT_CORAL, 240, 128, 128, 255);
    color_set("lightcoral", &LIGHTCORAL, 240, 128, 128, 255);
    color_set("lightcyan1", &LIGHTCYAN1, 224, 255, 255, 255);
    color_set("lightcyan2", &LIGHTCYAN2, 209, 238, 238, 255);
    color_set("lightcyan3", &LIGHTCYAN3, 180, 205, 205, 255);
    color_set("lightcyan4", &LIGHTCYAN4, 122, 139, 139, 255);
    color_set("light_cyan", &LIGHT_CYAN, 224, 255, 255, 255);
    color_set("lightcyan", &LIGHTCYAN, 224, 255, 255, 255);
    color_set("lightgoldenrod1", &LIGHTGOLDENROD1, 255, 236, 139, 255);
    color_set("lightgoldenrod2", &LIGHTGOLDENROD2, 238, 220, 130, 255);
    color_set("lightgoldenrod3", &LIGHTGOLDENROD3, 205, 190, 112, 255);
    color_set("lightgoldenrod4", &LIGHTGOLDENROD4, 139, 129, 76, 255);
    color_set("light_goldenrod", &LIGHT_GOLDENROD, 238, 221, 130, 255);
    color_set("lightgoldenrod", &LIGHTGOLDENROD, 238, 221, 130, 255);
    color_set("light_goldenrod_yellow", &LIGHT_GOLDENROD_YELLOW, 250, 250, 210, 255);
    color_set("lightgoldenrodyellow", &LIGHTGOLDENRODYELLOW, 250, 250, 210, 255);
    color_set("light_gray", &LIGHT_GRAY, 211, 211, 211, 255);
    color_set("lightgray", &LIGHTGRAY, 211, 211, 211, 255);
    color_set("light_green", &LIGHT_GREEN, 144, 238, 144, 255);
    color_set("lightgreen", &LIGHTGREEN, 144, 238, 144, 255);
    color_set("light_grey", &LIGHT_GREY, 211, 211, 211, 255);
    color_set("lightgrey", &LIGHTGREY, 211, 211, 211, 255);
    color_set("lightpink1", &LIGHTPINK1, 255, 174, 185, 255);
    color_set("lightpink2", &LIGHTPINK2, 238, 162, 173, 255);
    color_set("lightpink3", &LIGHTPINK3, 205, 140, 149, 255);
    color_set("lightpink4", &LIGHTPINK4, 139, 95, 101, 255);
    color_set("light_pink", &LIGHT_PINK, 255, 182, 193, 255);
    color_set("lightpink", &LIGHTPINK, 255, 182, 193, 255);
    color_set("lightsalmon1", &LIGHTSALMON1, 255, 160, 122, 255);
    color_set("lightsalmon2", &LIGHTSALMON2, 238, 149, 114, 255);
    color_set("lightsalmon3", &LIGHTSALMON3, 205, 129, 98, 255);
    color_set("lightsalmon4", &LIGHTSALMON4, 139, 87, 66, 255);
    color_set("light_salmon", &LIGHT_SALMON, 255, 160, 122, 255);
    color_set("lightsalmon", &LIGHTSALMON, 255, 160, 122, 255);
    color_set("light_sea_green", &LIGHT_SEA_GREEN, 32, 178, 170, 255);
    color_set("lightseagreen", &LIGHTSEAGREEN, 32, 178, 170, 255);
    color_set("lightskyblue1", &LIGHTSKYBLUE1, 176, 226, 255, 255);
    color_set("lightskyblue2", &LIGHTSKYBLUE2, 164, 211, 238, 255);
    color_set("lightskyblue3", &LIGHTSKYBLUE3, 141, 182, 205, 255);
    color_set("lightskyblue4", &LIGHTSKYBLUE4, 96, 123, 139, 255);
    color_set("light_sky_blue", &LIGHT_SKY_BLUE, 135, 206, 250, 255);
    color_set("lightskyblue", &LIGHTSKYBLUE, 135, 206, 250, 255);
    color_set("light_slate_blue", &LIGHT_SLATE_BLUE, 132, 112, 255, 255);
    color_set("lightslateblue", &LIGHTSLATEBLUE, 132, 112, 255, 255);
    color_set("light_slate_gray", &LIGHT_SLATE_GRAY, 119, 136, 153, 255);
    color_set("lightslategray", &LIGHTSLATEGRAY, 119, 136, 153, 255);
    color_set("light_slate_grey", &LIGHT_SLATE_GREY, 119, 136, 153, 255);
    color_set("lightslategrey", &LIGHTSLATEGREY, 119, 136, 153, 255);
    color_set("lightsteelblue1", &LIGHTSTEELBLUE1, 202, 225, 255, 255);
    color_set("lightsteelblue2", &LIGHTSTEELBLUE2, 188, 210, 238, 255);
    color_set("lightsteelblue3", &LIGHTSTEELBLUE3, 162, 181, 205, 255);
    color_set("lightsteelblue4", &LIGHTSTEELBLUE4, 110, 123, 139, 255);
    color_set("light_steel_blue", &LIGHT_STEEL_BLUE, 176, 196, 222, 255);
    color_set("lightsteelblue", &LIGHTSTEELBLUE, 176, 196, 222, 255);
    color_set("lightyellow1", &LIGHTYELLOW1, 255, 255, 224, 255);
    color_set("lightyellow2", &LIGHTYELLOW2, 238, 238, 209, 255);
    color_set("lightyellow3", &LIGHTYELLOW3, 205, 205, 180, 255);
    color_set("lightyellow4", &LIGHTYELLOW4, 139, 139, 122, 255);
    color_set("light_yellow", &LIGHT_YELLOW, 255, 255, 224, 255);
    color_set("lightyellow", &LIGHTYELLOW, 255, 255, 224, 255);
    color_set("lime_green", &LIME_GREEN, 50, 205, 50, 255);
    color_set("limegreen", &LIMEGREEN, 50, 205, 50, 255);
    color_set("lime", &LIME, 50, 205, 50, 255);
    color_set("linen", &LINEN, 250, 240, 230, 255);
    color_set("magenta1", &MAGENTA1, 255, 0, 255, 255);
    color_set("magenta2", &MAGENTA2, 238, 0, 238, 255);
    color_set("magenta3", &MAGENTA3, 205, 0, 205, 255);
    color_set("magenta4", &MAGENTA4, 139, 0, 139, 255);
    color_set("magenta", &MAGENTA, 255, 0, 255, 255);
    color_set("maroon1", &MAROON1, 255, 52, 179, 255);
    color_set("maroon2", &MAROON2, 238, 48, 167, 255);
    color_set("maroon3", &MAROON3, 205, 41, 144, 255);
    color_set("maroon4", &MAROON4, 139, 28, 98, 255);
    color_set("maroon", &MAROON, 176, 48, 96, 255);
    color_set("medium_aquamarine", &MEDIUM_AQUAMARINE, 102, 205, 170, 255);
    color_set("mediumaquamarine", &MEDIUMAQUAMARINE, 102, 205, 170, 255);
    color_set("medium_blue", &MEDIUM_BLUE, 0, 0, 205, 255);
    color_set("mediumblue", &MEDIUMBLUE, 0, 0, 205, 255);
    color_set("mediumorchid1", &MEDIUMORCHID1, 224, 102, 255, 255);
    color_set("mediumorchid2", &MEDIUMORCHID2, 209, 95, 238, 255);
    color_set("mediumorchid3", &MEDIUMORCHID3, 180, 82, 205, 255);
    color_set("mediumorchid4", &MEDIUMORCHID4, 122, 55, 139, 255);
    color_set("medium_orchid", &MEDIUM_ORCHID, 186, 85, 211, 255);
    color_set("mediumorchid", &MEDIUMORCHID, 186, 85, 211, 255);
    color_set("mediumpurple1", &MEDIUMPURPLE1, 171, 130, 255, 255);
    color_set("mediumpurple2", &MEDIUMPURPLE2, 159, 121, 238, 255);
    color_set("mediumpurple3", &MEDIUMPURPLE3, 137, 104, 205, 255);
    color_set("mediumpurple4", &MEDIUMPURPLE4, 93, 71, 139, 255);
    color_set("medium_purple", &MEDIUM_PURPLE, 147, 112, 219, 255);
    color_set("mediumpurple", &MEDIUMPURPLE, 147, 112, 219, 255);
    color_set("medium_sea_green", &MEDIUM_SEA_GREEN, 60, 179, 113, 255);
    color_set("mediumseagreen", &MEDIUMSEAGREEN, 60, 179, 113, 255);
    color_set("medium_slate_blue", &MEDIUM_SLATE_BLUE, 123, 104, 238, 255);
    color_set("mediumslateblue", &MEDIUMSLATEBLUE, 123, 104, 238, 255);
    color_set("medium_spring_green", &MEDIUM_SPRING_GREEN, 0, 250, 154, 255);
    color_set("mediumspringgreen", &MEDIUMSPRINGGREEN, 0, 250, 154, 255);
    color_set("medium_turquoise", &MEDIUM_TURQUOISE, 72, 209, 204, 255);
    color_set("mediumturquoise", &MEDIUMTURQUOISE, 72, 209, 204, 255);
    color_set("medium_violet_red", &MEDIUM_VIOLET_RED, 199, 21, 133, 255);
    color_set("mediumvioletred", &MEDIUMVIOLETRED, 199, 21, 133, 255);
    color_set("midnight_blue", &MIDNIGHT_BLUE, 25, 25, 112, 255);
    color_set("midnightblue", &MIDNIGHTBLUE, 25, 25, 112, 255);
    color_set("mint_cream", &MINT_CREAM, 245, 255, 250, 255);
    color_set("mintcream", &MINTCREAM, 245, 255, 250, 255);
    color_set("mistyrose1", &MISTYROSE1, 255, 228, 225, 255);
    color_set("mistyrose2", &MISTYROSE2, 238, 213, 210, 255);
    color_set("mistyrose3", &MISTYROSE3, 205, 183, 181, 255);
    color_set("mistyrose4", &MISTYROSE4, 139, 125, 123, 255);
    color_set("misty_rose", &MISTY_ROSE, 255, 228, 225, 255);
    color_set("mistyrose", &MISTYROSE, 255, 228, 225, 255);
    color_set("moccasin", &MOCCASIN, 255, 228, 181, 255);
    color_set("navajowhite1", &NAVAJOWHITE1, 255, 222, 173, 255);
    color_set("navajowhite2", &NAVAJOWHITE2, 238, 207, 161, 255);
    color_set("navajowhite3", &NAVAJOWHITE3, 205, 179, 139, 255);
    color_set("navajowhite4", &NAVAJOWHITE4, 139, 121, 94, 255);
    color_set("navajo_white", &NAVAJO_WHITE, 255, 222, 173, 255);
    color_set("navajowhite", &NAVAJOWHITE, 255, 222, 173, 255);
    color_set("navy_blue", &NAVY_BLUE, 0, 0, 128, 255);
    color_set("navyblue", &NAVYBLUE, 0, 0, 128, 255);
    color_set("navy", &NAVY, 0, 0, 128, 255);
    color_set("old_lace", &OLD_LACE, 253, 245, 230, 255);
    color_set("oldlace", &OLDLACE, 253, 245, 230, 255);
    color_set("olivedrab1", &OLIVEDRAB1, 192, 255, 62, 255);
    color_set("olivedrab2", &OLIVEDRAB2, 179, 238, 58, 255);
    color_set("olivedrab3", &OLIVEDRAB3, 154, 205, 50, 255);
    color_set("olivedrab4", &OLIVEDRAB4, 105, 139, 34, 255);
    color_set("olive_drab", &OLIVE_DRAB, 107, 142, 35, 255);
    color_set("olivedrab", &OLIVEDRAB, 107, 142, 35, 255);
    color_set("light_orange", &LIGHT_ORANGE, 255, 200, 40, 255);
    color_set("orange1", &ORANGE1, 255, 165, 0, 255);
    color_set("orange2", &ORANGE2, 238, 154, 0, 255);
    color_set("orange3", &ORANGE3, 205, 133, 0, 255);
    color_set("orange4", &ORANGE4, 139, 90, 0, 255);
    color_set("orange", &ORANGE, 255, 165, 0, 255);
    color_set("orangered1", &ORANGERED1, 255, 69, 0, 255);
    color_set("orangered2", &ORANGERED2, 238, 64, 0, 255);
    color_set("orangered3", &ORANGERED3, 205, 55, 0, 255);
    color_set("orangered4", &ORANGERED4, 139, 37, 0, 255);
    color_set("orange_red", &ORANGE_RED, 255, 69, 0, 255);
    color_set("orangered", &ORANGERED, 255, 69, 0, 255);
    color_set("orchid1", &ORCHID1, 255, 131, 250, 255);
    color_set("orchid2", &ORCHID2, 238, 122, 233, 255);
    color_set("orchid3", &ORCHID3, 205, 105, 201, 255);
    color_set("orchid4", &ORCHID4, 139, 71, 137, 255);
    color_set("orchid", &ORCHID, 218, 112, 214, 255);
    color_set("pale_goldenrod", &PALE_GOLDENROD, 238, 232, 170, 255);
    color_set("palegoldenrod", &PALEGOLDENROD, 238, 232, 170, 255);
    color_set("palegreen1", &PALEGREEN1, 154, 255, 154, 255);
    color_set("palegreen2", &PALEGREEN2, 144, 238, 144, 255);
    color_set("palegreen3", &PALEGREEN3, 124, 205, 124, 255);
    color_set("palegreen4", &PALEGREEN4, 84, 139, 84, 255);
    color_set("pale_green", &PALE_GREEN, 152, 251, 152, 255);
    color_set("palegreen", &PALEGREEN, 152, 251, 152, 255);
    color_set("paleturquoise1", &PALETURQUOISE1, 187, 255, 255, 255);
    color_set("paleturquoise2", &PALETURQUOISE2, 174, 238, 238, 255);
    color_set("paleturquoise3", &PALETURQUOISE3, 150, 205, 205, 255);
    color_set("paleturquoise4", &PALETURQUOISE4, 102, 139, 139, 255);
    color_set("pale_turquoise", &PALE_TURQUOISE, 175, 238, 238, 255);
    color_set("paleturquoise", &PALETURQUOISE, 175, 238, 238, 255);
    color_set("palevioletred1", &PALEVIOLETRED1, 255, 130, 171, 255);
    color_set("palevioletred2", &PALEVIOLETRED2, 238, 121, 159, 255);
    color_set("palevioletred3", &PALEVIOLETRED3, 205, 104, 137, 255);
    color_set("palevioletred4", &PALEVIOLETRED4, 139, 71, 93, 255);
    color_set("pale_violet_red", &PALE_VIOLET_RED, 219, 112, 147, 255);
    color_set("palevioletred", &PALEVIOLETRED, 219, 112, 147, 255);
    color_set("papaya_whip", &PAPAYA_WHIP, 255, 239, 213, 255);
    color_set("papayawhip", &PAPAYAWHIP, 255, 239, 213, 255);
    color_set("peachpuff1", &PEACHPUFF1, 255, 218, 185, 255);
    color_set("peachpuff2", &PEACHPUFF2, 238, 203, 173, 255);
    color_set("peachpuff3", &PEACHPUFF3, 205, 175, 149, 255);
    color_set("peachpuff4", &PEACHPUFF4, 139, 119, 101, 255);
    color_set("peach_puff", &PEACH_PUFF, 255, 218, 185, 255);
    color_set("peachpuff", &PEACHPUFF, 255, 218, 185, 255);
    color_set("peru", &PERU, 205, 133, 63, 255);
    color_set("pink1", &PINK1, 255, 181, 197, 255);
    color_set("pink2", &PINK2, 238, 169, 184, 255);
    color_set("pink3", &PINK3, 205, 145, 158, 255);
    color_set("pink4", &PINK4, 139, 99, 108, 255);
    color_set("pink", &PINK, 255, 192, 203, 255);
    color_set("plum1", &PLUM1, 255, 187, 255, 255);
    color_set("plum2", &PLUM2, 238, 174, 238, 255);
    color_set("plum3", &PLUM3, 205, 150, 205, 255);
    color_set("plum4", &PLUM4, 139, 102, 139, 255);
    color_set("plum", &PLUM, 221, 160, 221, 255);
    color_set("powder_blue", &POWDER_BLUE, 176, 224, 230, 255);
    color_set("powderblue", &POWDERBLUE, 176, 224, 230, 255);
    color_set("purple1", &PURPLE1, 155, 48, 255, 255);
    color_set("purple2", &PURPLE2, 145, 44, 238, 255);
    color_set("purple3", &PURPLE3, 125, 38, 205, 255);
    color_set("purple4", &PURPLE4, 85, 26, 139, 255);
    color_set("purple", &PURPLE, 160, 32, 240, 255);
    color_set("red1", &RED1, 255, 0, 0, 255);
    color_set("red2", &RED2, 238, 0, 0, 255);
    color_set("red3", &RED3, 205, 0, 0, 255);
    color_set("red4", &RED4, 139, 0, 0, 255);
    color_set("red", &RED, 255, 0, 0, 255);
    color_set("rosybrown1", &ROSYBROWN1, 255, 193, 193, 255);
    color_set("rosybrown2", &ROSYBROWN2, 238, 180, 180, 255);
    color_set("rosybrown3", &ROSYBROWN3, 205, 155, 155, 255);
    color_set("rosybrown4", &ROSYBROWN4, 139, 105, 105, 255);
    color_set("rosy_brown", &ROSY_BROWN, 188, 143, 143, 255);
    color_set("rosybrown", &ROSYBROWN, 188, 143, 143, 255);
    color_set("royalblue1", &ROYALBLUE1, 72, 118, 255, 255);
    color_set("royalblue2", &ROYALBLUE2, 67, 110, 238, 255);
    color_set("royalblue3", &ROYALBLUE3, 58, 95, 205, 255);
    color_set("royalblue4", &ROYALBLUE4, 39, 64, 139, 255);
    color_set("royal_blue", &ROYAL_BLUE, 65, 105, 225, 255);
    color_set("royalblue", &ROYALBLUE, 65, 105, 225, 255);
    color_set("saddle_brown", &SADDLE_BROWN, 139, 69, 19, 255);
    color_set("saddlebrown", &SADDLEBROWN, 139, 69, 19, 255);
    color_set("salmon1", &SALMON1, 255, 140, 105, 255);
    color_set("salmon2", &SALMON2, 238, 130, 98, 255);
    color_set("salmon3", &SALMON3, 205, 112, 84, 255);
    color_set("salmon4", &SALMON4, 139, 76, 57, 255);
    color_set("salmon", &SALMON, 250, 128, 114, 255);
    color_set("sandy_brown", &SANDY_BROWN, 244, 164, 96, 255);
    color_set("sandybrown", &SANDYBROWN, 244, 164, 96, 255);
    color_set("seagreen1", &SEAGREEN1, 84, 255, 159, 255);
    color_set("seagreen2", &SEAGREEN2, 78, 238, 148, 255);
    color_set("seagreen3", &SEAGREEN3, 67, 205, 128, 255);
    color_set("seagreen4", &SEAGREEN4, 46, 139, 87, 255);
    color_set("sea_green", &SEA_GREEN, 46, 139, 87, 255);
    color_set("seagreen", &SEAGREEN, 46, 139, 87, 255);
    color_set("seashell1", &SEASHELL1, 255, 245, 238, 255);
    color_set("seashell2", &SEASHELL2, 238, 229, 222, 255);
    color_set("seashell3", &SEASHELL3, 205, 197, 191, 255);
    color_set("seashell4", &SEASHELL4, 139, 134, 130, 255);
    color_set("seashell", &SEASHELL, 255, 245, 238, 255);
    color_set("sienna1", &SIENNA1, 255, 130, 71, 255);
    color_set("sienna2", &SIENNA2, 238, 121, 66, 255);
    color_set("sienna3", &SIENNA3, 205, 104, 57, 255);
    color_set("sienna4", &SIENNA4, 139, 71, 38, 255);
    color_set("sienna", &SIENNA, 160, 82, 45, 255);
    color_set("skyblue1", &SKYBLUE1, 135, 206, 255, 255);
    color_set("skyblue2", &SKYBLUE2, 126, 192, 238, 255);
    color_set("skyblue3", &SKYBLUE3, 108, 166, 205, 255);
    color_set("skyblue4", &SKYBLUE4, 74, 112, 139, 255);
    color_set("sky_blue", &SKY_BLUE, 135, 206, 235, 255);
    color_set("skyblue", &SKYBLUE, 135, 206, 235, 255);
    color_set("slateblue1", &SLATEBLUE1, 131, 111, 255, 255);
    color_set("slateblue2", &SLATEBLUE2, 122, 103, 238, 255);
    color_set("slateblue3", &SLATEBLUE3, 105, 89, 205, 255);
    color_set("slateblue4", &SLATEBLUE4, 71, 60, 139, 255);
    color_set("slate_blue", &SLATE_BLUE, 106, 90, 205, 255);
    color_set("slateblue", &SLATEBLUE, 106, 90, 205, 255);
    color_set("slategray1", &SLATEGRAY1, 198, 226, 255, 255);
    color_set("slategray2", &SLATEGRAY2, 185, 211, 238, 255);
    color_set("slategray3", &SLATEGRAY3, 159, 182, 205, 255);
    color_set("slategray4", &SLATEGRAY4, 108, 123, 139, 255);
    color_set("slate_gray", &SLATE_GRAY, 112, 128, 144, 255);
    color_set("slategray", &SLATEGRAY, 112, 128, 144, 255);
    color_set("slate_grey", &SLATE_GREY, 112, 128, 144, 255);
    color_set("slategrey", &SLATEGREY, 112, 128, 144, 255);
    color_set("snow1", &SNOW1, 255, 250, 250, 255);
    color_set("snow2", &SNOW2, 238, 233, 233, 255);
    color_set("snow3", &SNOW3, 205, 201, 201, 255);
    color_set("snow4", &SNOW4, 139, 137, 137, 255);
    color_set("snow", &SNOW, 255, 250, 250, 255);
    color_set("springgreen1", &SPRINGGREEN1, 0, 255, 127, 255);
    color_set("springgreen2", &SPRINGGREEN2, 0, 238, 118, 255);
    color_set("springgreen3", &SPRINGGREEN3, 0, 205, 102, 255);
    color_set("springgreen4", &SPRINGGREEN4, 0, 139, 69, 255);
    color_set("spring_green", &SPRING_GREEN, 0, 255, 127, 255);
    color_set("springgreen", &SPRINGGREEN, 0, 255, 127, 255);
    color_set("steelblue1", &STEELBLUE1, 99, 184, 255, 255);
    color_set("steelblue2", &STEELBLUE2, 92, 172, 238, 255);
    color_set("steelblue3", &STEELBLUE3, 79, 148, 205, 255);
    color_set("steelblue4", &STEELBLUE4, 54, 100, 139, 255);
    color_set("steel_blue", &STEEL_BLUE, 70, 130, 180, 255);
    color_set("steelblue", &STEELBLUE, 70, 130, 180, 255);
    color_set("tan1", &TAN1, 255, 165, 79, 255);
    color_set("tan2", &TAN2, 238, 154, 73, 255);
    color_set("tan3", &TAN3, 205, 133, 63, 255);
    color_set("tan4", &TAN4, 139, 90, 43, 255);
    color_set("tan", &TAN, 210, 180, 140, 255);
    color_set("thistle1", &THISTLE1, 255, 225, 255, 255);
    color_set("thistle2", &THISTLE2, 238, 210, 238, 255);
    color_set("thistle3", &THISTLE3, 205, 181, 205, 255);
    color_set("thistle4", &THISTLE4, 139, 123, 139, 255);
    color_set("thistle", &THISTLE, 216, 191, 216, 255);
    color_set("tomato1", &TOMATO1, 255, 99, 71, 255);
    color_set("tomato2", &TOMATO2, 238, 92, 66, 255);
    color_set("tomato3", &TOMATO3, 205, 79, 57, 255);
    color_set("tomato4", &TOMATO4, 139, 54, 38, 255);
    color_set("tomato", &TOMATO, 255, 99, 71, 255);
    color_set("turquoise1", &TURQUOISE1, 0, 245, 255, 255);
    color_set("turquoise2", &TURQUOISE2, 0, 229, 238, 255);
    color_set("turquoise3", &TURQUOISE3, 0, 197, 205, 255);
    color_set("turquoise4", &TURQUOISE4, 0, 134, 139, 255);
    color_set("turquoise", &TURQUOISE, 64, 224, 208, 255);
    color_set("violet", &VIOLET, 238, 130, 238, 255);
    color_set("violetred1", &VIOLETRED1, 255, 62, 150, 255);
    color_set("violetred2", &VIOLETRED2, 238, 58, 140, 255);
    color_set("violetred3", &VIOLETRED3, 205, 50, 120, 255);
    color_set("violetred4", &VIOLETRED4, 139, 34, 82, 255);
    color_set("violet_red", &VIOLET_RED, 208, 32, 144, 255);
    color_set("violetred", &VIOLETRED, 208, 32, 144, 255);
    color_set("wheat1", &WHEAT1, 255, 231, 186, 255);
    color_set("wheat2", &WHEAT2, 238, 216, 174, 255);
    color_set("wheat3", &WHEAT3, 205, 186, 150, 255);
    color_set("wheat4", &WHEAT4, 139, 126, 102, 255);
    color_set("wheat", &WHEAT, 245, 222, 179, 255);
    color_set("white", &WHITE, 255, 255, 255, 255);
    color_set("white_smoke", &WHITE_SMOKE, 245, 245, 245, 255);
    color_set("whitesmoke", &WHITESMOKE, 245, 245, 245, 255);
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
