#ifndef __TERMGL_H__
#define  __TERMGL_H__

#include <stdint.h>         // uint16_t
#include <string.h>         // memcpy()
#include <stdlib.h>         // malloc(), calloc(), free()
#include <stdio.h>          // printf()

struct termgl_pxl
{
    uint16_t r, g, b;
};

struct termgl_pxlbuffer
{
    uint16_t width, hight;
    struct termgl_pxl *buffer;
};

struct termgl_pxlbuffer *
termgl_pxlbuffer_new (uint16_t width, uint16_t hight)
{
    struct termgl_pxlbuffer * pxlbuffer = (struct termgl_pxlbuffer *)malloc(sizeof(struct termgl_pxlbuffer));

    // allocation failed
    if (pxlbuffer == NULL)
        goto exit_fail;

    // setting struct fields
    pxlbuffer->hight = hight;
    pxlbuffer->width = width;
    pxlbuffer->buffer = (struct termgl_pxl *)calloc(hight * width, sizeof(struct termgl_pxl));

    // buffer allocation failed
    if (pxlbuffer->buffer == NULL)
        goto exit_fail_cleanup;

    return pxlbuffer;

exit_fail_cleanup:
    free (pxlbuffer);
exit_fail:
    return NULL;
}

void
termgl_pxlbuffer_delete (struct termgl_pxlbuffer *pxlbuffer)
{
    if (pxlbuffer == NULL) return;
    if (pxlbuffer->buffer != NULL) free (pxlbuffer->buffer);
    free (pxlbuffer);
}

void
termgl_pxlbuffer_set(struct termgl_pxlbuffer *pxlbuffer,
                     uint16_t x, uint16_t y,
                     struct termgl_pxl pxl)
{
    // todo: raise an error?
    if (x >= pxlbuffer->width && y >= pxlbuffer->hight)
        return;
    
    // todo: buffer could be null causing SEGFAULT
    memcpy(pxlbuffer->buffer + (x * pxlbuffer->width) + y, &pxl, sizeof(struct termgl_pxl));
}


void
termgl_pxlbuffer_draw(struct termgl_pxlbuffer *pxlbuffer)
{
    struct termgl_pxl *iter;
    for (int y = 0, base = 0; y < pxlbuffer->hight; ++y)
    {
        for (int x = 0; x < pxlbuffer->width; ++x)
        {
            iter = pxlbuffer->buffer + base + y;
            printf("\033[48:2:%d:%d:%dm  ", iter->r, iter->g, iter->b);
        }
        putchar('\n');
        base += pxlbuffer->hight;
    }
}

typedef void (*termgl_pxlfunc)(struct termgl_pxl *) ;
void
termgl_pxlbuffer_map(struct termgl_pxlbuffer * pxlbuffer, termgl_pxlfunc f)
{
    // todo: validate arguments
    uint32_t pxl_count = pxlbuffer->hight * pxlbuffer->width;
    struct termgl_pxl *first = pxlbuffer->buffer,
                      *last = first + pxl_count;
    while (first != last)
    {
        f(first);
        ++first;
    }
}

#endif // __TERMGL_H__