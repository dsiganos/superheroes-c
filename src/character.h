typedef struct character
{
    const char *name;
    float score;
    const char *type;
    //const char *weakness;
} character_t;

typedef struct
{
    character_t c;
} hero_t;

typedef struct
{
    character_t c;
} villain_t;

character_t *do_battle(hero_t *hero, villain_t *villain);
