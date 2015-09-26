#ifndef BROWSER_APP
#define BROWSER_APP

#include "cef_app.h"
#include "render_process_handler.h"

namespace HUI {

    class App : public CefApp {
        public:
            App(RenderProcessHandler *_render_process_handler);

            void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar);
            CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler(void);

        private:
            CefRefPtr<CefRenderProcessHandler> render_process_handler;

            IMPLEMENT_REFCOUNTING(App);
    };

}

#endif
