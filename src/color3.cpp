//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_gl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"

#include <string.h>  // do not remove
#include <strings.h> // do not remove, strcasecmp

// begin sort marker1 {
color HOT_PINK;
color HOTPINK;
color HOTPINK1;
color HOTPINK2;
color HOTPINK3;
color HOTPINK4;
color INDIAN_RED;
color INDIANRED;
color INDIANRED1;
color INDIANRED2;
color INDIANRED3;
color INDIANRED4;
color IVORY;
color IVORY1;
color IVORY2;
color IVORY3;
color IVORY4;
color KHAKI;
color KHAKI1;
color KHAKI2;
color KHAKI3;
color KHAKI4;
color LAVENDER;
color LEMON_CHIFFON;
color LEMONCHIFFON;
color WATER;
color DEEPWATER;
color WALL;
color LEMONCHIFFON1;
color LEMONCHIFFON2;
color LEMONCHIFFON3;
color LEMONCHIFFON4;
color LIGHTBLUE;
color LIGHTBLUE1;
color LIGHTBLUE2;
color LIGHTBLUE3;
color LIGHTBLUE4;
color LIGHTCORAL;
color LIGHTCYAN;
color LIGHTCYAN1;
color LIGHTCYAN2;
color LIGHTCYAN3;
color LIGHTCYAN4;
color LIGHTGRAY;
color LIGHTGREEN;
color LIGHTGREY;
color LIGHTPINK;
color LIGHTPINK1;
color LIGHTPINK2;
color LIGHTPINK3;
color LIGHTPINK4;
color LIGHTSEAGREEN;
color LIGHTSKYBLUE;
color LIGHTSKYBLUE1;
color LIGHTSKYBLUE2;
color LIGHTSKYBLUE3;
color LIGHTSKYBLUE4;
color LIGHTSLATEBLUE;
color LIGHTSLATEGRAY;
color LIGHTSLATEGREY;
// end sort marker1 }

void color_init3(void)
{
  TRACE_AND_INDENT();

  // begin sort marker2 {
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
  color_set("lavender", &LAVENDER, 230, 230, 250, 255);
  color_set("lemonchiffon1", &LEMONCHIFFON1, 255, 250, 205, 255);
  color_set("lemonchiffon2", &LEMONCHIFFON2, 238, 233, 191, 255);
  color_set("lemonchiffon3", &LEMONCHIFFON3, 205, 201, 165, 255);
  color_set("lemonchiffon4", &LEMONCHIFFON4, 139, 137, 112, 255);
  color_set("lemon_chiffon", &LEMON_CHIFFON, 255, 250, 205, 255);
  color_set("lemonchiffon", &LEMONCHIFFON, 255, 250, 205, 255);
  color_set("water", &WATER, 84, 84, 232, 255);
  color_set("deepwater", &DEEPWATER, 20, 38, 124, 255);
  color_set("wall", &WALL, 247, 188, 193, 255);
  color_set("lightblue1", &LIGHTBLUE1, 191, 239, 255, 255);
  color_set("lightblue2", &LIGHTBLUE2, 178, 223, 238, 255);
  color_set("lightblue3", &LIGHTBLUE3, 154, 192, 205, 255);
  color_set("lightblue4", &LIGHTBLUE4, 104, 131, 139, 255);
  color_set("lightblue", &LIGHTBLUE, 173, 216, 230, 255);
  color_set("lightcoral", &LIGHTCORAL, 240, 128, 128, 255);
  color_set("lightcyan1", &LIGHTCYAN1, 224, 255, 255, 255);
  color_set("lightcyan2", &LIGHTCYAN2, 209, 238, 238, 255);
  color_set("lightcyan3", &LIGHTCYAN3, 180, 205, 205, 255);
  color_set("lightcyan4", &LIGHTCYAN4, 122, 139, 139, 255);
  color_set("lightcyan", &LIGHTCYAN, 224, 255, 255, 255);
  color_set("lightgray", &LIGHTGRAY, 211, 211, 211, 255);
  color_set("lightgrey", &LIGHTGREY, 211, 211, 211, 255);
  color_set("lightgreen", &LIGHTGREEN, 144, 238, 144, 255);
  color_set("lightpink1", &LIGHTPINK1, 255, 174, 185, 255);
  color_set("lightpink2", &LIGHTPINK2, 238, 162, 173, 255);
  color_set("lightpink3", &LIGHTPINK3, 205, 140, 149, 255);
  color_set("lightpink4", &LIGHTPINK4, 139, 95, 101, 255);
  color_set("lightpink", &LIGHTPINK, 255, 182, 193, 255);
  color_set("lightseagreen", &LIGHTSEAGREEN, 32, 178, 170, 255);
  color_set("lightskyblue1", &LIGHTSKYBLUE1, 176, 226, 255, 255);
  color_set("lightskyblue2", &LIGHTSKYBLUE2, 164, 211, 238, 255);
  color_set("lightskyblue3", &LIGHTSKYBLUE3, 141, 182, 205, 255);
  color_set("lightskyblue4", &LIGHTSKYBLUE4, 96, 123, 139, 255);
  color_set("lightskyblue", &LIGHTSKYBLUE, 135, 206, 250, 255);
  color_set("lightslateblue", &LIGHTSLATEBLUE, 132, 112, 255, 255);
  color_set("lightslategray", &LIGHTSLATEGRAY, 119, 136, 153, 255);
  color_set("lightslategrey", &LIGHTSLATEGREY, 119, 136, 153, 255);
  // end sort marker2 }
}
