//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_ttf.h"
#include "my_string.h"

Fontp fixed_font;

static std::map<std::string, Fontp > fonts;

void font_fini (void)
{_
}

static Fontp font_load (std::string name, std::string file, int size, int style)
{_
    auto f = font_find(name);

    if (f) {
        return (f);
    }

    if (name == "") {
        ERR("no name for font %s", __FUNCTION__);
        return (0);
    }

    f = ttf_new(file, size, style);

    auto result = fonts.insert(std::make_pair(name, f));

    if (result.second == false) {
        ERR("font insert name [%s] failed", name.c_str());
        return (f);
    }

#ifdef ENABLE_GENERATE_TTF
    ttf_read_tga(f, file.c_str(), size);
#endif

    return (f);
}

Fontp font_find (std::string file)
{_
    if (file == "") {
        ERR("no filename given for font find %s", __FUNCTION__);
        return (0);
    }

    auto result = fonts.find(file);
    if (result == fonts.end()) {
        return (0);
    }

    return (result->second);
}

uint8_t font_init (void)
{_
#ifdef ENABLE_GENERATE_TTF
    //
    // Generate bitmaps from TTF.
    //
    auto tmp = std::string(TTF_PATH) + mybasename(FIXED_FONT, __FUNCTION__);
    ttf_write_tga(tmp, FONT_SIZE, TTF_STYLE_NORMAL);

    DIE("generated fonts");
#endif

    fixed_font = font_load("fixed", (char*)FIXED_FONT,
                           FONT_WIDTH,
                           TTF_STYLE_NORMAL);

    return (true);
}
