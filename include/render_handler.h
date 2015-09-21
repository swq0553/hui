#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H

#include "cef_render_handler.h"

namespace HUI {

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
            virtual void Draw(void);
        protected:
            unsigned int width;
            unsigned int height;
            int paint_width;
            int paint_height;
            unsigned char *paint_buffer;

            IMPLEMENT_REFCOUNTING(RenderHandler);
    };

}

#endif
