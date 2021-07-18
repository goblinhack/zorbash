//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_array_bounds_check.h"

//
// This is used by the AI to work out if a monst can jump over an obstacle "*"
// 's' is the start
// 'e' is the end of the jump
// 'x' is a chasm/lava/... and not an obstacle like a wall
//
#define JUMP_WIDTH 5

static std::string jump_data [] = {

    // jump length 4
    "s...."
    ".1..."
    "..2.."
    "...3."
    "....e",

    ".s..."
    ".1..."
    "..2.."
    "...3."
    "...e.",

    "..s.."
    "..1.."
    "..2.."
    "..3.."
    "..e..",

    "...s."
    "...1."
    "..2.."
    ".3..."
    ".e...",

    "....s"
    "...1."
    "..2.."
    ".3..."
    "e....",

    // jump length 3
    "....."
    ".s..."
    "..1.."
    "...2."
    "....e",

    "....."
    ".s..."
    "..1.."
    "..2.."
    "...e.",

    "....."
    "..s.."
    "..1.."
    "..2.."
    "..e..",

    "....."
    "...s."
    "..1.."
    "..2.."
    ".e...",

    "....."
    "...s."
    "..1.."
    ".2..."
    "e....",

    // jump length 3
    "s...."
    ".1..."
    "..2.."
    "...e."
    ".....",

    ".s..."
    "..1.."
    "..2.."
    "...e."
    ".....",

    "..s.."
    "..1.."
    "..2.."
    "..e.."
    ".....",

    "...s."
    "..1.."
    "..2.."
    ".e..."
    ".....",

    "....s"
    "...1."
    "..2.."
    ".e..."
    ".....",

    // jump length 2
    "....."
    ".s..."
    "..1.."
    "...e."
    ".....",

    "....."
    ".s..."
    "..1.."
    "...e."
    ".....",

    "....."
    "..s.."
    "..1.."
    "..e.."
    ".....",

    "....."
    "...s."
    "..1.."
    ".e..."
    ".....",

    "....."
    "...s."
    "..1.."
    ".e..."
    ".....",
};

void Game::init_jump_paths()
{
    bool debug = true;

    jump_paths.clear();

    std::string tmp;
    std::vector<std::string> cands;

    for (const auto &s : jump_data) {
        if (s.length() != JUMP_WIDTH * JUMP_WIDTH) {
            DIE("bad jump data");
        }

        //
        // Read the jump data
        //
        std::array< std::array<char, JUMP_WIDTH>, JUMP_WIDTH> tmp {};

        int x = 0;
        int y = 0;
        for (int i = 0; i < JUMP_WIDTH * JUMP_WIDTH; i++) {
            set(tmp, x, y, s[i]);
            if (++x >= JUMP_WIDTH) {
                x = 0;
                y++;
            }
        }

        for (int rot = 0; rot < 4; rot++) {
            //
            // Rotate
            //
            std::array< std::array<char, JUMP_WIDTH>, JUMP_WIDTH> tmp2 {};
            for (auto y = 0; y < JUMP_WIDTH; y++) {
                for (auto x = 0; x < JUMP_WIDTH; x++) {
                    set(tmp2, JUMP_WIDTH - y - 1, x, get(tmp, x, y));
                }
            }
            tmp = tmp2;

            std::string out;
            for (auto y = 0; y < JUMP_WIDTH; y++) {
                for (auto x = 0; x < JUMP_WIDTH; x++) {
                    out += get(tmp, x, y);
                }
            }

            cands.push_back(out);
            if (out.length() != JUMP_WIDTH * JUMP_WIDTH) {
                DIE("bad derived jump data");
            }
        }
    }

    std::sort(cands.begin(), cands.end());
    auto last = std::unique(cands.begin(), cands.end());
    cands.erase(last, cands.end());

    std::cout << std::endl;
    for (const auto &s : cands) {
        if (debug) {
            std::cout << "[" << s <<  "]" << " ";
        }

        if (s.length() != JUMP_WIDTH * JUMP_WIDTH) {
            DIE("bad derived jump data 2");
        }

        std::size_t start = s.find("s");
        if (start == std::string::npos) {
            DIE("no start jump char");
        }
        std::size_t end = s.find("e");
        if (end == std::string::npos) {
            DIE("no end jump char");
        }

        std::vector<char> cs = { 's', '1', '2', '3', 'e' };

        std::array< std::array<char, JUMP_WIDTH>, JUMP_WIDTH> tmp {};
        int x = 0;
        int y = 0;
        for (int i = 0; i < JUMP_WIDTH * JUMP_WIDTH; i++) {
            set(tmp, x, y, s[i]);
            if (++x >= JUMP_WIDTH) {
                x = 0;
                y++;
            }
        }

        auto offset = (int) std::floor(JUMP_WIDTH / 2);

        std::vector<point> ps;
        for (auto c : cs) {
            for (auto y = 0; y < JUMP_WIDTH; y++) {
                for (auto x = 0; x < JUMP_WIDTH; x++) {
                    if (get(tmp, x, y) == c) {
                        point p(point(x - offset, y - offset));
                        ps.push_back(p);
                        if (debug) {
                            std::cout << "(" << p.x << "," << p.y << ")" << " ";
                        }
                        goto next;
                    }
                }
            }
next:
            continue;
        }

        if (debug) {
            std::cout << std::endl;
        }

        jump_paths.push_back(ps);
    }
}
