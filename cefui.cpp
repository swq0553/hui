#include "include/cefui.h"


CEFUI::CEFUI(int argc, char **argv, RenderHandler *_render_handler) {
    // Static Init Stuff... should this class be a singleton?
    CefMainArgs args(argc, argv);
    CefExecuteProcess(args, nullptr, NULL);

    CefSettings settings;
    //CefString(&settings.locales_dir_path) = "/usr/local/lib/locales";

    CefInitialize(args, settings, nullptr, NULL);

    // Per GUI init stuff
    CefWindowInfo windowInfo;
    CefBrowserSettings browser_settings;

    windowInfo.SetAsWindowless(0, true);

    renderHandler = _render_handler;

    client = new BrowserClient(renderHandler);
    browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "", browser_settings, nullptr);
}

void CEFUI::load(const char* url) {
    browser->GetMainFrame()->LoadURL(url);
}

void CEFUI::draw(void) {
    CefDoMessageLoopWork();
    renderHandler->Draw();
}

void CEFUI::reshape(int w, int h) {
    renderHandler->Reshape(w, h);
    browser->GetHost()->WasResized();
}

void CEFUI::mouseMove(int x, int y) {
    mouseX = x;
    mouseY = y;

    CefMouseEvent event;
    event.x = x;
    event.y = y;

    browser->GetHost()->SendMouseMoveEvent(event, false);
}

void CEFUI::mouseClick(int btn, int state) {
    CefMouseEvent event;
    event.x = mouseX;
    event.y = mouseY;

    bool mouseUp = state == 0;
    CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
    browser->GetHost()->SendMouseClickEvent(event, btnType, mouseUp, 1);
}

void CEFUI::keyPress(int key) {
    CefKeyEvent event;
    event.native_key_code = key;
    event.type = KEYEVENT_KEYDOWN;

    browser->GetHost()->SendKeyEvent(event);
}

void CEFUI::executeJS(const char* command) {
    CefRefPtr<CefFrame> frame = browser->GetMainFrame();
    frame->ExecuteJavaScript(command, frame->GetURL(), 0);

    // TODO limit frequency of texture updating
    CefRect rect;
    renderHandler->GetViewRect(browser, rect);
    browser->GetHost()->Invalidate(PET_VIEW);
}
