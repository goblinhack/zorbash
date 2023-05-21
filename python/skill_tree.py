import my

my.map_load_skill_tree(
    skill_data=[
        "d1", "skill_devoted_thrust1",
        "d2", "skill_devoted_thrust2",
        "g1", "skill_gold_to_health",
        "a1", "skill_secondary_attack",
        "[]", "",
    ],
    tree_data=[
        "d1->d2                      g1<-[]<-g1  ",
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
        "a1->a1->a1                              ",
        "                                        ",
    ],
)
