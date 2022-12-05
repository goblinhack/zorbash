import my


def init(self, name):
    # begin sort marker
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_removable_if_out_of_slots(self, True)
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_SWING)
    # end sort marker

    delay = 20
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_left.1", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_left.2", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="cyan",
            tile=name + "_left.3", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="cyan",
            tile=name + "_left.4", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_left.5", delay_ms=delay, is_dir_none=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_left.6",
            delay_ms=delay,
            is_dir_none=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    delay = 20
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="cyan",
            tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="cyan",
            tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_left.6",
            delay_ms=delay,
            is_dir_left=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="cyan",
            tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="cyan",
            tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_left.6",
            delay_ms=delay,
            is_dir_right=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="cyan",
            tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="cyan",
            tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_up.6",
            delay_ms=delay,
            is_dir_up=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="cyan",
            tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="cyan",
            tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="cyan",
            tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="cyan",
            tile=name + "_up.6",
            delay_ms=delay,
            is_dir_down=True,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)
