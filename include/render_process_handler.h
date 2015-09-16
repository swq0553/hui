#ifndef RENDER_PROCESS_HANDLER_H
#define RENDER_PROCESS_HANDLER_H

#include "cef_render_process_handler.h"

class RenderProcessHandler : public CefRenderProcessHandler {
    public:
        RenderProcessHandler(void);
        void OnContextCreated(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefV8Context> context);
    private:
        //

        IMPLEMENT_REFCOUNTING(RenderProcessHandler);
};

#endif
