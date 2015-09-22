#include <iostream>
#include "cpptest.h"
#include "include/hui.h"

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
};

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
        Tests(void) {
            TEST_ADD(Tests::test_js_values);
        }

    protected:
        void setup(void) {
            hui = new HUI::HUI(0, render_handler);
            //hui->Reshape(1280, 720);
            //hui->Load("file:///home/douglas/Projects/huios/tests/assets/index.html");
        }

        void tear_down(void) {
            delete hui;
        }

    private:
        void test_js_values(void) {
            //hui->VisitDOM(CefRefPtr<CefDOMVisitor>(&visitor));
            TEST_ASSERT(true);
        }

        TestRenderHandler *render_handler;
        HUI::HUI *hui;
        //DOMVisitor visitor;
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

    Test::TextOutput output(Test::TextOutput::Verbose);
    Tests tests;

    int return_code = tests.run(output) ? EXIT_SUCCESS : EXIT_FAILURE;

    HUI::HUI::Shutdown();

    return return_code;
}
