//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_test.h"
#include "my_command.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_wid_popup.h"
#include "my_wid_text_box.h"
#include "my_ascii.h"

static void wid_test_wid_create(void);

void wid_test_fini (void)
{_
}

uint8_t wid_test_init (void)
{_
    wid_test_wid_create();

    return (true);
}

//
// Create the test
//
static void wid_test_wid_create (void)
{_
    {
        point tl = {0, 2};
        point br = {WID_POPUP_WIDTH_NORMAL, ACTIONBAR_TL_Y - 2};
        auto w = new WidPopup(tl, br, tile_find_mand("player1.pose"));
        w->log("%%fg=yellow$This is a really long descriptive string that is a bit boring");
    }
}
