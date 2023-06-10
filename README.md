<!-- Bugs                                                                                                                                         -->
<!-- ------                                                                                                                                       -->
<!-- Death by jumping in the abyss, crash on new game (I add a save). Not reproduced. -->
<!-- Distinction between depth & jumpable plateform not always clear. I saw my char jumped to their death but didnt know why. I thought the floor broke under. -->
<!-- Maybe auto-pause when damage taken? (Like walking on lava) -->
<!-- I died by being burn alive by some "beacon of light" / brazier. -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Performance                                                                                                                                  -->
<!-- ------                                                                                                                                       -->
<!-- sudo operf ./zorbash-game --playername discobob --seed victimlake --nodebug --quick-start                                                    -->
<!-- opreport  --demangle=smart --symbols| less                                                                                                   -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Skills                                                                                                                                       -->
<!-- ------                                                                                                                                       -->
<!-- - skill, dodge                                                                                                                               -->
<!-- - skill, instakill, once per level                                                                                                           -->
<!-- - skill, heroic charge, rush enemy                                                                                                           -->
<!-- - skill, guaranteed hit, but you have no defense in the next move                                                                            -->
<!-- - skill, whirl attack, attack 2 or 3 enemies                                                                                                 -->
<!-- - skill, defensive mode, recover stamina                                                                                                     -->
<!-- - skill, kneecap, hobble enemy                                                                                                               -->
<!-- - skill, switch to defensive                                                                                                                 -->
<!-- - skill, blind strike, attack the eyes                                                                                                       -->
<!-- - skill, slash and roll                                                                                                                      -->
<!-- - skill, slash and jump                                                                                                                      -->
<!-- - skill, spring attack, give up a round for 2.5 times damage                                                                                 -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- MVP plan                                                                                                                                     -->
<!-- ------                                                                                                                                       -->
<!-- - wort food ? fungus foods and some poisonous?                                                                                               -->
<!-- - pressure plate, that monsters avoid                                                                                                        -->
<!-- - stealth                                                                                                                                    -->
<!-- - cracked walls                                                                                                                              -->
<!-- - paralysis dart                                                                                                                             -->
<!-- - cloak of slime                                                                                                                             -->
<!-- - sword of slime                                                                                                                             -->
<!-- - spider web spawn small spiders?                                                                                                            -->
<!-- - monsters with random buffs like vampirism would be interesting                                                                             -->
<!-- - chaos bell of summoning                                                                                                                    -->
<!-- - crystals walls (or chest) that reflect, so can use on yourself or ally                                                                     -->
<!-- - need allies                                                                                                                                -->
<!-- - cursed weapon with bad luck                                                                                                                -->
<!-- - luck trap                                                                                                                                  -->
<!-- - runics on weapons, like vampirism, force, quietus, lightning                                                                               -->
<!-- - ogre totems?                                                                                                                               -->
<!-- - swamp level                                                                                                                                -->
<!-- - boss 1 Mummy mummy, ankh of life                                                                                                           -->
<!-- - boss 2 slime boss, spawns slimes, tries to jump splat the player                                                                           -->
<!--          swamp tiles that allow 50% movement                                                                                                 -->
<!--          boss will eat swamp wort to spawn                                                                                                   -->
<!--          explode bog tiles to kill boss                                                                                                      -->
<!-- - boss 3 rat king boss, sewer like level with rats coming out of the walls                                                                   -->
<!-- - boss 4 goblin king boss, will be happy if the rat king crown is given                                                                      -->
<!-- - boss 5 water level, kraken?                                                                                                                -->
<!-- - boss 6 ...                                                                                                                                 -->
<!-- - boss 7 face a clone of yourself                                                                                                            -->
<!-- - boss 8 Place crystals at the alter of Zorb. This opens a vault. Go inside and battle zorbash.                                              -->
<!-- -        If you win, the gods turn on you and you get to replaced Zorbash.                                                                   -->
<!-- -        You spare zorbash, he regenerates, you run out and destroy the alter and the demi gods, return to home.                             -->
<!-- -        The curse was that the alter of Zorb would grant demi god status to any that sacrificed one that was dear to them.                  -->
<!-- -        This curse must be renewed many times. Zorbash, -ash means servant of Zorb was such a team member who was sacrificed.               -->
<!-- -        The only way to break the curse is to destroy the crystals. Zorbash will then be freed from servitude.                              -->
<!-- - different sound for bosses                                                                                                                 -->
<!-- - crystal collection                                                                                                                         -->
<!-- - 4 bosses and final zorb boss                                                                                                               -->
<!-- - char selection                                                                                                                             -->
<!-- - level fall through to special level ?                                                                                                      -->
<!-- - hub shop levels                                                                                                                            -->
<!-- - basecamp level?                                                                                                                            -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- UI                                                                                                                                           -->
<!-- ------                                                                                                                                       -->
<!-- - monst head should be on top of armor                                                                                                       -->
<!-- - rest until better                                                                                                                          -->
<!-- - auto explore                                                                                                                               -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Level                                                                                                                                        -->
<!-- ------                                                                                                                                       -->
<!-- - tomb of past player ? or random player ? leads to random small room?                                                                       -->
<!-- - gold needs to do something - shop? buy/sell                                                                                                -->
<!-- - totems are like mobs, but do not spawn except initially. The worshippers are imbued with power but do not die when the totem does.         -->
<!-- - vaults                                                                                                                                     -->
<!-- - portable hunger - teleports you to a room full of digestive juices                                                                         -->
<!-- - moving floor                                                                                                                               -->
<!-- - shove chocolate frog statue, get frog?                                                                                                     -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Traps                                                                                                                                        -->
<!-- ------                                                                                                                                       -->
<!-- - moving blocks?                                                                                                                             -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Poison                                                                                                                                       -->
<!-- ------                                                                                                                                       -->
<!-- - chocolote frog cures poison?                                                                                                               -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Doors                                                                                                                                        -->
<!-- ------                                                                                                                                       -->
<!-- - hit door, summon monst chance                                                                                                              -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- AI                                                                                                                                           -->
<!-- ------                                                                                                                                       -->
<!-- - eat corpses, like a bat corpse?                                                                                                            -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Rings                                                                                                                                        -->
<!-- ------                                                                                                                                       -->
<!-- - necro protection ring                                                                                                                      -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Staffs                                                                                                                                       -->
<!-- ------                                                                                                                                       -->
<!-- - staves that recharge                                                                                                                       -->
<!-- - staff of death should stop regenerating monst                                                                                               -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Potions                                                                                                                                      -->
<!-- ------                                                                                                                                       -->
<!-- - have a monster use a potion?                                                                                                               -->
<!-- - antipoison potion                                                                                                                          -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Armor                                                                                                                                        -->
<!-- ------                                                                                                                                       -->
<!-- - dragon scale mail for fire proofing                                                                                                        -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Weapons                                                                                                                                      -->
<!-- ------                                                                                                                                       -->
<!-- - holy water cures poison                                                                                                                    -->
<!-- - strength penalties                                                                                                                         -->
<!-- - blessed items resist explosion                                                                                                             -->
<!-- - warhammer should kill parent slime in one go                                                                                               -->
<!-- - warhammer smash skeletton                                                                                                                  -->
<!-- - (blunt/warhamma?) slime specific weapon does not cause slimes to split                                                                     -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Monsts                                                                                                                                       -->
<!-- ------                                                                                                                                       -->
<!-- - chccolate golem fires chocolate                                                                                                            -->
<!-- - chickens - battle chickens - lay eggs as food - and they get names                                                                         -->
<!-- - acid jellies should damage weapons                                                                                                         -->
<!-- - mold growth / floor puddings                                                                                                               -->
<!-- - bloodgrass, grows near corpses                                                                                                             -->
<!-- - shove/lure monsters into webs?                                                                                                             -->
<!-- - rat pack and king rat / cranium rat                                                                                                        -->
<!-- - zombie camel?                                                                                                                              -->
<!-- - sewer wolf?                                                                                                                                -->
<!-- - invisible monst?                                                                                                                           -->
<!-- - monster that runs from light ?                                                                                                             -->
<!-- - tentacles out of the ground that try to surround you                                                                                       -->
<!-- - dungeon walrus; long headed walrus with many tusks                                                                                         -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Gods                                                                                                                                         -->
<!-- ------                                                                                                                                       -->
<!-- - runes lean more torwards old gods                                                                                                          -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Gfx                                                                                                                                          -->
<!-- ------                                                                                                                                       -->
<!-- - tiny pixel effects that bounce?                                                                                                            -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Player                                                                                                                                       -->
<!-- ------                                                                                                                                       -->
<!-- - weight factors into jumping                                                                                                                -->
<!-- - carry eat slime mold and gain acid resis?                                                                                                  -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->
<!-- Spells                                                                                                                                       -->
<!-- ------                                                                                                                                       -->
<!-- - spell capacitor                                                                                                                            -->
<!-- - spell chaining                                                                                                                             -->
<!-- ------                                                                                                                                       -->
<!--                                                                                                                                              -->

