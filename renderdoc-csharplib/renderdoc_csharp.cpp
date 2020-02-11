#define WIN32
#include "api/app/renderdoc_app.h"
#include <wrl.h>
#include <cassert>

#ifdef RENDERDOCCSHARPLIB_EXPORTS
#define RENDERDOC_API extern "C" __declspec(dllexport)
#else
#define RENDERDOC_API __declspec(dllimport)
#endif

RENDERDOC_API_1_4_0* ms_renderdoc = nullptr;

namespace Renderdoc
{
    RENDERDOC_API void _cdecl Initialize()
    {
        if (HMODULE mod = LoadLibrary(L"renderdoc.dll"))
        {
            pRENDERDOC_GetAPI RENDERDOC_GetAPI = (pRENDERDOC_GetAPI)GetProcAddress(mod, "RENDERDOC_GetAPI");
            int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_4_0, (void**)&ms_renderdoc);
            assert(ret == 1);

            ms_renderdoc->SetCaptureFilePathTemplate("renderdoc_captures/capture");
        }
    }

    RENDERDOC_API void _cdecl BeginCapture()
    {
        if (ms_renderdoc)
            ms_renderdoc->StartFrameCapture(nullptr, nullptr);
    }

    RENDERDOC_API void _cdecl EndCapture()
    {
        if (ms_renderdoc)
            ms_renderdoc->EndFrameCapture(nullptr, nullptr);
    }
}