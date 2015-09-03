#include "include/huios.h"

int HUIOS::Init(int argc, char **argv) {
    CefMainArgs args(argc, argv);
    int exit_code = CefExecuteProcess(args, nullptr, NULL);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    //CefString(&settings.locales_dir_path) = "/usr/local/lib/locales";
    CefInitialize(args, settings, nullptr, NULL);

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
    browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "http://google.com", browser_settings, nullptr);
}

void HUIOS::load(const char* url) {
    browser->GetMainFrame()->LoadURL(url);
}

void HUIOS::update(void) {
//     CefRunMessageLoop();
    CefDoMessageLoopWork();
}

void HUIOS::draw(void) {
    renderHandler->Draw();
}

void HUIOS::reshape(int w, int h) {
    renderHandler->Reshape(w, h);
    browser->GetHost()->WasResized();
}

void HUIOS::mouseMove(int x, int y) {
    mouseX = x;
    mouseY = y;

    CefMouseEvent event;
    event.x = x;
    event.y = y;

    browser->GetHost()->SendMouseMoveEvent(event, false);
}

void HUIOS::mouseClick(int btn, int state) {
    CefMouseEvent event;
    event.x = mouseX;
    event.y = mouseY;

    bool mouseUp = state == 0;
    CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
    browser->GetHost()->SendMouseClickEvent(event, btnType, mouseUp, 1);
}

void HUIOS::keyPress(int key) {
    CefKeyEvent event;
    event.native_key_code = key;
    event.type = KEYEVENT_KEYDOWN;

    browser->GetHost()->SendKeyEvent(event);
}

void HUIOS::executeJS(const char* command) {
    CefRefPtr<CefFrame> frame = browser->GetMainFrame();
    frame->ExecuteJavaScript(command, frame->GetURL(), 0);

    // TODO limit frequency of texture updating
    CefRect rect;
    renderHandler->GetViewRect(browser, rect);
    browser->GetHost()->Invalidate(PET_VIEW);
}

