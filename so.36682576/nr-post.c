void printPostOrderIterative(BSTNode *root)
{
    BSTNode *cur;
    Stack s;
    s.top = NULL;
    Stack output;
    output.top = NULL;

    if (!root) {
        return;
    }


    push(&s, root);

    while (isEmpty(&s) != 1 ) {
        cur = s.top;
        push(&output,cur);
        pop(&s);
        if (cur->left){
            push(&s, cur->left);
        }
        if (cur->right){
            push(&s, cur->right);
        }
    }
    while (isEmpty(&output) != 1) {
        printf("%d", output.top);
        pop(&output);
    }
}

