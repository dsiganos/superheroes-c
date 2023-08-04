#include <gtest/gtest.h>

#include "character.h"

TEST(battle, hero_wins)
{
    character_t hero {"Batman", 8.3, "hero"};
    character_t villain = {"Joker", 8.2, "villain"};
    EXPECT_EQ(do_battle((hero_t *) &hero, (villain_t *) &villain), &hero);
    EXPECT_NE(do_battle((hero_t *) &hero, (villain_t *) &villain), &villain);
}

TEST(battle, hero_wins_equality)
{
    character_t hero {"Batman", 8.3, "hero"};
    character_t villain = {"Joker", 8.3, "villain"};
    EXPECT_EQ(do_battle((hero_t *) &hero, (villain_t *) &villain), &hero);
    EXPECT_NE(do_battle((hero_t *) &hero, (villain_t *) &villain), &villain);
}

TEST(battle, villain_wins)
{
    character_t hero {"Batman", 8.3, "hero"};
    character_t villain = {"Joker", 8.4, "villain"};
    EXPECT_EQ(do_battle((hero_t *) &hero, (villain_t *) &villain), &villain);
    EXPECT_NE(do_battle((hero_t *) &hero, (villain_t *) &villain), &hero);
}

TEST(battle, negatives)
{
    character_t hero {"Batman", -8.3, "hero"};
    character_t villain = {"Joker", -8.2, "villain"};
    EXPECT_EQ(do_battle((hero_t *) &hero, (villain_t *) &villain), &villain);
    EXPECT_NE(do_battle((hero_t *) &hero, (villain_t *) &villain), &hero);
}
