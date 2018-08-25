import zx


def map_data_init():

    #
    # entrance rooms
    #
    zx.map_load_room(entrance=True, left=True, combo=[
                    "xDxxxxxxxxx",
                    "x.........x",
                    "x....SS...x",
                    "D...SSSS..x",
                    "x....SS...D",
                    "x.........x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(entrance=True, left=True, combo=[
                    "xDxxxxxxxxx",
                    "x.....S...x",
                    "x....SS...x",
                    "D...SSSSS.x",
                    "x....SS...D",
                    "x.....S...x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(entrance=True, up=True, combo=[
                    "xDxxxxxxxxx",
                    "x....S....x",
                    "x...SSS...x",
                    "x..SSSSS..x",
                    "D....S....x",
                    "x....S....D",
                    "xxDxxxxxxxx" ])
    zx.map_load_room(entrance=True, down=True, combo=[
                    "xDxxxxxxxxx",
                    "x....S....x",
                    "D....S....x",
                    "x..SSSSS..D",
                    "x...SSS...x",
                    "x....S....x",
                    "xxDxxxxxxxx" ])


    #
    # exit rooms
    #
    zx.map_load_room(exit=True, combo=[
                    "xDxxxxxxxxx",
                    "x.........x",
                    "D...E.E...x",
                    "x....E....D",
                    "x...E.E...x",
                    "x.........x",
                    "xxDxxxxxxxx" ])

    #
    # lock rooms
    #
    zx.map_load_room(lock=True, left=True, combo=[
                    "xDxxxxxxxxx",
                    "x.........x",
                    "x....LL...x",
                    "D...LLLL..x",
                    "x....LL...D",
                    "x.........x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(lock=True, left=True, combo=[
                    "xDxxxxxxxxx",
                    "x.....L...x",
                    "x....LL...x",
                    "D...LLLLL.x",
                    "x....LL...D",
                    "x.....L...x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(lock=True, up=True, combo=[
                    "xDxxxxxxxxx",
                    "x....L....x",
                    "x...LLL...x",
                    "x..LLLLL..x",
                    "D....L....x",
                    "x....L....D",
                    "xxDxxxxxxxx" ])
    zx.map_load_room(lock=True, down=True, combo=[
                    "xDxxxxxxxxx",
                    "x....L....x",
                    "D....L....x",
                    "x..LLLLL..D",
                    "x...LLL...x",
                    "x....L....x",
                    "xxDxxxxxxxx" ])

    #
    # key rooms
    #
    zx.map_load_room(key=True, left=True, combo=[
                    "xDxxxxxxxxx",
                    "x.........x",
                    "x...kkk...x",
                    "D...kkk...x",
                    "x...kkk...D",
                    "x.........x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(key=True, left=True, combo=[
                    "xDxxxxxxxxx",
                    "x.....k...x",
                    "x....kk...x",
                    "D...kkkkk.x",
                    "x....kk...D",
                    "x.....k...x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(key=True, up=True, combo=[
                    "xDxxxxxxxxx",
                    "x....k....x",
                    "x...kkk...x",
                    "x..kkkkk..x",
                    "D....k....x",
                    "x....k....D",
                    "xxDxxxxxxxx" ])
    zx.map_load_room(key=True, down=True, combo=[
                    "xDxxxxxxxxx",
                    "x....k....x",
                    "D....k....x",
                    "x..kkkkk..D",
                    "x...kkk...x",
                    "x....k....x",
                    "xxDxxxxxxxx" ])

    #
    # normal rooms
    #
    zx.map_load_room(left=True, combo=[
                    "xDxxxxxxxxx",
                    "x...i.i...x",
                    "x..i...i..x",
                    "D.iiiiiii.x",
                    "x..i...i..D",
                    "x...i.i...x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(left=True, combo=[
                    "xDxxxxxxxxx",
                    "x...i.....x",
                    "x..i......x",
                    "D.iiiiiii.x",
                    "x..i......D",
                    "x...i.....x",
                    "xxxDxxxxxxx" ])
    zx.map_load_room(up=True, combo=[
                    "xDxxxxxxxxx",
                    "x....i....x",
                    "x...iii...x",
                    "x..i.i.i..x",
                    "D....i....x",
                    "x....i....D",
                    "xxDxxxxxxxx" ])
    zx.map_load_room(down=True, combo=[
                    "xDxxxxxxxxx",
                    "x....i....x",
                    "D....i....x",
                    "x..i.i.i..D",
                    "x...iii...x",
                    "x....i....x",
                    "xxDxxxxxxxx" ])
    zx.map_load_room(left=True, combo=[
                    "xDxxxxxxxxxxx",
                    "x...........x",
                    "x...i...i...x",
                    "x..i.....i..x",
                    "D.iiiiiiiii.x",
                    "x..i.....i..D",
                    "x...i...i...x",
                    "x...........x",
                    "xxxDxxxxxxxxx" ])
    zx.map_load_room(left=True, combo=[
                    "xDxxxxxxxxxxx",
                    "x...........x",
                    "x...i.......x",
                    "x..i........x",
                    "D.iiiiiiiii.x",
                    "x..i........D",
                    "x...i.......x",
                    "x...........x",
                    "xxxDxxxxxxxxx" ])
    zx.map_load_room(up=True, combo=[
                    "xDxxxxxxxxxxx",
                    "x.....i.....x",
                    "x....iii....x",
                    "x...i.i.i...x",
                    "D.....i.....x",
                    "x.....i.....D",
                    "x.....i.....x",
                    "x.....i.....x",
                    "xxxDxxxxxxxxx" ])
    zx.map_load_room(down=True, combo=[
                    "xDxxxxxxxxxxx",
                    "x.....i.....x",
                    "x.....i.....x",
                    "x.....i.....x",
                    "D.....i.....x",
                    "x...i.i.i...D",
                    "x....iii....x",
                    "x.....i.....x",
                    "xxxDxxxxxxxxx" ])
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
