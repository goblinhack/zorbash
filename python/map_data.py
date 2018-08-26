import zx


def map_data_init():

    #
    # entrance rooms
    #
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx.........xx",
                    "......S......",
                    ".....xxx.....",
                    ".....xxx.....",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx.........xx",
                    "......S....xx",
                    ".....xxx...xx",
                    ".....xxx...xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx........xxx",
                    "x..S.......xx",
                    "xxxxx......xx",
                    "xxxxx......xx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])


    #
    # exit rooms
    #
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    ".............",
                    "..E..........",
                    ".xxx.........",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxx.......xxx",
                    ".............",
                    "......E......",
                    ".....xxx.....",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "............x",
                    "..........E.x",
                    "..........xxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx.......x",
                    "xxxxx....E..x",
                    "xxxxx..xxxx.x",
                    "xxxxx...xxx.x",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx....xxxx",
                    "xxxxx.....xxx",
                    "...........xx",
                    "........E..xx",
                    ".......xxx.xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "...........xx",
                    ".......E...xx",
                    "......xxx..xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx......xx",
                    "xxxxx......xx",
                    "xxxxx...E..xx",
                    "xxxxx..xxx.xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_entrance=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxx.......x",
                    "xxxxx....E..x",
                    "xxxxx...xxx.x",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])

    #
    # lock rooms
    #
    zx.map_load_room(is_lock=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    ".............",
                    ".....xxx.....",
                    ".............",
                    "xLLLx...xLLLx",
                    "xLLLx...xLLLx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_lock=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    ".............",
                    ".............",
                    ".............",
                    "xLLLLLLLLLLLx",
                    "xLLLLLLLLLLLx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_lock=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxx..xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xLLLx..xxxxxx",
                    "xLLLx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_lock=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxxx..xxxxx",
                    "xx......xxxxx",
                    "xx......xxxxx",
                    "xxLLLLxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx......xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_lock=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxx..xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xLLLxLLxxxxxx",
                    "xLLLxLLxxxxxx",
                    "xxxxxxxxxxxxx" ])

    #
    # key rooms
    #
    zx.map_load_room(is_key=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "x..........xx",
                    "....k........",
                    "...xxx.......",
                    ".............",
                    "xxx........xx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "x...........x",
                    "........k....",
                    ".......xxx...",
                    ".............",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxx.....xx",
                    ".........k.xx",
                    "........xx.xx",
                    "...........xx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xx......xxxxx",
                    "xx.........xx",
                    "xx..k......xx",
                    "xxxxx......xx",
                    "xxxxx..xxxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx......xx",
                    "xxxxx....k.xx",
                    "........xx.xx",
                    "...........xx",
                    "...........xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxx.......xx",
                    "xxx....k...xx",
                    "......xxx..xx",
                    "..........xxx",
                    "...........xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xx........xxx",
                    "xxk.......xxx",
                    "xxx....x..xxx",
                    "xx....x...xxx",
                    "xx........xxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(is_key=True, combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx.........xx",
                    "xx.........xx",
                    "xx.......k.xx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])

    #
    # normal rooms
    #
    zx.map_load_room(combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    ".............",
                    ".............",
                    ".............",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    ".............",
                    ".............",
                    ".............",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(combo=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
map_data_init()
