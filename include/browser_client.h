#ifndef BROWSER_CLIENT_H
#define BROWSER_CLIENT_H

#include "cef_client.h"

#include "render_handler.h"
#include "request_handler.h"

namespace HUI {

    class LoadHandler : public CefLoadHandler {
        public:
            LoadHandler(void);

            void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode);
            bool IsSiteLoaded(void);
        private:
            bool site_loaded;

            IMPLEMENT_REFCOUNTING(LoadHandler);
    };

    class BrowserClient : public CefClient {
        public:
            BrowserClient(RenderHandler *_render_handler);

            virtual CefRefPtr<CefRenderHandler> GetRenderHandler(void);
            virtual CefRefPtr<CefRequestHandler> GetRequestHandler(void);
            virtual CefRefPtr<CefLoadHandler> GetLoadHandler(void);

            bool IsSiteLoaded(void);

        private:
            CefRefPtr<CefRenderHandler> render_handler;
            CefRefPtr<CefRequestHandler> request_handler;
            CefRefPtr<CefLoadHandler> load_handler;

            IMPLEMENT_REFCOUNTING(BrowserClient);
    };

}

#endif
