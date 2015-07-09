#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "cef_render_handler.h"

class RenderHandler : public CefRenderHandler {
  public:
    RenderHandler(void);

    void Reshape(unsigned int _width, unsigned int _height);
    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
    void OnPaint(CefRefPtr<CefBrowser> browser,
                 PaintElementType type,
                 const RectList &dirty_rects,
                 const void *_paint_buffer,
                 int _paint_width,
                 int _paint_height);
    void Draw(void);

  protected:
    unsigned int width;
    unsigned int height;
    int paint_width;
    int paint_height;
    unsigned char *paint_buffer;

  private:
    IMPLEMENT_REFCOUNTING(RenderHandler);
};

#endif
