#include "character.h"
#include <assert.h>

// return the character that wins
character_t *do_battle(hero_t *hero, villain_t *villain)
{
    assert(hero);
    assert(villain);
    if (hero->c.score >= villain->c.score)
    {
        return &hero->c;
    }
    return &villain->c;
}
