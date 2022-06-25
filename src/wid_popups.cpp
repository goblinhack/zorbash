//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_wid_inventory.hpp"
#include "my_wid_popups.hpp"

bool wid_popup_exists(void)
{
  return (wid_collect || wid_skills || wid_enchant || wid_load || wid_save || wid_config_keyboard_window ||
          wid_quit_window || wid_inventory_window);
}
