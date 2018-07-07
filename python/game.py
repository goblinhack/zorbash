import mm
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

        t = g.push_block(tp_name="player1", at=point.Point(8, 8, 8))
        g.player = t

        g.push_block(tp_name="wall3", at=point.Point(8, 8, 1))
        g.push_block(tp_name="wall3", at=point.Point(8, 8, 2))
        g.push_block(tp_name="wall3", at=point.Point(8, 8, 3))
        g.push_block(tp_name="wall3", at=point.Point(8, 8, 4))

        g.push_block(tp_name="wall2", at=point.Point(7, 7, 0))
        g.push_block(tp_name="wall1", at=point.Point(4, 4, 0))

        g.push_block(tp_name="wall1", at=point.Point(1, 1, 0))
        g.push_block(tp_name="wall1", at=point.Point(0, 0, 0))

        for z in range(4):
            for x in range(mm.MAP_WIDTH):
                if x & 2:
                    g.push_block(tp_name="wall1", at=point.Point(x, 3, z))
                    g.push_block(tp_name="wall2", at=point.Point(3, x, z))

        for z in range(1):
            for x in range(mm.MAP_WIDTH):
                g.push_block(tp_name="wall2", at=point.Point(x, 3, 3))
                g.push_block(tp_name="wall2", at=point.Point(3, x, 3))

        for x in range(32):
            for y in range(32):
                g.push_block(tp_name="wall3", at=point.Point(x, y, 0))

        for x in range(20):
            g.push_block(tp_name="wall2", at=point.Point(x, mm.MAP_HEIGHT - 1, 1))
        for y in range(15):
            g.push_block(tp_name="wall2", at=point.Point(mm.MAP_WIDTH - 1, y, 1))

        for z in range(int(mm.MAP_DEPTH)):
            for x in range(20):
                g.push_block(tp_name="wall2", at=point.Point(x, 0, z))

            for y in range(20):
                g.push_block(tp_name="wall2", at=point.Point(0, y, z))


    def new_level(self, seed):

        self.game_map_create()
        self.level = level.Level(at=self.where, seed=seed)
        self.level.load(self.where.x, self.where.y)
        self.game_map_created()

    def load_level_finalize(self):
        self.zzz1 = 0.0
        mm.game_set_zzz1(self.zzz1)
        self.zzz2 = 0.0
        mm.game_set_zzz2(self.zzz2)
        self.zzz3 = 0.0
        mm.game_set_zzz3(self.zzz3)
        self.zzz4 = 0.0
        mm.game_set_zzz4(self.zzz4)
        self.zzz5 = 0.0
        mm.game_set_zzz5(self.zzz5)
        self.zzz6 = 0.0
        mm.game_set_zzz6(self.zzz6)
        self.zzz7 = 0.0
        mm.game_set_zzz7(self.zzz7)
        self.zzz8 = 0.0
        mm.game_set_zzz8(self.zzz8)
        self.zzz9 = 0.0
        mm.game_set_zzz9(self.zzz9)
        self.zzz10 = 0.0
        mm.game_set_zzz10(self.zzz10)
        self.zzz11 = 0.0
        mm.game_set_zzz11(self.zzz11)
        self.zzz12 = 0.0
        mm.game_set_zzz12(self.zzz12)
        self.zzz13 = 0.0
        mm.game_set_zzz13(self.zzz13)
        self.zzz14 = 0.0
        mm.game_set_zzz14(self.zzz14)
        self.zzz15 = 0.0
        mm.game_set_zzz15(self.zzz15)
        self.zzz16 = 0.0
        mm.game_set_zzz16(self.zzz16)
        self.zzz17 = 0.0
        mm.game_set_zzz17(self.zzz17)
        self.zzz18 = 0.0
        mm.game_set_zzz18(self.zzz18)
        self.zzz19 = 0.0
        mm.game_set_zzz19(self.zzz19)
        self.zzz20 = 0.0
        mm.game_set_zzz20(self.zzz20)
        self.zzz21 = 0.0
        mm.game_set_zzz21(self.zzz21)
        self.zzz22 = 0.0
        mm.game_set_zzz22(self.zzz22)
        self.zzz23 = 0.0
        mm.game_set_zzz23(self.zzz23)
        self.zzz24 = 0.0
        mm.game_set_zzz24(self.zzz24)
        self.zzz25 = 0.0
        mm.game_set_zzz25(self.zzz25)
        self.zzz26 = 0.0
        mm.game_set_zzz26(self.zzz26)
        self.zzz27 = 0.0
        mm.game_set_zzz27(self.zzz27)
        self.zzz28 = 0.0
        mm.game_set_zzz28(self.zzz28)
        self.zzz29 = 0.0
        mm.game_set_zzz29(self.zzz29)
        self.zzz30 = 0.0
        mm.game_set_zzz30(self.zzz30)
        self.zzz31 = 0.0
        mm.game_set_zzz31(self.zzz31)
        self.zzz32 = 0.0
        mm.game_set_zzz32(self.zzz32)
        self.zzz33 = 0.0
        mm.game_set_zzz33(self.zzz33)
        self.zzz34 = 0.0
        mm.game_set_zzz34(self.zzz34)
        self.zzz35 = 0.0
        mm.game_set_zzz35(self.zzz35)
        self.zzz36 = 0.0
        mm.game_set_zzz36(self.zzz36)
        self.zzz37 = 0.0
        mm.game_set_zzz37(self.zzz37)
        self.zzz38 = 0.0
        mm.game_set_zzz38(self.zzz38)
        self.zzz39 = 0.0
        mm.game_set_zzz39(self.zzz39)
        self.zzz40 = 0.0
        mm.game_set_zzz40(self.zzz40)
        self.zzz41 = 0.0
        mm.game_set_zzz41(self.zzz41)
        self.zzz42 = 0.0
        mm.game_set_zzz42(self.zzz42)
        self.zzz43 = 0.0
        mm.game_set_zzz43(self.zzz43)
        self.zzz44 = 0.0
        mm.game_set_zzz44(self.zzz44)
        self.zzz45 = 0.0
        mm.game_set_zzz45(self.zzz45)
        self.zzz46 = 0.0
        mm.game_set_zzz46(self.zzz46)
        self.zzz47 = 0.0
        mm.game_set_zzz47(self.zzz47)
        self.zzz48 = 0.0
        mm.game_set_zzz48(self.zzz48)
        self.zzz49 = 0.0
        mm.game_set_zzz49(self.zzz49)
        self.zzz50 = 0.0
        mm.game_set_zzz50(self.zzz50)
        self.zzz51 = 0.0
        mm.game_set_zzz51(self.zzz51)
        self.zzz52 = 0.0
        mm.game_set_zzz52(self.zzz52)
        self.zzz53 = 0.0
        mm.game_set_zzz53(self.zzz53)
        self.zzz54 = 0.0
        mm.game_set_zzz54(self.zzz54)
        self.zzz55 = 0.0
        mm.game_set_zzz55(self.zzz55)
        self.zzz56 = 0.0
        mm.game_set_zzz56(self.zzz56)
        self.zzz57 = 0.0
        mm.game_set_zzz57(self.zzz57)
        self.zzz58 = 0.0
        mm.game_set_zzz58(self.zzz58)
        self.zzz59 = 0.0
        mm.game_set_zzz59(self.zzz59)
        self.zzz60 = 0.0
        mm.game_set_zzz60(self.zzz60)
        self.zzz61 = 0.0
        mm.game_set_zzz61(self.zzz61)
        self.zzz62 = 0.0
        mm.game_set_zzz62(self.zzz62)
        self.zzz63 = 0.0
        mm.game_set_zzz63(self.zzz63)
        self.zzz64 = 0.0
        mm.game_set_zzz64(self.zzz64)
        self.zzz65 = 0.0
        mm.game_set_zzz65(self.zzz65)
        self.zzz66 = 0.0
        mm.game_set_zzz66(self.zzz66)
        self.zzz67 = 0.0
        mm.game_set_zzz67(self.zzz67)
        self.zzz68 = 0.0
        mm.game_set_zzz68(self.zzz68)
        self.zzz69 = 0.0
        mm.game_set_zzz69(self.zzz69)
        self.zzz70 = 0.0
        mm.game_set_zzz70(self.zzz70)
        self.zzz71 = 0.0
        mm.game_set_zzz71(self.zzz71)
        self.zzz72 = 0.0
        mm.game_set_zzz72(self.zzz72)
        self.zzz73 = 0.0
        mm.game_set_zzz73(self.zzz73)
        self.zzz74 = 0.0
        mm.game_set_zzz74(self.zzz74)
        self.zzz75 = 0.0
        mm.game_set_zzz75(self.zzz75)
        self.zzz76 = 0.0
        mm.game_set_zzz76(self.zzz76)
        self.zzz77 = 0.0
        mm.game_set_zzz77(self.zzz77)

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
            mm.con("Game saved to {}".format(s))
            mm.tip("Game saved to {}".format(s))

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
            mm.log("Game loading from {}".format(s))

            self.seed = pickle.load(f)
            self.where = pickle.load(f)
            self.last_level_seed = pickle.load(f)
            self.post_creation_hooks()
            self.new_level(self.last_level_seed)
            mm.log("Game loading completed for level {} from {}".format(str(self.level), s))

        if self.version != self.__class__.class_version:
            self.upgrade()

    def destroy(self):
        l = self.level
        l.destroy()

    def game_map_create(self):
        mm.game_map_create()

    def game_map_created(self):
        mm.game_map_created()

    def map_wid_destroy(self):
        mm.game_map_destroy()

    #
    # Mouse is over a map tile
    #
    def mouse_over(self, w, tx, ty, x, y, wheelx, wheely, button):
        self.map_selected_tile(tx, ty)

        #tip = "Tile: {},{} ".format(tx, ty)
        #tip += "pixel: {},{}".format(x, y)
        #mm.tip(tip)

        if wheelx > 0:
            mm.game_set_move_left() 
            return True

        if wheelx < 0:
            mm.game_set_move_right() 
            return True

        if wheely < 0:
            mm.game_set_move_down() 
            return True

        if wheely > 0:
            mm.game_set_move_up() 
            return True

        return True

    #
    # Mouse is over a map tile
    #
    def map_selected_tile(self, x, y):

        mm.game_map_unhighlight_tile(
            self.last_selected_tile_x,
            self.last_selected_tile_y)

        self.last_selected_tile_x = x
        self.last_selected_tile_y = y

        mm.game_map_highlight_tile(x, y, "icon-selected", "icon-highlighted")

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

        if sym == mm.SDLK_BACKQUOTE:
            return False

        if sym == mm.SDLK_BACKSLASH:
            return False

        if sym == mm.SDLK_LEFT or sym == mm.SDLK_a:
            mm.game_set_move_left() 
            return True

        if sym == mm.SDLK_RIGHT or sym == mm.SDLK_d:
            mm.game_set_move_right() 
            return True

        if sym == mm.SDLK_DOWN or sym == mm.SDLK_s:
            mm.game_set_move_down() 
            return True

        if sym == mm.SDLK_UP or sym == mm.SDLK_w:
            mm.game_set_move_up() 
            return True

        if sym == mm.SDLK_z or sym == mm.SDLK_j:
            mm.game_set_move_jump() 
            return True

        if mod == mm.KMOD_LCTRL or mod == mm.KMOD_RCTRL:
            if sym == mm.SDLK_s:
                self.save()
                return True

        if sym == mm.SDLK_LCTRL:
            return False
        if sym == mm.SDLK_LSHIFT:
            return False
        if sym == mm.SDLK_LALT:
            return False
        if sym == mm.SDLK_LGUI:
            return False
        if sym == mm.SDLK_RCTRL:
            return False
        if sym == mm.SDLK_RSHIFT:
            return False
        if sym == mm.SDLK_RALT:
            return False
        if sym == mm.SDLK_RGUI:
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
        keys = mm.SDLGetKeyState()

        #
        # Don't want auto repeat of move
        #
        #if keys[mm.SDL_SCANCODE_LEFT]:
        #    mm.game_set_move_left() 

        #if keys[mm.SDL_SCANCODE_RIGHT]:
        #    mm.game_set_move_right() 

        #if keys[mm.SDL_SCANCODE_DOWN]:
        #    mm.game_set_move_down() 

        #if keys[mm.SDL_SCANCODE_UP]:
        #    mm.game_set_move_up() 

        self.player_get_next_move()

    def push_block(self, tp_name, at):

        l = g.level

        t = thing.Thing(level=l, tp_name=tp_name, at=at)

        t.push()

        return t