<p align="center">
<img alt="Pixel art" src="pics/banner.png" width="100%">
</p>

Welcome to the lair of the dread tentacleye, Zorbash. Collect the crystals of Zorb and confront Zorbash to win.

Latest release [found here](https://github.com/goblinhack/zorbash/releases/tag/v0.0.3)

Content:
- Dungeon, sewer, swamp, ice, lava, chasms and flooded dungeon biomes
- No end game, bosses or crystal collection yet
- Multiple skill trees
- Looking for feedback
<!-- begin type marker -->
- 103 x monsters
- 52 x food
- 19 x treasure
- 13 x weapons
- 13 x items
- 12 x buffs
- 9 x skills
- 6 x staffs
- 6 x shield
- 6 x boots
- 5 x rings
- 5 x keys
- 4 x gauntlets
- 4 x debuffs
- 4 x armor
- 4 x amulets
- 3 x mobs
- 3 x doors
- 3 x cloaks
- 2 x traps
- 2 x potions
- 1 x player
<!-- end type marker -->

Comments and suggestions welcome.

Pixel art and ascii mode options
--------------------------------

Press TAB to switch between modes during the game.

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.1.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.1.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.2.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.2.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.3.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.3.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.4.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.4.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.5.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.5.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.6.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.6.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.7.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.7.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.8.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.8.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.9.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.9.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.10.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.10.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.11.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.11.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.12.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.12.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.13.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.13.png" width="45%">
</p>

<p align="center">
<img alt="Pixel art" src="pics/pixelart/screenshot.14.png" width="45%">
&nbsp; &nbsp; &nbsp; &nbsp;
<img alt="Ascii art" src="pics/ascii/screenshot.14.png" width="45%">
</p>

Pixelart Screenshots
--------------------

![Alt text](pics/pixelart/screenshot.1.png?raw=true "")
![Alt text](pics/pixelart/screenshot.2.png?raw=true "")
![Alt text](pics/pixelart/screenshot.3.png?raw=true "")
![Alt text](pics/pixelart/screenshot.4.png?raw=true "")
![Alt text](pics/pixelart/screenshot.5.png?raw=true "")
![Alt text](pics/pixelart/screenshot.6.png?raw=true "")
![Alt text](pics/pixelart/screenshot.7.png?raw=true "")
![Alt text](pics/pixelart/screenshot.8.png?raw=true "")
![Alt text](pics/pixelart/screenshot.9.png?raw=true "")
![Alt text](pics/pixelart/screenshot.10.png?raw=true "")
![Alt text](pics/pixelart/screenshot.11.png?raw=true "")
![Alt text](pics/pixelart/screenshot.12.png?raw=true "")
![Alt text](pics/pixelart/screenshot.13.png?raw=true "")
![Alt text](pics/pixelart/screenshot.14.png?raw=true "")
![Alt text](pics/pixelart/screenshot.15.png?raw=true "")
![Alt text](pics/pixelart/screenshot.16.png?raw=true "")
![Alt text](pics/pixelart/screenshot.17.png?raw=true "")
![Alt text](pics/pixelart/screenshot.18.png?raw=true "")
![Alt text](pics/pixelart/screenshot.19.png?raw=true "")
![Alt text](pics/pixelart/screenshot.20.png?raw=true "")
![Alt text](pics/pixelart/screenshot.21.png?raw=true "")
![Alt text](pics/pixelart/screenshot.22.png?raw=true "")

Ascii Screenshots
-----------------

![Alt text](pics/ascii/screenshot.1.png?raw=true "")
![Alt text](pics/ascii/screenshot.2.png?raw=true "")
![Alt text](pics/ascii/screenshot.3.png?raw=true "")
![Alt text](pics/ascii/screenshot.4.png?raw=true "")
![Alt text](pics/ascii/screenshot.5.png?raw=true "")
![Alt text](pics/ascii/screenshot.6.png?raw=true "")
![Alt text](pics/ascii/screenshot.7.png?raw=true "")
![Alt text](pics/ascii/screenshot.8.png?raw=true "")
![Alt text](pics/ascii/screenshot.9.png?raw=true "")
![Alt text](pics/ascii/screenshot.10.png?raw=true "")
![Alt text](pics/ascii/screenshot.11.png?raw=true "")
![Alt text](pics/ascii/screenshot.12.png?raw=true "")
![Alt text](pics/ascii/screenshot.13.png?raw=true "")
![Alt text](pics/ascii/screenshot.14.png?raw=true "")

How to build
------------

- On Linux: (Ubuntu 22.10, Fedora 37 + Python 3.11)
<pre>
    sh ./RUNME
</pre>
- On MacOS (needs Mac Ports/Homebrew).
- Does not work with anaconda (help wanted as I do not use anaconda):
<pre>
    sh ./RUNME
</pre>
- Docker (experimental, it builds but cannot find a video display):
<pre>
    sh ./RUNME.docker.ubuntu
    sh ./RUNME.docker.fedora
    sh ./RUNME.docker.debian
</pre>
- On Windows (todo)
<!-- - On Windows (todo): (install msys2 first via https://www.msys2.org/) -->
<!-- <pre>                                                                 -->
<!--     sh ./RUNME.windows.mingw64                                        -->
<!-- </pre>                                                                -->

If it doesn't build, just email goblinhack@gmail.com for help

Hardware Specs
--------------
The game should run fine on low end PCs, a half decent graphics card and
likely > 4g of RAM. If graphics is a limitation, you could run it in ascii
mode. I'd be interested in knowing of any low end specs that people get
this PC working on.

Dependancies
------------
OpenGL, SDL2 and Python3 (tested up to 3.11) is needed.

<!-- In days of old, The Zorbashian Empire discovered the Earth and they wrought much rage -->
<!-- upon her verdant soils. Their wrath was mighty and left the world scarred and in darkness. -->
<!--  -->
<!-- Those that remain, scavenge amongst the ruins of once great cities. Religious zealotry -->
<!-- has taken hold and all technology is viewed as demonic magic and forbidden. To be found -->
<!-- with Zorbashian tech is a death sentence. -->
<!--  -->
<!-- The planet is now a hellscape. Lava flows freely from the gushing wounds in the soil -->
<!-- and deserts grow larger every year. The animals have mutated into fearsome beasts and -->
<!-- the only safety is to be found in the undercities. -->
<!--  -->
<!-- Your task, nobel one, is only to survive, for in surviving we continue to resist. -->
<!-- If you are able to strike a blow against the Zorbashian demons then seek out their -->
<!-- many underground bases. It is from here they spawn from their far off realm. But -->
<!-- beware, they have many dread beasts guarding their bases. -->
<!--  -->
<!-- Legend says that there is a master base somewhere, where the Emperor Zorbash resides. -->
<!-- Whether this is true or not, cannot be said but to strike at the heart of their rule -->
<!-- may be enough to drive the Zorbashians out. And then we can be free again. -->
<!--  -->
<!--                       Hark! Hear now a tale untold -->
<!--                       since ancient times of yore -->
<!--                       of Zorbash, forgotten beast of old,  -->
<!--                       who dwelled deep near the Earth’s core -->
<!--                        -->
<!--                       ‘Twas from the Abyss he first arose, -->
<!--                       Forged treasures gold and gleaming.  -->
<!--                       A deadly lure to tempt all those -->
<!--                       Prone to greed and scheming -->
<!--                        -->
<!--                       Many fell before his throne,  -->
<!--                       Heroes fell asunder. -->
<!--                       His lightning gaze turned flesh to bone -->
<!--                       His roar was loud as thunder. -->
<!--                        -->
<!--                       Quenchless, thirsting, dripping gore -->
<!--                       His thousand eyes unmatched -->
<!--                       Until one tenacious band of four -->
<!--                       From him vict’ry snatched.  -->
<!--                        -->
<!--                       Although, ‘twas not an easy fight - -->
<!--                       A sacrifice was made. -->
<!--                       A volunteer, their faithful knight, -->
<!--                       Made sure the price was paid.  -->
<!--                        -->
<!--                       As godlings, the remaining three -->
<!--                       rose with fame and glory -->
<!--                       But that’s not yet the finale -->
<!--                       Of Zorbanadu’s dark story. -->
<!--                        -->
<!--                       For in the depths of Zorbash’s den,  -->
<!--                       A necromancer schemed. -->
<!--                       She planned to raise the beast again, -->
<!--                       And rule as his Dark Queen. -->
<!--                        -->
<!--                       So now Zorbash has come to life -  -->
<!--                       (Though ‘tis more like life’s dark shadow) -->
<!--                       With his fiersome undead wife -->
<!--                       Can you save us all, dear hero?  -->
<!--                        -->
<!--``` -->
<!--                       Secret Verses:                                         -->
<!--                       Twas not an easy fight, it’s true                      -->
<!--                       But not in the way you think.                          -->
<!--                       Our swords cut deep, drew blood_like goo               -->
<!--                       We fought in perfect sync.                             -->
<!--                                                                              -->
<!--                       But as we slashed, great Zorbash did                   -->
<!--                       Let loose an awful cry                                 -->
<!--                       For though blood streamed from each eyelid,            -->
<!--                       He could not seem to die.                              -->
<!--                                                                              -->
<!--                       We fought for days; the beast did roar                 -->
<!--                       And cry all the more miserably                         -->
<!--                       I found myself filled more and more                    -->
<!--                       with a surprising sympathy.                            -->
<!--                                                                              -->
<!--                       In my own house, I had much gold.                      -->
<!--                       A stash I’d saved away.                                -->
<!--                       How would I feel if someone strolled                   -->
<!--                       Into my house one day?                                 -->
<!--                                                                              -->
<!--                       ‘Twas after all, his residence                         -->
<!--                       We’d strolled into so boldly.                          -->
<!--                       He’d every right, after our offense,                   -->
<!--                       To try and kill us slowly                              -->
<!--                                                                              -->
<!--                       I shared my doubts with my dear friends,               -->
<!--                       And received an unhappy surprise                       -->
<!--                       “Betrayal!” they said. “Well, that debate’s at an end. -->
<!--                       You should be the one that dies!”                      -->
<!--                                                                              -->
<!--                       As it turns out, they’d already decided                -->
<!--                       To resort to the darkest extremes.                     -->
<!--                       My weakness, my pity had provided                      -->
<!--                       An excuse for our glorious team.                       -->

Graphics
--------
- Various items and monsters by Oryx, [found here](https://www.oryxdesignlab.com/)
<!-- Oryx: Order Number: #102084 (placed on January 16, 2016 03:14PM EST) -->
- Various items and food by Henry Software, [found here](https://henrysoftware.itch.io)
<!-- purchased on itch.io -->
- Various monsters by DeepDiveGameStudio, [found here](https://deepdivegamestudio.itch.io/)
- Rocks by Pixel Overlord, [found here](https://pixeloverload.itch.io/48x-rock-tile-maps)
<!-- purchased on itch.io -->

Music
-----
- Main music by the amazing Markus Heichelbech (deceased senior technician): [found here](http://nosoapradio.us)
<!-- and https://drive.google.com/drive/folders/0B_fD62tSeGaVRlBaZWJwS29JSnM -->

Sound effects
-------------
- 8 bit sounds by Oryx [found here](https://www.oryxdesignlab.com/)
- Bone by ChrisReierson [found here](https://freesound.org/people/ChrisReierson/)
- Coin drop by Flem0527 [found here](https://freesound.org/people/Flem0527/sounds/630018/)
- Door by danielvj [found here](https://freesound.org/people/danielvj/)
- Door by TiesWijnen [found here](https://freesound.org/people/TiesWijnen/)
- Door souds by Patchytherat [found here](https://freesound.org/people/patchytherat/sounds/530987/)
- Falling sound [found here](https://freesound.org/people/nomiqbomi/sounds/578808/)
- Footstep by Rico Casazza [found here](https://freesound.org/people/Rico_Casazza/)
- Gold coins by Herkules92 [found here](https://freesound.org/people/Herkules92/)
- Grunt squeak by vmgraw [found here](https://freesound.org/people/vmgraw/)
- Impact by Adam N [found here](https://freesound.org/people/egomassive/)
- Impact by Deathscyp [found here](https://freesound.org/people/Deathscyp/)
- Impact by Dersuperanton [found here](https://freesound.org/people/dersuperanton/)
- Impact by RobinHood76 [found here](https://freesound.org/people/Robinhood76/)
- Kraken sound [found here](https://freesound.org/people/cylon8472/)
- Monster death by Michel88 [found here](https://freesound.org/people/Michel88/)
- Monster epic death [found here](https://freesound.org/people/Syna-Max/sounds/56304/)
- Monster sound [found here](https://freesound.org/people/NicknameLarry/)
- Power up by GameAudio [found here](https://freesound.org/people/GameAudio/)
- Pressure plate by Proolsen [found here](https://freesound.org/people/proolsen/sounds/466272/)
- Rat growl by qubodup [found here](https://freesound.org/people/qubodup/)
- Rat hiss by qubodup [found here](https://freesound.org/people/qubodup/)
- Rat squeak by tim.kahn [found here](https://freesound.org/people/tim.kahn/)
- Sheep sounds by n_audioman [found here](https://freesound.org/people/n_audioman/)
- Skill learn by Mrthenoronha [found here](https://freesound.org/people/Mrthenoronha/)
- Slime by Konstati [found here](https://freesound.org/people/konstati/)
- Slime by wubitog [found here](https://freesound.org/people/wubitog/)
- Slime by Zuzek06 [found here](https://freesound.org/people/Zuzek06/)
- Sword by Danjocross [found here](https://freesound.org/people/Danjocross/)
- Sword by XxChr0nosxX [found here](https://freesound.org/people/XxChr0nosxX/)
- Sword sounds by Q.K [found here](https://freesound.org/people/Q.K./)
- Sword sounds by qubodup [found here](https://freesound.org/people/qubodup/sounds/442769/)
- Sword sounds by SlavicMagic [found here](https://freesound.org/people/SlavicMagic/sounds/446015/)
- Water splash by launemax [found here](https://freesound.org/people/launemax/)
- Wood break by Deathscyp [found here](https://freesound.org/people/Deathscyp/)
