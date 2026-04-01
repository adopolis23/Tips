workspace "TipsWorkspace"
    architecture "x86_64"
    configurations { "Debug", "Release" }

project "Tips"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files {
        "src/**.h",
        "src/**.cpp",
        "src/scene/**.cpp",
        "libs/glad/src/glad.c",

        -- ImGui core files 
        "external/imgui/imgui.cpp",
        "external/imgui/imgui_draw.cpp",
        "external/imgui/imgui_widgets.cpp",
        "external/imgui/imgui_tables.cpp",
        "external/imgui/imgui_demo.cpp",

        -- ImGui core headers
        "external/imgui/*.h",

        -- SDL2 + OpenGL backend
        "external/imgui/backends/imgui_impl_sdl2.cpp",
        "external/imgui/backends/imgui_impl_sdlrenderer2.cpp",
        "external/imgui/backends/imgui_impl_sdl2.h",
        "external/imgui/backends/imgui_impl_opengl3.cpp",
        "external/imgui/backends/imgui_impl_opengl3.h"
    }

    includedirs {
        "src",
        "libs/glad/include",
        "/usr/include",
        "libs/glad/include",

        "external/imgui",
        "external/imgui/backends",

        -- linux include path
        "/usr/include/SDL2",
        "E:/dev/vcpkg/installed/x64-windows/include"
    }

    libdirs { "E:/dev/vcpkg/installed/x64-windows/lib" }

    filter "system:linux"
        links { "SDL2", "GL", "dl", "pthread" }
        defines { 'PATH="/home/bran406/dev/OpenGL/"' }

    filter "system:windows"
        links { "SDL2", "opengl32" }
        defines { 'PATH="E:/dev/OpenGL/"' }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
