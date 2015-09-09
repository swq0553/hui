#include "include/request_handler.h"
#include <iostream>


Route::Route(std::regex _route) {
    route = _route;
}

std::regex Route::RouteRegex(void) {
    return route;
}

void Route::Call(void) {
    //
}

void Route::HandleRequest(void) {
    //
}


RESTRoute::RESTRoute(std::regex _route) : Route(_route) {
    //
}

void RESTRoute::Get(void) {
    //
}

void RESTRoute::Put(void) {
    //
}

void RESTRoute::Post(void) {
    //
}

void RESTRoute::Delete(void) {
    //
}


RequestHandler::RequestHandler(void) {
    routes.clear();
}

cef_return_value_t RequestHandler::OnBeforeResourceLoad(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefRequest> request, CefRefPtr<CefRequestCallback> callback) {
    std::cout << "OnBeforeResourceLoad" << std::endl;
    std::cout << "URL: " << request->GetURL().ToString() << std::endl;
    return RV_CONTINUE;
}

void RequestHandler::OnResourceRedirect(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                                        const CefString& old_url, CefString& new_url) {
    std::cout << "OnResourceRedirect" << std::endl;
    std::cout << "Old URL: " << old_url.ToString() << std::endl;
    std::cout << "New URL: " << new_url.ToString() << std::endl;
}

bool RequestHandler::OnResourceResponse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                                        CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response) {
    std::cout << "OnResourceResponse" << std::endl;
    std::cout << "URL: " << request->GetURL().ToString() << std::endl;
    return false;
}
