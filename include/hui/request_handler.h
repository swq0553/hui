#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <regex>
#include <vector>
#include "cef_client.h"
#include "cef_request_handler.h"

namespace HUI {

    class RequestHandler;

    class Response {
        public:
            Response(void);
            Response(std::string _mime_type, std::string _content);

            std::string GetMimeType(void);
            std::string GetContent(void);

            void SetMimeType(std::string _mime_type);
            void SetContent(std::string _content);
        private:
            std::string mime_type;
            std::string content;
    };

    class Route  {
            friend class RequestHandler;

        public:
            Route(std::regex _route);

            std::regex RouteRegex(void);
            virtual Response *HandleRequest(std::string url, std::string method,
                                            std::vector<std::pair<std::string, std::string> > get,
                                            std::vector<std::pair<std::string, std::string> > post);

        protected:
            virtual Response *Call(std::string url, std::string method,
                                   std::vector<std::pair<std::string, std::string> > get,
                                   std::vector<std::pair<std::string, std::string> > post);

            std::regex route;
    };

    class RESTRoute : public Route {
        public:
            RESTRoute(std::regex _route);

            virtual Response *Get(std::string id = "");
            virtual Response *Put(std::string id, std::vector<std::pair<std::string, std::string> > post);
            virtual Response *Post(std::vector<std::pair<std::string, std::string> > post);
            virtual Response *Delete(std::string id);
            virtual Response *Options(void);
        protected:
            virtual Response *Call(std::string url, std::string method,
                                   std::vector<std::pair<std::string, std::string> > get,
                                   std::vector<std::pair<std::string, std::string> > post);
    };

    class JSONRESTRoute : public Route {
        public:
            JSONRESTRoute(std::regex _route);

            virtual Response *Get(std::string id = "");
            virtual Response *Put(std::string id, std::string data);
            virtual Response *Post(std::string data);
            virtual Response *Delete(std::string id);
            virtual Response *Options(void);
        private:
            virtual Response *Call(std::string url, std::string method,
                                   std::vector<std::pair<std::string, std::string> > get,
                                   std::vector<std::pair<std::string, std::string> > post);
    };

    std::string ReadPostElementBytes(CefRefPtr<CefPostDataElement> element);

    class RequestHandler : public CefRequestHandler {
        public:
            RequestHandler(void);

            CefRefPtr<CefResourceHandler> GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                                             CefRefPtr<CefFrame> frame,
                                                             CefRefPtr<CefRequest> request);
            void RegisterRoute(Route *route);
        private:
            std::vector<Route *> routes;

            IMPLEMENT_REFCOUNTING(RequestHandler);
    };

}

#endif
