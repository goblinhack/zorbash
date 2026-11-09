//
// Copyright goblinhack@gmail.com
//
// Converted from python/sound.py
//

#include "my_native.hpp"

namespace mod_modules_sound {





void module_init(void)
{
  my::sound_load(0.5, "data/sounds/creatures/sheep.wav", "sheep");
  my::sound_load(0.5, "data/sounds/creatures/bones1.wav", "bones1");
  my::sound_load(0.5, "data/sounds/creatures/bones2.wav", "bones2");
  my::sound_load(0.5, "data/sounds/creatures/growl10.wav", "growl10");
  my::sound_load(0.5, "data/sounds/creatures/growl1.wav", "growl1");
  my::sound_load(0.5, "data/sounds/creatures/growl2.wav", "growl2");
  my::sound_load(0.5, "data/sounds/creatures/growl3.wav", "growl3");
  my::sound_load(0.5, "data/sounds/creatures/growl4.wav", "growl4");
  my::sound_load(0.5, "data/sounds/creatures/growl5.wav", "growl5");
  my::sound_load(0.5, "data/sounds/creatures/growl6.wav", "growl6");
  my::sound_load(0.5, "data/sounds/creatures/growl7.wav", "growl7");
  my::sound_load(0.5, "data/sounds/creatures/growl8.wav", "growl8");
  my::sound_load(0.5, "data/sounds/creatures/growl9.wav", "growl9");
  my::sound_load(0.5, "data/sounds/creatures/hiss10.wav", "hiss10");
  my::sound_load(0.5, "data/sounds/creatures/hiss1.wav", "hiss1");
  my::sound_load(0.5, "data/sounds/creatures/hiss2.wav", "hiss2");
  my::sound_load(0.5, "data/sounds/creatures/hiss3.wav", "hiss3");
  my::sound_load(0.5, "data/sounds/creatures/hiss4.wav", "hiss4");
  my::sound_load(0.5, "data/sounds/creatures/hiss5.wav", "hiss5");
  my::sound_load(0.5, "data/sounds/creatures/hiss6.wav", "hiss6");
  my::sound_load(0.5, "data/sounds/creatures/hiss7.wav", "hiss7");
  my::sound_load(0.5, "data/sounds/creatures/hiss8.wav", "hiss8");
  my::sound_load(0.5, "data/sounds/creatures/hiss9.wav", "hiss9");
  my::sound_load(0.5, "data/sounds/creatures/monst_death1.wav", "monst_death1");
  my::sound_load(0.5, "data/sounds/creatures/slime1.wav", "slime1");
  my::sound_load(0.5, "data/sounds/creatures/slime2.wav", "slime2");
  my::sound_load(0.5, "data/sounds/creatures/slime3.wav", "slime3");
  my::sound_load(0.5, "data/sounds/creatures/slime4.wav", "slime4");
  my::sound_load(0.5, "data/sounds/creatures/slime5.wav", "slime5");
  my::sound_load(0.5, "data/sounds/creatures/slime6.wav", "slime6");
  my::sound_load(0.5, "data/sounds/creatures/slime7.wav", "slime7");
  my::sound_load(0.5, "data/sounds/creatures/slime8.wav", "slime8");
  my::sound_load(0.5, "data/sounds/creatures/slime9.wav", "slime9");
  my::sound_load(0.5, "data/sounds/creatures/squeaky_toy.wav", "squeaky_toy");
  my::sound_load(0.5, "data/sounds/impacts/door_break.wav", "door_break");
  my::sound_load(0.5, "data/sounds/impacts/door_hit1.wav", "door_hit1");
  my::sound_load(0.5, "data/sounds/impacts/door_hit2.wav", "door_hit2");
  my::sound_load(0.5, "data/sounds/impacts/door_open.wav", "door_open");
  my::sound_load(0.5, "data/sounds/impacts/player_hit1.wav", "player_hit1");
  my::sound_load(0.5, "data/sounds/impacts/player_hit2.wav", "player_hit2");
  my::sound_load(0.5, "data/sounds/impacts/player_hit3.wav", "player_hit3");
  my::sound_load(0.5, "data/sounds/impacts/player_hit4.wav", "player_hit4");
  my::sound_load(0.5, "data/sounds/impacts/player_hit5.wav", "player_hit5");
  my::sound_load(0.5, "data/sounds/impacts/player_punch.wav", "player_punch");
  my::sound_load(0.5, "data/sounds/impacts/sword_impact1.wav", "sword_impact1");
  my::sound_load(0.5, "data/sounds/impacts/sword_impact2.wav", "sword_impact2");
  my::sound_load(0.5, "data/sounds/impacts/sword_impact2.wav", "sword_impact3");
  my::sound_load(0.5, "data/sounds/impacts/sword_impact2.wav", "sword_impact4");
  my::sound_load(0.5, "data/sounds/impacts/sword_swing1.wav", "sword_swing1");
  my::sound_load(0.5, "data/sounds/impacts/sword_swing2.wav", "sword_swing2");
  my::sound_load(0.5, "data/sounds/interface/click2.wav", "click");
  my::sound_load(0.5, "data/sounds/interface/keypress.wav", "keypress");
  my::sound_load(0.5, "data/sounds/misc/door_stone.wav", "door_stone");
  my::sound_load(0.5, "data/sounds/misc/drop.wav", "drop");
  my::sound_load(0.5, "data/sounds/misc/fall.wav", "fall");
  my::sound_load(1.0, "data/sounds/abilities/lightning_a.wav", "lightning_a");
  my::sound_load(1.0, "data/sounds/abilities/lightning_b.wav", "lightning_b");
  my::sound_load(1.0, "data/sounds/abilities/teleport.wav", "teleport");
  my::sound_load(1.0, "data/sounds/creatures/monst_death_epic.wav", "monst_death_epic");
  my::sound_load(1.0, "data/sounds/creatures/monster_roar_epic.wav", "monster_roar_epic");
  my::sound_load(1.0, "data/sounds/creatures/monster_roar.wav", "monster_roar");
  my::sound_load(1.0, "data/sounds/creatures/slime_attack.wav", "slime_attack");
  my::sound_load(1.0, "data/sounds/creatures/slime_jump.wav", "slime_jump");
  my::sound_load(1.0, "data/sounds/creatures/squelch.wav", "squelch");
  my::sound_load(1.0, "data/sounds/impacts/explosion_a.wav", "explosion_a");
  my::sound_load(1.0, "data/sounds/impacts/explosion_b.wav", "explosion_b");
  my::sound_load(1.0, "data/sounds/impacts/explosion_c.wav", "explosion_c");
  my::sound_load(1.0, "data/sounds/impacts/explosion_d.wav", "explosion_d");
  my::sound_load(1.0, "data/sounds/impacts/explosion_e.wav", "explosion_e");
  my::sound_load(1.0, "data/sounds/impacts/686849__ccen18__glass-shatter.wav", "explosion_crystal");
  my::sound_load(1.0, "data/sounds/impacts/splash1.wav", "splash1");
  my::sound_load(1.0, "data/sounds/impacts/splash2.wav", "splash2");
  my::sound_load(1.0, "data/sounds/impacts/splash3.wav", "splash3");
  my::sound_load(1.0, "data/sounds/impacts/splash4.wav", "splash4");
  my::sound_load(1.0, "data/sounds/impacts/splash5.wav", "splash5");
  my::sound_load(1.0, "data/sounds/impacts/splash6.wav", "splash6");
  my::sound_load(1.0, "data/sounds/impacts/sword_swing3.wav", "sword_swing3");
  my::sound_load(1.0, "data/sounds/interface/1up_a.wav", "potion");
  my::sound_load(1.0, "data/sounds/interface/coin.wav", "coin");
  my::sound_load(1.0, "data/sounds/misc/clack.wav", "bonk");
  my::sound_load(1.0, "data/sounds/misc/coindrop.wav", "coindrop");
  my::sound_load(1.0, "data/sounds/misc/footsteps1.wav", "footsteps1");
  my::sound_load(1.0, "data/sounds/misc/footsteps2.wav", "footsteps2");
  my::sound_load(1.0, "data/sounds/misc/footsteps3.wav", "footsteps3");
  my::sound_load(1.0, "data/sounds/misc/footsteps4.wav", "footsteps4");
  my::sound_load(1.0, "data/sounds/misc/footsteps5.wav", "footsteps5");
  my::sound_load(1.0, "data/sounds/misc/footsteps6.wav", "footsteps6");
  my::sound_load(1.0, "data/sounds/misc/footsteps7.wav", "footsteps7");
  my::sound_load(1.0, "data/sounds/misc/footsteps8.wav", "footsteps8");
  my::sound_load(1.0, "data/sounds/misc/gold.wav", "gold");
  my::sound_load(1.0, "data/sounds/misc/powerup.wav", "powerup");
  my::sound_load(1.0, "data/sounds/misc/pressure_plate.wav", "pressure_plate");
  my::sound_load(1.0, "data/sounds/misc/sword_equip.wav", "sword_equip");
}

} // namespace mod_modules_sound
