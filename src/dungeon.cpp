

class Dungeon {
public:
    Dugeon (rooms,
            rooms_on_level=20,
            fixed_room_chance=10):

        self.width = mm.MAP_WIDTH
        self.height = mm.MAP_HEIGHT
        self.charmap = charmap

        #
        # Set if we fail to generate
        #
        self.generate_failed = False

        #
        # All possible rooms we will choose from. Initially these are fixed
        # rooms and we add more random ones onto this list.
        #
        self.rooms = rooms

        #
        # First range of rooms are fixed; rest randomly generated
        #
        self.fixed_room_count = len(self.rooms)

        #
        # How many rooms on the level.
        #
        self.rooms_on_level = 0

        #
        # Chance of a corridor splitting
        #
        self.corridor_fork_chance = 35
        self.tunnel_fork_chance = 95

        #
        # Lower, longer corridors
        #
        self.corridor_grow_chance = 2
        self.tunnel_grow_chance = 1

        #
        # How often a random room is locked
        #
        self.room_locked_chance = 5

        #
        # How close corridors should be to each other
        #
        self.corridor_spacing = 3

        #
        # What chance for fixed versus random rooms
        #
        self.fixed_room_chance = fixed_room_chance

        #
        # For random shape rooms, how large?
        #
        self.min_room_size = 10

        #
        # Depth is how many rooms from the start room we are
        #
        self.roomno_depth = {}

        #
        # Rooms that have all doors locked
        #
        self.roomno_locked = {}

        #
        # Exits from each room
        #
        self.room_exits = {}

        #
        # The tiles of a each romm
        #
        self.room_occupiable_tiles = {}

        #
        # z Depths of the level
        #
        self.depth_map = None

        #
        # The map
        #
        self.cells = [[[' ' for d in range(charmap.depth.max)]
                       for i in range(self.height)]
                      for j in range(self.width)]
        self.roomno_cells = [[-1 for i in range(self.height)]
                             for j in range(self.width)]

        #
        # Create all randomly shaped rooms.
        #
        for count in range(0, 2):
            self.rooms_all_create_random_shapes()

        #
        # Total of fixed and random room
        #
        self.fixed_roomno_list = list(range(0, self.fixed_room_count))
        random.shuffle(self.fixed_roomno_list)

        self.random_roomno_list = list(range(self.fixed_room_count,
                                             len(self.rooms)))
        random.shuffle(self.random_roomno_list)

        #
        # First room goes in the center. The rest hang off of its
        # corridors.
        #
        if not self.rooms_place_all(rooms_on_level):
            self.generate_failed = True
            return

        self.debug("^^^ placed all rooms ^^^")

        #
        # Remove dangling corridors that go nowhere.
        #
        self.rooms_trim_corridors()
        self.debug("^^^ trimmed all corridors ^^^")

        #
        # Remove corridors that go nowhere.
        #
        self.rooms_trim_looped_corridors()
        self.debug("^^^ trimmed all looped corridors ^^^")

        #
        # How far from the start is each room?
        #
        self.rooms_set_depth()
        self.debug("^^^ calculated depth ^^^")

#        self.rooms_dump_info()

        #
        # Randomly lock some rooms
        #
        self.rooms_randomly_lock()
        self.debug("^^^ locked some rooms ^^^")

        #
        # Redo the depth. Rooms that are locked add extra depth points.
        #
        self.rooms_set_depth()
        self.debug("^^^ calculated depth ^^^")

        #
        # Plug gaps in the wall that go nowhere.
        #
        self.rooms_plug_walls()
        self.debug("^^^ plugged all walls ^^^")

        #
        # Any dead end doors with no corridor, zap em
        #
        self.rooms_plug_doors()
        self.debug("^^^ removed dead end doors ^^^")

        #
        # Find where we can place stuff like exits
        #
        self.rooms_find_occupiable_tiles()

        #
        # Place start and exit of the dungeon
        #
        if not self.rooms_place_start():
            self.generate_failed = True
            return
        self.debug("^^^ placed start ^^^")

        if not self.rooms_place_exit():
            self.generate_failed = True
            return
        self.debug("^^^ placed exit ^^^")

        if not self.rooms_place_keys():
            self.generate_failed = True
            return
        self.debug("^^^ placed keys ^^^")

        #
        # Create a random depth map for the level
        #
        self.add_depth_map()
        self.debug("^^^ placed depth map ^^^")

        for i in range(random.randint(0, 2)):
            self.add_chasm()

        #
        # Water or lava levels?
        #
        if random.randint(0, 100) < 100:
            for i in range(random.randint(0, 3)):
                self.add_lava()

            for i in range(random.randint(0, 100)):
                self.add_water()

        if random.randint(0, 100) < 2:
            for i in range(random.randint(0, 3)):
                self.add_water()

            for i in range(random.randint(0, 100)):
                self.add_lava()

        self.debug("^^^ placed hazards ^^^")

        #
        # Water next to a chasm or lava? remove it
        #
        self.remove_chasm_next_to_water()
        self.remove_lava_next_to_water()

        #
        # Let lava melt through walls
        #
        self.dissolve_room_walls()
        self.debug("^^^ dissolved walls ^^^")

        self.dissolve_room_cwalls()
        self.debug("^^^ dissolved cwalls ^^^")

        #
        # Bridges rise and fall
        #
        self.rooms_corridor_bridge_height()
        self.debug("^^^ calculated bridge height ^^^")

        #
        # Add walls around corridors?
        #
        self.add_cwall()
        self.debug("^^^ add corridor walls ^^^")

        #
        # Add random bridges in the darkness
        #
        self.add_chasm_bridges()
        self.add_lava_bridges()
        self.add_water_bridges()
        self.debug("^^^ add chasm bridges ^^^")

        #
        # Bridges rise and fall
        #
        self.rooms_corridor_bridge_height()
        self.debug("^^^ calculated bridge height ^^^")
        self.rooms_corridor_bridge_smooth()

        self.add_rock()
        self.debug("^^^ add rock ^^^")

        self.add_tunnels()
        self.debug("^^^ add tunnels ^^^")

        self.add_treasure()
        self.debug("^^^ add treasure ^^^")

