#ifndef CEFGUI_H
#define CEFGUI_H

#include "cef_app.h"

#include "browser_client.h"
#include "render_handler.h"

class HUIOS;

HUIOS* initCefgui(int argc, char** argv);

class HUIOS {
    public:
        static int Init(int argc, char **argv);
        static void Shutdown(void);

        HUIOS(unsigned int _window_handle, RenderHandler *_render_handler = nullptr);

        void load(const char*);
        void update(void);
        void draw(void);
        void reshape(int, int);

        void mouseMove(int, int);
        void mouseClick(int, int);
        void keyPress(int);

        void executeJS(const char*);

    private:
        int mouseX, mouseY;
        unsigned int window_handle;

        CefRefPtr<CefBrowser> browser;
        CefRefPtr<BrowserClient> client;

        RenderHandler* renderHandler;
};

#endif
