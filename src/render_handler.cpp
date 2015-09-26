#include <iostream>
#include <fstream>
#include "hui/render_handler.h"

namespace HUI {

    RenderHandler::RenderHandler(void) {
        width = 800;
        height = 500;
        paint_width = 800;
        paint_height = 500;
        paint_buffer = nullptr;
        is_dirty = false;
    }

    void RenderHandler::Reshape(unsigned int _width, unsigned int _height) {
        width = _width;
        height = _height;
    }

    bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
        rect = CefRect(0, 0, width, height);
        return true;
    }

    void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
                                PaintElementType type,
                                const RectList &dirty_rects,
                                const void* _paint_buffer,
                                int _paint_width,
                                int _paint_height) {
        paint_width = _paint_width;
        paint_height = _paint_height;
        paint_buffer = static_cast<unsigned char *>(const_cast<void *>(_paint_buffer));
        is_dirty = true;
    }

    unsigned int RenderHandler::GetWidth(void) {
        return width;
    }

    unsigned int RenderHandler::GetHeight(void) {
        return height;
    }

    int RenderHandler::GetPaintWidth(void) {
        return paint_width;
    }

    int RenderHandler::GetPaintHeight(void) {
        return paint_height;
    }

    unsigned char *RenderHandler::GetPaintBuffer(void) {
        return paint_buffer;
    }

    bool HUI::RenderHandler::IsDirty(void) {
        if (is_dirty) {
            is_dirty = false;
            return true;
        }
        return false;
    }


}
