import zx

#
# entrance rooms
#
zx.map_load_room(entrance=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....S..xx",
"xx.....xx",
"xx.....xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(entrance=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....S....",
"xx.....xx",
"xx.....xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(entrance=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....S..xx",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(entrance=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....S....",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(entrance=True, room_data=[
"xxxx.xxxx",
"xxxx.xxxx",
"xx.....xx",
"xx.....xx",
"....S....",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])

#
# exit rooms
#
zx.map_load_room(exit=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....E..xx",
"xx.....xx",
"xx.....xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(exit=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....E....",
"xx.....xx",
"xx.....xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(exit=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....E..xx",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(exit=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....E....",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(exit=True, room_data=[
"xxxx.xxxx",
"xxxx.xxxx",
"xx.....xx",
"xx.....xx",
"....E....",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])

#
# directional combined with exit rooms
#
zx.map_load_room(exit=True, depth=1, left=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x...x...x",
"x..xx...x",
"x.xxxxx..",
"x..xx...x",
"x...x...x",
"xE......x",
"xxxxxxxxx"])

#
# directional rooms
#
zx.map_load_room(left=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x...x...x",
"x..xx...x",
"x.xxxxx..",
"x..xx...x",
"x...x...x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(left=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x...x...x",
"x..xx...x",
"..xxxxx..",
"x..xx...x",
"x...x...x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(left=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x...x...x",
"x..xx...x",
"x.xxxxx..",
"x..xx...x",
"x...x...x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(left=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x...x...x",
"x..xx...x",
"..xxxxx..",
"x..xx...x",
"x...x...x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(left=True, room_data=[
"xxxx.xxxx",
"x.......x",
"x...x...x",
"x..xx...x",
"..xxxxx..",
"x..xx...x",
"x...x...x",
"x.......x",
"xxxx.xxxx"])

#
# lock rooms
#
zx.map_load_room(lock=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.LLL.xx",
"xx.LLL.xx",
"...LLL...",
"xx.LLL.xx",
"xx.LLL.xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(lock=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx...LLxx",
"xx.LLLLxx",
"...LLL.xx",
"xxLLLL.xx",
"xxLL...xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(lock=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xxLLLLLxx",
"xxLLLLLxx",
"..LLLLL..",
"xxLLLLLxx",
"xxLLLLLxx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(lock=True, room_data=[
"xxxx.xxxx",
"xxxx.xxxx",
"xxLLLLLxx",
"xxLLLLLxx",
"..LLLLL..",
"xxLLLLLxx",
"xxLLLLLxx",
"xxxx.xxxx",
"xxxx.xxxx"])

#
# key rooms
#
zx.map_load_room(key=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....k..xx",
"xx.....xx",
"xx.....xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(key=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....k....",
"xx.....xx",
"xx.....xx",
"xxxxxxxxx",
"xxxxxxxxx"])
zx.map_load_room(key=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....k..xx",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(key=True, room_data=[
"xxxxxxxxx",
"xxxxxxxxx",
"xx.....xx",
"xx.....xx",
"....k....",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])
zx.map_load_room(key=True, room_data=[
"xxxx.xxxx",
"xxxx.xxxx",
"xx.....xx",
"xx.....xx",
"....k....",
"xx.....xx",
"xx.....xx",
"xxxx.xxxx",
"xxxx.xxxx"])

#
# depth 1 rooms
#
zx.map_load_room(depth=1, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xx...x",
"x...x...x",
"....x...x",
"x...x...x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xx...x",
"x...x...x",
"....x....",
"x...x...x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xx...x",
"x...x...x",
"....x...x",
"x...x...x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xx...x",
"x...x...x",
"....x....",
"x...x...x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxx.xxxx",
"x.......x",
"x..xx...x",
"x...x...x",
"....x....",
"x...x...x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])

#
# depth 2 rooms
#
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx..x",
"x..x....x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx...",
"x..x....x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx..x",
"x..x....x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx...",
"x..x....x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=2, room_data=[
"xxxx.xxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx...",
"x..x....x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])

#
# depth 3 rooms
#
zx.map_load_room(depth=3, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx..x",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=3, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx...",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=3, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx..x",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=3, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx...",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=3, room_data=[
"xxxx.xxxx",
"x.......x",
"x..xxx..x",
"x....x..x",
"...xxx...",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])

#
# depth 4 rooms
#
zx.map_load_room(depth=4, room_data=[
"xxxxxxxxx",
"x.......x",
"x..x.x..x",
"x..x.x..x",
"...xxx..x",
"x....x..x",
"x....x..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=4, room_data=[
"xxxxxxxxx",
"x.......x",
"x..x.x..x",
"x..x.x..x",
"...xxx...",
"x....x..x",
"x....x..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=4, room_data=[
"xxxxxxxxx",
"x.......x",
"x..x.x..x",
"x..x.x..x",
"...xxx..x",
"x....x..x",
"x....x..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=4, room_data=[
"xxxxxxxxx",
"x.......x",
"x..x.x..x",
"x..x.x..x",
"...xxx...",
"x....x..x",
"x....x..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=4, room_data=[
"xxxx.xxxx",
"x.......x",
"x..x.x..x",
"x..x.x..x",
"...xxx...",
"x....x..x",
"x....x..x",
"x.......x",
"xxxx.xxxx"])

#
# depth 5 rooms
#
zx.map_load_room(depth=5, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x..x....x",
"...xxx..x",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=5, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x..x....x",
"...xxx...",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(depth=5, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x..x....x",
"...xxx..x",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=5, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x..x....x",
"...xxx...",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(depth=5, room_data=[
"xxxx.xxxx",
"x.......x",
"x..xxx..x",
"x..x....x",
"...xxx...",
"x....x..x",
"x..xxx..x",
"x.......x",
"xxxx.xxxx"])

#
# secret rooms
#
zx.map_load_room(secret=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x.x..x..x",
"....xx..x",
"x...x...x",
"x...x...x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(secret=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x.x..x..x",
"....xx...",
"x...x...x",
"x...x...x",
"x.......x",
"xxxxxxxxx"])
zx.map_load_room(secret=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x.x..x..x",
"....xx..x",
"x...x...x",
"x...x...x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(secret=True, room_data=[
"xxxxxxxxx",
"x.......x",
"x..xxx..x",
"x.x..x..x",
"....xx...",
"x...x...x",
"x...x...x",
"x.......x",
"xxxx.xxxx"])
zx.map_load_room(secret=True, room_data=[
"xxxx.xxxx",
"x.......x",
"x..xxx..x",
"x.x..x..x",
"....xx...",
"x...x...x",
"x...x...x",
"x.......x",
"xxxx.xxxx"])
