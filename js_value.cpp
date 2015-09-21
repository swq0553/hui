#include "include/js_value.h"
#include <iostream>


CefRefPtr<CefV8Value> ConvertJSValueToCef(JSValue *in) {
    if (in->Type() == JSValue::JS_BOOL) {
        JSBoolValue *val = static_cast<JSBoolValue *>(in);
        return CefV8Value::CreateBool(val->Get());
    } else if (in->Type() == JSValue::JS_DOUBLE) {
        JSDoubleValue *val = static_cast<JSDoubleValue *>(in);
        return CefV8Value::CreateDouble(val->Get());
    } else if (in->Type() == JSValue::JS_INT) {
        JSIntValue *val = static_cast<JSIntValue *>(in);
        return CefV8Value::CreateInt(val->Get());
    } else if (in->Type() == JSValue::JS_STRING) {
        JSStringValue *val = static_cast<JSStringValue *>(in);
        return CefV8Value::CreateString(val->Get());
    } else if (in->Type() == JSValue::JS_UINT) {
        JSUIntValue *val = static_cast<JSUIntValue *>(in);
        return CefV8Value::CreateUInt(val->Get());
    } else if (in->Type() == JSValue::JS_NULL) {
        return CefV8Value::CreateNull();
    } else if (in->Type() == JSValue::JS_ARRAY) {
        JSArrayValue *val = static_cast<JSArrayValue *>(in);
        CefRefPtr<CefV8Value> cval = CefV8Value::CreateArray(val->Size());
        for (unsigned int i = 0; i < val->Size(); i++) {
            cval->SetValue(i, ConvertJSValueToCef(val->Get(i)));
        }
        return cval;
    } else if (in->Type() == JSValue::JS_OBJECT) {
        JSObjectValue *val = static_cast<JSObjectValue *>(in);
        CefRefPtr<CefV8Value> cval = CefV8Value::CreateObject(NULL);
        std::vector<std::string> keys = val->Keys();
        std::vector<std::string>::iterator key_iter = keys.begin();
        while (key_iter != keys.end()) {
            cval->SetValue(CefString(*key_iter), ConvertJSValueToCef(val->Get(*key_iter)), V8_PROPERTY_ATTRIBUTE_NONE);
            ++key_iter;
        }
        return cval;
    } else if (in->Type() == JSValue::JS_FUNCTION) {
        JSFunction *func = static_cast<JSFunction *>(in);
        return CefV8Value::CreateFunction(func->Name(), func);
    }
    return CefV8Value::CreateNull();
}


JSValue *ConvertCefToJSValue(CefRefPtr<CefV8Value> in) {
    if (in->IsNull()) {
        return new JSValue();
    } else if (in->IsBool()) {
        return new JSBoolValue(in->GetBoolValue());
    } else if (in->IsInt()) {
        return new JSIntValue(in->GetIntValue());
    } else if (in->IsUInt()) {
        return new JSUIntValue(in->GetUIntValue());
    } else if (in->IsDouble()) {
        return new JSDoubleValue(in->GetDoubleValue());
    } else if (in->IsString()) {
        return new JSStringValue(in->GetStringValue());
    } else if (in->IsArray()) {
        JSArrayValue *out = new JSArrayValue();
        unsigned int size = in->GetArrayLength();
        for (unsigned int i = 0; i < size; i++) {
            out->Push(ConvertCefToJSValue(in->GetValue(i)));
        }
        return out;
    } else if (in->IsObject()) {
        JSObjectValue *out = new JSObjectValue();
        std::vector<CefString> keys;
        in->GetKeys(keys);
        std::vector<CefString>::iterator key_iter = keys.begin();
        while (key_iter != keys.end()) {
            out->Set((*key_iter).ToString(), ConvertCefToJSValue(in->GetValue(*key_iter)));
            ++key_iter;
        }
        return out;
    } else if (in->IsFunction()) {
        return new JSValue();
    }
    return new JSValue();
}


JSValue::JSValue(void) {
    type = JS_NULL;
}

JSValue::~JSValue(void) {
    //
}

JSValue::JSValueType JSValue::Type(void) {
    return type;
}

std::string JSValue::TypeString(void) {
    if (type == JS_NULL) {
        return "null";
    } else if (type == JS_BOOL) {
        return "bool";
    } else if (type == JS_INT) {
        return "int";
    } else if (type == JS_UINT) {
        return "uint";
    } else if (type == JS_DOUBLE) {
        return "double";
    } else if (type == JS_STRING) {
        return "string";
    } else if (type == JS_ARRAY) {
        return "array";
    } else if (type == JS_OBJECT) {
        return "object";
    } else if (type == JS_FUNCTION) {
        return "function";
    }
}


