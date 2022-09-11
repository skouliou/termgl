#include <stdint.h>         // uint16_t
#include <string.h>         // memcpy()
#include <stdlib.h>         // malloc(), calloc(), free(), abs(), rand()
#include <stdio.h>          // printf()

#include "termgl.h"
#include "util.h"

struct tgl_framebuffer_s *
tgl_framebuffer_new (uint16_t width, uint16_t hight)
{
    struct tgl_framebuffer_s * fbuffer = (struct tgl_framebuffer_s *)malloc(sizeof(*fbuffer));

    // allocation failed
    if (fbuffer == NULL)
        goto exit_fail;

    // setting struct fields
    fbuffer->hight = hight;
    fbuffer->width = width;
    fbuffer->buffer = (struct tgl_rgb_s *)calloc(hight * width, sizeof(struct tgl_rgb_s));

    // buffer allocation failed
    if (fbuffer->buffer == NULL)
        goto exit_fail_cleanup;

    return fbuffer;

exit_fail_cleanup:
    free (fbuffer);
exit_fail:
    return NULL;
}

void
tgl_framebuffer_delete (struct tgl_framebuffer_s *fbuffer)
{
    if (fbuffer == NULL) return;
    if (fbuffer->buffer != NULL) free (fbuffer->buffer);
    free (fbuffer);
}

void
tgl_framebuffer_set(struct tgl_framebuffer_s *fbuffer,
                     uint16_t x, uint16_t y,
                     struct tgl_rgb_s rgb_val)
{
    // todo: raise an error?
    if (x >= fbuffer->width && y >= fbuffer->hight)
        return;
    
    // todo: buffer could be null causing SEGFAULT
    memcpy(fbuffer->buffer + (y * fbuffer->hight) + x, &rgb_val, sizeof(struct tgl_rgb_s));
}


void
tgl_framebuffer_draw(struct tgl_framebuffer_s *fbuffer)
{
    struct tgl_rgb_s *iter;
    for (int y = 0, base = 0; y < fbuffer->hight; ++y)
    {
        for (int x = 0; x < fbuffer->width; ++x)
        {
            iter = fbuffer->buffer + base + x;
            printf("\033[48:2:%d:%d:%dm  ", iter->r, iter->g, iter->b, x, y);
        }
        putchar('\n');
        base += fbuffer->hight;
    }
}

void
tgl_framebuffer_map (struct tgl_framebuffer_s * fbuffer, tgl_pxl_shader_f f)
{
    // todo: validate arguments
    uint32_t pxl_count = fbuffer->hight * fbuffer->width;
    struct tgl_rgb_s *first = fbuffer->buffer,
                      *last = first + pxl_count;
    while (first != last)
    {
        f(first);
        ++first;
    }
}

void
tgl_line (struct tgl_framebuffer_s *fbuffer,
             int x0, int y0, int x1, int y1, struct tgl_rgb_s color)
{
    int x, y;
    for (float t = 0; t < 1; t += 0.03)
    {
        x = x0 + (x1 - x0) * t;
        y = y0 + (y1 - y0) * t;
        tgl_framebuffer_set(fbuffer, x, y, color);
    }
}
