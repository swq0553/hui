#ifndef CEFGUI_H
#define CEFGUI_H

#include "cef_app.h"

#include "browser_client.h"
#include "render_handler.h"

class HUIOS;

HUIOS* initCefgui(int argc, char** argv);

class HUIOS {
    public:
        enum MouseButton {
            MB_LEFT = 0,
            MB_RIGHT,
            MB_MIDDLE,
            MB_BACK,
            MB_FORWARD
        };

        static int Init(int argc, char **argv);
        static void Shutdown(void);

        HUIOS(unsigned int _window_handle, RenderHandler *_render_handler = nullptr);

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

    private:
        int mouseX, mouseY;
        unsigned int window_handle;

        CefRefPtr<CefBrowser> browser;
        CefRefPtr<BrowserClient> client;

        RenderHandler* renderHandler;
};

#endif
