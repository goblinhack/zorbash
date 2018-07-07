import traceback
import mm
import thing
import sys
import os
import pickle
import tp
import point


class Level:

    class_version = 1

    def __init__(self, at, seed):

        self.where = at
        self.seed = seed
        self.max_thing_id = 0

        #
        # All things in the level
        #
        self.all_things = {}

        self.things_at = [[[[] for z in range(mm.MAP_DEPTH)]
                          for y in range(mm.MAP_HEIGHT)]
                          for x in range(mm.MAP_WIDTH)]

        self.version = self.__class__.class_version

    def log(self, msg):
        mm.log("Level {}: {}".format(str(self), msg))

    def con(self, msg):
        mm.con("Level {}: {}".format(str(self), msg))

    def debug(self, msg):
        return
        mm.log("Level {}: {}".format(str(self), msg))

    def err(self, msg):
        mm.con("".join(traceback.format_stack()))
        mm.err("Level {}: ERROR: {}".format(self, msg))

    def die(self, msg):
        mm.con("".join(traceback.format_stack()))
        mm.die("Level {}: FATAL ERROR: {}".format(self, msg))

    def __str__(self):
        return "level.{}.{}.{}".format(
                self.where.x,
                self.where.y,
                self.where.z)

    def destroy(self):
        self.log("Destroying level {")

        #
        # to avoid dictionary changed size during iteration, walk the keys
        #
        for thing_id, t in self.all_things.items():

            #
            # Delete from the parent too
            #
            if thing_id in self.level.all_things:
                del self.level.all_things[thing_id]

            t.destroy()

        self.log("} Destroyed level")
        del self

    def dump(self):

        for i in self.all_things:
            self.all_things[i].dump()

    def save(self, path):

        to = os.path.normcase(os.path.join(path, str(self)))
        self.log("Save level to {}".format(to))
        mm.tip("Save level to {}".format(to))

        with open(to, 'wb') as f:
            pickle.dump(self.where, f, pickle.HIGHEST_PROTOCOL)
            pickle.dump(self.max_thing_id, f, pickle.HIGHEST_PROTOCOL)
            pickle.dump(self.all_things, f, pickle.HIGHEST_PROTOCOL)
            pickle.dump(self.seed, f, pickle.HIGHEST_PROTOCOL)

    def upgrade(self):

        if self.version < 2:
            self.v2_field = 2

        self.debug("upgraded from ver {} to {}".format(
                   self.version, self.__class__.class_version))

        self.version = self.__class__.class_version

    def load(self, cx, cy):
        self.con("Load level at {},{}".format(cx, cy))

        s = os.path.normcase(os.path.join(os.environ["APPDATA"], str(self)))
        if not os.path.isfile(s):
            self.con("Cannot find previously saved level {}".format(s))
            s = "data/world/" + str(self)
            if not os.path.isfile(s):
                self.con("Cannot find fresh level {}".format(s))

        if os.path.isfile(s):
            with open(s, 'rb') as f:
                self.con("Load level from {}".format(s))
                self.where = pickle.load(f)
                self.max_thing_id = pickle.load(f)
                self.all_things = pickle.load(f)
                self.seed = pickle.load(f)

            if self.version != self.__class__.class_version:
                self.upgrade()

        #
        # recreate the widgets for this thing
        #
        for thing_id, t in self.all_things.items():
            t = self.all_things[thing_id]
            t.loaded(self)

    def thing_find(self, p, tp_name):

        if p.oob():
            return None

        for t in self.things_at[p.x][p.y][p.z]:
            if t.tp.name == tp_name:
                return t

        return None

    def thing_find_same_type(self, p, tp_name):

        if p.oob():
            return None

        f = tp.all_tps[tp_name]
        for t in self.things_at[p.x][p.y][p.z]:
            if tp.same_type(f, t.tp):
                return t

        return None

    def is_movement_blocking_at(self, p):

        if p.oob():
            return True

        things = self.things_at[p.x][p.y][p.z]
        if not things:
            return True
        
        for t in things:
            if t.tp.is_movement_blocking:
                return True

        return False

    def thing_top(self, p):

        if p.oob():
            return None

        for t in self.things_at[p.x][p.y][p.z]:
            return t

        return None

    def things_at(self, p):

        if p.oob():
            return None

        r = []
        for t in self.things_at[p.x][p.y][p.z]:
            r.append(t)

        return r

    #
    # find an object via some flag it has, e.g if t.is_dungeon_way_up
    # e.g. entrance = self.tp_is_where("is_dungeon_way_up")
    #
    def tp_is_where(self, value):

        for z in range(mm.MAP_DEPTH):
            for y in range(mm.MAP_HEIGHT):
                for x in range(mm.MAP_WIDTH):
                    for t in self.things_at[x][y][z]:
                        v = getattr(t.tp, value)
                        if v is not None:
                            if v:
                                return (point.Point(x, y, z))

        return None

    def things_remove_all(self):

        for z in range(mm.MAP_DEPTH):
            for y in range(mm.MAP_HEIGHT):
                for x in range(mm.MAP_WIDTH):
                    while self.things_at[x][y][z]:
                        for t in self.things_at[x][y][z]:
                            t.destroy("via things remove all")

    def things_flood_fill_(self, p, tp, walked):

        sys.setrecursionlimit(mm.MAP_WIDTH * mm.MAP_HEIGHT)

        if p.oob():
            return

        if walked[p.x][p.y] == 1:
            return

        walked[p.x][p.y] = 1

        for f in self.things_at[p.x][p.y][p.z]:
            other_tp = f.tp

            if tp.is_wall:
                return

        t = self.thing_find_same_type(p, tp.name)
        if t is not None:
            t.destroy("via flood fill")

        t = thing.Thing(level=self,
                        tp_name=tp.name,
                        at = point.Point(p.x, p.y, p.z))
        t.push()

        self.things_flood_fill_(point.Point(p.x - 1, p.y, p.z), tp, walked)
        self.things_flood_fill_(point.Point(p.x + 1, p.y, p.z), tp, walked)
        self.things_flood_fill_(point.Point(p.x, p.y - 1, p.z), tp, walked)
        self.things_flood_fill_(point.Point(p.x, p.y + 1, p.z), tp, walked)

    def things_flood_fill(self, p, tp):

        if tp is None:
            return

        walked = [[0 for i in range(mm.MAP_HEIGHT)]
                  for j in range(mm.MAP_WIDTH)]

        self.things_flood_fill_(p, tp, walked)

    def thing_push(self, p, t):

        #
        # When loading the game again, things think they are on
        # the level already.
        #
        l = self.things_at[p.x][p.y][p.z]
        if t in l:
            return

        l.append(t)

        self.all_things[t.thing_id] = t

    def thing_pop(self, p, t):

        l = self.things_at[p.x][p.y][p.z]
        if not t in l:
            return

        l.remove(t)

        del self.all_things[t.thing_id]
