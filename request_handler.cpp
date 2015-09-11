#include "include/request_handler.h"

#include "wrapper/cef_stream_resource_handler.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>


Response::Response(void) {
    mime_type = "text/html";
    content = "";
}

Response::Response(std::string _mime_type, std::string _content) {
    mime_type = _mime_type;
    content = _content;
}

std::string Response::GetMimeType(void) {
    return mime_type;
}

std::string Response::GetContent(void) {
    return content;
}

void Response::SetMimeType(std::string _mime_type) {
    mime_type = _mime_type;
}

void Response::SetContent(std::string _content) {
    content = _content;
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


Route::Route(std::regex _route) {
    route = _route;
}

std::regex Route::RouteRegex(void) {
    return route;
}

Response *Route::Call(std::string url, std::string method,
                      std::vector<std::pair<std::string, std::string> > get,
                      std::vector<std::pair<std::string, std::string> > post) {
    return HandleRequest(url, method, get, post);
}

Response *Route::HandleRequest(std::string url, std::string method,
                          std::vector<std::pair<std::string, std::string> > get,
                          std::vector<std::pair<std::string, std::string> > post) {
    return nullptr;
}


RESTRoute::RESTRoute(std::regex _route) : Route(_route) {
    //
}

Response *RESTRoute::Get(std::string id) {
    return nullptr;
}

Response *RESTRoute::Put(std::string id,
                         std::vector<std::pair<std::string, std::string> > post) {
    return nullptr;
}

Response *RESTRoute::Post(std::vector<std::pair<std::string, std::string> > post) {
    return nullptr;
}

Response *RESTRoute::Delete(std::string id) {
    return nullptr;
}

Response *RESTRoute::Call(std::string url, std::string method,
                          std::vector<std::pair<std::string, std::string> > get,
                          std::vector<std::pair<std::string, std::string> > post) {
    return nullptr;
}


JSONRESTRoute::JSONRESTRoute(std::regex _route) : Route(_route) {
    //
}

Response *JSONRESTRoute::Get(std::string id) {
    return nullptr;
}

Response *JSONRESTRoute::Put(std::string id,
                             std::string data) {
    return nullptr;
}

Response *JSONRESTRoute::Post(std::string data) {
    return nullptr;
}

Response *JSONRESTRoute::Delete(std::string id) {
    return nullptr;
}

Response *JSONRESTRoute::Call(std::string url, std::string method,
                              std::vector<std::pair<std::string, std::string> > get,
                              std::vector<std::pair<std::string, std::string> > post) {
    return nullptr;
}


//ResourceHandler::ResourceHandler(std::string _url, std::string _method,
//                                 std::vector<std::pair<std::string, std::string> > _get,
//                                 std::vector<std::pair<std::string, std::string> > _post,
//                                 Route *_route) {
//    url = _url;
//    method = _method;
//    get = _get;
//    post = _post;
//    route = _route;
//}


RequestHandler::RequestHandler(void) {
    routes.clear();
}

CefRefPtr<CefResourceHandler> RequestHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                                                 CefRefPtr<CefFrame> frame,
                                                                 CefRefPtr<CefRequest> request) {
    // Evaluate if match, if so, return new ResourceHandler();
//    std::cout << "URL: " << request->GetURL().ToString() << std::endl;
    std::string url = request->GetURL().ToString();
    int split_index = url.find_first_of('?');
    std::string base_url;
    std::string get_params;
    if (split_index == -1) {
        base_url = url;
    } else {
        base_url = url.substr(0, split_index);
        get_params = url.substr(split_index + 1);
    }

    bool found = false;
    Route *route = nullptr;
    std::vector<Route *>::iterator route_iter = routes.begin();
    while (route_iter != routes.end() && !found) {
        route = (*route_iter);
        std::smatch match;
        if (std::regex_search(base_url, match, route->RouteRegex())) {
            found = true;
        }
        ++route_iter;
    }
    std::cout << "URL: " << base_url << std::endl;
    std::cout << "Found: " << found << std::endl;

//    std::cout << "Base URL: " << base_url << std::endl;
//    std::cout << "Method: " << request->GetMethod().ToString() << std::endl;

    if (found) {
        std::string method = request->GetMethod().ToString();

        std::vector<std::pair<std::string, std::string> > get;
        std::vector<std::string> get_param_chunks = split(get_params, '&');
        std::vector<std::string>::iterator get_param_chunk_iter = get_param_chunks.begin();
        while (get_param_chunk_iter != get_param_chunks.end()) {
            std::string chunk = (*get_param_chunk_iter);
            std::string name = chunk.substr(0, chunk.find_first_of('='));
            std::string value = chunk.substr(chunk.find_first_of('='));
            get.push_back(std::pair<std::string, std::string>(name, value));
            ++get_param_chunk_iter;
        }

        std::vector<std::pair<std::string, std::string> > post;
        CefRefPtr<CefPostData> post_data = request->GetPostData();
        if (post_data.get() != nullptr) {
            std::cout << "WAAAA?" << std::endl;
            CefPostData::ElementVector post_elements;
            post_data->GetElements(post_elements);
            CefPostData::ElementVector::iterator post_elem_iter = post_elements.begin();
            while (post_elem_iter != post_elements.end()) {
                std::string element_data;
                std::string element_type;
                CefRefPtr<CefPostDataElement> element = (*post_elem_iter);
                if (element->GetType() == PDE_TYPE_EMPTY) {
                    element_type = "empty";
                } else if (element->GetType() == PDE_TYPE_BYTES) {
                    size_t byte_count = element->GetBytesCount();
                    char *bytes = new char[byte_count];
                    element->GetBytes(byte_count, (void *)(bytes));
                    element_data = std::string(bytes);
                    element_type = "string";
                } else if (element->GetType() == PDE_TYPE_FILE) {
                    element_data = element->GetFile().ToString();
                    element_type = "file";
                }
                post.push_back(std::pair<std::string, std::string>(element_type, element_data));
                ++post_elem_iter;
            }
        }

        Response *result = route->Call(base_url, method, get, post);
        if (result == nullptr) {
            return nullptr;
        }
        std::cout << result->GetMimeType() << ": " << result->GetContent() << std::endl;
        CefRefPtr<CefStreamReader> result_stream = CefStreamReader::CreateForData(
            static_cast<void*>(const_cast<char*>(result->GetContent().c_str())),
            result->GetContent().size());
        CefResponse::HeaderMap headers;
        headers.insert(std::pair<CefString, CefString>("Access-Control-Allow-Origin", "*"));
        return new CefStreamResourceHandler(200, "200 OK", result->GetMimeType(), headers, result_stream);
    }

    return nullptr;
}

void RequestHandler::RegisterRoute(Route *route) {
    std::cout << "Pushing Route Handler" << std::endl;
    routes.push_back(route);
}
