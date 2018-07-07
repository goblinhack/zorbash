import mm
import game


def hook_new_game():
    mm.con("New game hook")
    game.game_new()


def hook_destroy_game():
    mm.con("Destroy game hook")

    if game.g:
        game.g.destroy()


def hook_game_tick():
    if game.g:
        game.g.tick()


def hook_update_player_nexthops(nexthops):
    if game.g:
        for o in nexthops:
            (x, y) = o

        game.g.nexthops = nexthops
