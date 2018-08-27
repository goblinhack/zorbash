import zx


def map_data_init():

    #
    # entrance rooms
    #
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx.........xx",
                    "......S......",
                    ".....xxx.....",
                    ".....xxx.....",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx.........xx",
                    "......S....xx",
                    ".....xxx...xx",
                    ".....xxx...xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
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
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    ".............",
                    "..E..........",
                    ".xxx.........",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxx.......xxx",
                    ".............",
                    "......E......",
                    ".....xxx.....",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "............x",
                    "..........E.x",
                    "..........xxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx.......x",
                    "xxxxx....E..x",
                    "xxxxx..xxxx.x",
                    "xxxxx...xxx.x",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx....xxxx",
                    "xxxxx.....xxx",
                    "...........xx",
                    "........E..xx",
                    ".......xxx.xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "...........xx",
                    ".......E...xx",
                    "......xxx..xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx......xx",
                    "xxxxx......xx",
                    "xxxxx...E..xx",
                    "xxxxx..xxx.xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(entrance=True, room_data=[
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
    zx.map_load_room(lock=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    ".............",
                    ".....xxx.....",
                    ".............",
                    "xLLLx...xLLLx",
                    "xLLLx...xLLLx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(lock=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    ".............",
                    ".............",
                    ".............",
                    "xLLLLLLLLLLLx",
                    "xLLLLLLLLLLLx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(lock=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxx..xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xLLLx..xxxxxx",
                    "xLLLx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(lock=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxxx..xxxxx",
                    "xx......xxxxx",
                    "xx......xxxxx",
                    "xxLLLLxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xx......xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(lock=True, room_data=[
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
    zx.map_load_room(key=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "x..........xx",
                    "....k........",
                    "...xxx.......",
                    ".............",
                    "xxx........xx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(key=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "x...........x",
                    "........k....",
                    ".......xxx...",
                    ".............",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(key=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxx.....xx",
                    ".........k.xx",
                    "........xx.xx",
                    "...........xx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(key=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xx......xxxxx",
                    "xx.........xx",
                    "xx..k......xx",
                    "xxxxx......xx",
                    "xxxxx..xxxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(key=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx......xx",
                    "xxxxx....k.xx",
                    "........xx.xx",
                    "...........xx",
                    "...........xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(key=True, room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxx.......xx",
                    "xxx....k...xx",
                    "......xxx..xx",
                    "..........xxx",
                    "...........xx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(key=True, room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xx........xxx",
                    "xxk.......xxx",
                    "xxx....x..xxx",
                    "xx....x...xxx",
                    "xx........xxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(key=True, room_data=[
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
    zx.map_load_room(room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    ".............",
                    ".............",
                    ".............",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    ".............",
                    ".............",
                    ".............",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx" ])
    zx.map_load_room(room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(room_data=[
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "........xxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(room_data=[
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxx...xxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx",
                    "xxxxxxxxxxxxx" ])
    zx.map_load_room(room_data=[
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
