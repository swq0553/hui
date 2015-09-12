#ifndef BROWSER_APP
#define BROWSER_APP

#include "cef_app.h"

class App : public CefApp {
    public:
        App(void);

        void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar);


        IMPLEMENT_REFCOUNTING(App);
};

#endif