    def debug(self, s):
        return
        self.dump()
        mm.log(s)

    #
    # Check for room overlaps
    #
    def room_can_be_placed(self, roomno, x, y):
        room = self.rooms[roomno]

        if x < 2:
            return False
        elif x + room.width >= self.width - 2:
            return False

        if y < 2:
            return False
        elif y + room.height >= self.height - 2:
            return False

        vert_floor_slice = room.vert_slice["floor"]

        for ry in range(room.height):
            for rx in range(room.width):
                if vert_floor_slice[rx][ry] == charmap.FLOOR:
                    if self.is_any_floor_at(x + rx, y + ry):
                        return False
        return True

    #
    # Dump a room onto the level. No checks
    #
    def room_place(self, roomno, x, y):
        room = self.rooms[roomno]

        self.roomno_locked[roomno] = False

        for d in range(charmap.depth.max):
            dname = charmap.depth.to_name[d]
            if dname in room.vert_slice:
                rvert_slice = room.vert_slice[dname]
                for ry in range(room.height):
                    for rx in range(room.width):
                        rchar = rvert_slice[rx][ry]
                        tx = x + rx
                        ty = y + ry
                        if rchar != charmap.SPACE:
                            self.putc(tx, ty, d, rchar)
                            self.putr(tx, ty, roomno)
                        if rchar == charmap.DOOR:
                            self.roomno_locked[roomno] = True

        self.rooms_on_level += 1

        #
        # Keep track of what rooms we've added. We'll work out what joins
        # onto what later.
        #
        self.room_connection[roomno] = set()
        self.roomnos.add(roomno)

    #
    # Try to push a room on the level
    #
    def room_place_if_no_overlaps(self, roomno, x, y):
        if not self.room_can_be_placed(roomno, x, y):
            return False

        self.room_place(roomno, x, y)
        return True

    #
    # Grow a corridor in the given direction
    #
    def room_corridor_draw(self, x, y, dx, dy, clen=0, fork_count=0,
                           c=charmap.CORRIDOR):
        x += dx
        y += dy

        if x < 2:
            return
        elif x >= self.width - 3:
            return

        if y < 2:
            return
        elif y >= self.height - 3:
            return

        if self.getc(x, y, charmap.depth.floor) is None:
            return

        if self.is_any_floor_at(x, y):
            return

        clen += 1

        self.putc(x, y, charmap.depth.floor, c)

        #
        # Reached the end of a corridor?
        #
        if random.randint(1, 100) < clen * self.corridor_grow_chance:
            self.corridor_ends.append((x, y))
            return

        #
        # Stopped growing. Fork the corridor.
        # Don't do corridors forks adjacent to each other.
        #
        if fork_count < 3 and clen % 2 == 0:
            if random.randint(1, 100) < self.corridor_fork_chance:
                self.room_corridor_draw(x, y, dy, dx, clen, fork_count + 1,
                                        c=c)

            if random.randint(1, 100) < self.corridor_fork_chance:
                self.room_corridor_draw(x, y, -dy, -dx, clen,
                                        fork_count + 1, c=c)

        #
        # Keep on growing
        #
        self.room_corridor_draw(x, y, dx, dy, clen, fork_count + 1, c=c)

    #
    # Grow a tunnel in the given direction
    #
    def room_tunnel_draw(self, x, y, dx, dy, clen=0, fork_count=0,
                         c=charmap.DUSTY):
        x += dx
        y += dy

        if x < 2:
            return
        elif x >= self.width - 3:
            return

        if y < 2:
            return
        elif y >= self.height - 3:
            return

        if not self.is_rock_at(x, y):

            if random.randint(1, 100) < 20:
                for dx, dy in biome.ALL_DELTAS:
                    tx = x + dx
                    ty = y + dy

                    if not self.is_wall_at(tx, ty) and \
                       not self.is_cwall_at(tx, ty) and \
                       not self.is_corridor_at(tx, ty) and \
                       not self.is_dusty_at(tx, ty):
                        self.putc(tx, ty, charmap.depth.wall, charmap.SPACE)
                        self.putc(tx, ty, charmap.depth.floor, charmap.FLOOR)
            return

        clen += 1

        self.putc(x, y, charmap.depth.wall, charmap.SPACE)
        self.putc(x, y, charmap.depth.floor, c)

        #
        # Reached the end of a corridor?
        #
        if random.randint(1, 100) < clen * self.corridor_grow_chance:
            return

        #
        # Stopped growing. Fork the corridor.
        # Don't do tunnels forks adjacent to each other.
        #
        if fork_count < 3 and clen % 2 == 0:
            if random.randint(1, 100) < self.tunnel_fork_chance:
                self.room_tunnel_draw(x, y, dy, dx, clen, fork_count + 1, c)

            if random.randint(1, 100) < self.tunnel_fork_chance:
                self.room_tunnel_draw(x, y, -dy, -dx, clen, fork_count + 1, c)

        #
        # Keep on growing
        #
        self.room_tunnel_draw(x, y, dx, dy, clen, fork_count + 1, c)

    #
    # Search the whole level for possible room exits
    #
    def rooms_find_all_exits(self):
        self.inuse = [[0 for i in range(self.height)]
                      for j in range(self.width)]
        cand = [[0 for i in range(self.height)]
                for j in range(self.width)]

        #
        # First pass find all the places we could place a corridor
        #
        border = self.corridor_spacing
        for y in range(border + 1, self.height - (border + 1)):
            for x in range(border + 1, self.width - (border + 1)):

                if not self.is_floor_at_fast(x, y):
                    continue

                if self.is_wall_at(x, y):
                    self.inuse[x][y] = 1
                    continue

                if self.is_corridor_at(x, y):
                    self.inuse[x][y] = 1
                    continue

                if not self.is_any_floor_at(x + 1, y):
                    cand[x][y] = 1
                elif not self.is_any_floor_at(x - 1, y):
                    cand[x][y] = 1
                elif not self.is_any_floor_at(x, y - 1):
                    cand[x][y] = 1
                elif not self.is_any_floor_at(x, y + 1):
                    cand[x][y] = 1

        possible_new_corridors = []

