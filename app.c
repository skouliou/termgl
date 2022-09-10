#include "termgl.h"

void set_pxl(struct termgl_pxl *pxl, uint8_t r, uint8_t g, uint8_t b)
{
    pxl->r = r;
    pxl->g = g;
    pxl->b = b;
}

void set_red   (struct termgl_pxl *pxl) { set_pxl(pxl, 255, 0, 0); }
void set_green (struct termgl_pxl *pxl) { set_pxl(pxl, 0, 255, 0); }
void set_blue  (struct termgl_pxl *pxl) { set_pxl(pxl, 0, 0, 255); }
void set_black (struct termgl_pxl *pxl) { set_pxl(pxl, 0, 0, 0); }
void set_white (struct termgl_pxl *pxl) { set_pxl(pxl, 255, 255, 255); }

int main (int argc, char *argv[argc])
{
    struct termgl_pxlbuffer *buf = termgl_pxlbuffer_new(40, 30);

    termgl_pxlbuffer_map(buf, set_black);
    termgl_pxlbuffer_draw(buf);

    termgl_pxlbuffer_delete (buf);
    return 0;
}