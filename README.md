Zorbash
-------

Welcome to the lair of the dread beholder, Zorbash. 
Liberate the Orb of Zorb and defeat Zorbash to win.

(Well you will once the game is finished! :)

This is work in progress. It's sort of playable right now but probably way too tough.
Comments and suggestions welcome at this early stage.

Graphics
--------
- Various items and monsters by Oryx, [found here](https://www.oryxdesignlab.com/)
<!-- Oryx: Order Number: #102084 (placed on January 16, 2016 03:14PM EST) -->

Music
-----
- Main music by the amazing Markus Heichelbech (deceased senior technician): [found here](http://nosoapradio.us)
<!-- and https://drive.google.com/drive/folders/0B_fD62tSeGaVRlBaZWJwS29JSnM -->

Sound effects
-------------
- 8 bit sounds by Oryx, [found here](https://www.oryxdesignlab.com/)
- Door sounds by TiesWijnen, [found here](https://freesound.org/people/TiesWijnen/)
- Door sounds by danielvj, [found here](https://freesound.org/people/danielvj/)
- Impact sounds by Adam N, [found here](https://freesound.org/people/egomassive/)
- Impact sounds by Deathscyp, [found here](https://freesound.org/people/Deathscyp/)
- Impact sounds by Dersuperanton, [found here](https://freesound.org/people/dersuperanton/)
- Impact sounds by RobinHood76, [found here](https://freesound.org/people/Robinhood76/)
- Key sounds by uEffects, [found here](https://freesound.org/people/uEffects/)
- Slime sounds by Konstati, [found here](https://freesound.org/people/konstati/)
- Sword sounds by Danjocross, [found here](https://freesound.org/people/Danjocross/)
- Sword sounds by XxChr0nosxX, [found here](https://freesound.org/people/XxChr0nosxX/)
- Sword sounds by qubodup, [found here](https://freesound.org/people/qubodup/)
- Wood break sounds by Deathscyp, [found here](https://freesound.org/people/Deathscyp/)
- Footstep sounds by Rico Casazza, [found here](https://freesound.org/people/Rico_Casazza/)

Screenshots
-----------
![Alt text](pics/screenshot.1.png?raw=true "")
![Alt text](pics/screenshot.2.png?raw=true "")
![Alt text](pics/screenshot.3.png?raw=true "")
![Alt text](pics/screenshot.4.png?raw=true "")
![Alt text](pics/screenshot.5.png?raw=true "")
![Alt text](pics/screenshot.6.png?raw=true "")
![Alt text](pics/screenshot.7.png?raw=true "")
![Alt text](pics/screenshot.8.png?raw=true "")
![Alt text](pics/screenshot.9.png?raw=true "")
![Alt text](pics/screenshot.10.png?raw=true "")
![Alt text](pics/screenshot.11.png?raw=true "")
![Alt text](pics/screenshot.12.png?raw=true "")
![Alt text](pics/screenshot.13.png?raw=true "")
![Alt text](pics/screenshot.14.png?raw=true "")
![Alt text](pics/screenshot.15.png?raw=true "")

Older Screenshots
-----------------
![Alt text](pics/old/screenshot.1.png?raw=true "")
![Alt text](pics/old/screenshot.2.png?raw=true "")
![Alt text](pics/old/screenshot.3.png?raw=true "")
![Alt text](pics/old/screenshot.4.png?raw=true "")
![Alt text](pics/old/screenshot.5.png?raw=true "")
![Alt text](pics/old/screenshot.6.png?raw=true "")
![Alt text](pics/old/screenshot.7.png?raw=true "")
![Alt text](pics/old/screenshot.8.png?raw=true "")
![Alt text](pics/old/screenshot.9.png?raw=true "")
![Alt text](pics/old/screenshot.10.png?raw=true "")
![Alt text](pics/old/screenshot.11.png?raw=true "")
![Alt text](pics/old/screenshot.12.png?raw=true "")
![Alt text](pics/old/screenshot.13.png?raw=true "")
![Alt text](pics/old/screenshot.14.png?raw=true "")
![Alt text](pics/old/screenshot.15.png?raw=true "")

How to build
------------

- On Linux: (last tried ubuntu 19.04 on Sat Feb 13 15:12:42 GMT 2021)
<pre>
    sh ./RUNME
</pre>
- Ubuntu docker (experimental):
<pre>
    sh ./RUNME.docker.ubuntu
</pre>
- On MacOS:
<pre>
    sh ./RUNME
</pre>
- On Windows: (install msys2 first via https://www.msys2.org/)
<pre>
    sh ./RUNME.windows.mingw64
</pre>

If it doesn't build, just email goblinhack@gmail.com for help

Dependancies
------------
SDL2 and Python3 is needed.
- Ubuntu
<pre>
    sudo apt-get install xutils-dev
    sudo apt-get install libsdl2-dev
    sudo apt-get install libsdl2-mixer-dev
    sudo apt-get install libsdl2-ttf-dev
    sudo apt-get install python3-dev
    sudo apt-get install python3-pip
</pre>
- MacOS (install Mac Ports first [found here](https://www.macports.org/))
<pre>
    sudo port install makedepend
    sudo port install libsdl2
    sudo port install libsdl2_mixer
    sudo port install libsdl2_ttf
    sudo port install python3*
</pre>
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
<!--                       Our swords cut deep, drew blood-like goo               -->
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

