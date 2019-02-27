#include "posixver.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Frame
{
    char* name;
    unsigned int duration;
};

typedef struct Frame Frame;

struct Link
{
    Frame *frame;
    struct Link *next;
};

typedef struct Link Link;

static void print_list(Link *root);

static void changePos(Link **anchor_link, const char *name, int pos)
{
    assert(anchor_link != 0 && name != 0 && pos >= 0);
    Link *root = *anchor_link;
    Link *link = root;
    Link *prev = 0;
    int count = 1;
    while (link != 0 && strcmp(link->frame->name, name) != 0)
    {
        prev = link;
        link = link->next;
        count++;
    }
    if (link == 0)      // Name not found - no swap!
        return;
    if (count == pos)   // Already in target position - no swap
        return;
    if (count == 1)     // Moving first item; update root
    {
        assert(link == root);
        *anchor_link = root->next;
        root = *anchor_link;
    }
    else
    {
        assert(prev != 0);
        prev->next = link->next;
    }
    // link is detached; now where does it go?
    if (pos == 1)       // Move to start; update root
    {
        link->next = root;
        *anchor_link = link;
        return;
    }
    Link *node = root;
    for (int i = 1; i < pos - 1 && node->next != 0; i++)
        node = node->next;
    link->next = node->next;
    node->next = link;
}

static void print_list(Link *root)
{
    const char *pad = "";
    while (root != 0)
    {
        printf("%s[%s]", pad, root->frame->name);
        root = root->next;
        pad = "->";
    }
}

static void free_frame(Frame *frame)
{
    if (frame != 0)
    {
        free(frame->name);
        free(frame);
    }
}

static void free_link(Link *link)
{
    while (link != 0)
    {
        Link *next = link->next;
        free_frame(link->frame);
        free(link);
        link = next;
    }
}

static Frame *make_frame(const char *name, unsigned int number)
{
    Frame *frame = malloc(sizeof(*frame));
    if (frame != 0)
    {
        frame->name = strdup(name);
        frame->duration = number;
    }
    return frame;
}

static Link *make_link(const char *name, unsigned int number)
{
    Link *link = malloc(sizeof(*link));
    if (link != 0)
    {
        link->frame = make_frame(name, number);
        link->next = 0;
    }
    return link;
}

static Link *make_list(int num, Frame *frames)
{
    Link *head = 0;
    Link *tail = 0;
    for (int k = 0; k < num; k++)
    {
        Link *link = make_link(frames[k].name, frames[k].duration);
        assert(link != 0 && link->frame != 0);  // Lazy!
        if (head == 0)
            head = link;
        if (tail != 0)
            tail->next = link;
        tail = link;
    }
    return head;
}

int main(void)
{
    Frame frames[] =
    {
        { "pic1", 0 },
        { "pic2", 1 },
        { "pic3", 2 },
        { "pic4", 3 },
        { "pic5", 4 },      // Never in the list, but searched for
    };
    enum { NUM_FRAMES = sizeof(frames) / sizeof(frames[0]) };

    for (int i = 0; i < NUM_FRAMES; i++)
    {
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            Link *head = make_list(NUM_FRAMES - 1, frames);
            print_list(head);
            printf(" == %s to %u == ", frames[i].name, j + 1);
            changePos(&head, frames[i].name, j + 1);
            print_list(head);
            putchar('\n');
            free_link(head);
        }
    }

    return 0;
}
