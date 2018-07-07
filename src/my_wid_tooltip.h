/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

widp wid_tooltip(std::string text, float x, float y, fontp font);
widp wid_tooltip_simple(std::string text);
widp wid_tooltip_transient(std::string text, uint32_t delay);
widp wid_tooltip_large_transient(std::string text, uint32_t delay);
