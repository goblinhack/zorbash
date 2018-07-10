import zx
import level
import thing
import pickle
import os.path
import game
import console
import point

global g


class Game:

    class_version = 1

    def __init__(self):

        self.version = self.__class__.class_version

        self.level = None

        #
        # Max thing ID in use in any level. This grows forever.
        #
        self.save_file = "save_file"
        self.player = None

        self.last_level_seed = None
        self.last_selected_tile_x = 0
        self.last_selected_tile_y = 0

        self.post_creation_hooks()

    def post_creation_hooks(self):

        self.nexthops = None

    def new_game(self):

        self.seed = 10
        self.where = point.Point(0, 0, 0)
        self.new_level(self.seed)

        #t = g.push_block(tp_name="player1", at=point.Point(8, 8, 0))
        #g.player = t

        #g.push_block(tp_name="wall3", at=point.Point(8, 8, 1))
        #g.push_block(tp_name="wall3", at=point.Point(8, 8, 2))
        #g.push_block(tp_name="wall3", at=point.Point(8, 8, 3))
        #g.push_block(tp_name="wall3", at=point.Point(8, 8, 4))

        #g.push_block(tp_name="wall2", at=point.Point(7, 7, 0))
        #g.push_block(tp_name="wall1", at=point.Point(4, 4, 0))

        #g.push_block(tp_name="wall1", at=point.Point(1, 1, 0))
        #g.push_block(tp_name="wall1", at=point.Point(0, 0, 0))

        #for z in range(4):
        #    for x in range(zx.MAP_WIDTH):
        #        if x & 2:
        #            g.push_block(tp_name="wall1", at=point.Point(x, 3, z))
        #            g.push_block(tp_name="wall2", at=point.Point(3, x, z))

        #for z in range(1):
        #    for x in range(zx.MAP_WIDTH):
        #        g.push_block(tp_name="wall2", at=point.Point(x, 3, 3))
        #        g.push_block(tp_name="wall2", at=point.Point(3, x, 3))

        #for x in range(32):
        #    for y in range(32):
        #        g.push_block(tp_name="wall3", at=point.Point(x, y, 0))

        #for x in range(20):
        #    g.push_block(tp_name="wall2", at=point.Point(x, zx.MAP_HEIGHT - 1, 1))
        #for y in range(15):
        #    g.push_block(tp_name="wall2", at=point.Point(zx.MAP_WIDTH - 1, y, 1))

        #for z in range(int(zx.MAP_DEPTH)):
        #    for x in range(20):
        #        g.push_block(tp_name="wall2", at=point.Point(x, 0, z))

        #    for y in range(20):
        #        g.push_block(tp_name="wall2", at=point.Point(0, y, z))


    def new_level(self, seed):

        self.level = level.Level(at=self.where, seed=seed)
        self.level.load(self.where.x, self.where.y)

    def save(self):
        l = self.level

        s = os.path.normcase(
                os.path.join(os.environ["APPDATA"], self.save_file))

        with open(s, 'wb') as f:
            pickle.dump(self.seed, f, pickle.HIGHEST_PROTOCOL)
            pickle.dump(self.where, f, pickle.HIGHEST_PROTOCOL)

            self.last_level_seed = l.seed
            pickle.dump(self.last_level_seed, f, pickle.HIGHEST_PROTOCOL)

            l.save(os.path.join(os.environ["APPDATA"]))
            zx.con("Game saved to {}".format(s))
            zx.tip("Game saved to {}".format(s))

    def upgrade(self):

        if self.version < 2:
            self.v2_field = 2

