import traceback
import mm
import tp
import game
import point


class Thing:

    class_version = 2

    def __init__(self, tp_name, level=None, at=None):

        self.version = self.__class__.class_version
        self.v1_field = 1

        self.level = level
        self.tp_name = tp_name
        self.is_moving = False
        self.nexthops = []

        level.max_thing_id += 1
        self.thing_id = level.max_thing_id

        if tp_name not in tp.all_tps:
            self.err("Thing template {} does not exist".format(tp_name))

        self.tp = tp.all_tps[tp_name]

        if at is None:
            self.at = Point(-1, -1, -1)
        else:
            self.at = at

        self.on_level = False
        self.tilename = None

        self.debug("created thing on level {} at {}".format(self.level, self.at))

        #
        # Save on the level all things list. We can't save onto the level
        # yet as that depends on the thing co-ords which we do not have
        # until it is pushed.
        #
        if self.thing_id in self.level.all_things:
            self.die("thing ID {} is already in the level list".format(
                     self.thing_id))
            return

        level.all_things[self.thing_id] = self
        self.level.all_things[self.thing_id] = self

        self.name = str(self)
        mm.thing_new(self, self.thing_id, tp_name)

        if self.tp.thing_init is not None:
            self.tp.thing_init(self)

        self.post_creation_hooks()

    def post_creation_hooks(self):

        if self.tp.is_player:
            self.con("Player is on {} at {}".format(self.level, self.at))
            game.g.player = self

    def __getstate__(self):
        result = self.__dict__.copy()
        #self.log("__getstate__ thing on level {} at {}".format(self.level, self.at))

        if "tp" not in result:
            self.dump()
            self.die("Trying to save thing that has no template")
        del result['tp']

        if "level" not in result:
            self.dump()
            self.die("Trying to save thing that has no level")
        del result['level']

        if self.tp.is_player:
            self.log("Save player on level {}".format(self.level))
        return result

    def __setstate__(self, dict):
        self.__dict__ = dict

    def __str__(self):
        return "{}:{}".format(self.thing_id, self.tp_name)

    def log(self, msg):
        mm.log("Thing {}: {}".format(str(self), msg))

    def con(self, msg):
        mm.con("Thing {}: {}".format(str(self), msg))

    def debug(self, msg):
        #mm.log("Thing {} ({}, {}): {}".format(str(self), self.at.x, self.at.y, msg))
        return

    def err(self, msg):
        mm.con("".join(traceback.format_stack()))
        mm.err("Thing {}: ERROR: {}".format(self, msg))

    def die(self, msg):
        mm.con("".join(traceback.format_stack()))
        mm.die("Thing {}: FATAL ERROR: {}".format(self, msg))

    def dump(self):
        self.log("@ {},{} on level {}".format(str(self.at), self.level))

    def destroy(self, reason="no reason"):

        if hasattr(self.tp, "thing_destroyed"):
            if self.tp.thing_destroyed is not None:
                self.tp.thing_destroyed(self)

        if self.on_level:
            self.pop()

        self.debug("Destroying thing, {}".format(reason) + " {")

        if self.thing_id in self.level.all_things:
            del self.level.all_things[self.thing_id]

        mm.thing_destroyed(self, reason)

        self.debug("} " + "Destroyed thing, {}".format(reason))
        del self

    def upgrade(self):

        if self.version < 2:
            self.v2_field = 2

        self.debug("upgraded from ver {} to {}".format(
                   self.version, self.__class__.class_version))

        self.version = self.__class__.class_version

    #
    # Loaded from save file into a level
    #
    def loaded(self, level):

        if self.version != self.__class__.class_version:
            self.upgrade()

        level.all_things[self.thing_id] = self

        self.level = level
        self.tp = tp.all_tps[self.tp_name]

        mm.thing_new(self, self.thing_id, self.tp_name)

        if self.on_level:
            self.on_level = False
            self.push()
            if self.tilename is not None:
                self.set_tilename(self.tilename)

        #self.log("loaded thing on level {} at {}".format(self.level, self.at))

        self.post_creation_hooks()

    #
    # Move a thing and see it move smoothly on the map
    #
    def move(self, to):

        if to.oob():
            return

        self.update_pos(to)

        mm.thing_move_to(self, to.x, to.y)

    def update_pos(self, at):

        self.at = at

    #
    # Associate the thing with a given level
    #
    def push(self, at=None):

        if at is None:
            at = self.at

        if at.oob():
            self.die("Out of bounds at {}".format(self.at))
            return

        self.on_level = True
        self.debug("pushed")

        self.at = at

        self.level.thing_push(self.at, self)

        mm.thing_push(self)

        if hasattr(self.tp, "thing_pushed"):
            if self.tp.thing_pushed is not None:
                self.tp.thing_pushed(self)

    #
    # De-associate the thing with its level
    #
    def pop(self):
        if not self.on_level:
            self.err("Is not on the map")
            return
        self.on_level = False
        self.debug("pop")

        self.level.thing_pop(self.at, self)
        mm.thing_pop(self)

    def set_long_name(self, value=""):
        self.long_name = value

    def set_tilename(self, name):
        self.tilename = name
        mm.set_tilename(self, name)

    def set_tp(self, tp_name):
        self.tp = tp.all_tps[tp_name]
        mm.thing_set_tp(self, tp_name)
