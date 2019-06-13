/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_ttf.h"
#include "my_string.h"

static int32_t font_inited;

Fontp fixed_font;

static std::map<std::string, std::shared_ptr< class Font > > fonts;

void font_fini (void)
{_
    if (font_inited) {
        font_inited = false;

        fixed_font = 0;
        fonts.erase(fonts.begin(), fonts.end());
    }
}

static Fontp font_load (std::string name, std::string file, int size, int style)
{_
    auto f = font_find(name);

    if (f) {
        return (f);
    }

    if (name == "") {
        DIE("no name for font %s", __FUNCTION__);
        return (0);
    }

    f = ttf_new(file, size, style);

    auto result = fonts.insert(std::make_pair(name, f));

    if (result.second == false) {
        DIE("font insert name [%s] failed", name.c_str());
    }

#ifdef ENABLE_GENERATE_TTF
    ttf_read_tga(f, file.c_str(), size);
#endif

    return (f);
}

Fontp font_find (std::string file)
{_
    if (file == "") {
        DIE("no filename given for font find %s", __FUNCTION__);
    }

    auto result = fonts.find(file);
    if (result == fonts.end()) {
        return (0);
    }

    return (result->second);
}

uint8_t font_init (void)
{_
    font_inited = true;

#ifdef ENABLE_GENERATE_TTF
    /*
     * Generate bitmaps from TTF.
     */
    auto tmp = std::string(TTF_PATH) + mybasename(FIXED_FONT, __FUNCTION__);
    ttf_write_tga(tmp, FONT_SIZE, TTF_STYLE_NORMAL);

    DIE("generated fonts");
#endif

    fixed_font = font_load("fixed", (char*)FIXED_FONT,
                           FONT_SIZE,
                           TTF_STYLE_NORMAL);

    return (true);
}
