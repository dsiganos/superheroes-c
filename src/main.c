#include "./battle.h"

int main(int argc, char *argv[]) {
    print_args(argc, argv);

    char* winner;

    winner = battle(argv[1], argv[2]);

    printf("The winner is ... %s\n", winner);
}