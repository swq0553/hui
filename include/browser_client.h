#ifndef BROWSER_CLIENT_H
#define BROWSER_CLIENT_H

#include "cef_client.h"

#include "render_handler.h"
#include "request_handler.h"

namespace HUI {

    class BrowserClient : public CefClient {
        public:
            BrowserClient(RenderHandler *_render_handler);

            virtual CefRefPtr<CefRenderHandler> GetRenderHandler(void);
            virtual CefRefPtr<CefRequestHandler> GetRequestHandler(void);

        private:
            CefRefPtr<CefRenderHandler> render_handler;
            CefRefPtr<CefRequestHandler> request_handler;

            IMPLEMENT_REFCOUNTING(BrowserClient);
    };

}

#endif