        #
        # Next pass filter all places we could start that are too near
        # to other corridors that already exist, or are candidates to
        # create.
        #
        for y in range(border + 1, self.height - (border + 1)):
            for x in range(border + 1, self.width - (border + 1)):

                if not cand[x][y]:
                    continue

                c = - self.corridor_spacing
                d = self.corridor_spacing + 1

                #
                # Check no corridor adjacent to any other one nearby. Or
                # any new one we plan.
                #
                skip = False
                for dx in range(c, d):
                    for dy in range(c, d):
                        if dx == 0 and dy == 0:
                            continue

                        if cand[x + dx][y + dy]:
                            self.inuse[x + dx][y + dy] = 1
                            skip = True
                            break

                        if self.is_corridor_at(x + dx, y + dy):
                            self.inuse[x + dx][y + dy] = 1
                            skip = True
                            break
                    if skip:
                        break
                if skip:
                    continue

                possible_new_corridors.append((x, y))

        #
        # Return the final list of corridor starts
        #
        return possible_new_corridors

    #
    # For each room exit (and we search the whole room) grow corridors
    #
    def rooms_all_grow_new_corridors(self):

        possible_new_corridors = self.rooms_find_all_exits()

        #
        # For each possible direction of a corridor, sprout one.
        #
        for coord in possible_new_corridors:
            x, y = coord

            # a b c
            # d * f
            # g h i
            b = self.inuse[x][y-1]
            d = self.inuse[x-1][y]
            f = self.inuse[x+1][y]
            h = self.inuse[x][y+1]

            if not b:
                self.room_corridor_draw(x, y, 0, - 1, c=charmap.CORRIDOR)
            if not d:
                self.room_corridor_draw(x, y, -1, 0, c=charmap.CORRIDOR)
            if not f:
                self.room_corridor_draw(x, y, 1, 0, c=charmap.CORRIDOR)
            if not h:
                self.room_corridor_draw(x, y, 0, 1, c=charmap.CORRIDOR)

    #
    # From a fixed list of random roomnos, return the next one. This
    # ensures no room will ever appear more than once.
    #
    def rooms_get_next_roomno(self):
        while True:
            if random.randint(0, 100) <= self.fixed_room_chance:
                roomno = self.fixed_roomno_list.pop(0)
                self.fixed_roomno_list.append(roomno)
            else:
                roomno = self.random_roomno_list.pop(0)
                self.random_roomno_list.append(roomno)

            #
            # Make sure we never place the same room twice.
            #
            if roomno not in self.roomnos:
                return roomno

        return roomno

    #
    # Search for corridor end points and try to dump rooms there.
    #
    def rooms_all_try_to_place_at_end_of_corridors(self):

        roomno = self.rooms_get_next_roomno()
        room = self.rooms[roomno]
        placed_a_room = False

        #
        # For all corridor end points.
        #
        for coord in self.corridor_ends:
            cx, cy = coord

            #
            # Try to attach room only by it's edges. This is a bit quicker
            # than searching the room for exits.
            #
            for edge in room.edge_exits:
                rx, ry = edge

                x = cx - rx
                y = cy - ry

                if self.room_place_if_no_overlaps(roomno, x - 1, y):
                    placed_a_room = True
                elif self.room_place_if_no_overlaps(roomno, x + 1, y):
                    placed_a_room = True
                elif self.room_place_if_no_overlaps(roomno, x, y - 1):
                    placed_a_room = True
                elif self.room_place_if_no_overlaps(roomno, x, y + 1):
                    placed_a_room = True

                if placed_a_room:
                    break

            if placed_a_room:
                break

        #
        # Placed at least one?
        #
        return placed_a_room

    #
    # Place the first room in a level, in the center ish. First room should
    # not be a fixed room.
    #
    def room_place_first(self):
        self.room_connection = {}

        room_place_tries = 0
        while True:
            room_place_tries += 1

            #
            # First room should not be fixed.
            #
            roomno = self.rooms_get_next_roomno()
            if roomno < self.fixed_room_count:
                room = self.rooms[roomno]
                if room.can_be_placed_as_first_room is not True:
                    if room_place_tries < 100:
                        continue

            room = self.rooms[roomno]
            x = int(self.width / 2)
            y = int(self.height / 2)
            room = self.rooms[roomno]
            x -= int(room.width / 2)
            y -= int(room.height / 2)

            if self.room_place_if_no_overlaps(roomno, x, y):
                self.roomno_first = roomno

                room = self.rooms[roomno]
                room.can_be_placed_as_start = True
                room.can_be_placed_as_exit = False
                return True

            if room_place_tries > 1000:
                mm.err("Could not place first room")
                return False

    #
    # Place remaining rooms hanging off of the corridors of the last.
    #
    def rooms_place_remaining(self, rooms_on_level):
        self.corridor_ends = []
        self.rooms_all_grow_new_corridors()

        room_place_tries = 0
        while self.rooms_on_level < rooms_on_level:
            room_place_tries += 1
            if room_place_tries > rooms_on_level * 10:
                mm.log("Tried to place rooms for too long, made {0} rooms".
                       format(self.rooms_on_level))
#                self.dump()
                return False

            #
            # If we place at least one new room, we will have new corridors
            # to grow.
            #
            if self.rooms_all_try_to_place_at_end_of_corridors():
                self.rooms_all_grow_new_corridors()

        return True

    #
    # Place all rooms
    #
    def rooms_place_all(self, rooms_on_level):
        self.roomnos = set()
        if not self.room_place_first():
            return False
        if not self.rooms_place_remaining(rooms_on_level):
            return False
        self.roomnos = sorted(self.roomnos)
        return True

    #
    # Remove dangling corridors that go nowhere.
    #
    def rooms_trim_corridors(self):
        trimmed = True
        while trimmed:
            trimmed = False
            for y in range(self.height):
                for x in range(self.width):
                    if not self.is_corridor_at(x, y):
                        continue

