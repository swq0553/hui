#include <iostream>
#include <fstream>
#include "include/render_handler.h"

RenderHandler::RenderHandler(void) {
    width = 1280;
    height = 720;
    paint_width = 1280;
    paint_height = 720;
    paint_buffer = new unsigned char[paint_width * paint_height * 4];
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
    if (_paint_width != paint_width || _paint_height != paint_height) {
        // NOTE: Crashes if it makes it in here for some reason!
        if (paint_buffer != nullptr) {
            delete paint_buffer;
        }
        paint_buffer = new unsigned char[paint_width * paint_height * 4];
    }
    paint_width = _paint_width;
    paint_height = _paint_height;
    memcpy(paint_buffer, _paint_buffer, sizeof(unsigned char) * paint_width * paint_height * 4);
    Draw();
}

void RenderHandler::Draw(void) {
    std::cout << "Drawing Here?" << std::endl;
}
