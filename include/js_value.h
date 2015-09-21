#ifndef JS_VALUE_H
#define JS_VALUE_H

#include <string>
#include <vector>
#include <unordered_map>

#include "cef_app.h"

namespace HUI {

    class JSValue {
        public:
            enum JSValueType {
                JS_NULL = 0,
                JS_BOOL,
                JS_INT,
                JS_UINT,
                JS_DOUBLE,
                JS_STRING,
                JS_ARRAY,
                JS_OBJECT,
                JS_FUNCTION
            };

            JSValue(void);
            ~JSValue(void);

            JSValueType Type(void);
            std::string TypeString(void);
        protected:
            JSValueType type;
    };

    class JSBoolValue : public JSValue {
        public:
            JSBoolValue(void);
            JSBoolValue(bool _value);
            ~JSBoolValue(void);

            void Set(bool _value);
            bool Get(void);
        private:
            bool value;
    };

    class JSIntValue : public JSValue {
        public:
            JSIntValue(void);
            JSIntValue(int _value);
            ~JSIntValue(void);

            void Set(int _value);
            int Get(void);
        private:
            int value;
    };

    class JSUIntValue : public JSValue {
        public:
            JSUIntValue(void);
            JSUIntValue(unsigned int _value);
            ~JSUIntValue(void);

            void Set(unsigned int _value);
            unsigned int Get(void);
        private:
            unsigned int value;
    };

    class JSDoubleValue : public JSValue {
        public:
            JSDoubleValue(void);
            JSDoubleValue(double _value);
            ~JSDoubleValue(void);

            void Set(double _value);
            double Get(void);
        private:
            double value;
    };

    class JSStringValue : public JSValue {
        public:
            JSStringValue(void);
            JSStringValue(std::string _value);
            ~JSStringValue(void);

            void Set(std::string _value);
            std::string Get(void);
        private:
            std::string value;
    };

    class JSArrayValue : public JSValue {
        public:
            JSArrayValue(void);
            ~JSArrayValue(void);

            unsigned int Size(void);
            void Push(JSValue *value);
            JSValue *Get(unsigned int index);
        private:
            std::vector<JSValue *> values;
    };

    class JSObjectValue : public JSValue {
        public:
            JSObjectValue(void);
            ~JSObjectValue(void);

            std::vector<std::string> Keys(void);
            unsigned int Size(void);
            void Set(std::string, JSValue *value);
            JSValue *Get(std::string key);
        private:
            std::unordered_map<std::string, JSValue *> values;
    };

    class JSFunction : public JSValue, public CefV8Handler {
        public:
            JSFunction(void);
            JSFunction(std::string _name);
            ~JSFunction(void);

            std::string Name(void);
            void SetName(std::string _name);
            virtual JSValue *Call(std::string name, JSObjectValue *obj_this,
                                  std::vector<JSValue *> parameters, std::string exception);
            bool Execute(const CefString& name, CefRefPtr<CefV8Value> object,
                         const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval,
                         CefString& exception);
        private:
            std::string name;

            IMPLEMENT_REFCOUNTING(JSFunction);
    };

    CefRefPtr<CefV8Value> ConvertJSValueToCef(JSValue *in);
    JSValue *ConvertCefToJSValue(CefRefPtr<CefV8Value> in);

}

#endif