                    nbrs = 0
                    if self.is_corridor_or_floor_at(x - 1, y):
                        if not self.is_wall_at(x - 1, y):
                            nbrs += 1
                    if self.is_corridor_or_floor_at(x + 1, y):
                        if not self.is_wall_at(x + 1, y):
                            nbrs += 1
                    if self.is_corridor_or_floor_at(x, y - 1):
                        if not self.is_wall_at(x, y - 1):
                            nbrs += 1
                    if self.is_corridor_or_floor_at(x, y + 1):
                        if not self.is_wall_at(x, y + 1):
                            nbrs += 1
                    if nbrs < 2:
                        self.putc(x, y, charmap.depth.floor, charmap.SPACE)
                        trimmed = True

    #
    # Remove dangling corridors that go nowhere.
    #
    def rooms_trim_looped_corridors(self):

        walked = [[0 for i in range(self.height)]
                  for j in range(self.width)]

        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                if walked[x][y]:
                    continue

                if not self.is_corridor_at(x, y) and \
                   not self.is_door_at(x, y):
                    continue

                roomno = None
                corridor = self.flood_find(x, y, self.is_corridor_or_door_at)

                #
                # We've found all tiles in this corridor. Now find all rooms
                # adjacent to the corridor and connect many to many
                #
                rooms_adjoining_this_corridor = set()
                for c in corridor:
                    cx, cy = c

                    walked[cx][cy] = 1

                    for dx, dy in biome.XY_DELTAS:
                        if self.is_movement_blocking_at(cx + dx, cy + dy):
                            continue

                        fx = cx + dx
                        fy = cy + dy

                        if not self.is_floor_at(fx, fy) and \
                           not self.is_door_at(fx, fy):
                            continue

                        #
                        # Keep track of all room exits so we can use them
                        # later to place doors perhaps
                        #
                        roomno = self.getr(fx, fy)
                        if roomno not in self.room_exits:
                            self.room_exits[roomno] = set()
                        self.room_exits[roomno].add((fx, fy))

                        #
                        # Add this room to the list of adjoining rooms
                        #
                        rooms_adjoining_this_corridor.add(roomno)

                #
                # Connect each room to each other to build a graph
                #
                for roomno in rooms_adjoining_this_corridor:
                    for n in rooms_adjoining_this_corridor:
                        self.room_connection[n].add(roomno)
                        self.room_connection[roomno].add(n)

                if len(rooms_adjoining_this_corridor) < 2:
                    self.flood_replace(x, y,
                                       charmap.depth.floor,
                                       charmap.CORRIDOR,
                                       charmap.SPACE)

    #
    # Display room connectivity info
    #
    def rooms_dump_info(self):

        for r in self.roomnos:
            mm.log("room {0} --> neighbor {1}".format(r,
                                                      self.room_connection[r]))
            for e in self.room_exits[r]:
                mm.log("    exit at {0}".format(e))

    #
    # Lock some rooms - not the first room
    #
    def rooms_randomly_lock(self):

        for roomno in self.roomnos:
            if roomno not in self.roomno_depth:
                self.dump()
                sys.exit(1)

            if self.roomno_locked[roomno]:
                continue

            if self.roomno_depth[roomno] > 0:
                if random.randint(0, 100) < self.room_locked_chance:
                    for e in self.room_exits[roomno]:
                        ex, ey = e
                        self.putc(ex, ey, charmap.depth.wall, charmap.DOOR)
                        self.roomno_locked[roomno] = True

    #
    # Starting from the first room, do a breadth first search to find out
    # the depth of all rooms from the first.
    #
    def rooms_set_depth(self):

        roomno = self.roomno_first
        stack = [roomno]

        self.roomno_depth = {}
        self.roomno_depth[roomno] = 0

        while len(stack) > 0:
            roomno = stack.pop(0)

            #
            # Rooms are harder to get to
            #
            if roomno in self.roomno_locked:
                if self.roomno_locked[roomno]:
                    self.roomno_depth[roomno] = self.roomno_depth[roomno] + 2

            for neb in self.room_connection[roomno]:
                if neb not in self.roomno_depth:
                    stack.append(neb)
                    self.roomno_depth[neb] = self.roomno_depth[roomno] + 1

    #
    # Make corridors rise up
    #
    def rooms_corridor_bridge_height(self):

        self.bridge_height = [[0 for i in range(self.height)]
                              for j in range(self.width)]

        for y in range(self.height):
            for x in range(self.width):
                if not self.is_corridor_at(x, y) and \
                   not self.is_dusty_at(x, y):
                    continue

                if self.is_wall_at(x, y) or \
                   self.is_cwall_at(x, y):
                    continue

                score = 0

                #
                # Bridges only span obstacles
                #
                for dx, dy in biome.XY_DELTAS:
                    tx = x + dx
                    ty = y + dy

                    if self.is_water_at(tx, ty):
                        score += 1

                    if self.is_chasm_at(tx, ty):
                        score += 1

                    if self.is_lava_at(tx, ty):
                        score += 1

                    #
                    # Part of a bridge?
                    #
                    if self.bridge_height[tx][ty]:
                        score += 1

                if score < 1:
                    continue

                #
                # Find the bridge size
                #
                for x1 in range(x, 0, -1):
                    if not self.is_corridor_at(x1, y) and \
                       not self.is_dusty_at(x1, y):
                        break

                for x2 in range(x + 1, self.width, 1):
                    if not self.is_corridor_at(x2, y) and \
                       not self.is_dusty_at(x2, y):
                        break

                cw = x2 - x1

                for y1 in range(y, 0, -1):
                    if not self.is_corridor_at(x, y1) and \
                       not self.is_dusty_at(x, y1):
                        break

                for y2 in range(y + 1, self.height, 1):
                    if not self.is_corridor_at(x, y2) and \
                       not self.is_dusty_at(x, y2):
                        break

                ch = y2 - y1

                #
                # Which dimension of bridge is thickest?
                #
                if cw > ch:
                    step = (x - x1) / cw
                    if step < 0.5:
                        self.bridge_height[x][y] = (x - x1)
                    else:
                        self.bridge_height[x][y] = (x2 - x)
                else:
                    step = (y - y1) / ch
                    if step < 0.5:
                        self.bridge_height[x][y] = (y - y1)
                    else:
                        self.bridge_height[x][y] = (y2 - y)

    def rooms_corridor_bridge_smooth(self):

