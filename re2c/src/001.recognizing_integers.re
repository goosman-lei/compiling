#include <stdio.h>

static const char *lex(const char *YYCURSOR) {
    const char *YYMARKER;       // YYMARKER是必须的, 因为规则可能重叠: 它会保存最长成功匹配的输入位置.
                                // 比如, 我们有两个重叠的规则"a"和"abc", 输入字符串是"abd".
                                //      在匹配完字符"a"之后, 仍然有机会匹配到"abc"
                                //      但是, 当分析器扫描到字符"d"的时候, 它就必须回溯.

    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;     // 哨兵是一个不会在正常输入中出现的特殊字符.
                                // 它出现在输入的结尾处, 作为词法分析器的扫描停止标记
                                // 在这个Case中, 哨兵字符是NULL.
                                // 所有参数都以NULL字符终止, 并且参数中不会出现NULL字符.
                                // 当词法分析器扫描到NULL字符, 就会停止读取.
                                // 注意: 这里我们并不会对输入做任何假定, 可以包括任何字符.
                                //      但是, 我们需要确保哨兵字符不能在规则中出现

    end = "\x00";
    bin = '0b' [01]+;
    oct = "0" [0-7]*;
    dec = [1-9][0-9]*;
    hex = '0x' [0-9a-fA-F]+;

    *       { return "err"; }   // 默认Case.
                                // 一定要有*描述的默认规则, 否则词法分析器可能产生未定义行为.
                                // 使用-Wundefined-control-flow可以在没有默认规则时, 让re2c显示没有覆盖的输入case
    bin end { return "bin"; }
    oct end { return "oct"; }
    dec end { return "dec"; }
    hex end { return "hex"; }
     */
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i ++) {
        printf("%s: %s\n", lex(argv[i]), argv[i]);
    }
    return 0;
}