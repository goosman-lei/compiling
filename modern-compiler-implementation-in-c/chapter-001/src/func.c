#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "func.h"

static void parse_error(const char *msg, ...);
static void parse_exp(A_exp e);
static void parse_expList(A_expList el);

void parse_stmt(A_stm s) {
    switch (s->kind) {
        case A_compoundStm:
            parse_stmt(s->u.compound.stm1);
            printf(" ; ");
            parse_stmt(s->u.compound.stm2);
            break;
        case A_assignStm:
            printf("%s := ", s->u.assign.id);
            parse_exp(s->u.assign.exp);
            break;
        case A_printStm:
            printf("print(");
            parse_expList(s->u.print.exps);
            printf(")");
            break;
        default:
            parse_error("unknown statement kind: %d\n", s->kind);
    }
}

static void parse_exp(A_exp e) {
    switch (e->kind) {
        case A_idExp:
            printf("%s", e->u.id);
            break;
        case A_numExp:
            printf("%d", e->u.num);
            break;
        case A_opExp:
            parse_exp(e->u.op.left);
            switch (e->u.op.oper) {
                case A_plus:
                    printf(" + ");
                    break;
                case A_minus:
                    printf(" - ");
                    break;
                case A_times:
                    printf(" * ");
                    break;
                case A_div:
                    printf(" / ");
                    break;
                default:
                    parse_error("unknown op type: %d\n", e->u.op.oper);
            }
            parse_exp(e->u.op.right);
            break;
        case A_eseqExp:
            printf("(");
            parse_stmt(e->u.eseq.stm);
            printf(", ");
            parse_exp(e->u.eseq.exp);
            printf(")");
            break;
        default:
            parse_error("unknown exp kind: %d\n", e->kind);
    }
}

static void parse_expList(A_expList el) {
    switch (el->kind) {
        case A_pairExpList:
            parse_exp(el->u.pair.head);
            printf(", ");
            parse_expList(el->u.pair.tail);
            break;
        case A_lastExpList:
            parse_exp(el->u.last);
            break;
        default:
            parse_error("unknown expList kind: %d\n", el->kind);
    }
}

static void parse_error(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    exit(1);
}