JSBoolValue::JSBoolValue(void) {
    type = JS_BOOL;
    value = false;
}

JSBoolValue::JSBoolValue(bool _value) {
    type = JS_BOOL;
    value = _value;
}

JSBoolValue::~JSBoolValue(void) {
    //
}

void JSBoolValue::Set(bool _value) {
    value = _value;
}

bool JSBoolValue::Get(void) {
    return value;
}


JSIntValue::JSIntValue(void) {
    type = JS_INT;
    value = 0;
}

JSIntValue::JSIntValue(int _value) {
    type = JS_INT;
    value = _value;
}

JSIntValue::~JSIntValue(void) {
    //
}

void JSIntValue::Set(int _value) {
    value = _value;
}

int JSIntValue::Get(void) {
    return value;
}


JSUIntValue::JSUIntValue(void) {
    type = JS_UINT;
    value = 0;
}

JSUIntValue::JSUIntValue(unsigned int _value) {
    type = JS_UINT;
    value = _value;
}

JSUIntValue::~JSUIntValue(void) {
    //
}

void JSUIntValue::Set(unsigned int _value) {
    value = _value;
}

unsigned int JSUIntValue::Get(void) {
    return value;
}


JSDoubleValue::JSDoubleValue(void) {
    type = JS_DOUBLE;
    value = 0.0;
}

JSDoubleValue::JSDoubleValue(double _value) {
    type = JS_DOUBLE;
    value = _value;
}

JSDoubleValue::~JSDoubleValue(void) {
    //
}

void JSDoubleValue::Set(double _value) {
    value = _value;
}

double JSDoubleValue::Get(void) {
    return value;
}


JSStringValue::JSStringValue(void) {
    type = JS_STRING;
    value.clear();
}

JSStringValue::JSStringValue(std::string _value) {
    type = JS_STRING;
    value = _value;
}

JSStringValue::~JSStringValue(void) {
    //
}

void JSStringValue::Set(std::string _value) {
    value = _value;
}

std::string JSStringValue::Get(void) {
    return value;
}


JSArrayValue::JSArrayValue(void) {
    type = JS_ARRAY;
    values.clear();
}

JSArrayValue::~JSArrayValue(void) {
    values.clear();
}

unsigned int JSArrayValue::Size(void) {
    return values.size();
}

void JSArrayValue::Push(JSValue *value) {
    values.push_back(value);
}

JSValue *JSArrayValue::Get(unsigned int index) {
    if (index < values.size()) {
        return values[index];
    }
    return nullptr;
}


JSObjectValue::JSObjectValue(void) {
    type = JS_OBJECT;
    values.clear();
}

JSObjectValue::~JSObjectValue(void) {
    values.clear();
}

std::vector<std::string> JSObjectValue::Keys(void) {
    std::vector<std::string> keys;
    std::unordered_map<std::string, JSValue *>::iterator value_iter = values.begin();
    while (value_iter != values.end()) {
        keys.push_back((*value_iter).first);
        ++value_iter;
    }
    return keys;
}

unsigned int JSObjectValue::Size(void) {
    return values.size();
}

void JSObjectValue::Set(std::string key, JSValue *value) {
    values[key] = value;
}

JSValue *JSObjectValue::Get(std::string key) {
    if (values.count(key)) {
        return values[key];
    }
    return nullptr;
}



JSFunction::JSFunction(void) {
    type = JS_FUNCTION;
    name = "default_function_name";
}

JSFunction::JSFunction(std::string _name) {
    type = JS_FUNCTION;
    name = _name;
}

JSFunction::~JSFunction(void) {
    //
}

std::string JSFunction::Name(void) {
    return name;
}

std::string JSFunction::SetName(std::string _name) {
    name = _name;
}

JSValue *JSFunction::Call(std::string name, JSObjectValue *obj_this,
                          std::vector<JSValue *> parameters, std::string exception) {
    return new JSValue();
}

bool JSFunction::Execute(const CefString &_name, CefRefPtr<CefV8Value> object,
                         const CefV8ValueList &arguments, CefRefPtr<CefV8Value> &retval,
                         CefString &exception) {
    std::string converted_name = _name.ToString();
    if (converted_name != name) {
        return false;
    }

    JSValue *this_obj = ConvertCefToJSValue(object);
    std::vector<JSValue *> parameters;
    for (int i = 0; i < arguments.size(); i++) {
        parameters.push_back(ConvertCefToJSValue(arguments[i]));
    }
    std::string return_exception;
    JSValue *return_value = Call(converted_name, static_cast<JSObjectValue *>(this_obj),
                                 parameters, return_exception);
    if (return_value == nullptr) {
        return_value = new JSValue();
    }
    retval = ConvertJSValueToCef(return_value);
    exception = CefString(return_exception);

    return true;
}
