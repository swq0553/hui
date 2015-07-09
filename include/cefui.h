#ifndef CEFGUI_H
#define CEFGUI_H

#include "cef_app.h"

#include "browser_client.h"
#include "render_handler.h"

class CEFUI;

CEFUI* initCefgui(int argc, char** argv);

class CEFUI {
  public:
    CEFUI(int argc, char **argv, RenderHandler *_render_handler = nullptr);

    void load(const char*);
    void draw(void);
    void reshape(int, int);

    void mouseMove(int, int);
    void mouseClick(int, int);
    void keyPress(int);

    void executeJS(const char*);

  private:
    int mouseX, mouseY;

    CefRefPtr<CefBrowser> browser;
    CefRefPtr<BrowserClient> client;

    RenderHandler* renderHandler;

};

#endif
