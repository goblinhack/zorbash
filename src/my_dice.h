//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_DICE_H_
#define _MY_DICE_H_

#include <string>

class Dice {
private:
    int ndice {};
    int sides {};
    int modifier {};
    std::string hd;
public:
    Dice (void);
    std::string to_string (void) const;
    const char *to_cstring(void);
    Dice (std::string s);
    int roll(void) const;
    int operator ()() const;
};
#endif
