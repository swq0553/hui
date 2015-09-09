#include "include/browser_client.h"

BrowserClient::BrowserClient(RenderHandler *_render_handler) : render_handler(_render_handler) {
    request_handler = new RequestHandler();
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
    return render_handler;
}

CefRefPtr<CefRequestHandler> BrowserClient::GetRequestHandler() {
    return request_handler;
}
