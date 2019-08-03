//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_charmap.h"
#include "my_game.h"

typedef std::shared_ptr< class Level > Levelp;
typedef std::vector<Levelp> Levels;

class Level
{
private:
public:
    static Levels all_levels;

    Level (void)
    {
        this->levelno = all_levels.size();

        newptr(this, "level");
    }

    ~Level (void)
    {
        oldptr(this);
    }

    //
    // Unique per level.
    //
    uint32_t                levelno {0};
    uint8_t                 width  {CHUNK_WIDTH};
    uint8_t                 height {CHUNK_HEIGHT};
    uint8_t                 depth  {0};

    char                    data[CHUNK_WIDTH][CHUNK_HEIGHT][MAP_DEPTH] = {{{' '}}};

    static Levelp level_new(void);
    void finalize(void);
    void dump(void);
};
