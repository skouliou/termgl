#include "termgl.h"

void set_pxl(struct tgl_rgb_s *pxl, uint8_t r, uint8_t g, uint8_t b)
{
    pxl->r = r;
    pxl->g = g;
    pxl->b = b;
}

void set_red   (struct tgl_rgb_s *pxl) { set_pxl(pxl, 255, 0, 0); }
void set_green (struct tgl_rgb_s *pxl) { set_pxl(pxl, 0, 255, 0); }
void set_blue  (struct tgl_rgb_s *pxl) { set_pxl(pxl, 0, 0, 255); }
void set_black (struct tgl_rgb_s *pxl) { set_pxl(pxl, 0, 0, 0); }
void set_white (struct tgl_rgb_s *pxl) { set_pxl(pxl, 255, 255, 255); }

int main (int argc, char *argv[argc])
{
    struct tgl_framebuffer_s *buf = tgl_framebuffer_new (40, 30);

    tgl_framebuffer_map (buf, set_black);
    tgl_line (buf, 0, 0, 10, 10, (struct tgl_rgb_s){255, 0, 0});
    tgl_line (buf, 10, 0, 0, 10, (struct tgl_rgb_s){255, 0, 0});
    tgl_line (buf, 20, 20, 30, 5, (struct tgl_rgb_s){255, 0, 0});
    tgl_framebuffer_draw (buf);

    tgl_framebuffer_delete (buf);
    return 0;
}