#        self.debug("upgraded from ver {} to {}".format(
#                   self.version, self.__class__.class_version))

        self.version = self.__class__.class_version

    def load(self):

        s = os.path.normcase(os.path.join(os.environ["APPDATA"],
                                          self.save_file))
        with open(s, 'rb') as f:
            zx.log("Game loading from {}".format(s))

            self.seed = pickle.load(f)
            self.where = pickle.load(f)
            self.last_level_seed = pickle.load(f)
            self.post_creation_hooks()
            self.new_level(self.last_level_seed)
            zx.log("Game loading completed for level {} from {}".format(str(self.level), s))

        if self.version != self.__class__.class_version:
            self.upgrade()

    def destroy(self):
        l = self.level
        l.destroy()

    def game_map_create(self):
        zx.game_map_create()

    def game_map_created(self):
        zx.game_map_created()

    def map_wid_destroy(self):
        zx.game_map_destroy()

    #
    # Mouse is over a map tile
    #
    def mouse_over(self, w, tx, ty, x, y, wheelx, wheely, button):
        self.map_selected_tile(tx, ty)

        #tip = "Tile: {},{} ".format(tx, ty)
        #tip += "pixel: {},{}".format(x, y)
        #zx.tip(tip)

        if wheelx > 0:
            zx.game_set_move_left() 
            return True

        if wheelx < 0:
            zx.game_set_move_right() 
            return True

        if wheely < 0:
            zx.game_set_move_down() 
            return True

        if wheely > 0:
            zx.game_set_move_up() 
            return True

        return True

    #
    # Mouse is over a map tile
    #
    def map_selected_tile(self, x, y):

        zx.game_map_unhighlight_tile(
            self.last_selected_tile_x,
            self.last_selected_tile_y)

        self.last_selected_tile_x = x
        self.last_selected_tile_y = y

        zx.game_map_highlight_tile(x, y, "icon-selected", "icon-highlighted")

    #
    # Move the player to the chosen tile
    #
    def mouse_down(self, w, tx, ty, x, y, button):

        l = self.level

        return True

    #
    # Player input
    #
    def key_down(self, w, sym, mod):

        if g is None or g.level is None:
            return False

        tx = self.last_selected_tile_x
        ty = self.last_selected_tile_y
        at = point.Point(tx, ty, 0)
        l = self.level

        if sym == zx.SDLK_BACKQUOTE:
            return False

        if sym == zx.SDLK_BACKSLASH:
            return False

        if sym == zx.SDLK_LEFT or sym == zx.SDLK_a:
            zx.game_set_move_left() 
            return True

        if sym == zx.SDLK_RIGHT or sym == zx.SDLK_d:
            zx.game_set_move_right() 
            return True

        if sym == zx.SDLK_DOWN or sym == zx.SDLK_s:
            zx.game_set_move_down() 
            return True

        if sym == zx.SDLK_UP or sym == zx.SDLK_w:
            zx.game_set_move_up() 
            return True

        if sym == zx.SDLK_z or sym == zx.SDLK_j:
            zx.game_set_move_jump() 
            return True

        if mod == zx.KMOD_LCTRL or mod == zx.KMOD_RCTRL:
            if sym == zx.SDLK_s:
                self.save()
                return True

        if sym == zx.SDLK_LCTRL:
            return False
        if sym == zx.SDLK_LSHIFT:
            return False
        if sym == zx.SDLK_LALT:
            return False
        if sym == zx.SDLK_LGUI:
            return False
        if sym == zx.SDLK_RCTRL:
            return False
        if sym == zx.SDLK_RSHIFT:
            return False
        if sym == zx.SDLK_RALT:
            return False
        if sym == zx.SDLK_RGUI:
            return False

        return True

    def player_get_next_move(self):

        player = self.player
        if not player:
            return

        if self.nexthops is None:
            return

        if len(self.nexthops) == 0:
            return

        x, y = self.nexthops[-1]
        p = point.Point(x, y, 0)

        self.nexthops.pop()

        #    t = l.thing_find(x, y, "ember1")
        #    if t is None:
        #        t = thing.Thing(level=l, tp_name="ember1", x=x, y=y)
        #        t.push()
        l = g.level
        if not l.is_movement_blocking_at(p):
            self.player.move(p)

    def tick(self):
        keys = zx.SDLGetKeyState()

        #
        # Don't want auto repeat of move
        #
        #if keys[zx.SDL_SCANCODE_LEFT]:
        #    zx.game_set_move_left() 

        #if keys[zx.SDL_SCANCODE_RIGHT]:
        #    zx.game_set_move_right() 

        #if keys[zx.SDL_SCANCODE_DOWN]:
        #    zx.game_set_move_down() 

        #if keys[zx.SDL_SCANCODE_UP]:
        #    zx.game_set_move_up() 

        self.player_get_next_move()

    def push_block(self, tp_name, at):

        l = g.level

        t = thing.Thing(level=l, tp_name=tp_name, at=at)

        t.push()

        return t


def game_mouse_over(w, tx, ty, x, y, wheelx, wheely, button):
    if g is None or g.level is None:
        return False

    #zx.con("game_mouse_over tile {} {}".format(tx, ty)) 
    g.mouse_over(w, tx, ty, x, y, wheelx, wheely, button)


def game_mouse_down(w, tx, ty, x, y, button):
    if g is None or g.level is None:
        return False

    #zx.con("game_mouse_down {}".format(button)) 
    return g.mouse_down(w, tx, ty, x, y, button)


def game_key_down(w, sym, mod):
    if g is None or g.level is None:
        return False

    return g.key_down(w, sym, mod)


def game_tick(w, sym, mod):
    if g.level is None:
        zx.con("no level")
    if g is None:
        zx.con("no game")
    if g is None or g.level is None:
        return False
    zx.con("tick")

    return g.tick()


g = None


def game_restore():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        zx.con("Load")
        g.load()
    else:
        return False


def game_new_or_restore():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        zx.con("Load saved game at {}".format(s))
        g.load()
    else:
        zx.con("Cannot find saved game at {}, make a new game".format(s))
        g.new_game()

    zx.tip("Press h for help.")


def game_restore():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        zx.con("Load")
        g.load()
    else:
        return False


def game_saved_exists():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        return True
    else:
        return False


def game_init():
    global g

    if g is not None:
        return False

    game_dir = os.path.join(os.environ["APPDATA"], "zorbash")

    zx.log("Appdata dir is " + game_dir)

    g = Game()
