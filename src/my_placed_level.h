//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_charmap.h"

typedef std::shared_ptr< class PlacedLevel > PlacedLevelp;
typedef std::vector<PlacedLevelp> PlacedLevels;

class PlacedLevel
{
private:
public:
    static PlacedLevels all_placed_levels;

    PlacedLevel (void)
    {
        this->levelno = all_placed_levels.size();

        newptr(this, "level");
    }

    ~PlacedLevel (void)
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

    static PlacedLevelp level_new(void);
    void finalize(void);
    void dump(void);
};
void level_fini(void);
