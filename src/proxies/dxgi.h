//
// Created by erik9 on 5/11/2024.
//

#ifndef DXGI_H
#define DXGI_H

#include "proxies/setup.h"

namespace proxies::dxgi {
    #pragma optimize("", off)
    
    void DUMMY0()
    {
        #pragma comment(linker, "/EXPORT:ApplyCompatResolutionQuirking=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY1()
    {
        #pragma comment(linker, "/EXPORT:CompatString=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY2()
    {
        #pragma comment(linker, "/EXPORT:CompatValue=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY3()
    {
        #pragma comment(linker, "/EXPORT:DXGIDumpJournal=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY4()
    {
        #pragma comment(linker, "/EXPORT:PIXBeginCapture=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY5()
    {
        #pragma comment(linker, "/EXPORT:PIXEndCapture=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY6()
    {
        #pragma comment(linker, "/EXPORT:PIXGetCaptureState=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY7()
    {
        #pragma comment(linker, "/EXPORT:SetAppCompatStringPointer=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY8()
    {
        #pragma comment(linker, "/EXPORT:UpdateHMDEmulationStatus=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY9()
    {
        #pragma comment(linker, "/EXPORT:CreateDXGIFactory1=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY10()
    {
    #pragma comment(linker, "/EXPORT:CreateDXGIFactory2=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY11()
    {
        #pragma comment(linker, "/EXPORT:CreateDXGIFactory=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY12()
    {
        #pragma comment(linker, "/EXPORT:DXGID3D10CreateDevice=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    void DUMMY13()
    {
        #pragma comment(linker, "/EXPORT:DXGID3D10CreateLayeredDevice=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY14()
    {
        #pragma comment(linker, "/EXPORT:DXGID3D10GetLayeredDeviceSize=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY15()
    {
        #pragma comment(linker, "/EXPORT:DXGID3D10RegisterLayers=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }
    
    void DUMMY16()
    {
        #pragma comment(linker, "/EXPORT:VerQueryDXGIDeclareAdapterRemovalSupportValueW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY17()
    {
        #pragma comment(linker, "/EXPORT:DXGIDisableVBlankVirtualization=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY18()
    {
        #pragma comment(linker, "/EXPORT:DXGIGetDebugInterface1=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY19()
    {
        #pragma comment(linker, "/EXPORT:DXGIReportAdapterConfiguration=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }


    #pragma optimize("", on)

    static ExportDir versionExport{
        {
            {DUMMY0, "ApplyCompatResolutionQuirking"},
            {DUMMY1, "CompatString"},
            {DUMMY2, "CompatValue"},
            {DUMMY3, "DXGIDumpJournal"},
            {DUMMY4, "PIXBeginCapture"},
            {DUMMY5, "PIXEndCapture"},
            {DUMMY6, "PIXGetCaptureState"},
            {DUMMY7, "SetAppCompatStringPointer"},
            {DUMMY8, "UpdateHMDEmulationStatus"},
            {DUMMY9, "CreateDXGIFactory1"},
            {DUMMY10, "CreateDXGIFactory2"},
            {DUMMY11, "CreateDXGIFactory"},
            {DUMMY12, "DXGID3D10CreateDevice"},
            {DUMMY13, "DXGID3D10CreateLayeredDevice"},
            {DUMMY14, "DXGID3D10GetLayeredDeviceSize"},
            {DUMMY15, "DXGID3D10RegisterLayers"},
            {DUMMY16, "VerQueryDXGIDeclareAdapterRemovalSupportValueW"},
            {DUMMY17, "DXGIDisableVBlankVirtualization"},
            {DUMMY18, "DXGIGetDebugInterface1"},
            {DUMMY19, "DXGIReportAdapterConfiguration"}
        },
        LoadLibraryA("C:/Windows/System32/dxgi.dll")
    };

}
#endif //DXGI_H