def game_mouse_over(w, tx, ty, x, y, wheelx, wheely, button):
    if g is None or g.level is None:
        return False

    #mm.con("game_mouse_over tile {} {}".format(tx, ty)) 
    g.mouse_over(w, tx, ty, x, y, wheelx, wheely, button)


def game_mouse_down(w, tx, ty, x, y, button):
    if g is None or g.level is None:
        return False

    #mm.con("game_mouse_down {}".format(button)) 
    return g.mouse_down(w, tx, ty, x, y, button)


def game_key_down(w, sym, mod):
    if g is None or g.level is None:
        return False

    return g.key_down(w, sym, mod)


def game_tick(w, sym, mod):
    if g.level is None:
        mm.con("no level")
    if g is None:
        mm.con("no game")
    if g is None or g.level is None:
        return False
    mm.con("tick")

    return g.tick()


g = None


def game_restore():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        mm.con("Load")
        g.load()
    else:
        return False

    g.load_level_finalize()


def game_new_or_restore():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        mm.con("Load saved game at {}".format(s))
        g.load()
    else:
        mm.con("Cannot find saved game at {}, make a new game".format(s))
        g.new_game()

    g.load_level_finalize()
    mm.tip("Press h for help.")


def game_restore():
    global g

    if g is None:
        return False

    s = os.path.normcase(os.path.join(os.environ["APPDATA"], g.save_file))
    if os.path.isfile(s):
        mm.con("Load")
        g.load()
    else:
        return False

    g.load_level_finalize()


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

    mm.log("Appdata dir is " + game_dir)

    g = Game()
