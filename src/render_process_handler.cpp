#include "hui/render_process_handler.h"
#include <iostream>


namespace HUI {

    RenderProcessHandler::RenderProcessHandler(RenderProcessHandlerValues _values) {
        values = _values;
    }

    void RenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                                CefRefPtr<CefFrame> frame,
                                                CefRefPtr<CefV8Context> context) {
        CefRefPtr<CefV8Value> object = context->GetGlobal();

        //    CefV8Value::CreateFunction(CefString("function_name"), )
        RenderProcessHandlerValues::iterator value_iter = values.begin();
        while (value_iter != values.end()) {
            std::pair<std::string, JSValue *> value = (*value_iter);
            std::string key_name = value.first;
            JSValue *json_value = value.second;
            object->SetValue(key_name, ConvertJSValueToCef(json_value), V8_PROPERTY_ATTRIBUTE_NONE);
            ++value_iter;
        }
    }

}
