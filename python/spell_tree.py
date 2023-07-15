import my

my.map_load_spell_tree(
    spell_data=[
        "fd", "spell_summon_food",
        "mm", "spell_magic_missile",
        "sA", "spell_summon_monst_A",
        "sB", "spell_summon_monst_B",
        "sC", "spell_summon_monst_C",
        "sD", "spell_summon_monst_D",
        "sE", "spell_summon_monst_E",
    ])

my.map_load_spell_tree(
    tree_name="combat",
    tree_data=[
        "mm                                      ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
    ],
)

my.map_load_spell_tree(
    tree_name="summoning",
    tree_data=[
        "fd                                      ",
        "                                        ",
        "sA->sB->sC->sD->sE                      ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
        "                                        ",
    ],
)
