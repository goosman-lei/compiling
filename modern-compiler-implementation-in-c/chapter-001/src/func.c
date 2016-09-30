#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "func.h"

static void parse_error(const char *msg, ...);
static void dump_code(const char *msg, ...);
static int parse_exp(A_exp e);
static void parse_expList(A_expList el, int print);

void parse_stmt(A_stm s) {
    int rightV;
    switch (s->kind) {
        case A_compoundStm:
            parse_stmt(s->u.compound.stm1);
            dump_code(" ; ");
            parse_stmt(s->u.compound.stm2);
            break;
        case A_assignStm:
            dump_code("%s := ", s->u.assign.id);
            rightV = parse_exp(s->u.assign.exp);
            ns_set(s->u.assign.id, rightV);
            break;
        case A_printStm:
            dump_code("print(");
            parse_expList(s->u.print.exps, 1);
            dump_code(")");
            break;
        default:
            parse_error("unknown statement kind: %d\n", s->kind);
    }
}

static int parse_exp(A_exp e) {
    int leftV;
    int rightV;
    switch (e->kind) {
        case A_idExp:
            dump_code("%s", e->u.id);
            return ns_get(e->u.id);
        case A_numExp:
            dump_code("%d", e->u.num);
            return e->u.num;
        case A_opExp:
            leftV = parse_exp(e->u.op.left);
            switch (e->u.op.oper) {
                case A_plus:
                    dump_code(" + ");
                    break;
                case A_minus:
                    dump_code(" - ");
                    break;
                case A_times:
                    dump_code(" * ");
                    break;
                case A_div:
                    dump_code(" / ");
                    break;
                default:
                    parse_error("unknown op type: %d\n", e->u.op.oper);
            }
            rightV = parse_exp(e->u.op.right);
            switch (e->u.op.oper) {
                case A_plus:
                    return leftV + rightV;
                case A_minus:
                    return leftV - rightV;
                case A_times:
                    return leftV * rightV;
                case A_div:
                    return leftV / rightV;
            }
            break;
        case A_eseqExp:
            dump_code("(");
            parse_stmt(e->u.eseq.stm);
            dump_code(", ");
            rightV = parse_exp(e->u.eseq.exp);
            dump_code(")");
            return rightV;
        default:
            parse_error("unknown exp kind: %d\n", e->kind);
    }
}

static void parse_expList(A_expList el, int print) {
    int rightV;
    switch (el->kind) {
        case A_pairExpList:
            rightV = parse_exp(el->u.pair.head);
            dump_code(", ");
            if (print) {
                printf("%d\n", rightV);
            }
            parse_expList(el->u.pair.tail, print);
            break;
        case A_lastExpList:
            rightV = parse_exp(el->u.last);
            if (print) {
                printf("%d\n", rightV);
            }
            break;
        default:
            parse_error("unknown expList kind: %d\n", el->kind);
    }
}

static void dump_code(const char *msg, ...) {
    return ;
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
}

static void parse_error(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    exit(1);
}
