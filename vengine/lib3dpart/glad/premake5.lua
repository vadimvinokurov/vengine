project "GLAD"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}
	
	includedirs
	{ 
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "VE_DEBUG"
		runtime "Debug"
		optimize "Off"
		symbols "On"
		
	filter "configurations:Release"
		defines "VE_RELEASE"
		runtime "Release"
		optimize "Speed"
		symbols "Off"
		
	filter "configurations:Profile"
		defines "VE_PROFILE"
		runtime "Release"
		optimize "Speed"
		symbols "Off"
	
	filter "configurations:Retail"
		defines "VE_RETAIL"
		runtime "Release"
		optimize "Speed"
		symbols "Off"