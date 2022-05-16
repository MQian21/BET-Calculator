#include <stdio.h>
#include "bet.h"

// The input file for the IO test client consist of
//   one or more expressions [exp]:
//
//   a [exp] is a    [value]
//                   ([op] [exp] [exp])
//   a [op] is a     *
//                   +
//   a [value] is a  1
//                   2
//                  ...
//                   9
int main(void)
{
    struct bet *expr_tree = NULL;
    while ((expr_tree = bet_read()) != NULL)
    {
        printf("The BET evaluates to %d.\n", bet_evaluate(expr_tree));
        bet_destroy(expr_tree);
    }
}