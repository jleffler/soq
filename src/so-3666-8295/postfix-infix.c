/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Postfix to infix expression conversion
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "stderr.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char optstr[] = "hV";
static const char usestr[] = "[-hV] expression [expression...]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

/*
** SO 36668295
** Convert postfix expressions with single digit numbers into infix expressions.
*/

typedef struct Stack
{
    size_t     tos;
    size_t     size;
    char     **stack;
} Stack;

#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_postfix_infix_c[];
const char jlss_id_postfix_infix_c[] = "@(#)$Id$";
#endif /* lint */

static void stack_init(Stack *stack)
{
    stack->tos = 0;
    stack->size = 0;
    stack->stack = 0;
}

static void stack_push_str(Stack *stack, const char *str)
{
    if (stack->tos == stack->size)
    {
        size_t n_size = (stack->size + 2) * 2;
        void  *n_data = realloc(stack->stack, n_size * sizeof(*stack->stack));
        if (n_data == 0)
            err_syserr("out of memory\n");
        stack->size = n_size;
        stack->stack = n_data;
    }
    stack->stack[stack->tos] = strdup(str);
    if (stack->stack[stack->tos] == 0)
        err_syserr("out of memory\n");
    stack->tos++;
}

static void stack_push_chr(Stack *stack, char c)
{
    char str[2] = { c, '\0' };
    stack_push_str(stack, str);
}

static char *stack_pop(Stack *stack)
{
    if (stack->tos == 0)
        err_error("Pop on empty stack\n");
    return(stack->stack[--stack->tos]);
}

static void stack_free(Stack *stack)
{
    for (size_t i = 0; i < stack->tos; i++)
        free(stack->stack[i]);
    free(stack->stack);
}

#undef is_operator
static bool is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

static void postfix_infix(const char *postfix)
{
    assert(postfix != 0);
    printf("Postfix expression: %s\n", postfix);
    char c;
    bool valid = true;
    Stack stack;

    stack_init(&stack);
    while ((c = *postfix++) != '\0')
    {
        if (isdigit(c))
            stack_push_chr(&stack, c);
        else if (is_operator(c))
        {
            char *rhs = stack_pop(&stack);
            char *lhs = stack_pop(&stack);
            size_t l_rhs = strlen(rhs);
            size_t l_lhs = strlen(lhs);
            char expr[l_lhs + l_rhs + sizeof("()*()")];
            snprintf(expr, sizeof(expr), "%s%s%s%c%s%s%s",
                    (l_lhs > 1) ? "(" : "", lhs, (l_lhs > 1) ? ")" : "", c,
                    (l_rhs > 1) ? "(" : "", rhs, (l_rhs > 1) ? ")" : "");
            stack_push_str(&stack, expr);
            free(lhs);
            free(rhs);
        }
        else if (isspace(c))
            continue;
        else
        {
            err_remark("Invalid character %c (0x%.2X) found\n", c, c);
            valid = false;
            break;
        }
    }

    if (valid)
    {
        if (stack.tos != 1)
            err_remark("Stack has wrong number of entries (%zu instead of 1)\n", stack.tos);
        else
        {
            char *infix = stack_pop(&stack);
            printf("Infix expression: %s\n", infix);
            free(infix);
        }
    }
    stack_free(&stack);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("PROG", &"@(#)$Revision$ ($Date$)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    for (int i = optind; i < argc; i++)
        postfix_infix(argv[i]);

    return 0;
}
