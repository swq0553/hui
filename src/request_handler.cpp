#include "hui/request_handler.h"

#include "wrapper/cef_stream_resource_handler.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace HUI {

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

    Response *RESTRoute::Options(void) {
        return new Response("text/html", "ok");
    }

    Response *RESTRoute::Call(std::string url, std::string method,
                              std::vector<std::pair<std::string, std::string> > get,
                              std::vector<std::pair<std::string, std::string> > post) {
        std::smatch matches;
        bool result = std::regex_search(url, matches, route);
        std::string id = "";
        if (result) {
            std::string match = matches[0];
            int index = url.find(match);
            if (index != -1) {
                int start_index = index + match.size() + 1;
                if (start_index < int(url.size())) {
                    id = url.substr(start_index);
                }
            }
        }

        if (method == "GET") {
            return Get(id);
        } else if (method == "POST") {
            return Post(post);
        } else if (method == "PUT") {
            return Put(id, post);
        } else if (method == "DELETE") {
            return Delete(id);
        } else if (method == "OPTIONS") {
            return Options();
        }
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

    Response *JSONRESTRoute::Options(void) {
        return new Response("application/json", "{\"status\": \"ok\"");
    }

    Response *JSONRESTRoute::Call(std::string url, std::string method,
                                  std::vector<std::pair<std::string, std::string> > get,
                                  std::vector<std::pair<std::string, std::string> > post) {
        std::smatch matches;
        bool result = std::regex_search(url, matches, route);
        std::string id = "";
        if (result) {
            std::string match = matches[0];
            int index = url.find(match);
            if (index != -1) {
                int start_index = index + match.size() + 1;
                if (start_index < int(url.size())) {
                    id = url.substr(start_index);
                }
            }
        }

        std::string post_json = "";
        if (method == "POST" || method == "PUT") {
            std::vector<std::pair<std::string, std::string> >::iterator post_iter = post.begin();
            while (post_iter != post.end()) {
                std::pair<std::string, std::string> p = (*post_iter);
                post_json = p.second;
                break;
            }
        }

        if (method == "GET") {
            return Get(id);
        } else if (method == "POST") {
            return Post(post_json);
        } else if (method == "PUT") {
            return Put(id, post_json);
        } else if (method == "DELETE") {
            return Delete(id);
        } else if (method == "OPTIONS") {
            return Options();
        }
        return nullptr;
    }


    RequestHandler::RequestHandler(void) {
        routes.clear();
    }

    std::string ReadPostElementBytes(CefRefPtr<CefPostDataElement> element) {
        size_t byte_count = element->GetBytesCount();
        char *bytes = new char[byte_count + 1];
        element->GetBytes(byte_count + 1, (void *)(bytes));
        bytes[byte_count] = '\0';
        return std::string(bytes);
    }

    CefRefPtr<CefResourceHandler> RequestHandler::GetResourceHandler(CefRefPtr<CefBrowser> browser,
                                                                     CefRefPtr<CefFrame> frame,
                                                                     CefRefPtr<CefRequest> request) {
        std::string url = request->GetURL().ToString();
        std::string method = request->GetMethod().ToString();

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

        if (found) {
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
                        element_data = ReadPostElementBytes(element);
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

            std::string content_str = result->GetContent();
            int content_size = content_str.size();
            const char *content = content_str.c_str();

            CefRefPtr<CefStreamReader> result_stream = CefStreamReader::CreateForData(
                                                           static_cast<void*>(const_cast<char*>(content)), content_size);
            CefResponse::HeaderMap headers;
            headers.insert(std::pair<CefString, CefString>("Access-Control-Allow-Origin", "*"));
            headers.insert(std::pair<CefString, CefString>("Access-Control-Allow-Methods", "POST, GET, PUT, OPTIONS, PATCH, DELETE"));

            return new CefStreamResourceHandler(200, "200 OK", result->GetMimeType(), headers, result_stream);
        }

        return nullptr;
    }

    void RequestHandler::RegisterRoute(Route *route) {
        routes.push_back(route);
    }

}
