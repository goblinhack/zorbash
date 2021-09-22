//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_random_name.h"
#include "my_random.h"

static const char *dict2_names[] = {
    "ace",   "acid",  "aged",  "ahead", "aid",   "ail",   "ails",  "aim",   "aims",  "air",   "airs",    "al",
    "ale",   "algae", "amaze", "amber", "amigo", "among", "angel", "anger", "angst", "anon",  "ape",     "apes",
    "apex",  "arc",   "arch",  "ark",   "armor", "arms",  "army",  "aroma", "arose", "atlas", "attic",   "auger",
    "aura",  "awake", "ax",    "axe",   "baby",  "back",  "bait",  "band",  "bane",  "barb",  "bard",    "basil",
    "bat",   "bates", "bats",  "bear",  "beast", "bite",  "blade", "blaze", "bled",  "bleed", "blood",   "bone",
    "boss",  "bound", "braid", "brain", "breed", "brew",  "brush", "brute", "buddy", "buffy", "bug",     "buggy",
    "bugs",  "burp",  "butt",  "cage",  "caged", "cages", "call",  "calm",  "candy", "carat", "cast",    "cave",
    "caved", "caves", "chasm", "claim", "clan",  "claw",  "claws", "cloak", "club",  "clue",  "coven",   "crud",
    "crypt", "cult",  "cure",  "curse", "death", "deli",  "dell",  "demo",  "demon", "den",   "descent", "devil",
    "diner", "dingo", "disco", "diva",  "doc",   "dom",   "drain", "drake", "drama", "dregs", "drip",    "drips",
    "drop",  "dude",  "dudes", "duel",  "duke",  "dukes", "dune",  "dunes", "dusk",  "ears",  "ed",      "edge",
    "eel",   "eels",  "eerie", "egg",   "eggs",  "ego",   "egos",  "elder", "elite", "ennui", "ery",     "es",
    "ess",   "eve",   "evil",  "fable", "fall",  "falls", "farm",  "farms", "fauna", "fear",  "feast",   "fists",
    "flail", "flank", "flee",  "flesh", "flies", "flog",  "fool",  "fools", "foot",  "foray", "force",   "forge",
    "fork",  "forth", "forum", "fried", "fries", "fuel",  "fumes", "gala",  "game",  "gamer", "games",   "garb",
    "gas",   "gate",  "gates", "gator", "geek",  "geeks", "genie", "gift",  "gifts", "glass", "gleam",   "glory",
    "goal",  "goals", "god",   "gods",  "gold",  "gorge", "gouge", "gown",  "gowns", "grasp", "greed",   "grid",
    "grief", "grime", "grind", "grove", "grunt", "guard", "gulag", "hair",  "hairs", "haste", "haunt",   "haven",
    "havoc", "hero",  "hill",  "hippo", "hope",  "hour",  "hugs",  "humor", "hydra", "hymn",  "hype",    "ice",
    "iest",  "ilk",   "ill",   "ills",  "ire",   "itch",  "ize",   "karma", "kid",   "kiddo", "kids",    "kill",
    "kills", "kiss",  "knock", "knoll", "lair",  "lake",  "land",  "lands", "lang",  "law",   "life",    "lifer",
    "light", "like",  "liked", "likes", "limbo", "limbs", "lime",  "limo",  "limp",  "llama", "lord",    "lords",
    "lore",  "love",  "loved", "lover", "loves", "luck",  "lunch", "lure",  "lured", "lures", "lurk",    "lurks",
    "mace",  "maker", "mall",  "manor", "memo",  "mensa", "mercy", "mess",  "mill",  "mine",  "mob",     "mobs",
    "moral", "motto", "mould", "mush",  "nacho", "nada",  "nest",  "nexus", "ninja", "norm",  "north",   "ogre",
    "oil",   "oops",  "ooze",  "opal",  "opus",  "otter", "pain",  "peak",  "peaks", "pearl", "pile",    "piles",
    "plaza", "plot",  "plots", "ploy",  "point", "poise", "pool",  "poop",  "prime", "privy", "prize",   "prune",
    "puppy", "rain",  "rat",   "rave",  "raven", "realm", "recon", "rex",   "rhino", "ruin",  "ruins",   "rule",
    "ruled", "ruler", "rules", "rune",  "runes", "rust",  "saber", "sable", "sack",  "sacks", "salon",   "salsa",
    "salt",  "sand",  "sands", "satyr", "sauce", "sauna", "scale", "scalp", "scar",  "scuff", "scum",    "sicko",
    "silk",  "sink",  "site",  "sites", "skids", "skull", "spire", "staff", "stake", "star",  "steel",   "swamp",
    "taste", "toll",  "tower", "zoo",
};

const char *dict2_name(void) { return dict2_names[ pcg_random_range(0, ARRAY_SIZE(dict2_names)) ]; }
