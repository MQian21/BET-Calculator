#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "bet.h"

// === BET NODES =============================================================

struct bnode
{
    struct bnode *left;
    struct bnode *right;
    char op_val;
};

// bnode_read() reads a single expression from input.
// time: O(n)
static struct bnode *bnode_read(void)
{
    char c = ' ';
    if (scanf(" %c", &c) != 1)
    {
        return NULL;
    }
    if (c == ')')
    {
        return bnode_read();
    }

    struct bnode *bn = malloc(sizeof(struct bnode));

    if (c == '(')
    {
        (scanf(" %c", &c));
        bn->op_val = c;
        bn->left = bnode_read();
        bn->right = bnode_read();
    }
    else
    {
        bn->op_val = c;
        bn->left = NULL;
        bn->right = NULL;
    }
    return bn;
}

// bnode_destroy(bn) releases all resources allocated by bnode bn.
// time: O(n)
static void bnode_destroy(struct bnode *bn)
{
    if (bn != NULL)
    {
        bnode_destroy(bn->left);
        bnode_destroy(bn->right);
    }
    free(bn);
}

// bnode_evaluate(bn) evaluates the value of bnode bn.
// time: O(n)
static int bnode_evaluate(const struct bnode *bn)
{
    int convert_num = 0;
    if (bn != NULL)
    {
        if ((bn->op_val >= 48) && (bn->op_val <= 57))
        {
            convert_num = bn->op_val - '0';
        }
        else if (bn->op_val == '+')
        {
            int num1 = bnode_evaluate(bn->left);
            int num2 = bnode_evaluate(bn->right);
            return num1 + num2;
        }
        else if (bn->op_val == '*')
        {
            int num1 = bnode_evaluate(bn->left);
            int num2 = bnode_evaluate(bn->right);
            return num1 * num2;
        }
    }
    return convert_num;
}

// === BINARY EXPRESSION TREE ================================================

// See bet.h for documentation.
struct bet
{
    struct bnode *root;
};

// See bet.h for documentation.
struct bet *bet_read(void)
{
    struct bet *bet = NULL;
    struct bnode *root = bnode_read();
    if (root != NULL)
    {
        bet = malloc(sizeof(struct bet));
        bet->root = root;
    }
    return bet;
}

// See bet.h for documentation.
void bet_destroy(struct bet *bet)
{
    assert(bet);
    assert(bet->root);
    bnode_destroy(bet->root);
    free(bet);
}

// See bet.h for documentation.
int bet_evaluate(const struct bet *bet)
{
    assert(bet);
    assert(bet->root);
    return bnode_evaluate(bet->root);
}