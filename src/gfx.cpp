//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_tile.h"
#include "my_gfx.h"

static void gfx_init_text (void)
{
    std::initializer_list<std::string> tiles = {
        //////////////////////////////////////////////////////////////////
        // sp     !       "       #       $       %       &       '
        //////////////////////////////////////////////////////////////////
        "C0",   "C1",   "C2",   "C3",   "C4",   "C5",   "C6",   "C7",
        //////////////////////////////////////////////////////////////////
        //  (     )       *       +       ,       -       .       /
        //////////////////////////////////////////////////////////////////
        "C8",   "C9",   "C10",  "C11",  "C12",  "C13",  "C14",  "C15",
        //////////////////////////////////////////////////////////////////
        //  0     1       2       3       4       5       6       7
        //////////////////////////////////////////////////////////////////
        "C16",  "C17",  "C18",  "C19",  "C20",  "C21",  "C22",  "C23",
        //////////////////////////////////////////////////////////////////
        //  8     9       :       ;       <       =       >       ?
        //////////////////////////////////////////////////////////////////
        "C24",  "C25",  "C26",  "C27",  "C28",  "C29",  "C30",  "C31",
        //////////////////////////////////////////////////////////////////
        //  @     A       B       C       D       E       F       G
        //////////////////////////////////////////////////////////////////
        "C32",  "C33",  "C34",  "C35",  "C36",  "C37",  "C38",  "C39",
        //////////////////////////////////////////////////////////////////
        //  H     I       J       K       L       M       N       O
        //////////////////////////////////////////////////////////////////
        "C40",  "C41",  "C42",  "C43",  "C44",  "C45",  "C46",  "C47",
        //////////////////////////////////////////////////////////////////
        //  P     Q       R       S       T       U       V       W
        //////////////////////////////////////////////////////////////////
        "C48",  "C49",  "C50",  "C51",  "C52",  "C53",  "C54",  "C55",
        //////////////////////////////////////////////////////////////////
        //  X     Y       Z       [       \       ]       ^       _
        //////////////////////////////////////////////////////////////////
        "C56",  "C57",  "C58",  "C59",  "C60",  "C61",  "C62",  "C63",
        //////////////////////////////////////////////////////////////////
        //  `     a       b       c       d       e       f       g
        //////////////////////////////////////////////////////////////////
        "C64",  "C65",  "C66",  "C67",  "C68",  "C69",  "C70",  "C71",
        //////////////////////////////////////////////////////////////////
        //  h     i       j       k       l       m       n       o
        //////////////////////////////////////////////////////////////////
        "C72",  "C73",  "C74",  "C75",  "C76",  "C77",  "C78",  "C79",
        //////////////////////////////////////////////////////////////////
        //  p     q       r       s       t       u       v       w
        //////////////////////////////////////////////////////////////////
        "C80",  "C81",  "C82",  "C83",  "C84",  "C85",  "C86",  "C87",
        //////////////////////////////////////////////////////////////////
        //  x     y       z       {       |       }       ~       del
        //////////////////////////////////////////////////////////////////
        "C88",  "C89",  "C90",  "C91",  "C92",  "C93",  "C94",  "C95",
        //////////////////////////////////////////////////////////////////
        //  blk  [$]     lbs    arrow
        //////////////////////////////////////////////////////////////////
        "C96",  "C97",  "C98",  "C99", "C100", "", "", "",
    };

    const  std::vector<std::string> arr(tiles);
    tile_load_arr_sprites("data/ttf/loresfont.tga", "text",
                          UI_FONT_WIDTH, UI_FONT_HEIGHT, arr);
}

static void gfx_init_ui (void)
{
    {
        std::initializer_list<std::string> tiles = {
            "ui_popup",
        };
        const  std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup.tga", "ui_popup", 80, 152, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_short",
        };
        const  std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_short.tga", "ui_popup_short", 80, 34, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_notice",
        };
        const  std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_notice.tga", "ui_popup_notice", 80, 34, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_wide",
        };
        const  std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_wide.tga", "ui_popup_wide", 120, 152, arr);
    }

    {
        std::initializer_list<std::string> tiles = {
            "ui_popup_widest",
        };
        const  std::vector<std::string> arr(tiles);
        tile_load_arr("data/gfx/ui_popup_widest.tga", "ui_popup_widest", 320, 152, arr);
    }
}

void gfx_init (void)
{
    gfx_init_text();
    gfx_init_ui();
    gfx_init0();
    gfx_init1();
    gfx_init2();
    gfx_init3();
    gfx_init4();
    gfx_init5();
    gfx_init6();
    gfx_init7();
    gfx_init8();
    gfx_init9();
    gfx_init10();
    gfx_init11();
}

void gfx_fini (void)
{
}
