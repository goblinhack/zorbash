//
// Copyright goblinhack@gmail.com
//
// Converted from python/spell_tree.py
//

#include "my_native.hpp"

namespace mod_modules_spell_tree {





void module_init(void)
{
  my::map_load_spell_tree(std::vector< std::string >{
      "fd",
      "spell_of_summon_food",
      "rk",
      "spell_of_summon_rock",
      "mm",
      "spell_of_magic_missile",
      "sA",
      "spell_of_summon_monst1",
      "sB",
      "spell_of_summon_monst2",
      "sC",
      "spell_of_summon_monst3",
      "sD",
      "spell_of_summon_monst4",
      "sE",
      "spell_of_summon_monst5",
      "dA",
      "spell_of_dominate_monst1",
      "dB",
      "spell_of_dominate_monst2",
      "dC",
      "spell_of_dominate_monst3",
      "dD",
      "spell_of_dominate_monst4",
      "dE",
      "spell_of_dominate_monst5",
      "hh",
      "spell_of_haste",
      "ss",
      "spell_of_slowness",
      "bk",
      "spell_of_beckoning",
      "rp",
      "spell_of_repulsion",
      "HH",
      "spell_of_holding",
      "PP",
      "spell_of_protection",
      "Sc",
      "spell_of_sanctuary",
    });
  my::map_load_spell_tree({}, std::vector< std::string >{
      "mm                              ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
    }, "combat");
  my::map_load_spell_tree({}, std::vector< std::string >{
      "HH                              ",
      "                                ",
      "PP                              ",
      "                                ",
      "Sc                              ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
    }, "defensive");
  my::map_load_spell_tree({}, std::vector< std::string >{
      "hh                              ",
      "                                ",
      "ss                              ",
      "                                ",
      "bk                              ",
      "                                ",
      "rp                              ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
    }, "movement");
  my::map_load_spell_tree({}, std::vector< std::string >{
      "fd                              ",
      "                                ",
      "rk                              ",
      "                                ",
      "sA->sB->sC->sD->sE              ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
    }, "summoning");
  my::map_load_spell_tree({}, std::vector< std::string >{
      "dA->dB->dC->dD->dE              ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
      "                                ",
    }, "psi");
}

} // namespace mod_modules_spell_tree
