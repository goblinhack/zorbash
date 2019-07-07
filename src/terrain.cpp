//https://gamedev.stackexchange.com/questions/12449/midpoint-displacement-algorithm

#include "my_game.h"
#include "my_color.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

signed char scrand(signed char r = 127) { return (-r + 2 * (myrand() % r)); }

signed char** midpoint_disp_algo (signed char**old_map, 
                                  unsigned map_width, 
                                  signed char displacement) 
{
    size_t n = (2 * map_width) - 1;

    signed char** new_map = new signed char*[n];
    for (unsigned i = 0; i < n; ++i) {
        new_map[i] = new signed char[n];
    }

    // Resize
    // 1 0 1
    // 0 0 0
    // 1 0 1
    for (size_t i = 0; i < n; i += 2) {
        for (size_t j = !(i % 2 == 0); j < n; j += 2) {
            new_map[i][j] = old_map[i / 2][j / 2];
        }
    }

    // Diamond algorithm
    // 0 0 0
    // 0 X 0
    // 0 0 0
    for (size_t i = 1; i < n; i += 2) {
        for (size_t j = 1; j < n; j += 2) {
            signed char& map_ij = new_map[i][j];

            signed char a = new_map[i - 1][j - 1];
            signed char b = new_map[i - 1][j + 1];
            signed char c = new_map[i + 1][j - 1];
            signed char d = new_map[i + 1][j + 1];
            map_ij = (a + b + c + d) / 4;

            int rv = scrand(displacement);
            if (map_ij + rv > 127 )
                map_ij = 127;
            else if(map_ij + rv < -128)
                map_ij = -128;
            else
                map_ij += rv;
        }
    }

    // Square algorithm
    // 0 1 0
    // 1 0 1
    // 0 1 0
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = (i % 2 == 0); j < n; j += 2) {
            signed char& map_ij = new_map[i][j];

            // get surrounding values
            signed char a = 0, b = a, c = a, d = a;
            if (i != 0) a = new_map[i - 1][j];
            if (j != 0) b = new_map[i][j - 1];
            if (j + 1 != n) c = new_map[i][j + 1];
            if (i + 1 != n) d = new_map[i + 1][j];

            // average calculation
            if (i == 0) map_ij = (b + c + d) / 3;
            else if (j == 0) map_ij = (a + c + d) / 3;
            else if (j + 1 == n) map_ij = (a + b + d) / 3;
            else if (i + 1 == n) map_ij = (a + b + c) / 3;
            else map_ij = (a + b + c + d) / 4;

            int rv = scrand(displacement);
            if (map_ij + rv > 127 )
                map_ij = 127;
            else if(map_ij + rv < -128)
                map_ij = -128;
            else
                map_ij += rv;
        }
    }
    return new_map;
}

signed char** createnoise(unsigned n) 
{
    signed char** noise = new signed char*[n];
    for (unsigned i = 0; i < n; ++i) {
        noise[i] = new signed char[n];
        for (unsigned j = 0; j < n; ++j) noise[i][j] = scrand();
    }
    return noise;
}

static void dump (int map_width, signed char**the_map)
{
    int w = map_width;
    int h = map_width;
    static int count;
    auto filename = dynprintf("map.%d.ppm", ++count);
    auto fp = fopen(filename, "w");
    fprintf(fp, "P6\n%d %d\n255\n",w,h);

    int i, j;

    for (j=h-1;j>=0;j--) {
        for (i=0;i<w;i++) {
            color c;
            c = WHITE;

            if (the_map[i][j] < 120) {
                c = GRAY;
            }
            if (the_map[i][j] < 110) {
                c = GRAY;
            }
            if (the_map[i][j] < 100) {
                c = GREEN1;
            }
            if (the_map[i][j] < 90) {
                c = GREEN2;
            }
            if (the_map[i][j] < 80) {
                c = GREEN3;
            }
            if (the_map[i][j] < 70) {
                c = GREEN4;
            }
            if (the_map[i][j] < 60) {
                c = GREEN;
            }
            if (the_map[i][j] < 50) {
                c = GREEN;
            }
            if (the_map[i][j] < 40) {
                c = YELLOWGREEN;
            }
            if (the_map[i][j] < 35) {
                c = YELLOW;
            }
            if (the_map[i][j] < 30) {
                c = CYAN;
            }
            if (the_map[i][j] < 20) {
                c = LIGHTBLUE;
                c.b += the_map[i][j];
            }
            if (the_map[i][j] < 10) {
                c = BLUE2;
                c.b += the_map[i][j];
            }
            if (the_map[i][j] < 5) {
                c = BLUE;
                c.b += the_map[i][j];
            }

            fputc(c.r, fp);
            fputc(c.g, fp);
            fputc(c.b, fp);
        }
    }

    fclose(fp);
    myfree(filename);
}

int terrain (void) 
{
    const unsigned map_width = 1024;
    mysrand(4);

    signed char** final_map = new signed char*[map_width];
    for (unsigned i = 0; i < map_width; ++i) {
        final_map[i] = new signed char[map_width];
        for (unsigned j = 0; j < map_width; ++j) {
            final_map[i][j] = scrand();
        }
    }

    for (unsigned i = 1; i < 8; ++i)  {
        final_map = midpoint_disp_algo(final_map, map_width, 64 / i);
    }

    dump(map_width, final_map);

#if 0
    for (unsigned i = 0; i < map_width; ++i) {
        for (unsigned j = 0; j < map_width; ++j) {
            float d = DISTANCE(map_width / 2, map_width / 2, i, j);
            float max_d = DISTANCE(map_width / 2, map_width / 2, 0, 0);
            float scale = 1.0 - (d / max_d);
            scale = pow(scale, 1.1);
                final_map[i][j] = (int)((float)(final_map[i][j]) * scale);
        }
    }
    dump(map_width, final_map);
#endif

    return 0;
}

