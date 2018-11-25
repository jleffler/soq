#ifndef CACHE_READER_H_INCLUDED
#define CACHE_READER_H_INCLUDED

typedef struct cr_file cr_file;

extern cr_file *cr_open(char *filename, int buffersize);
extern void cr_close(cr_file *f);
extern int cr_read_byte(cr_file *f);

#endif /* CACHE_READER_H_INCLUDED */
