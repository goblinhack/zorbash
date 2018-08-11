/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

//
// Implements layered cycles that can be used to then create a dungeon
//

class Node {
public:
    /*
     * Nodes have a depth number, optional key, start and exit and corridors
     * to adjoining depths. Depth increases as we get closer to the exit.
     */
    int depth                                 {0};
    /*
     * pass 1 is the main dungeon
     * pass 2 are secret levels
     */
    int pass                                  {0};
    int x, y;
    /*
     * Not necessarily an actual key or lock, but something allowing access
     * to the other node. Only one key per node depth.
     */
    bool is_key                               {false};
    bool is_lock                              {false};
    bool is_entrance                          {false};
    bool is_exit                              {false};
    bool has_exit_up                          {false};
    bool has_exit_down                        {false};
    bool has_exit_left                        {false};
    bool has_exit_right                       {false};
    bool has_secret_exit_up                   {false};
    bool has_secret_exit_down                 {false};
    bool has_secret_exit_left                 {false};
    bool has_secret_exit_right                {false};
};

class Nodes {
public:
    std::vector<Node>                         nodes;
    int nodes_width                           {5};
    int nodes_height                          {5};
    int max_depth                             {0};

    /*
     * Water, rocks etc...
     */
    int depth_obstacle                        {-1};

    Nodes (int nodes_width, int nodes_height) :
        nodes_width                  (nodes_width),
        nodes_height                 (nodes_height)
    {_
        finish_constructor();
    }

    Nodes ()
    {_
        finish_constructor();
    }

    void finish_constructor(void);
    void debug(std::string msg);
    int offset(const int x, const int y);
    bool is_oob(const int x, const int y);
    Node *node_addr(const int x, const int y);
    void putn(const int x, const int y, const Node n);
    Node *getn(const int x, const int y);
    point random_dir(void);
    void random_dir(int *dx, int *dy);
    void init_nodes(void);
    int snake_walk(int depth, int max_placed, int pass);
    void join_nodes_of_same_depth(int depth, int pass);
    void join_depth_to_next_depth(int depth, int pass);
    void join_depth_secret(int depth, int pass);
    void place_lock(int depth, int pass);
    void hide_other_locks(int depth, int pass);
    void place_key(int depth, int pass);
    void place_entrance(void);
    void place_exit(void);
    void set_max_depth(void);
};
