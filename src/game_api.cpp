//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_game.hpp"

void Game::set_request_reset_state_change(void)
{
  if (request_reset_state_change)
    return;
  LOG("Set request_reset_state_change");
  request_reset_state_change = true;
}

void Game::set_request_to_remake_rightbar(void)
{
  if (request_to_remake_rightbar)
    return;
  LOG("Set request_to_remake_rightbar");
  request_to_remake_rightbar = true;
}

void Game::set_request_to_remake_inventory(void)
{
  if (request_to_remake_inventory)
    return;
  LOG("Set request_to_remake_inventory");
  request_to_remake_inventory = true;
}

void Game::set_request_to_remake_actionbar(void)
{
  if (request_to_remake_actionbar)
    return;
  LOG("Set request_to_remake_actionbar");
  request_to_remake_actionbar = true;
}

void Game::set_request_to_remake_skillbox(void)
{
  if (request_to_remake_skillbox)
    return;
  LOG("Set request_to_remake_skillbox");
  request_to_remake_skillbox = true;
}

void Game::set_request_to_remake_debuffbox(void)
{
  if (request_to_remake_debuffbox)
    return;
  LOG("Set request_to_remake_debuffbox");
  request_to_remake_debuffbox = true;
}

void Game::set_request_to_remake_buffbox(void)
{
  if (request_to_remake_buffbox)
    return;
  LOG("Set request_to_remake_buffbox");
  request_to_remake_buffbox = true;
}

void Game::set_request_to_update_same_level(void)
{
  if (request_to_update_same_level)
    return;
  LOG("Set request_to_update_same_level");
  request_to_update_same_level = true;
}

void Game::set_request_to_save_snapshot(void)
{
  if (request_to_save_snapshot)
    return;
  LOG("Set request_to_save_snapshot");
  request_to_save_snapshot = true;
}

void Game::set_currently_saving_snapshot(void)
{
  if (currently_saving_snapshot)
    return;
  LOG("Set currently_saving_snapshot");
  currently_saving_snapshot = true;
}

void Game::set_request_to_update_inventory_with_thing_over(void)
{
  if (request_to_update_inventory_with_thing_over)
    return;
  LOG("Set request_to_update_inventory_with_thing_over");
  request_to_update_inventory_with_thing_over = true;
}

void Game::set_request_to_update_inventory_with_thing_selected(void)
{
  if (request_to_update_inventory_with_thing_selected)
    return;
  LOG("Set request_to_update_inventory_with_thing_selected");
  request_to_update_inventory_with_thing_selected = true;
}

void Game::unset_request_reset_state_change(void)
{
  if (! request_reset_state_change)
    return;
  LOG("Unset request_reset_state_change");
  request_reset_state_change = false;
}

void Game::unset_request_to_remake_rightbar(void)
{
  if (! request_to_remake_rightbar)
    return;
  LOG("Unset request_to_remake_rightbar");
  request_to_remake_rightbar = false;
}

void Game::unset_request_to_remake_inventory(void)
{
  if (! request_to_remake_inventory)
    return;
  LOG("Unset request_to_remake_inventory");
  request_to_remake_inventory = false;
}

void Game::unset_request_to_remake_actionbar(void)
{
  if (! request_to_remake_actionbar)
    return;
  LOG("Unset request_to_remake_actionbar");
  request_to_remake_actionbar = false;
}

void Game::unset_request_to_remake_skillbox(void)
{
  if (! request_to_remake_skillbox)
    return;
  LOG("Unset request_to_remake_skillbox");
  request_to_remake_skillbox = false;
}

void Game::unset_request_to_remake_debuffbox(void)
{
  if (! request_to_remake_debuffbox)
    return;
  LOG("Unset request_to_remake_debuffbox");
  request_to_remake_debuffbox = false;
}

void Game::unset_request_to_remake_buffbox(void)
{
  if (! request_to_remake_buffbox)
    return;
  LOG("Unset request_to_remake_buffbox");
  request_to_remake_buffbox = false;
}

void Game::unset_request_to_update_same_level(void)
{
  if (! request_to_update_same_level)
    return;
  LOG("Unset request_to_update_same_level");
  request_to_update_same_level = false;
}

void Game::unset_request_to_save_snapshot(void)
{
  if (! request_to_save_snapshot)
    return;
  LOG("Unset request_to_save_snapshot");
  request_to_save_snapshot = false;
}

void Game::unset_currently_saving_snapshot(void)
{
  if (! currently_saving_snapshot)
    return;
  LOG("Unset currently_saving_snapshot");
  currently_saving_snapshot = false;
}

void Game::unset_request_to_update_inventory_with_thing_over(void)
{
  if (! request_to_update_inventory_with_thing_over)
    return;
  LOG("Unset request_to_update_inventory_with_thing_over");
  request_to_update_inventory_with_thing_over = false;
}

void Game::unset_request_to_update_inventory_with_thing_selected(void)
{
  if (! request_to_update_inventory_with_thing_selected)
    return;
  LOG("Unset request_to_update_inventory_with_thing_selected");
  request_to_update_inventory_with_thing_selected = false;
}
