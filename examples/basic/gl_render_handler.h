#ifndef GL_RENDER_HANDLER_H
#define GL_RENDER_HANDLER_H

#include "include/render_handler.h"

class GLRenderHandler : public RenderHandler {
public:
    GLRenderHandler(void);
    ~GLRenderHandler(void);

    void Draw(void);
    GLuint GetTextureHandle(void);

private:
    GLuint texture_handle;
};

#endif // GL_RENDER_HANDLER_H
