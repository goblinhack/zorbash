//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_string.h"
#include "slre.h"

bool Thing::matches (const std::string& what) const
{
    if (strisregexp(what.c_str())) {
        struct slre slre;
        if (slre_compile(&slre, what.c_str())) {
            auto name = short_text_name();
            if (slre_match(&slre, name.c_str(), name.size(), 0 /* captures */)) {
                return true;
            }
        }
	return false;
    }

    if (ai_avoid_distance() &&                                (what == "ai_avoid_distance"))                                { return true; }
    if (ai_vision_distance() &&                               (what == "ai_vision_distance"))                               { return true; }
    if (attack_eater() &&                                     (what == "attack_eater"))                                     { return true; }
    if (attack_humanoid() &&                                  (what == "attack_humanoid"))                                  { return true; }
    if (attack_living() &&                                    (what == "attack_living"))                                    { return true; }
    if (attack_lunge() &&                                     (what == "attack_lunge"))                                     { return true; }
    if (attack_meat() &&                                      (what == "attack_meat"))                                      { return true; }
    if (attack_shove() &&                                     (what == "attack_shove"))                                     { return true; }
    if (attack_shove_chance_d1000() &&                        (what == "attack_shove_chance_d1000"))                        { return true; }
    if (hates_acid() &&                                      (what == "hates_acid"))                                      { return true; }
    if (hates_fire() &&                                      (what == "hates_fire"))                                      { return true; }
    if (hates_poison() &&                                    (what == "hates_poison"))                                    { return true; }
    if (hates_water() &&                                     (what == "hates_water"))                                     { return true; }
    if (blast_max_radius() &&                                 (what == "blast_max_radius"))                                 { return true; }
    if (blast_min_radius() &&                                 (what == "blast_min_radius"))                                 { return true; }
    if (damage_doubled_from_acid() &&                         (what == "damage_doubled_from_acid"))                         { return true; }
    if (damage_doubled_from_fire() &&                         (what == "damage_doubled_from_fire"))                         { return true; }
    if (damage_doubled_from_poison() &&                       (what == "damage_doubled_from_poison"))                       { return true; }
    if (damage_doubled_from_water() &&                        (what == "damage_doubled_from_water"))                        { return true; }
    if (gfx_flickers() &&                                     (what == "gfx_flickers"))                                         { return true; }
    if (is_able_to_change_levels() &&                         (what == "is_able_to_change_levels"))                         { return true; }
    if (is_able_to_fall() &&                                  (what == "is_able_to_fall"))                                  { return true; }
    if (is_able_to_fire_at() &&                               (what == "is_able_to_fire_at"))                               { return true; }
    if (is_able_to_see_through_doors() &&                     (what == "is_able_to_see_through_doors"))                     { return true; }
    if (is_able_to_walk_through_walls() &&                    (what == "is_able_to_walk_through_walls"))                    { return true; }
    if (is_acid() &&                                          (what == "is_acid"))                                          { return true; }
    if (is_acid_lover() &&                                    (what == "is_acid_lover"))                                    { return true; }
    if (is_active() &&                                        (what == "is_active"))                                        { return true; }
    if (is_alive_monst() &&                                   (what == "is_alive_monst"))                                   { return true; }
    if (is_always_hit() &&                                    (what == "is_always_hit"))                                    { return true; }
    if (is_ascend_dungeon() &&                                (what == "is_ascend_dungeon"))                                { return true; }
    if (is_ascend_sewer() &&                                  (what == "is_ascend_sewer"))                                  { return true; }
    if (is_attackable_by_monst() &&                           (what == "is_attackable_by_monst"))                           { return true; }
    if (is_attackable_by_player() &&                          (what == "is_attackable_by_player"))                          { return true; }
    if (is_auto_collect_item() &&                             (what == "is_auto_collect_item"))                             { return true; }
    if (is_bag() &&                                           (what == "is_bag"))                                           { return true; }
    if (is_bleeder() &&                                       (what == "is_bleeder"))                                       { return true; }
    if (is_blood() &&                                         (what == "is_blood"))                                         { return true; }
    if (is_blood_splatter() &&                                (what == "is_blood_splatter"))                                { return true; }
    if (is_brazier() &&                                       (what == "is_brazier"))                                       { return true; }
    if (is_rrr99() &&                                         (what == "is_rrr99"))                                      { return true; }
    if (is_carrier_of_treasure_class_a() &&                   (what == "is_carrier_of_treasure_class_a"))                   { return true; }
    if (is_carrier_of_treasure_class_b() &&                   (what == "is_carrier_of_treasure_class_b"))                   { return true; }
    if (is_carrier_of_treasure_class_c() &&                   (what == "is_carrier_of_treasure_class_c"))                   { return true; }
    if (is_chasm() &&                                         (what == "is_chasm"))                                         { return true; }
    if (is_collect_as_keys() &&                               (what == "is_collect_as_keys"))                               { return true; }
    if (is_collectable() &&                                   (what == "is_collectable"))                                   { return true; }
    if (is_combustible() &&                                   (what == "is_combustible"))                                   { return true; }
    if (is_corpse() &&                                        (what == "is_corpse"))                                        { return true; }
    if (is_corridor() &&                                      (what == "is_corridor"))                                      { return true; }
    if (is_critical_to_level() &&                             (what == "is_critical_to_level"))                             { return true; }
    if (is_cursor() &&                                        (what == "is_cursor"))                                        { return true; }
    if (is_cursor_can_hover_over() &&                         (what == "is_cursor_can_hover_over"))                         { return true; }
    if (is_cursor_can_hover_over_but_needs_double_click() &&  (what == "is_cursor_can_hover_over_but_needs_double_click"))  { return true; }
    if (is_cursor_path() &&                                   (what == "is_cursor_path"))                                   { return true; }
    if (is_dead_on_shove() &&                                 (what == "is_dead_on_shove"))                                 { return true; }
    if (is_deep_water() &&                                    (what == "is_deep_water"))                                    { return true; }
    if (is_descend_dungeon() &&                               (what == "is_descend_dungeon"))                               { return true; }
    if (is_descend_sewer() &&                                 (what == "is_descend_sewer"))                                 { return true; }
    if (is_described_when_hovering_over() &&                  (what == "is_described_when_hovering_over"))                  { return true; }
    if (is_dirt() &&                                          (what == "is_dirt"))                                          { return true; }
    if (is_door() &&                                          (what == "is_door"))                                          { return true; }
    if (is_droppable() &&                                     (what == "is_droppable"))                                     { return true; }
    if (is_ethereal() &&                                      (what == "is_ethereal"))                                      { return true; }
    if (is_ethereal_minion_generator() &&                     (what == "is_ethereal_minion_generator"))                     { return true; }
    if (is_explosion() &&                                     (what == "is_explosion"))                                     { return true; }
    if (is_extreme_hazard() &&                                (what == "is_extreme_hazard"))                                { return true; }
    if (is_fearless() &&                                      (what == "is_fearless"))                                      { return true; }
    if (is_fire() &&                                          (what == "is_fire"))                                          { return true; }
    if (is_very_combustible() &&                              (what == "is_very_combustible"))                                     { return true; }
    if (is_floating() &&                                      (what == "is_floating"))                                      { return true; }
    if (is_floor() &&                                         (what == "is_floor"))                                         { return true; }
    if (is_floor_deco() &&                                    (what == "is_floor_deco"))                                    { return true; }
    if (is_food() &&                                          (what == "is_food"))                                          { return true; }
    if (is_food_eater() &&                                    (what == "is_food_eater"))                                    { return true; }
    if (is_gold() &&                                          (what == "is_gold"))                                          { return true; }
    if (is_hazard() &&                                        (what == "is_hazard"))                                        { return true; }
    if (is_humanoid() &&                                      (what == "is_humanoid"))                                      { return true; }
    if (is_hunger_insatiable() &&                             (what == "is_hunger_insatiable"))                             { return true; }
    if (is_intelligent() &&                                   (what == "is_intelligent"))                                   { return true; }
    if (is_interesting() &&                                   (what == "is_interesting"))                                   { return true; }
    if (is_item() &&                                          (what == "is_item"))                                          { return true; }
    if (is_item_carrier() &&                                  (what == "is_item_carrier"))                                  { return true; }
    if (is_item_collected_as_gold() &&                        (what == "is_item_collected_as_gold"))                        { return true; }
    if (is_item_eater() &&                                    (what == "is_item_eater"))                                    { return true; }
    if (is_item_not_stackable() &&                            (what == "is_item_not_stackable"))                            { return true; }
    if (is_jelly() &&                                         (what == "is_jelly"))                                         { return true; }
    if (is_jelly_baby() &&                                    (what == "is_jelly_baby"))                                    { return true; }
    if (is_jelly_baby_eater() &&                              (what == "is_jelly_baby_eater"))                              { return true; }
    if (is_jelly_eater() &&                                   (what == "is_jelly_eater"))                                   { return true; }
    if (is_jelly_parent() &&                                  (what == "is_jelly_parent"))                                  { return true; }
    if (is_jumper() &&                                        (what == "is_jumper"))                                        { return true; }
    if (is_jumper_chance_d1000() &&                           (what == "is_jumper_chance_d1000"))                           { return true; }
    if (is_jumper_distance() &&                               (what == "is_jumper_distance"))                               { return true; }
    if (is_jumper_on_low_hp_chance_d1000() &&                 (what == "is_jumper_on_low_hp_chance_d1000"))                 { return true; }
    if (is_key() &&                                           (what == "is_key"))                                           { return true; }
    if (is_killed_on_hit_or_miss() &&                         (what == "is_killed_on_hit_or_miss"))                         { return true; }
    if (is_killed_on_hitting() &&                             (what == "is_killed_on_hitting"))                             { return true; }
    if (is_laser() &&                                         (what == "is_laser"))                                         { return true; }
    if (is_target_select_automatically_when_chosen() &&       (what == "is_target_select_automatically_when_chosen")) { return true; }
    if (is_lava() &&                                          (what == "is_lava"))                                          { return true; }
    if (is_light_blocker() &&                                 (what == "is_light_blocker"))                                 { return true; }
    if (is_living() &&                                        (what == "is_living"))                                        { return true; }
    if (is_loggable_for_important_stuff() &&                  (what == "is_loggable_for_important_stuff"))                  { return true; }
    if (is_loggable_for_unimportant_stuff() &&                (what == "is_loggable_for_unimportant_stuff"))                { return true; }
    if (is_meat() &&                                          (what == "is_meat"))                                          { return true; }
    if (is_meat_eater() &&                                    (what == "is_meat_eater"))                                    { return true; }
    if (is_minion() &&                                        (what == "is_minion"))                                        { return true; }
    if (is_minion_generator() &&                              (what == "is_minion_generator"))                              { return true; }
    if (is_monst() &&                                         (what == "is_monst"))                                         { return true; }
    if (is_moveable() &&                                      (what == "is_moveable"))                                      { return true; }
    if (is_movement_blocking_hard() &&                        (what == "is_movement_blocking_hard"))                        { return true; }
    if (is_movement_blocking_soft() &&                        (what == "is_movement_blocking_soft"))                        { return true; }
    if (is_msg() &&                                           (what == "is_msg"))                                           { return true; }
    if (is_no_tile() &&                                       (what == "is_no_tile"))                                       { return true; }
    if (is_player() &&                                        (what == "is_player"))                                        { return true; }
    if (is_poison() &&                                        (what == "is_poison"))                                        { return true; }
    if (loves_poison() &&                              (what == "loves_poison"))                                 { return true; }
    if (is_potion() &&                                        (what == "is_potion"))                                        { return true; }
    if (is_potion_eater() &&                                  (what == "is_potion_eater"))                                  { return true; }
    if (is_projectile() &&                                    (what == "is_projectile"))                                    { return true; }
    if (is_removeable_if_out_of_slots() &&                    (what == "is_removeable_if_out_of_slots"))                    { return true; }
    if (is_resurrectable() &&                                 (what == "is_resurrectable"))                                 { return true; }
    if (is_ripple() &&                                        (what == "is_ripple"))                                        { return true; }
    if (is_rock() &&                                          (what == "is_rock"))                                          { return true; }
    if (is_rrr1() &&                                          (what == "is_rrr1"))                                          { return true; }
    if (is_rrr10() &&                                         (what == "is_rrr10"))                                         { return true; }
    if (is_rrr11() &&                                         (what == "is_rrr11"))                                         { return true; }
    if (is_rrr12() &&                                         (what == "is_rrr12"))                                         { return true; }
    if (is_rrr13() &&                                         (what == "is_rrr13"))                                         { return true; }
    if (is_rrr14() &&                                         (what == "is_rrr14"))                                         { return true; }
    if (is_rrr15() &&                                         (what == "is_rrr15"))                                         { return true; }
    if (is_rrr16() &&                                         (what == "is_rrr16"))                                         { return true; }
    if (is_rrr17() &&                                         (what == "is_rrr17"))                                         { return true; }
    if (is_rrr18() &&                                         (what == "is_rrr18"))                                         { return true; }
    if (is_rrr19() &&                                         (what == "is_rrr19"))                                         { return true; }
    if (is_rrr2() &&                                          (what == "is_rrr2"))                                          { return true; }
    if (is_rrr20() &&                                         (what == "is_rrr20"))                                         { return true; }
    if (is_rrr21() &&                                         (what == "is_rrr21"))                                         { return true; }
    if (is_rrr22() &&                                         (what == "is_rrr22"))                                         { return true; }
    if (is_rrr23() &&                                         (what == "is_rrr23"))                                         { return true; }
    if (is_rrr24() &&                                         (what == "is_rrr24"))                                         { return true; }
    if (is_rrr25() &&                                         (what == "is_rrr25"))                                         { return true; }
    if (is_rrr26() &&                                         (what == "is_rrr26"))                                         { return true; }
    if (is_rrr27() &&                                         (what == "is_rrr27"))                                         { return true; }
    if (is_rrr28() &&                                         (what == "is_rrr28"))                                         { return true; }
    if (is_rrr29() &&                                         (what == "is_rrr29"))                                         { return true; }
    if (is_rrr3() &&                                          (what == "is_rrr3"))                                          { return true; }
    if (is_rrr30() &&                                         (what == "is_rrr30"))                                         { return true; }
    if (is_rrr31() &&                                         (what == "is_rrr31"))                                         { return true; }
    if (is_rrr32() &&                                         (what == "is_rrr32"))                                         { return true; }
    if (is_rrr33() &&                                         (what == "is_rrr33"))                                         { return true; }
    if (is_rrr34() &&                                         (what == "is_rrr34"))                                         { return true; }
    if (is_rrr35() &&                                         (what == "is_rrr35"))                                         { return true; }
    if (is_rrr36() &&                                         (what == "is_rrr36"))                                         { return true; }
    if (is_rrr37() &&                                         (what == "is_rrr37"))                                         { return true; }
    if (is_rrr38() &&                                         (what == "is_rrr38"))                                         { return true; }
    if (is_rrr39() &&                                         (what == "is_rrr39"))                                         { return true; }
    if (is_rrr4() &&                                          (what == "is_rrr4"))                                          { return true; }
    if (is_rrr40() &&                                         (what == "is_rrr40"))                                         { return true; }
    if (is_rrr41() &&                                         (what == "is_rrr41"))                                         { return true; }
    if (is_rrr42() &&                                         (what == "is_rrr42"))                                         { return true; }
    if (is_rrr43() &&                                         (what == "is_rrr43"))                                         { return true; }
    if (is_rrr44() &&                                         (what == "is_rrr44"))                                         { return true; }
    if (is_rrr45() &&                                         (what == "is_rrr45"))                                         { return true; }
    if (is_rrr46() &&                                         (what == "is_rrr46"))                                         { return true; }
    if (is_rrr47() &&                                         (what == "is_rrr47"))                                         { return true; }
    if (is_rrr48() &&                                         (what == "is_rrr48"))                                         { return true; }
    if (is_rrr49() &&                                         (what == "is_rrr49"))                                         { return true; }
    if (is_rrr5() &&                                          (what == "is_rrr5"))                                          { return true; }
    if (is_rrr50() &&                                         (what == "is_rrr50"))                                         { return true; }
    if (is_rrr51() &&                                         (what == "is_rrr51"))                                         { return true; }
    if (is_rrr52() &&                                         (what == "is_rrr52"))                                         { return true; }
    if (is_rrr53() &&                                         (what == "is_rrr53"))                                         { return true; }
    if (is_rrr54() &&                                         (what == "is_rrr54"))                                         { return true; }
    if (is_rrr55() &&                                         (what == "is_rrr55"))                                         { return true; }
    if (is_rrr56() &&                                         (what == "is_rrr56"))                                         { return true; }
    if (is_rrr57() &&                                         (what == "is_rrr57"))                                         { return true; }
    if (is_rrr58() &&                                         (what == "is_rrr58"))                                         { return true; }
    if (is_rrr59() &&                                         (what == "is_rrr59"))                                         { return true; }
    if (is_rrr6() &&                                          (what == "is_rrr6"))                                          { return true; }
    if (is_rrr60() &&                                         (what == "is_rrr60"))                                         { return true; }
    if (is_rrr61() &&                                         (what == "is_rrr61"))                                         { return true; }
    if (is_rrr62() &&                                         (what == "is_rrr62"))                                         { return true; }
    if (is_rrr63() &&                                         (what == "is_rrr63"))                                         { return true; }
    if (is_rrr64() &&                                         (what == "is_rrr64"))                                         { return true; }
    if (is_rrr65() &&                                         (what == "is_rrr65"))                                         { return true; }
    if (is_rrr66() &&                                         (what == "is_rrr66"))                                         { return true; }
    if (is_rrr67() &&                                         (what == "is_rrr67"))                                         { return true; }
    if (is_rrr68() &&                                         (what == "is_rrr68"))                                         { return true; }
    if (is_rrr69() &&                                         (what == "is_rrr69"))                                         { return true; }
    if (is_rrr7() &&                                          (what == "is_rrr7"))                                          { return true; }
    if (is_rrr70() &&                                         (what == "is_rrr70"))                                         { return true; }
    if (is_rrr71() &&                                         (what == "is_rrr71"))                                         { return true; }
    if (is_rrr72() &&                                         (what == "is_rrr72"))                                         { return true; }
    if (is_rrr73() &&                                         (what == "is_rrr73"))                                         { return true; }
    if (is_rrr74() &&                                         (what == "is_rrr74"))                                         { return true; }
    if (is_rrr75() &&                                         (what == "is_rrr75"))                                         { return true; }
    if (is_rrr76() &&                                         (what == "is_rrr76"))                                         { return true; }
    if (is_rrr77() &&                                         (what == "is_rrr77"))                                         { return true; }
    if (is_rrr78() &&                                         (what == "is_rrr78"))                                         { return true; }
    if (is_rrr79() &&                                         (what == "is_rrr79"))                                         { return true; }
    if (is_rrr8() &&                                          (what == "is_rrr8"))                                          { return true; }
    if (is_rrr80() &&                                         (what == "is_rrr80"))                                         { return true; }
    if (is_rrr81() &&                                         (what == "is_rrr81"))                                         { return true; }
    if (is_enchantstone() &&                                  (what == "is_enchantstone"))                                         { return true; }
    if (is_enchantable() &&                                   (what == "is_enchantable"))                                         { return true; }
    if (is_indestructible() &&                                (what == "is_indestructible"))                                         { return true; }
    if (is_bones() &&                                         (what == "is_bones"))                                         { return true; }
    if (is_soft_body() &&                                     (what == "is_soft_body"))                                         { return true; }
    if (is_foilage() &&                                       (what == "is_foilage"))                                         { return true; }
    if (gfx_very_small_shadow_caster() &&                     (what == "gfx_very_small_shadow_caster"))                                         { return true; }
    if (is_dry_fungus() &&                                    (what == "is_dry_fungus"))                                         { return true; }
    if (is_rrr9() &&                                          (what == "is_rrr9"))                                          { return true; }
    if (is_bridge() &&                                        (what == "is_bridge"))                                         { return true; }
    if (is_barrel() &&                                        (what == "is_barrel"))                                         { return true; }
    if (is_burnable() &&                                      (what == "is_burnable"))                                         { return true; }
    if (is_wand_eater() &&                                    (what == "is_wand_eater"))                                         { return true; }
    if (loves_fire() &&                                       (what == "loves_fire"))                                         { return true; }
    if (is_projectile() &&                                    (what == "is_projectile"))                                         { return true; }
    if (is_secret_door() &&                                   (what == "is_secret_door"))                                   { return true; }
    if (is_sewer_wall() &&                                    (what == "is_sewer_wall"))                                    { return true; }
    if (is_shallow_water() &&                                 (what == "is_shallow_water"))                                 { return true; }
    if (is_shovable() &&                                      (what == "is_shovable"))                                      { return true; }
    if (is_shown_on_leftbar() &&                              (what == "is_shown_on_leftbar"))                              { return true; }
    if (is_shown_uniquely_on_leftbar() &&                     (what == "is_shown_uniquely_on_leftbar"))                     { return true; }
    if (is_skill() &&                                         (what == "is_skill"))                                         { return true; }
    if (is_smoke() &&                                         (what == "is_smoke"))                                         { return true; }
    if (is_spawner() &&                                       (what == "is_spawner"))                                       { return true; }
    if (is_stamina_check() &&                                 (what == "is_stamina_check"))                                 { return true; }
    if (is_steal_item_chance_d1000() &&                       (what == "is_steal_item_chance_d1000"))                       { return true; }
    if (is_temporary_bag() &&                                 (what == "is_temporary_bag"))                                 { return true; }
    if (is_throwable() &&                                     (what == "is_throwable"))                                     { return true; }
    if (is_thrown_automatically_when_chosen() &&              (what == "is_thrown_automatically_when_chosen"))              { return true; }
    if (is_torch() &&                                         (what == "is_torch"))                                         { return true; }
    if (is_treasure() &&                                      (what == "is_treasure"))                                      { return true; }
    if (is_treasure_class_a() &&                              (what == "is_treasure_class_a"))                              { return true; }
    if (is_treasure_class_b() &&                              (what == "is_treasure_class_b"))                              { return true; }
    if (is_treasure_class_c() &&                              (what == "is_treasure_class_c"))                              { return true; }
    if (is_treasure_eater() &&                                (what == "is_treasure_eater"))                                { return true; }
    if (is_undead() &&                                        (what == "is_undead"))                                        { return true; }
    if (is_usable() &&                                        (what == "is_usable"))                                        { return true; }
    if (is_used_automatically_when_selected() &&              (what == "is_used_automatically_when_selected"))              { return true; }
    if (is_used_when_thrown() &&                              (what == "is_used_when_thrown"))                              { return true; }
    if (is_wall() &&                                          (what == "is_wall"))                                          { return true; }
    if (is_wall_dungeon() &&                                  (what == "is_wall_dungeon"))                                  { return true; }
    if (is_wand() &&                                          (what == "is_wand"))                                          { return true; }
    if (is_water_lover() &&                                   (what == "is_water_lover"))                                   { return true; }
    if (is_weapon() &&                                        (what == "is_weapon"))                                        { return true; }
    if (is_weapon_wielder() &&                                (what == "is_weapon_wielder"))                                { return true; }
    if (minion_leash_distance() &&                            (what == "minion_leash_distance"))                            { return true; }
    if (minion_limit() &&                                     (what == "minion_limit"))                                     { return true; }
    if (range_max() &&                                        (what == "range_max"))                                        { return true; }

    //
    // Any water type
    //
    if ((is_shallow_water() || is_deep_water()) &&            (what == "is_water"))                                         { return true; }

    return (what == short_text_name());
}

