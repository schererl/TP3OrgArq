#include <map>
#include <string>
using namespace std;

static map<string, string> memoria =
{
    {"0x00400000", "la $t1, 0($t2)"},
    {"0x00400001", "lw $t7, 0($t5)"},
    {"0x00400002", "addu $t1, $t4, $t5"},
    {"0x00400003", "move $t1, $t2"},
    {"0x00400004", "sll $t1, 2"},
    {"0x00400005", "beq $t1, $t2, $t3"},
    {"0x00400006", "bne $t1, $t5, $56"},
};
