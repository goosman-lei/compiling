#include <stdio.h>
#include "prog.h"


int main(int argc, char **argv) {
    A_stm p = prog();

    ns_init();

    parse_stmt(p);
}
