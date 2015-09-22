#ifndef CEFGUI_H
#define CEFGUI_H

#include "cef_app.h"

#include "browser_client.h"
#include "render_handler.h"
#include "render_process_handler.h"

namespace HUI {

    class HUI;

    HUI* initCefgui(int argc, char** argv);

    class HUI {
        public:
            enum MouseButton {
                MB_LEFT = 0,
                MB_RIGHT,
                MB_MIDDLE,
                MB_BACK,
                MB_FORWARD
            };

            static int Init(int argc, char **argv, RenderProcessHandlerValues _values);
            static void Shutdown(void);

            HUI(unsigned int _window_handle, RenderHandler *_render_handler = nullptr);

            void Load(const char*);
            void Update(void);
            void Draw(void);
            void Reshape(int _width, int _height);

            void MouseMove(int _x, int _y);
            void MouseButtonPress(MouseButton _button);
            void MouseButtonRelease(MouseButton _button);
            void KeyChar(int key);
            //        void KeyPress(int key);
            //        void KeyRelease(int key);

            void ExecuteJS(const char*);
            void VisitDOM(CefRefPtr<CefDOMVisitor> visitor);

            void RegisterRoute(Route *route);

        private:
            int mouseX, mouseY;
            unsigned int window_handle;

            CefRefPtr<CefBrowser> browser;
            CefRefPtr<BrowserClient> client;

            RenderHandler* renderHandler;
    };

}

#endif
