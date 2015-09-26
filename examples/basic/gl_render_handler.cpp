#include "gl_render_handler.h"

#include <iostream>

// GLRenderHandler::GLRenderHandler(void) : RenderHandler() {
//     glGenTextures(1, &texture_handle);
// }
//
// GLRenderHandler::~GLRenderHandler(void) {
//     //
// }
//
// void GLRenderHandler::Draw(void) {
//     glEnable(GL_TEXTURE_2D);
//     glBindTexture(GL_TEXTURE_2D, texture_handle);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, paint_width, paint_height,
//         0, GL_RGBA, GL_UNSIGNED_BYTE, paint_buffer);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// //    glBindTexture(GL_TEXTURE_2D, 0);
//
// //    std::cout << "Drawing " << paint_width << ", " << paint_height << std::endl;
// //    sf::Image out;
// //    out.create(paint_width, paint_height, paint_buffer);
// //    out.saveToFile("output.png");
// }
//
// GLuint GLRenderHandler::GetTextureHandle(void) {
//     return texture_handle;
// }
