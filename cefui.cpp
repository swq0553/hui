#include "include/cefui.h"

CEFUI* initCefgui(int argc, char** argv)
{
  CefMainArgs args(argc, argv);
  CefExecuteProcess(args, nullptr, NULL);

  CefSettings settings;

  // TODO make cross platform
  CefString(&settings.locales_dir_path) = "cef/linux/lib/locales";

  CefInitialize(args, settings, nullptr, NULL);

  return new CEFUI();
}

CEFUI::CEFUI()
{
  CefWindowInfo windowInfo;
  CefBrowserSettings settings;

  windowInfo.SetAsWindowless(0, true);

  renderHandler = new RenderHandler();

  client = new BrowserClient(renderHandler);
  browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "", settings, nullptr);
}

void CEFUI::load(const char* url)
{
  if (!renderHandler->initialized)
    renderHandler->init();

  browser->GetMainFrame()->LoadURL(url);
}

void CEFUI::draw(void)
{
  CefDoMessageLoopWork();
  renderHandler->draw();
}

void CEFUI::reshape(int w, int h)
{
  renderHandler->reshape(w, h);
  browser->GetHost()->WasResized();
}

void CEFUI::mouseMove(int x, int y)
{
  mouseX = x;
  mouseY = y;

  CefMouseEvent event;
  event.x = x;
  event.y = y;

  browser->GetHost()->SendMouseMoveEvent(event, false);
}

void CEFUI::mouseClick(int btn, int state)
{
  CefMouseEvent event;
  event.x = mouseX;
  event.y = mouseY;

  bool mouseUp = state == 0;
  CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
  browser->GetHost()->SendMouseClickEvent(event, btnType, mouseUp, 1);
}

void CEFUI::keyPress(int key)
{
  CefKeyEvent event;
  event.native_key_code = key;
  event.type = KEYEVENT_KEYDOWN;

  browser->GetHost()->SendKeyEvent(event);
}

void CEFUI::executeJS(const char* command)
{
  CefRefPtr<CefFrame> frame = browser->GetMainFrame();
  frame->ExecuteJavaScript(command, frame->GetURL(), 0);

  // TODO limit frequency of texture updating
  CefRect rect;
  renderHandler->GetViewRect(browser, rect);
  browser->GetHost()->Invalidate(PET_VIEW);
}
