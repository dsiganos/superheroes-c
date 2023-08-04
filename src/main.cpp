#include <stdio.h>
#include <assert.h>

#include "character.h"

character_t characters[] =
{
    {"Batman", 8.3, "hero"},
    {"Joker", 8.2, "villain"}
};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("too few args\n");
        return 1;
    }

    hero_t *hero = (hero_t *) (&characters[0]);
    villain_t *villain = (villain_t *) (&characters[1]);
    character_t *result = do_battle(hero, villain);
    printf("winner: %s\n", result->name);
   
    return 0;
}
