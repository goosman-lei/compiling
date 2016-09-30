#include "slp.h"

// a := 5 + 3 ; b := (print(a, a - 1), 10 * 1) ; print(b);
A_stm prog(void) {
    return A_CompoundStm(
        A_AssignStm("a", A_OpExp(                                                   // a := 5 + 3;
            A_NumExp(5),
            A_plus,
            A_NumExp(3))
        ),
        A_CompoundStm(
            A_AssignStm("b", A_EseqExp(                                             // b := (print(a, a-1), 10 * a);
                A_PrintStm(A_PairExpList(                                           // print(a, a - 1)
                    A_IdExp("a"),
                    A_LastExpList(A_OpExp(A_IdExp("a"), A_minus, A_NumExp(1)))
                )),
                A_OpExp(A_NumExp(10), A_times, A_IdExp("a"))                        // 10 * a
            )),
            A_PrintStm(A_LastExpList(A_IdExp("b")))                                 // print(b);
        )
    );
}