        new_bridge_height = [[0 for i in range(self.height)]
                             for j in range(self.width)]

        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):

                if not self.is_floor_at(x, y) and \
                   not self.is_corridor_at(x, y) and \
                   not self.is_dusty_at(x, y):
                    continue

                count = 1
                h = 0

                for dx, dy in biome.XY_DELTAS:
                    tx = x + dx
                    ty = y + dy

                    if self.bridge_height[tx][ty] != 0:
                        count += 1.0
                        h += self.bridge_height[tx][ty]

                if count == 0:
                    continue

                h = h / count

                new_bridge_height[x][y] = h

        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                self.bridge_height[x][y] = new_bridge_height[x][y]

    #
    # Any rooms opening onto nothing, fill them in
    #
    def rooms_plug_walls(self):
        for y in range(self.height):
            for x in range(self.width):
                if not self.is_floor_at_fast(x, y):
                    continue

                if self.is_door_at(x, y):
                    continue

                if self.is_movement_blocking_at(x, y):
                    continue

                for dx in range(-1, 2):
                    for dy in range(-1, 2):
                        if not self.is_any_floor_at(x + dx, y + dy):
                            self.putc(x + dx, y + dy,
                                      charmap.depth.wall, charmap.WALL)
                            self.putc(x + dx, y + dy,
                                      charmap.depth.floor, charmap.FLOOR)

    #
    # Wrap corridors in walls that are not bridges
    #
    def add_cwall(self):
        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                if not self.is_corridor_at(x, y):
                    continue

                if self.bridge_height[x][y] == 0:

                    if self.bridge_height[x+1][y] != 0:
                        self.bridge_height[x][y] = self.bridge_height[x+1][y]
                    if self.bridge_height[x-1][y] != 0:
                        self.bridge_height[x][y] = self.bridge_height[x-1][y]
                    if self.bridge_height[x][y-1] != 0:
                        self.bridge_height[x][y] = self.bridge_height[x][y-1]
                    if self.bridge_height[x][y+1] != 0:
                        self.bridge_height[x][y] = self.bridge_height[x][y+1]

                    for dx, dy in biome.ALL_DELTAS_BAR_MID:
                        tx = x + dx
                        ty = y + dy
                        if not self.is_anything_at(tx, ty):
                            self.putc(tx, ty, charmap.depth.wall,
                                      charmap.CWALL)

    #
    # Dissolve walls
    #
    def dissolve_room_walls(self):
        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                if not self.is_wall_at(x, y):
                    continue

                if random.randint(0, 100) < 90:
                    continue

                for dx, dy in biome.XY_DELTAS:
                    tx = x + dx
                    ty = y + dy

                    if self.is_wall_at(tx, ty):
                        continue

                    if self.is_cwall_at(tx, ty):
                        continue

                    if self.is_floor_at(tx, ty):
                        continue

                    if self.is_dissolves_walls_at(tx, ty):
                        if self.is_door_at(x + 1, y) or \
                           self.is_door_at(x - 1, y) or \
                           self.is_door_at(x, y + 1) or \
                           self.is_door_at(x, y - 1):
                            self.putc(x, y, charmap.depth.wall, charmap.DOOR)
                        else:
                            self.putc(x, y, charmap.depth.wall, charmap.SPACE)

                        break

    #
    # Dissolve corridor walls
    #
    def dissolve_room_cwalls(self):
        for y in range(1, self.height - 1):
            for x in range(1, self.width - 1):
                if not self.is_cwall_at(x, y):
                    continue

                if random.randint(0, 100) < 50:
                    continue

                for dx, dy in biome.XY_DELTAS:
                    tx = x + dx
                    ty = y + dy

                    if self.is_wall_at(tx, ty):
                        continue

                    if self.is_cwall_at(tx, ty):
                        continue

                    if self.is_floor_at(tx, ty):
                        continue

                    if self.is_dissolves_walls_at(tx, ty):
                        self.putc(x, y, charmap.depth.wall, charmap.SPACE)
                        break

    #
    # Any dead end doors with no corridor, zap em
    #
    def rooms_plug_doors(self):
        for y in range(self.height):
            for x in range(self.width):
                if not self.is_door_at(x, y):
                    continue

                ok = False
                for dx, dy in biome.XY_DELTAS:
                    if self.is_corridor_at(x + dx, y + dy):
                        ok = True
                        break

                if not ok:
                    self.putc(x, y, charmap.depth.wall, charmap.WALL)

    #
    # Find all tiles where we can place objects
    #
    def rooms_find_occupiable_tiles(self):
        for roomno in self.roomnos:
            self.room_occupiable_tiles[roomno] = []

        for y in range(self.height):
            for x in range(self.width):
                if not self.is_floor_at_fast(x, y):
                    continue

                if self.is_movement_blocking_at(x, y):
                    continue

                roomno = self.getr(x, y)

                self.room_occupiable_tiles[roomno].append((x, y))

    #
    # Any dead end doors with no corridor, zap em
    #
    def rooms_place_start(self):
        tries = 0
        while True:
            tries = tries + 1
            if tries > 100:
                return False

            while True:
                roomno = random.choice(self.roomnos)
                room = self.rooms[roomno]

                if room.can_be_placed_as_start:
                    break

            x, y = random.choice(self.room_occupiable_tiles[roomno])

            obstacle = False
            for dx, dy in biome.ALL_DELTAS:
                if self.is_movement_blocking_at(x + dx, y + dy):
                    obstacle = True
                    break

            if obstacle:
                continue

            self.putc(x, y, charmap.depth.wall, charmap.START)
            return True

    #
    # Any dead end doors with no corridor, zap em
    #
    def rooms_place_exit(self):
        tries = 0
        while True:
            tries = tries + 1
            if tries > 100:
                return False

            while True:
                roomno = random.choice(self.roomnos)
                room = self.rooms[roomno]

                if room.can_be_placed_as_exit:
                    break

            x, y = random.choice(self.room_occupiable_tiles[roomno])

            obstacle = False
            for dx, dy in biome.ALL_DELTAS:
                if self.is_movement_blocking_at(x + dx, y + dy):
                    obstacle = True
                    break

            if obstacle:
                continue

            self.putc(x, y, charmap.depth.wall, charmap.EXIT)
            return True

    #
    # For each locked room place a key at a dungeon depth less than
    # that of the room. This then allows nested locks.
    #
    def room_place_key(self, roomno):

        #
        # Find a room at a lower depth for this key. We should be able
        # to reach such rooms.
        #
        tries = 0
        while True:
            tries = tries + 1
            if tries > 100:
                return False

            key_roomno = random.choice(self.roomnos)
            if key_roomno == roomno:
                continue

            if self.roomno_depth[key_roomno] >= self.roomno_depth[roomno]:
                continue

            break

        #
        # Now place the key
        #
        tries = 0
        while True:
            tries = tries + 1
            if tries > 100:
                break

            #
            # Make sure there is space around the key
            #
            x, y = random.choice(self.room_occupiable_tiles[key_roomno])

            obstacle = False
            for dx, dy in biome.ALL_DELTAS:
                if self.is_movement_blocking_at(x + dx, y + dy):
                    obstacle = True
                    break

            if obstacle:
                continue

            self.putc(x, y, charmap.depth.wall, charmap.KEY)
            return True

    def rooms_place_keys(self):

        for roomno in self.roomnos:
            if not self.roomno_locked[roomno]:
                continue

            tries = 0
            while True:
                tries = tries + 1
                if tries > 100:
                    return False

                if self.room_place_key(roomno):
                    break

        return True

    #
    # Make randomly shaped rooms
    #
    # We use the map as a scratchpad for creating the room.
    #
    def rooms_all_create_random_shapes(self):
        cnt = 0

        #
        # First draw some random lines
        #
        while cnt < 10:
            x1 = random.randint(-10, self.width + 10)
            y1 = random.randint(-10, self.height + 10)
            x2 = random.randint(-10, self.width + 10)
            y2 = random.randint(-10, self.height + 10)
            self.line_draw((x1, y1), (x2, y2), charmap.depth.floor,
                           charmap.FLOOR)
            cnt += 1
        #
        # Next draw straight across lines.
        #
        cnt = 0
        while cnt < 10:
            x1 = random.randint(-10, self.width + 10)
            y1 = random.randint(-10, self.height + 10)
            x2 = x1 + 10
            y2 = y1
            self.line_draw((x1, y1), (x2, y2), charmap.depth.floor,
                           charmap.FLOOR)
            cnt += 1
        #
        # Next draw straight down lines.
        #
        cnt = 0
        while cnt < 10:
            x1 = random.randint(-10, self.width + 10)
            y1 = random.randint(-10, self.height + 10)
            x2 = x1
            y2 = y1 + 10
            self.line_draw((x1, y1), (x2, y2), charmap.depth.floor,
                           charmap.FLOOR)
            cnt += 1
        #
        # Next randomly fill in with floor tiles. This will make large
        # patches of connected floor tiles.
        #
        cnt = 0
        while cnt < 10:
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)
            self.flood_fill(x, y, charmap.depth.floor, charmap.FLOOR)
            cnt += 1
        #
        # Now carve out some empty regions. We could just do smaller
        # regions above, but somehow this looks better.
        #
        cnt = 0
        while cnt < 10:
            x1 = random.randint(-10, self.width + 10)
            y1 = random.randint(-10, self.height + 10)
            x2 = random.randint(-10, self.width + 10)
            y2 = random.randint(-10, self.height + 10)
            self.line_draw((x1, y1), (x2, y2), charmap.depth.floor,
                           charmap.SPACE)
            cnt += 1
        cnt = 0
        while cnt < 10:
            x1 = random.randint(-10, self.width + 10)
            y1 = random.randint(-10, self.height + 10)
            x2 = x1 + 10
            y2 = y1
            self.line_draw((x1, y1), (x2, y2), charmap.depth.floor,
                           charmap.SPACE)
            cnt += 1
        cnt = 0
        while cnt < 10:
            x1 = random.randint(-10, self.width + 10)
            y1 = random.randint(-10, self.height + 10)
            x2 = x1
            y2 = y1 + 10
            self.line_draw((x1, y1), (x2, y2), charmap.depth.floor,
                           charmap.SPACE)
            cnt += 1
        #
        # Now pull each room out of the level with a kind of inverse
        # flood fill.
        #
        cnt = 0
        for y in range(self.height):
            for x in range(self.width):
                if self.is_floor_at_fast(x, y):
                    roomno = self.flood_erase(x, y)
                    cnt += 1
                    #
                    # Filter to rooms of a certain size.
                    #
                    if len(roomno) < self.min_room_size:
                        continue

                    #
                    # Find the size of this random room.
                    #
                    minx = dmap.WALL
                    maxx = -dmap.WALL
                    miny = dmap.WALL
                    maxy = -dmap.WALL
                    for p in roomno:
                        rx, ry = p
                        if rx < minx:
                            minx = rx
                        if ry < miny:
                            miny = ry
                        if rx > maxx:
                            maxx = rx
                        if ry > maxy:
                            maxy = ry

                    rw = maxx - minx + 1
                    rh = maxy - miny + 1
                    rw += 2
                    rh += 2

                    #
                    # Now we need to create the floor and wall vertical
                    # room slices.
                    #
                    rcells = [[' ' for i in range(rh)] for j in range(rw)]
                    for p in roomno:
                        rx, ry = p
                        rx -= minx
                        ry -= miny
                        rx += 1
                        ry += 1
                        rcells[rx][ry] = charmap.FLOOR

                    for ry in range(rh):
                        for rx in range(rw):
                            if rcells[rx][ry] == charmap.FLOOR:
                                if rcells[rx-1][ry] == charmap.SPACE:
                                    rcells[rx-1][ry] = charmap.WALL
                                if rcells[rx+1][ry] == charmap.SPACE:
                                    rcells[rx+1][ry] = charmap.WALL
                                if rcells[rx][ry-1] == charmap.SPACE:
                                    rcells[rx][ry-1] = charmap.WALL
                                if rcells[rx][ry+1] == charmap.SPACE:
                                    rcells[rx][ry+1] = charmap.WALL

                    vert_floor_slice = copy.deepcopy(rcells)
                    vert_wall_slice = copy.deepcopy(rcells)
                    vert_obj_slice = [[' ' for i in range(rh)]
                                      for j in range(rw)]

                    for ry in range(0, rh):
                        for rx in range(0, rw):
                            if vert_floor_slice[rx][ry] == charmap.WALL:
                                vert_floor_slice[rx][ry] = charmap.FLOOR
                            if vert_wall_slice[rx][ry] == charmap.FLOOR:
                                vert_wall_slice[rx][ry] = charmap.SPACE
                            if vert_wall_slice[rx][ry] == charmap.WALL:
                                if rx % 2 == 0 and ry % 2 == 0:
                                    if random.randint(0, 100) < 50:
                                        vert_wall_slice[rx][ry] = charmap.SPACE
                    #
                    # To dump the room:
                    #
                    if False:
                        for ry in range(rh):
                            for rx in range(rw):
                                mm.puts(vert_floor_slice[rx][ry])
                            mm.puts("\n")

                        for ry in range(rh):
                            for rx in range(rw):
                                mm.puts(vert_wall_slice[rx][ry])
                            mm.puts("\n")

                    #
                    # Add to the rooms list.
                    #
                    r = room.Room()
                    r.vert_slice_add("floor", vert_floor_slice)
                    r.vert_slice_add("wall", vert_wall_slice)
                    r.vert_slice_add("obj", vert_obj_slice)
                    r.finalize()
                    r.can_be_placed_as_exit = True
                    self.rooms.append(r)

        #
        # Zero out the map as we were lazy and used it for a scratchpad
        # when creating rooms.
        #
        self.cells = [[[' ' for d in range(charmap.depth.max)]
                       for i in range(self.height)]
                      for j in range(self.width)]

    def add_depth_map(self):

        wall = dmap.WALL
        floor = dmap.FLOOR
        goal = dmap.GOAL

        self.depth_map = dmap.Dmap(width=self.width, height=self.height)

        for y in range(self.height):
            for x in range(self.width):
                self.depth_map.cells[x][y] = floor

        for x in [0, self.width - 1]:
            for y in range(self.height):
                self.depth_map.cells[x][y] = wall

        for y in [0, self.height - 1]:
            for x in range(self.width):
                self.depth_map.cells[x][y] = wall

        for i in range(0, 100):
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)
            self.depth_map.cells[x][y] = wall

        for i in range(0, 100):
            border = random.randint(1, 3)
            x = random.randint(border, self.width - border)
            y = random.randint(border, self.height - border)
            for dx in range(-border, border):
                for dy in range(-border, border):
                    if random.randint(0, 100) < 25:
                        self.depth_map.cells[x + dx][y + dy] = wall

        for i in range(0, 10):
            border = random.randint(1, 10)
            x = random.randint(border, self.width - border)
            y = random.randint(border, self.height - border)
            for dx in range(-border, border):
                for dy in range(-border, border):
                    if random.randint(0, 100) < 5:
                        self.depth_map.cells[x + dx][y + dy] = goal

        self.depth_map.process()

        if False:
            self.depth_map.dump()

    def depth_map_flood(self, x, y, depth, c):
        walked = [[0 for i in range(self.height)]
                  for j in range(self.width)]

        stack = [(x, y)]
        while len(stack) > 0:
            x, y = stack.pop(0)

            if self.is_oob(x, y):
                continue

            if walked[x][y]:
                continue

            walked[x][y] = 1

            if self.depth_map.cells[x][y] >= dmap.WALL:
                continue

            self.putc(x, y, depth, c)
            stack.append((x + 1, y))
            stack.append((x - 1, y))
            stack.append((x, y + 1))
            stack.append((x, y - 1))

    def add_water(self):
        x = random.randint(0, self.width - 1)
        y = random.randint(0, self.height - 1)
        self.depth_map_flood(x, y, charmap.depth.under, charmap.WATER)

    def remove_chasm_next_to_water(self):
        for y in range(self.height):
            for x in range(self.width):
                if not self.is_water_at(x, y):
                    continue

                for dx, dy in biome.ALL_DELTAS_BAR_MID:
                    tx = x + dx
                    ty = y + dy
                    if self.is_chasm_at(tx, ty):
                        self.putc(tx, ty, charmap.depth.under, charmap.WATER)

    def remove_lava_next_to_water(self):
        for y in range(self.height):
            for x in range(self.width):
                if not self.is_water_at(x, y):
                    continue

                for dx, dy in biome.ALL_DELTAS_BAR_MID:
                    tx = x + dx
                    ty = y + dy
                    if self.is_lava_at(tx, ty):
                        self.putc(x, y, charmap.depth.under, charmap.ROCK)
                        break

    def add_lava(self):
        x = random.randint(0, self.width - 1)
        y = random.randint(0, self.height - 1)
        self.depth_map_flood(x, y, charmap.depth.under, charmap.LAVA)

    def add_chasm(self):
        x = random.randint(0, self.width - 1)
        y = random.randint(0, self.height - 1)
        self.depth_map_flood(x, y, charmap.depth.under, charmap.CHASM)

    #
    # Find empty spots in chasms and create some random bridges
    #
    def add_chasm_bridges(self):
        for y in range(1, self.height, 2):
            for x in range(1, self.width, 2):
                if not self.is_chasm_at(x, y):
                    continue

                if not self.is_chasm_at(x - 1, y - 1) or \
                   not self.is_chasm_at(x, y - 1) or \
                   not self.is_chasm_at(x + 1, y - 1) or \
                   not self.is_chasm_at(x - 1, y) or \
                   not self.is_chasm_at(x + 1, y) or \
                   not self.is_chasm_at(x - 1, y + 1) or \
                   not self.is_chasm_at(x, y + 1) or \
                   not self.is_chasm_at(x + 1, y + 1):
                    continue

                if random.randint(0, 1000) < 995:
                    continue

                self.putc(x, y, charmap.depth.floor, charmap.DUSTY)

                self.room_corridor_draw(x, y, 0, - 1, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, -1, 0, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, 1, 0, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, 0, 1, c=charmap.DUSTY)

    #
    # Find empty spots in lavas and create some random bridges
    #
    def add_lava_bridges(self):
        for y in range(1, self.height, 2):
            for x in range(1, self.width, 2):
                if not self.is_lava_at(x, y):
                    continue

                if not self.is_lava_at(x - 1, y - 1) or \
                   not self.is_lava_at(x, y - 1) or \
                   not self.is_lava_at(x + 1, y - 1) or \
                   not self.is_lava_at(x - 1, y) or \
                   not self.is_lava_at(x + 1, y) or \
                   not self.is_lava_at(x - 1, y + 1) or \
                   not self.is_lava_at(x, y + 1) or \
                   not self.is_lava_at(x + 1, y + 1):
                    continue

                if random.randint(0, 1000) < 995:
                    continue

                self.putc(x, y, charmap.depth.floor, charmap.DUSTY)

                self.room_corridor_draw(x, y, 0, - 1, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, -1, 0, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, 1, 0, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, 0, 1, c=charmap.DUSTY)

    #
    # Find empty spots in waters and create some random bridges
    #
    def add_water_bridges(self):
        for y in range(1, self.height, 2):
            for x in range(1, self.width, 2):
                if not self.is_water_at(x, y):
                    continue

                if not self.is_water_at(x - 1, y - 1) or \
                   not self.is_water_at(x, y - 1) or \
                   not self.is_water_at(x + 1, y - 1) or \
                   not self.is_water_at(x - 1, y) or \
                   not self.is_water_at(x + 1, y) or \
                   not self.is_water_at(x - 1, y + 1) or \
                   not self.is_water_at(x, y + 1) or \
                   not self.is_water_at(x + 1, y + 1):
                    continue

                if random.randint(0, 1000) < 995:
                    continue

                self.putc(x, y, charmap.depth.floor, charmap.DUSTY)

                self.room_corridor_draw(x, y, 0, - 1, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, -1, 0, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, 1, 0, c=charmap.DUSTY)
                self.room_corridor_draw(x, y, 0, 1, c=charmap.DUSTY)

    #
    # Find empty spots in waters and create some random tunnels
    #
    def add_tunnels(self):
        for y in range(3, self.height, 4):
            for x in range(3, self.width, 4):

                if not self.is_rock_at(x - 1, y - 1) or \
                   not self.is_rock_at(x, y - 1) or \
                   not self.is_rock_at(x + 1, y - 1) or \
                   not self.is_rock_at(x - 1, y) or \
                   not self.is_rock_at(x + 1, y) or \
                   not self.is_rock_at(x - 1, y + 1) or \
                   not self.is_rock_at(x, y + 1) or \
                   not self.is_rock_at(x + 1, y + 1):
                    continue

                if random.randint(0, 100) < 75:
                    continue

                self.putc(x, y, charmap.depth.wall, charmap.SPACE)
                self.putc(x, y, charmap.depth.floor, charmap.DUSTY)

                self.room_tunnel_draw(x, y, 0, - 1, c=charmap.DUSTY)
                self.room_tunnel_draw(x, y, -1, 0, c=charmap.DUSTY)
                self.room_tunnel_draw(x, y, 1, 0, c=charmap.DUSTY)
                self.room_tunnel_draw(x, y, 0, 1, c=charmap.DUSTY)

    #
    # Find empty spots in waters and create some random tunnels
    #
    def add_treasure(self):

        for t in range(20):
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)

            if not self.is_floor_at(x, y) and \
               not self.is_corridor_at(x, y) and \
               not self.is_dusty_at(x, y):
                continue

            if self.is_wall_at(x, y) or \
               self.is_cwall_at(x, y) or \
               self.is_door_at(x, y) or \
               self.is_obj_at(x, y) or \
               self.is_dungeon_way_up_at(x, y) or \
               self.is_dungeon_way_down_at(x, y) or \
               self.is_key_at(x, y) or \
               self.is_rock_at(x, y):
                continue

            self.putc(x, y, charmap.depth.obj, charmap.TREASURE)

    def add_rock(self):
        for y in range(self.height):
            for x in range(self.width):
                for d in reversed(range(charmap.depth.max)):
                    c = self.cells[x][y][d]
                    if c != " ":
                        break

                if c == charmap.SPACE:
                    self.putc(x, y, charmap.depth.wall, charmap.ROCK)

    def dump(self, max_depth=charmap.depth.max):
        return
        from colored import fg, bg, attr

        for y in range(self.height):
            for x in range(self.width):
                for d in reversed(range(max_depth)):
                    c = self.cells[x][y][d]
                    cmap = charmap.charmap[c]
                    fg_name = cmap["fg"]
                    bg_name = cmap["bg"]
                    if c != " ":
                        break

                res = attr('reset')
                if c == charmap.FLOOR:
                    r = self.roomno_cells[x][y]
                    if r == -1:
                        c = "!"
                        color = fg("white") + bg("red")
                    else:
                        if self.depth_map is not None:
                            depth = self.depth_map.cells[x][y] % 64
                            color = fg(r + depth % 255) + bg(0)
                        else:
                            color = fg(r % 255) + bg(0)

                    r = self.getr(x, y)
                    if r is None:
                        mm.log("No room depth at {0},{1}".format(x, y))
                    else:
                        if r in self.roomno_depth:
                            d = self.roomno_depth[r]
                            c = chr(ord('0') + d)
                elif c == charmap.WATER:
                    if self.depth_map is not None:
                        depth = self.depth_map.cells[x][y] % 64
                        color = fg(depth % 255) + bg(0)
                    else:
                        color = fg(fg_name) + bg(bg_name)
                else:
                    color = fg(fg_name) + bg(bg_name)

                mm.puts(color + c + res)
            mm.puts("\n")

    def dump_depth(self, max_depth=charmap.depth.max):
        return
        from colored import fg, bg, attr

        for y in range(self.height):
            for x in range(self.width):
                for d in reversed(range(max_depth)):
                    c = self.cells[x][y][d]
                    if c != " ":
                        break

                color = None

                res = attr('reset')
                if c != charmap.SPACE:
                    if self.depth_map is not None:
                        d = self.depth_map.cells[x][y] % 64
                        c = chr(ord('0') + d)
                        color = fg(d % 32) + bg(0)

                if color:
                    mm.puts(color + c + res)
                else:
                    mm.puts(" ")

            mm.puts("\n")
