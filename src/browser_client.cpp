#include "include/browser_client.h"

namespace HUI {

    LoadHandler::LoadHandler(void) {
        site_loaded = false;
    }

    void LoadHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) {
        site_loaded = true;
    }

    bool LoadHandler::IsSiteLoaded(void) {
        return site_loaded;
    }

    BrowserClient::BrowserClient(RenderHandler *_render_handler) : render_handler(_render_handler) {
        request_handler = new RequestHandler();
        load_handler = new LoadHandler();
    }

    CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
        return render_handler;
    }

    CefRefPtr<CefRequestHandler> BrowserClient::GetRequestHandler() {
        return request_handler;
    }

    CefRefPtr<CefLoadHandler> BrowserClient::GetLoadHandler(void) {
        return load_handler;
    }

    bool BrowserClient::IsSiteLoaded(void) {
        return static_cast<LoadHandler *>(load_handler.get())->IsSiteLoaded();
    }

}
