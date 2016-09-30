#include <stdio.h>
#include "prog.h"


int main(int argc, char **argv) {
    A_stm p = prog();

    parse_stmt(p);

    printf("\n");
}
