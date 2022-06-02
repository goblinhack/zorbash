import my


class Tp:
    """thing template"""

    def __init__(self, name, text_long_name=None, text_short_name=None):
        self.name = name

        if text_long_name is None:
            self.text_long_name = name
        else:
            self.text_long_name = text_long_name

        if text_short_name is None:
            self.text_short_name = self.text_long_name
        else:
            self.text_short_name = text_short_name

        #
        # Load it into the game engine
        #
        my.tp_load(self)
