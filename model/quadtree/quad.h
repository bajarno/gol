// Mask for all check bits in metadata of a quad.
const uint8_t metadata_check_mask_all = 15;

// Mask for all exist bits in metadata of a quad.
const uint8_t metadata_exist_mask_all = 240;

// Lookup table for mask of check bit of a position in a quad. Position in
// the list corresponds to local position in the quad.
const uint8_t metadata_check_mask[] = {
    1,
    2,
    4,
    8,
};

// Lookup table for mask of all bits except check bit of a position in a quad.
// Position in the list corresponds to local position in the quad.
const uint8_t metadata_check_unmask[] = {
    254,
    253,
    251,
    247,
};

// Lookup table for mask of exist bit of a position in a quad. Position in
// the list corresponds to local position in the quad.
const uint8_t metadata_exist_mask[] = {
    16,
    32,
    64,
    128,
};

// Lookup table for mask of all bits except exist bit of a position in a quad.
// Position in the list corresponds to local position in the quad.
const uint8_t metadata_exist_unmask[] = {
    239,
    223,
    191,
    127,
};

// Represents a node in a quadtree.
typedef struct Quad
{
    // Value indicating the level of the quad. Leaf level is 0.
    uint8_t level;

    // Position.
    uint32_t x;
    uint32_t y;

    // 8 bits representing metadata. Lower four bits are for indicating change
    // in sub_quads. Upper four bits are for indicating existence of sub_quads.
    uint8_t metadata;

    // Pointers to subquads. If level = 1, points to a leaf. Otherwise, points
    // to other quad instances.
    void **sub_quads;

    // The quad containing the quad, or NULL if quad is top layer.
    struct Quad *parent;

    // Local position of the quad in its parent.
    uint8_t pos_in_parent;

    // SpinLock for reading and writing to data of quad, used for blocking
    // access by other threads.
    SDL_SpinLock read_lock;
} Quad;

// Initializes a new quad instance.
Quad *quad_init(uint32_t, uint32_t, uint8_t, Quad *);

// Sets the checkbit in the metadata of the sub quad at the given position to
// the given value.
void quad_set_check(Quad *, int, int);

// Gets the checkbit in the metadata of the parent quad representing the given
// quad.
int quad_get_check(Quad *);

// Sets sub quad at given position. Adjusts metadata accordingly.
void quad_set_sub_quad(Quad *, void *, int);

// Frees all memory associated with the quad.
void quad_deinit(Quad *quad);