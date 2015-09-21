#ifndef RENDER_PROCESS_HANDLER_H
#define RENDER_PROCESS_HANDLER_H

#include <unordered_map>
#include "js_value.h"

#include "cef_render_process_handler.h"

typedef std::unordered_map<std::string, JSValue *> RenderProcessHandlerValues;

class RenderProcessHandler : public CefRenderProcessHandler {
    public:
        RenderProcessHandler(RenderProcessHandlerValues _values);
        void OnContextCreated(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefV8Context> context);
    private:
        RenderProcessHandlerValues values;

        IMPLEMENT_REFCOUNTING(RenderProcessHandler);
};

#endif
