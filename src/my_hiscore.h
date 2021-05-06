//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_HISCORE_H_
#define _MY_HISCORE_H_

class HiScore
{   
public:
    HiScore (void) {}
    HiScore (std::string name, 
             int score, 
             int level_reached,
             std::string killed_by)
    {
        this->name = name;
        this->score = score;
        this->level_reached = level_reached;
        this->killed_by = killed_by;
    }

    ~HiScore (void) { }

    //
    // Who made the score?
    //
    std::string  name;
    std::string  killed_by;
    int          score;
    int          level_reached;

    //
    // The number of scores in the table.
    //
    static const int max = 10;
    static const int max_displayed = 10;

};
std::ostream& operator<<(std::ostream &out, Bits<const HiScore & > const my);
std::istream& operator>>(std::istream &in, Bits<HiScore &> my);

class HiScores
{
public:
    HiScores (void);
    ~HiScores (void);

    //
    // All the hiscores held in the file.
    //
    std::vector<HiScore> hiscores;

    void add_new_hiscore(Thingp player, const std::string &name, const std::string &killed_by);
    bool is_new_hiscore(Thingp player);
    bool is_new_highest_hiscore(Thingp player);
    const char *place_str(Thingp player);
};
std::ostream& operator<<(std::ostream &out, Bits<const HiScores & > const my);
std::istream& operator>>(std::istream &in, Bits<HiScores &> my);

#endif // _MY_THING_H_
