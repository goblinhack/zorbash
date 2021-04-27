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

bool Thing::matches (const std::string& what)
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
    if (avoids_acid() &&                                      (what == "avoids_acid"))                                      { return true; }
    if (avoids_fire() &&                                      (what == "avoids_fire"))                                      { return true; }
    if (avoids_poison() &&                                    (what == "avoids_poison"))                                    { return true; }
    if (avoids_water() &&                                     (what == "avoids_water"))                                     { return true; }
    if (blast_max_radius() &&                                 (what == "blast_max_radius"))                                 { return true; }
    if (blast_min_radius() &&                                 (what == "blast_min_radius"))                                 { return true; }
    if (damage_doubled_from_acid() &&                         (what == "damage_doubled_from_acid"))                         { return true; }
    if (damage_doubled_from_fire() &&                         (what == "damage_doubled_from_fire"))                         { return true; }
    if (damage_doubled_from_poison() &&                       (what == "damage_doubled_from_poison"))                       { return true; }
    if (damage_doubled_from_water() &&                        (what == "damage_doubled_from_water"))                        { return true; }
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
    if (is_burnable() &&                                      (what == "is_burnable"))                                      { return true; }
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
    if (is_flammable() &&                                     (what == "is_flammable"))                                     { return true; }
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
    if (is_laser_target_select_automatically_when_chosen() && (what == "is_laser_target_select_automatically_when_chosen")) { return true; }
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
    if (is_poison_immune() &&                                 (what == "is_poison_immune"))                                 { return true; }
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
    if (is_rrr82() &&                                         (what == "is_rrr82"))                                         { return true; }
    if (is_rrr83() &&                                         (what == "is_rrr83"))                                         { return true; }
    if (is_rrr84() &&                                         (what == "is_rrr84"))                                         { return true; }
    if (is_rrr85() &&                                         (what == "is_rrr85"))                                         { return true; }
    if (is_rrr86() &&                                         (what == "is_rrr86"))                                         { return true; }
    if (is_rrr87() &&                                         (what == "is_rrr87"))                                         { return true; }
    if (is_rrr88() &&                                         (what == "is_rrr88"))                                         { return true; }
    if (is_rrr89() &&                                         (what == "is_rrr89"))                                         { return true; }
    if (is_rrr9() &&                                          (what == "is_rrr9"))                                          { return true; }
    if (is_rrr90() &&                                         (what == "is_rrr90"))                                         { return true; }
    if (is_rrr91() &&                                         (what == "is_rrr91"))                                         { return true; }
    if (is_rrr92() &&                                         (what == "is_rrr92"))                                         { return true; }
    if (is_rrr93() &&                                         (what == "is_rrr93"))                                         { return true; }
    if (is_rrr94() &&                                         (what == "is_rrr94"))                                         { return true; }
    if (is_rrr95() &&                                         (what == "is_rrr95"))                                         { return true; }
    if (is_gfx_flickers() &&                                         (what == "is_gfx_flickers"))                                         { return true; }
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
