//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_ttf.h"

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
        ERR("No name for font %s", __FUNCTION__);
        return (0);
    }

    f = ttf_new(file, size, style);

    auto result = fonts.insert(std::make_pair(name, f));

    if (result.second == false) {
        ERR("Font insert name [%s] failed", name.c_str());
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
        ERR("No filename given for font find %s", __FUNCTION__);
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
    auto tmp = std::string(TTF_PATH) + mybasename(UI_FONT_NAME, __FUNCTION__);
    ttf_write_tga(tmp, UI_FONT_PIXEL_SIZE, TTF_STYLE_NORMAL);

    DIE("Generated fonts");
#endif

    fixed_font = font_load("fixed", (char*)UI_FONT_NAME,
                           UI_FONT_WIDTH,
                           TTF_STYLE_NORMAL);

    return true;
}
