#include "include/browser_app.h"

App::App(void) {
    //
}

void App::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
    registrar->AddCustomScheme("huios", true, false, false);
}
