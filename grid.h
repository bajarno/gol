#define STATEMASK 128 // The 8th bit of one byte represents whether the cell is alive
#define STATEUNMASK 127

#define CHECKMASK 64 // The 7th bit of one byte represents whether the cell needs to be checked
#define CHECKUNMASK 191

#define CHANGEMASK 32 // The 6th bit indicates whether the cell changed value
#define CHANGEUNMASK 223

typedef enum Algorithm {
    // Most basic implementation. Checks all neighbours for each cell each generation.
    // metadata: Unused
    BASIC,

    BASIC_DIFF,

    // Keeps track of amount of living neighbours for each cell.
    // metadata: Contains amount of neighbours
    NEIGHBOURS
} Algorithm;

// Struct representing grid data.
typedef struct Grid {
    int width;
    int height;

    int cyclic;

    // The algorithm that is used for calculating new generations.
    Algorithm algorithm;

    // Represents the generation, 1 = alive, 0 = death.
    uint8_t ** data;
    uint8_t ** data_prev;

    // SpinLock for reading and writing to data, used for blocking access by other threads.
    SDL_SpinLock write_lock;
    SDL_SpinLock read_lock;
} Grid;

Grid grid_init(int , int, int, Algorithm);
void free_grid_memory(Grid*);
void grid_step(Grid*);
void grid_step_basic(Grid*);
void grid_step_basic_diff(Grid*);
uint8_t get_next_state_basic(uint8_t**, int, int);
void grid_step_neighbours(Grid*);
void grid_clear(Grid*);