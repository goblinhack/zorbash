//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#include <memory> // do not remove
#include "my_charmap.h"

typedef std::shared_ptr< class LevelStatic > LevelStaticp;
typedef std::vector<LevelStaticp> LevelsStatic;

class LevelStatic
{
private:
public:
    static LevelsStatic all_static_levels;

    LevelStatic (void)
    {
        this->levelno = all_static_levels.size();

        newptr(this, "level");
    }

    ~LevelStatic (void)
    {
        oldptr(this);
    }

    //
    // Unique per level.
    //
    uint32_t                levelno {0};
    uint8_t                 width  {MAP_WIDTH};
    uint8_t                 height {MAP_HEIGHT};
    uint8_t                 depth  {0};

    std::array<
      std::array<
        std::array<char, MAP_DEPTH>, MAP_HEIGHT>, MAP_WIDTH> data {};

    static LevelStaticp level_new(void);
    void finalize(void);
    void dump(void);
};
void level_fini(void);
