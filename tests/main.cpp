#include <iostream>
#include "cpptest.h"
#include "hui/hui.h"
/*
class TestRenderHandler : public HUI::RenderHandler {
    public:
        TestRenderHandler(void) {
            //
        }

        ~TestRenderHandler(void) {
            //
        }

        void Draw(void) {
            //
        }

        int GetWidth(void) {
            return paint_width;
        }

        int GetHeight(void) {
            return paint_height;
        }

        unsigned char *GetBuffer(void) {
            return paint_buffer;
        }
};*/

class DOMVisitor : public CefDOMVisitor {
    public:

        void Visit(CefRefPtr<CefDOMDocument> document) {
            std::cout << "Visiting DOM" << std::endl;
        }

    private:

        IMPLEMENT_REFCOUNTING(DOMVisitor);
};

class Tests : public Test::Suite {
    public:
        Tests(HUI::HUI *_hui, DOMVisitor *_visitor) {
            hui = _hui;
            visitor = _visitor;

            TEST_ADD(Tests::test_js_values);
            TEST_ADD(Tests::test_dom_changes);
        }

    private:
        void test_js_values(void) {
            // TODO: Has to be done on a different thread.
//             CefRefPtr<CefV8Value> cef_bool = CefV8Value::CreateBool(true);
//             TEST_ASSERT(cef_bool->IsBool());

//             HUI::JSBoolValue *js_true_bool = new HUI::JSBoolValue(true);
//             CefRefPtr<CefV8Value> result = HUI::ConvertJSValueToCef(js_true_bool);
//             TEST_ASSERT(result->IsBool());
//             TEST_ASSERT(result->GetBoolValue());

//             HUI::JSBoolValue *js_false_bool = new HUI::JSBoolValue(false);
//             CefRefPtr<CefV8Value> result2 = HUI::ConvertJSValueToCef(js_false_bool);
//             TEST_ASSERT(result2->IsBool());
//             TEST_ASSERT(result2->GetBoolValue() == false);
        }

        void test_dom_changes(void) {
            // TODO: Has to be done on a different thread.
//             hui->ExecuteJS("kickoff();");
//             hui->VisitDOM(visitor);
        }

        DOMVisitor *visitor;
        HUI::HUI *hui;
};

int main(int argc, char **argv) {
    std::cout << "Testing..." << std::endl;

    HUI::RenderProcessHandlerValues values;
    values["test_null"] = new HUI::JSValue();
    values["test_bool"] = new HUI::JSBoolValue(true);
    values["test_int"] = new HUI::JSIntValue(5);
    values["test_negative_int"] = new HUI::JSIntValue(-5);
    values["test_uint"] = new HUI::JSIntValue(10);
    values["test_double"] = new HUI::JSDoubleValue(3.14159);
    values["test_string"] = new HUI::JSStringValue("Weeee");

    HUI::JSArrayValue *arr = new HUI::JSArrayValue();
    arr->Push(new HUI::JSDoubleValue(5.12));
    arr->Push(new HUI::JSIntValue(15));
    arr->Push(new HUI::JSStringValue("Array Stuff"));
    values["test_array"] = arr;

    HUI::JSObjectValue *obj = new HUI::JSObjectValue();
    obj->Set("sub_int", new HUI::JSIntValue(25));
    obj->Set("sub_string", new HUI::JSStringValue("Snarf"));
    values["test_object"] = obj;

    int code = HUI::HUI::Init(argc, argv, values);
    if (code >= 0) {
        return code;
    }

    DOMVisitor *visitor = new DOMVisitor();
    HUI::HUI *hui = new HUI::HUI(0);
    hui->Reshape(1280, 720);
    hui->Load("tests/assets/index.html");

    Test::TextOutput output(Test::TextOutput::Verbose);
    Tests tests(hui, visitor);

    int return_code = tests.run(output) ? EXIT_SUCCESS : EXIT_FAILURE;

    HUI::HUI::Shutdown();

    return return_code;
}
