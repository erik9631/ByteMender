//
// Created by erik9 on 5/11/2024.
//

#ifndef VERSION_H
#define VERSION_H
#include "proxies/setup.h"

namespace proxies::version {
    #pragma optimize("", off)


    void DUMMY0()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY1()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY2()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY3()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY4()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY5()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY6()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY7()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY8()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY9()
    {
        #pragma comment(linker, "/EXPORT:VerFindFileA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY10()
    {
    #pragma comment(linker, "/EXPORT:VerFindFileW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY11()
    {
        #pragma comment(linker, "/EXPORT:VerInstallFileA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY12()
    {
        #pragma comment(linker, "/EXPORT:VerInstallFileW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY13()
    {
        #pragma comment(linker, "/EXPORT:VerLanguageNameA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY14()
    {
        #pragma comment(linker, "/EXPORT:VerLanguageNameW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY15()
    {
        #pragma comment(linker, "/EXPORT:VerQueryValueA=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    void DUMMY16()
    {
        #pragma comment(linker, "/EXPORT:VerQueryValueW=" __FUNCDNAME__)
        CALL_DUMMY();
        function8byteFill = 0x9090909090909090;
    }

    #pragma optimize("", on)

    static ExportDir versionExport{
        {
            {DUMMY0, "GetFileVersionInfoA"},
            {DUMMY1, "GetFileVersionInfoByHandle"},
            {DUMMY2, "GetFileVersionInfoExA"},
            {DUMMY3, "GetFileVersionInfoExW"},
            {DUMMY4, "GetFileVersionInfoSizeA"},
            {DUMMY5, "GetFileVersionInfoSizeExA"},
            {DUMMY6, "GetFileVersionInfoSizeExW"},
            {DUMMY7, "GetFileVersionInfoSizeW"},
            {DUMMY8, "GetFileVersionInfoW"},
            {DUMMY9, "VerFindFileA"},
            {DUMMY10, "VerFindFileW"},
            {DUMMY11, "VerInstallFileA"},
            {DUMMY12, "VerInstallFileW"},
            {DUMMY13, "VerLanguageNameA"},
            {DUMMY14, "VerLanguageNameW"},
            {DUMMY15, "VerQueryValueA"},
            {DUMMY16, "VerQueryValueW"}
        },
        LoadLibraryA("C:/Windows/System32/version.dll")
    };

}
#endif //VERSION_H
