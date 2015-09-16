#include "include/render_process_handler.h"

RenderProcessHandler::RenderProcessHandler(void) {
    //
}

void RenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                            CefRefPtr<CefFrame> frame,
                                            CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> object = context->GetGlobal();

    CefRefPtr<CefV8Value> str = CefV8Value::CreateString("Test String");
    object->SetValue("test_string", str, V8_PROPERTY_ATTRIBUTE_NONE);

    CefRefPtr<CefV8Value> arr = CefV8Value::CreateArray(3);
    arr->SetValue(0, CefV8Value::CreateString("Array 0"));
    arr->SetValue(1, CefV8Value::CreateBool(true));
    arr->SetValue(2, CefV8Value::CreateDouble(1.42));
    object->SetValue("test_array", arr, V8_PROPERTY_ATTRIBUTE_NONE);

    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(NULL);
    obj->SetValue("sub_value", CefV8Value::CreateString("Weeee Object Sub-Value"), V8_PROPERTY_ATTRIBUTE_NONE);
    object->SetValue("test_obj", obj, V8_PROPERTY_ATTRIBUTE_NONE);
}
