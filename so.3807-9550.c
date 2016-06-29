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

static inline void changePos(Link** anchor_link, char* name1, int pos)
{
    assert(anchor_link != 0);
    assert(name1 != 0);
    assert(pos >= 0);
}

static void print_list(Link *root)
{
    const char *pad = "";
    while (root != 0)
    {
        printf("%s[%s]", pad, root->frame->name);
        root = root->next;
        pad = " -> ";
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

int main(void)
{
    Frame frames[] =
    {
        { "pic0", 0 },
        { "pic1", 1 },
        { "pic2", 2 },
        { "pic3", 3 },
    };
    enum { NUM_FRAMES = sizeof(frames) / sizeof(frames[0]) };

    for (int i = 0; i < NUM_FRAMES; i++)
    {
        for (int j = 0; j < NUM_FRAMES; j++)
        {
            Link *head = 0;
            Link *tail = 0;
            for (int k = 0; k < NUM_FRAMES; k++)
            {
                Link *link = make_link(frames[k].name, frames[k].duration);
                if (head == 0)
                    head = link;
                if (tail != 0)
                    tail->next = link;
                tail = link;
            }
            print_list(head);
            printf(" == %s to %u == ", frames[i].name, j);
            changePos(&head, frames[i].name, j);
            print_list(head);
            putchar('\n');

            free_link(head);
        }
    }
	return 0;
}
