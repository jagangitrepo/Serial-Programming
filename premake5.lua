require "cmake"

-- premake5.lua
workspace "Serial-Programming"
   configurations { "Debug", "Release" }

project "Serial-Async"
   kind "ConsoleApp"
   language "C++"
   cppdialect 'c++17'
   targetdir "bin/%{cfg.buildcfg}"

   links { "pthread" }

   files { 
      "include/**.h",
      "src/**.*"
   }

   includedirs {
      "include"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"