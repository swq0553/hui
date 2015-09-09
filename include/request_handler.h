#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <regex>
#include <vector>
#include "cef_client.h"
#include "cef_request_handler.h"

class Route  {
public:
    Route(std::regex _route);

    std::regex RouteRegex(void);
    virtual void HandleRequest(void);

protected:
    void Call(void);

    std::regex route;
};

class RESTRoute : public Route {
public:
    RESTRoute(std::regex _route);

    virtual void Get(void);
    virtual void Put(void);
    virtual void Post(void);
    virtual void Delete(void);
protected:
    void Call(void);
};

class RequestHandler : public CefRequestHandler {
    friend class Route;

    public:
        RequestHandler(void);

        cef_return_value_t OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefRequestCallback> callback);
        void OnResourceRedirect(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& old_url, CefString& new_url);
        bool OnResourceResponse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response);
    private:
        std::vector<Route *> routes;

    IMPLEMENT_REFCOUNTING(RequestHandler);
};

#endif