std::function<int(Thingp)> Thing::matches_to_func (const std::string& what)
{
    if (what == "ai_avoid_distance")                                { return &Thing::ai_avoid_distance; }
    if (what == "ai_vision_distance")                               { return &Thing::ai_vision_distance; }
    if (what == "attack_eater")                                     { return &Thing::attack_eater; }
    if (what == "attack_humanoid")                                  { return &Thing::attack_humanoid; }
    if (what == "attack_living")                                    { return &Thing::attack_living; }
    if (what == "attack_lunge")                                     { return &Thing::attack_lunge; }
    if (what == "attack_meat")                                      { return &Thing::attack_meat; }
    if (what == "attack_shove")                                     { return &Thing::attack_shove; }
    if (what == "attack_shove_chance_d1000")                        { return &Thing::attack_shove_chance_d1000; }
    if (what == "hates_acid")                                      { return &Thing::hates_acid; }
    if (what == "hates_fire")                                      { return &Thing::hates_fire; }
    if (what == "hates_poison")                                    { return &Thing::hates_poison; }
    if (what == "hates_water")                                     { return &Thing::hates_water; }
    if (what == "blast_max_radius")                                 { return &Thing::blast_max_radius; }
    if (what == "blast_min_radius")                                 { return &Thing::blast_min_radius; }
    if (what == "damage_doubled_from_acid")                         { return &Thing::damage_doubled_from_acid; }
    if (what == "damage_doubled_from_fire")                         { return &Thing::damage_doubled_from_fire; }
    if (what == "damage_doubled_from_poison")                       { return &Thing::damage_doubled_from_poison; }
    if (what == "damage_doubled_from_water")                        { return &Thing::damage_doubled_from_water; }
    if (what == "is_able_to_change_levels")                         { return &Thing::is_able_to_change_levels; }
    if (what == "is_able_to_fall")                                  { return &Thing::is_able_to_fall; }
    if (what == "is_able_to_fire_at")                               { return &Thing::is_able_to_fire_at; }
    if (what == "is_able_to_see_through_doors")                     { return &Thing::is_able_to_see_through_doors; }
    if (what == "is_able_to_walk_through_walls")                    { return &Thing::is_able_to_walk_through_walls; }
    if (what == "is_acid")                                          { return &Thing::is_acid; }
    if (what == "is_acid_lover")                                    { return &Thing::is_acid_lover; }
    if (what == "is_active")                                        { return &Thing::is_active; }
    if (what == "is_alive_monst")                                   { return &Thing::is_alive_monst; }
    if (what == "is_always_hit")                                    { return &Thing::is_always_hit; }
    if (what == "is_ascend_dungeon")                                { return &Thing::is_ascend_dungeon; }
    if (what == "is_ascend_sewer")                                  { return &Thing::is_ascend_sewer; }
    if (what == "is_attackable_by_monst")                           { return &Thing::is_attackable_by_monst; }
    if (what == "is_attackable_by_player")                          { return &Thing::is_attackable_by_player; }
    if (what == "is_auto_collect_item")                             { return &Thing::is_auto_collect_item; }
    if (what == "is_bag")                                           { return &Thing::is_bag; }
    if (what == "is_bleeder")                                       { return &Thing::is_bleeder; }
    if (what == "is_blood")                                         { return &Thing::is_blood; }
    if (what == "is_blood_splatter")                                { return &Thing::is_blood_splatter; }
    if (what == "is_brazier")                                       { return &Thing::is_brazier; }
    if (what == "is_rrr99")                                         { return &Thing::is_rrr99; }
    if (what == "is_carrier_of_treasure_class_a")                   { return &Thing::is_carrier_of_treasure_class_a; }
    if (what == "is_carrier_of_treasure_class_b")                   { return &Thing::is_carrier_of_treasure_class_b; }
    if (what == "is_carrier_of_treasure_class_c")                   { return &Thing::is_carrier_of_treasure_class_c; }
    if (what == "is_chasm")                                         { return &Thing::is_chasm; }
    if (what == "is_collect_as_keys")                               { return &Thing::is_collect_as_keys; }
    if (what == "is_collectable")                                   { return &Thing::is_collectable; }
    if (what == "is_combustible")                                   { return &Thing::is_combustible; }
    if (what == "is_corpse")                                        { return &Thing::is_corpse; }
    if (what == "is_corridor")                                      { return &Thing::is_corridor; }
    if (what == "is_critical_to_level")                             { return &Thing::is_critical_to_level; }
    if (what == "is_cursor")                                        { return &Thing::is_cursor; }
    if (what == "is_cursor_can_hover_over")                         { return &Thing::is_cursor_can_hover_over; }
    if (what == "is_cursor_can_hover_over_but_needs_double_click")  { return &Thing::is_cursor_can_hover_over_but_needs_double_click; }
    if (what == "is_cursor_path")                                   { return &Thing::is_cursor_path; }
    if (what == "is_dead_on_shove")                                 { return &Thing::is_dead_on_shove; }
    if (what == "is_deep_water")                                    { return &Thing::is_deep_water; }
    if (what == "is_descend_dungeon")                               { return &Thing::is_descend_dungeon; }
    if (what == "is_descend_sewer")                                 { return &Thing::is_descend_sewer; }
    if (what == "is_described_when_hovering_over")                  { return &Thing::is_described_when_hovering_over; }
    if (what == "is_dirt")                                          { return &Thing::is_dirt; }
    if (what == "is_door")                                          { return &Thing::is_door; }
    if (what == "is_droppable")                                     { return &Thing::is_droppable; }
    if (what == "is_ethereal")                                      { return &Thing::is_ethereal; }
    if (what == "is_ethereal_minion_generator")                     { return &Thing::is_ethereal_minion_generator; }
    if (what == "is_explosion")                                     { return &Thing::is_explosion; }
    if (what == "is_extreme_hazard")                                { return &Thing::is_extreme_hazard; }
    if (what == "is_fearless")                                      { return &Thing::is_fearless; }
    if (what == "is_fire")                                          { return &Thing::is_fire; }
    if (what == "is_very_combustible")                              { return &Thing::is_very_combustible; }
    if (what == "is_floating")                                      { return &Thing::is_floating; }
    if (what == "is_floor")                                         { return &Thing::is_floor; }
    if (what == "is_floor_deco")                                    { return &Thing::is_floor_deco; }
    if (what == "is_food")                                          { return &Thing::is_food; }
    if (what == "is_food_eater")                                    { return &Thing::is_food_eater; }
    if (what == "is_gold")                                          { return &Thing::is_gold; }
    if (what == "is_hazard")                                        { return &Thing::is_hazard; }
    if (what == "is_humanoid")                                      { return &Thing::is_humanoid; }
    if (what == "is_hunger_insatiable")                             { return &Thing::is_hunger_insatiable; }
    if (what == "is_intelligent")                                   { return &Thing::is_intelligent; }
    if (what == "is_interesting")                                   { return &Thing::is_interesting; }
    if (what == "is_item")                                          { return &Thing::is_item; }
    if (what == "is_item_carrier")                                  { return &Thing::is_item_carrier; }
    if (what == "is_item_collected_as_gold")                        { return &Thing::is_item_collected_as_gold; }
    if (what == "is_item_eater")                                    { return &Thing::is_item_eater; }
    if (what == "is_item_not_stackable")                            { return &Thing::is_item_not_stackable; }
    if (what == "is_jelly")                                         { return &Thing::is_jelly; }
    if (what == "is_jelly_baby")                                    { return &Thing::is_jelly_baby; }
    if (what == "is_jelly_baby_eater")                              { return &Thing::is_jelly_baby_eater; }
    if (what == "is_jelly_eater")                                   { return &Thing::is_jelly_eater; }
    if (what == "is_jelly_parent")                                  { return &Thing::is_jelly_parent; }
    if (what == "is_jumper")                                        { return &Thing::is_jumper; }
    if (what == "is_jumper_chance_d1000")                           { return &Thing::is_jumper_chance_d1000; }
    if (what == "is_jumper_distance")                               { return &Thing::is_jumper_distance; }
    if (what == "is_jumper_on_low_hp_chance_d1000")                 { return &Thing::is_jumper_on_low_hp_chance_d1000; }
    if (what == "is_key")                                           { return &Thing::is_key; }
    if (what == "is_killed_on_hit_or_miss")                         { return &Thing::is_killed_on_hit_or_miss; }
    if (what == "is_killed_on_hitting")                             { return &Thing::is_killed_on_hitting; }
    if (what == "is_laser")                                         { return &Thing::is_laser; }
    if (what == "is_target_select_automatically_when_chosen")       { return &Thing::is_target_select_automatically_when_chosen; }
    if (what == "is_lava")                                          { return &Thing::is_lava; }
    if (what == "is_light_blocker")                                 { return &Thing::is_light_blocker; }
    if (what == "is_living")                                        { return &Thing::is_living; }
    if (what == "is_loggable_for_important_stuff")                  { return &Thing::is_loggable_for_important_stuff; }
    if (what == "is_loggable_for_unimportant_stuff")                { return &Thing::is_loggable_for_unimportant_stuff; }
    if (what == "is_meat")                                          { return &Thing::is_meat; }
    if (what == "is_meat_eater")                                    { return &Thing::is_meat_eater; }
    if (what == "is_minion")                                        { return &Thing::is_minion; }
    if (what == "is_minion_generator")                              { return &Thing::is_minion_generator; }
    if (what == "is_monst")                                         { return &Thing::is_monst; }
    if (what == "is_moveable")                                      { return &Thing::is_moveable; }
    if (what == "is_movement_blocking_hard")                        { return &Thing::is_movement_blocking_hard; }
    if (what == "is_movement_blocking_soft")                        { return &Thing::is_movement_blocking_soft; }
    if (what == "is_msg")                                           { return &Thing::is_msg; }
    if (what == "is_no_tile")                                       { return &Thing::is_no_tile; }
    if (what == "is_player")                                        { return &Thing::is_player; }
    if (what == "is_poison")                                        { return &Thing::is_poison; }
    if (what == "loves_poison")                              { return &Thing::loves_poison; }
    if (what == "is_potion")                                        { return &Thing::is_potion; }
    if (what == "is_potion_eater")                                  { return &Thing::is_potion_eater; }
    if (what == "is_projectile")                                    { return &Thing::is_projectile; }
    if (what == "is_removeable_if_out_of_slots")                    { return &Thing::is_removeable_if_out_of_slots; }
    if (what == "is_resurrectable")                                 { return &Thing::is_resurrectable; }
    if (what == "is_ripple")                                        { return &Thing::is_ripple; }
    if (what == "is_rock")                                          { return &Thing::is_rock; }
    if (what == "is_rrr1")                                          { return &Thing::is_rrr1; }
    if (what == "is_rrr10")                                         { return &Thing::is_rrr10; }
    if (what == "is_rrr11")                                         { return &Thing::is_rrr11; }
    if (what == "is_rrr12")                                         { return &Thing::is_rrr12; }
    if (what == "is_rrr13")                                         { return &Thing::is_rrr13; }
    if (what == "is_rrr14")                                         { return &Thing::is_rrr14; }
    if (what == "is_rrr15")                                         { return &Thing::is_rrr15; }
    if (what == "is_rrr16")                                         { return &Thing::is_rrr16; }
    if (what == "is_rrr17")                                         { return &Thing::is_rrr17; }
    if (what == "is_rrr18")                                         { return &Thing::is_rrr18; }
    if (what == "is_rrr19")                                         { return &Thing::is_rrr19; }
    if (what == "is_rrr2")                                          { return &Thing::is_rrr2; }
    if (what == "is_rrr20")                                         { return &Thing::is_rrr20; }
    if (what == "is_rrr21")                                         { return &Thing::is_rrr21; }
    if (what == "is_rrr22")                                         { return &Thing::is_rrr22; }
    if (what == "is_rrr23")                                         { return &Thing::is_rrr23; }
    if (what == "is_rrr24")                                         { return &Thing::is_rrr24; }
    if (what == "is_rrr25")                                         { return &Thing::is_rrr25; }
    if (what == "is_rrr26")                                         { return &Thing::is_rrr26; }
    if (what == "is_rrr27")                                         { return &Thing::is_rrr27; }
    if (what == "is_rrr28")                                         { return &Thing::is_rrr28; }
    if (what == "is_rrr29")                                         { return &Thing::is_rrr29; }
    if (what == "is_rrr3")                                          { return &Thing::is_rrr3; }
    if (what == "is_rrr30")                                         { return &Thing::is_rrr30; }
    if (what == "is_rrr31")                                         { return &Thing::is_rrr31; }
    if (what == "is_rrr32")                                         { return &Thing::is_rrr32; }
    if (what == "is_rrr33")                                         { return &Thing::is_rrr33; }
    if (what == "is_rrr34")                                         { return &Thing::is_rrr34; }
    if (what == "is_rrr35")                                         { return &Thing::is_rrr35; }
    if (what == "is_rrr36")                                         { return &Thing::is_rrr36; }
    if (what == "is_rrr37")                                         { return &Thing::is_rrr37; }
    if (what == "is_rrr38")                                         { return &Thing::is_rrr38; }
    if (what == "is_rrr39")                                         { return &Thing::is_rrr39; }
    if (what == "is_rrr4")                                          { return &Thing::is_rrr4; }
    if (what == "is_rrr40")                                         { return &Thing::is_rrr40; }
    if (what == "is_rrr41")                                         { return &Thing::is_rrr41; }
    if (what == "is_rrr42")                                         { return &Thing::is_rrr42; }
    if (what == "is_rrr43")                                         { return &Thing::is_rrr43; }
    if (what == "is_rrr44")                                         { return &Thing::is_rrr44; }
    if (what == "is_rrr45")                                         { return &Thing::is_rrr45; }
    if (what == "is_rrr46")                                         { return &Thing::is_rrr46; }
    if (what == "is_rrr47")                                         { return &Thing::is_rrr47; }
    if (what == "is_rrr48")                                         { return &Thing::is_rrr48; }
    if (what == "is_rrr49")                                         { return &Thing::is_rrr49; }
    if (what == "is_rrr5")                                          { return &Thing::is_rrr5; }
    if (what == "is_rrr50")                                         { return &Thing::is_rrr50; }
    if (what == "is_rrr51")                                         { return &Thing::is_rrr51; }
    if (what == "is_rrr52")                                         { return &Thing::is_rrr52; }
    if (what == "is_rrr53")                                         { return &Thing::is_rrr53; }
    if (what == "is_rrr54")                                         { return &Thing::is_rrr54; }
    if (what == "is_rrr55")                                         { return &Thing::is_rrr55; }
    if (what == "is_rrr56")                                         { return &Thing::is_rrr56; }
    if (what == "is_rrr57")                                         { return &Thing::is_rrr57; }
    if (what == "is_rrr58")                                         { return &Thing::is_rrr58; }
    if (what == "is_rrr59")                                         { return &Thing::is_rrr59; }
    if (what == "is_rrr6")                                          { return &Thing::is_rrr6; }
    if (what == "is_rrr60")                                         { return &Thing::is_rrr60; }
    if (what == "is_rrr61")                                         { return &Thing::is_rrr61; }
    if (what == "is_rrr62")                                         { return &Thing::is_rrr62; }
    if (what == "is_rrr63")                                         { return &Thing::is_rrr63; }
    if (what == "is_rrr64")                                         { return &Thing::is_rrr64; }
    if (what == "is_rrr65")                                         { return &Thing::is_rrr65; }
    if (what == "is_rrr66")                                         { return &Thing::is_rrr66; }
    if (what == "is_rrr67")                                         { return &Thing::is_rrr67; }
    if (what == "is_rrr68")                                         { return &Thing::is_rrr68; }
    if (what == "is_rrr69")                                         { return &Thing::is_rrr69; }
    if (what == "is_rrr7")                                          { return &Thing::is_rrr7; }
    if (what == "is_rrr70")                                         { return &Thing::is_rrr70; }
    if (what == "is_rrr71")                                         { return &Thing::is_rrr71; }
    if (what == "is_rrr72")                                         { return &Thing::is_rrr72; }
    if (what == "is_rrr73")                                         { return &Thing::is_rrr73; }
    if (what == "is_rrr74")                                         { return &Thing::is_rrr74; }
    if (what == "is_rrr75")                                         { return &Thing::is_rrr75; }
    if (what == "is_rrr76")                                         { return &Thing::is_rrr76; }
    if (what == "is_rrr77")                                         { return &Thing::is_rrr77; }
    if (what == "is_rrr78")                                         { return &Thing::is_rrr78; }
    if (what == "is_rrr79")                                         { return &Thing::is_rrr79; }
    if (what == "is_rrr8")                                          { return &Thing::is_rrr8; }
    if (what == "is_rrr80")                                         { return &Thing::is_rrr80; }
    if (what == "is_rrr81")                                         { return &Thing::is_rrr81; }
    if (what == "is_enchantstone")                                  { return &Thing::is_enchantstone; }
    if (what == "is_enchantable")                                   { return &Thing::is_enchantable; }
    if (what == "is_indestructible")                                { return &Thing::is_indestructible; }
    if (what == "is_bones")                                         { return &Thing::is_bones; }
    if (what == "is_soft_body")                                     { return &Thing::is_soft_body; }
    if (what == "is_foilage")                                       { return &Thing::is_foilage; }
    if (what == "gfx_very_small_shadow_caster")                     { return &Thing::gfx_very_small_shadow_caster; }
    if (what == "is_dry_fungus")                                    { return &Thing::is_dry_fungus; }
    if (what == "is_rrr9")                                          { return &Thing::is_rrr9; }
    if (what == "is_bridge")                                        { return &Thing::is_bridge; }
    if (what == "is_barrel")                                        { return &Thing::is_barrel; }
    if (what == "is_burnable")                                      { return &Thing::is_burnable; }
    if (what == "is_wand_eater")                                    { return &Thing::is_wand_eater; }
    if (what == "loves_fire")                                       { return &Thing::loves_fire; }
    if (what == "is_projectile")                                    { return &Thing::is_projectile; }
    if (what == "gfx_flickers")                                     { return &Thing::gfx_flickers; }
    if (what == "is_secret_door")                                   { return &Thing::is_secret_door; }
    if (what == "is_sewer_wall")                                    { return &Thing::is_sewer_wall; }
    if (what == "is_shallow_water")                                 { return &Thing::is_shallow_water; }
    if (what == "is_shovable")                                      { return &Thing::is_shovable; }
    if (what == "is_shown_on_leftbar")                              { return &Thing::is_shown_on_leftbar; }
    if (what == "is_shown_uniquely_on_leftbar")                     { return &Thing::is_shown_uniquely_on_leftbar; }
    if (what == "is_skill")                                         { return &Thing::is_skill; }
    if (what == "is_smoke")                                         { return &Thing::is_smoke; }
    if (what == "is_spawner")                                       { return &Thing::is_spawner; }
    if (what == "is_stamina_check")                                 { return &Thing::is_stamina_check; }
    if (what == "is_steal_item_chance_d1000")                       { return &Thing::is_steal_item_chance_d1000; }
    if (what == "is_temporary_bag")                                 { return &Thing::is_temporary_bag; }
    if (what == "is_throwable")                                     { return &Thing::is_throwable; }
    if (what == "is_thrown_automatically_when_chosen")              { return &Thing::is_thrown_automatically_when_chosen; }
    if (what == "is_torch")                                         { return &Thing::is_torch; }
    if (what == "is_treasure")                                      { return &Thing::is_treasure; }
    if (what == "is_treasure_class_a")                              { return &Thing::is_treasure_class_a; }
    if (what == "is_treasure_class_b")                              { return &Thing::is_treasure_class_b; }
    if (what == "is_treasure_class_c")                              { return &Thing::is_treasure_class_c; }
    if (what == "is_treasure_eater")                                { return &Thing::is_treasure_eater; }
    if (what == "is_undead")                                        { return &Thing::is_undead; }
    if (what == "is_usable")                                        { return &Thing::is_usable; }
    if (what == "is_used_automatically_when_selected")              { return &Thing::is_used_automatically_when_selected; }
    if (what == "is_used_when_thrown")                              { return &Thing::is_used_when_thrown; }
    if (what == "is_wall")                                          { return &Thing::is_wall; }
    if (what == "is_wall_dungeon")                                  { return &Thing::is_wall_dungeon; }
    if (what == "is_wand")                                          { return &Thing::is_wand; }
    if (what == "is_water_lover")                                   { return &Thing::is_water_lover; }
    if (what == "is_weapon")                                        { return &Thing::is_weapon; }
    if (what == "is_weapon_wielder")                                { return &Thing::is_weapon_wielder; }
    if (what == "minion_leash_distance")                            { return &Thing::minion_leash_distance; }
    if (what == "minion_limit")                                     { return &Thing::minion_limit; }
    if (what == "range_max")                                        { return &Thing::range_max; }
    if (what == "is_water")                                         { return &Thing::is_water; }

    DIE("could not find a matches function for [%s]", what.c_str());
}
