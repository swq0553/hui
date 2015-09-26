#include "hui/browser_app.h"

namespace HUI {

    App::App(RenderProcessHandler *_render_process_handler) {
        render_process_handler = _render_process_handler;
    }

    void App::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
        registrar->AddCustomScheme("huios", true, false, false);
    }

    CefRefPtr<CefRenderProcessHandler> App::GetRenderProcessHandler(void) {
        return render_process_handler;
    }

}
