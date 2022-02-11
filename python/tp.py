import my


class Tp:
    """thing template"""

    def __init__(self, name, text_name=None, short_text_name=None):
        self.name = name

        if text_name is None:
            self.text_name = name
        else:
            self.text_name = text_name

        if short_text_name is None:
            self.short_text_name = self.text_name
        else:
            self.short_text_name = short_text_name

        #
        # Load it into the game engine
        #
        my.tp_load(self)

    def update(self):
        my.tp_update(self)

    def set_tile(self, tile=None, **kw):
        my.tp_set_tile(self, tile, **kw)

    def set_left1_tile(self, left1_tile=None, **kw):
        my.tp_set_left1_tile(self, left1_tile, **kw)

    def set_right1_tile(self, right1_tile=None, **kw):
        my.tp_set_right1_tile(self, right1_tile, **kw)

    def set_bot1_tile(self, bot1_tile=None, **kw):
        my.tp_set_bot1_tile(self, bot1_tile, **kw)

    def set_top1_tile(self, top1_tile=None, **kw):
        my.tp_set_top1_tile(self, top1_tile, **kw)

    def set_tl1_tile(self, tl1_tile=None, **kw):
        my.tp_set_tl1_tile(self, tl1_tile, **kw)

    def set_tr1_tile(self, tr1_tile=None, **kw):
        my.tp_set_tr1_tile(self, tr1_tile, **kw)

    def set_br1_tile(self, br1_tile=None, **kw):
        my.tp_set_br1_tile(self, br1_tile, **kw)

    def set_bl1_tile(self, bl1_tile=None, **kw):
        my.tp_set_bl1_tile(self, bl1_tile, **kw)

    def set_left2_tile(self, left2_tile=None, **kw):
        my.tp_set_left2_tile(self, left2_tile, **kw)

    def set_right2_tile(self, right2_tile=None, **kw):
        my.tp_set_right2_tile(self, right2_tile, **kw)

    def set_bot2_tile(self, bot2_tile=None, **kw):
        my.tp_set_bot2_tile(self, bot2_tile, **kw)

    def set_bot3_tile(self, bot3_tile=None, **kw):
        my.tp_set_bot3_tile(self, bot3_tile, **kw)

    def set_top2_tile(self, top2_tile=None, **kw):
        my.tp_set_top2_tile(self, top2_tile, **kw)

    def set_tl2_tile(self, tl2_tile=None, **kw):
        my.tp_set_tl2_tile(self, tl2_tile, **kw)

    def set_tr2_tile(self, tr2_tile=None, **kw):
        my.tp_set_tr2_tile(self, tr2_tile, **kw)

    def set_br2_tile(self, br2_tile=None, **kw):
        my.tp_set_br2_tile(self, br2_tile, **kw)

    def set_bl2_tile(self, bl2_tile=None, **kw):
        my.tp_set_bl2_tile(self, bl2_tile, **kw)
