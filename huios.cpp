#include "include/huios.h"
#include "include/browser_app.h"

#include <iostream>

int HUIOS::Init(int argc, char **argv, RenderProcessHandlerValues _values) {
    CefMainArgs args(argc, argv);
    CefRefPtr<App> app(new App(new RenderProcessHandler(_values)));
    int exit_code = CefExecuteProcess(args, app.get(), NULL);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    settings.remote_debugging_port = 8088;
    //CefString(&settings.locales_dir_path) = "/usr/local/lib/locales";
    CefInitialize(args, settings, app.get(), NULL);

    return exit_code;
}

void HUIOS::Shutdown(void) {
    CefShutdown();
}

HUIOS::HUIOS(unsigned int _window_handle, RenderHandler *_render_handler) {
    window_handle = _window_handle;

    // Per GUI init stuff
    CefWindowInfo windowInfo;
    CefBrowserSettings browser_settings;

    windowInfo.SetAsWindowless(0, true);

    renderHandler = _render_handler;

    client = new BrowserClient(renderHandler);
    browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "", browser_settings, nullptr);
}

void HUIOS::Load(const char* url) {
    browser->GetMainFrame()->LoadURL(url);
}

void HUIOS::Update(void) {
    browser->GetHost()->SetFocus(true);
    CefDoMessageLoopWork();
}

void HUIOS::Draw(void) {
    renderHandler->Draw();
}

void HUIOS::Reshape(int w, int h) {
    renderHandler->Reshape(w, h);
    browser->GetHost()->WasResized();
}

void HUIOS::MouseMove(int x, int y) {
    mouseX = x;
    mouseY = y;

    CefMouseEvent event;
    event.x = x;
    event.y = y;

    browser->GetHost()->SendMouseMoveEvent(event, false);
}

void HUIOS::MouseButtonPress(MouseButton btn) {
    CefMouseEvent event;
    event.x = mouseX;
    event.y = mouseY;

    CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
    if (btn == MB_RIGHT) {
        btnType = MBT_RIGHT;
    } else if (btn == MB_MIDDLE) {
        btnType = MBT_MIDDLE;
    }

    browser->GetHost()->SendMouseClickEvent(event, btnType, false, 1);
}

void HUIOS::MouseButtonRelease(MouseButton btn) {
    CefMouseEvent event;
    event.x = mouseX;
    event.y = mouseY;

    CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
    if (btn == MB_RIGHT) {
        btnType = MBT_RIGHT;
    } else if (btn == MB_MIDDLE) {
        btnType = MBT_MIDDLE;
    }

    browser->GetHost()->SendMouseClickEvent(event, btnType, true, 1);
}

//void HUIOS::KeyPress(int key) {
//    CefKeyEvent event;
//    event.unmodified_character = key;
//    event.character = key;
//    event.native_key_code = key;
//    event.type = KEYEVENT_KEYDOWN;

//    browser->GetHost()->SendKeyEvent(event);
//}

//void HUIOS::KeyRelease(int key) {
//    CefKeyEvent event;
//    event.unmodified_character = key;
//    event.character = key;
//    event.native_key_code = key;
//    event.type = KEYEVENT_KEYUP;
//    browser->GetHost()->SendKeyEvent(event);
//}

void HUIOS::KeyChar(int key) {
    CefKeyEvent event;
    event.unmodified_character = key;
    event.character = key;
    event.native_key_code = key;
    event.type = KEYEVENT_CHAR;
    browser->GetHost()->SendKeyEvent(event);
}

void HUIOS::ExecuteJS(const char* command) {
    CefRefPtr<CefFrame> frame = browser->GetMainFrame();
    frame->ExecuteJavaScript(command, frame->GetURL(), 0);

    // TODO limit frequency of texture updating
    CefRect rect;
    renderHandler->GetViewRect(browser, rect);
    browser->GetHost()->Invalidate(PET_VIEW);
}

void HUIOS::RegisterRoute(Route *route) {
    static_cast<RequestHandler *>(client->GetRequestHandler().get())->RegisterRoute(route);
}

