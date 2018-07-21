#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/json.hpp>
#include <limits>
#include <random>
#include <fstream>
#include "my_ptrcheck.h"
#include "my_game.h"
#include "my_main.h"
    
int cereal_test (const std::string save_file)
{
    {
        Map the_map;

        auto t1 = std::make_shared<class Thing>();
        the_map.all_things.insert(std::make_pair(t1->id, t1));

        auto t2 = std::make_shared<class Thing>();
        the_map.all_things.insert(std::make_pair(t2->id, t2));

        State state;
        state.map = the_map;

        Game game;
        game.state = state;

        std::ofstream os(save_file, std::ios::binary);
        cereal::JSONOutputArchive archive_out(os);

        archive_out(game);
    }

    {
        std::ifstream is(save_file);
        cereal::JSONInputArchive archive_in(is);
        Game in_game;
        archive_in(in_game);

        cereal::JSONOutputArchive archive_out(std::cout);
        archive_out(in_game);
    }

//    exit(0);
    return 0;
}
