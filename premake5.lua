-- premake5.lua
workspace "vengine"
	architecture "x64"
	configurations 
	{
		"Debug",
		"Release",
		"Profile",
		"Retail"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "vengine"
	location "vengine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/lib3dpart/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"VE_PLATFORM_WINDOWS",
			"VE_BUILD_DLL",
			"VE_ENGINE_REGION"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "VE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "VE_RELEASE"
		symbols "On"
		optimize "On"
		
	filter "configurations:Profile"
		defines "VE_PROFILE"
		optimize "On"
	
	filter "configurations:Retail"
		defines "VE_RETAIL"
		optimize "On"
	
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"vengine/lib3dpart/spdlog/include",
		"vengine/src"
	}
	
	links
	{
		"vengine"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"VE_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "VE_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "VE_RELEASE"
		symbols "On"
		optimize "On"
		
	filter "configurations:Profile"
		defines "VE_PROFILE"
		optimize "On"
	
	filter "configurations:Retail"
		defines "VE_RETAIL"
		optimize "On"
	
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"
