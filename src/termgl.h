#ifndef __TERMGL_H__
#define __TERMGL_H__

#include <stdint.h>     // uint8_t

struct tgl_rgb_s {
    uint16_t r, g, b;
};

struct tgl_framebuffer_s {
    uint8_t width, hight;
    struct tgl_rgb_s *buffer;
};

typedef void (tgl_pxl_shader_f)(struct tgl_rgb_s *);

struct tgl_framebuffer_s *
tgl_framebuffer_new (uint16_t width, uint16_t hight);

void
tgl_framebuffer_delete (struct tgl_framebuffer_s *fbuffer);

void
tgl_framebuffer_set (struct tgl_framebuffer_s *fbuffer, uint16_t x, uint16_t y,
                     struct tgl_rgb_s rgb_val);

void
tgl_framebuffer_draw (struct tgl_framebuffer_s *fbuffer);

void
tgl_framebuffer_map (struct tgl_framebuffer_s * pxlbuffer, tgl_pxl_shader_f f);

void
tgl_line (struct tgl_framebuffer_s *pxlbuffer,
             int x0, int y0, int x1, int y1, struct tgl_rgb_s color);

#endif // __TERMGL_H__