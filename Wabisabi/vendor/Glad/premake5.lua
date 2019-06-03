project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c",
    }
	includedirs
	{
		"include/",
	}
    
	filter "system:windows"
        systemversion "latest"
		defines 
		{ 
            "_CRT_SECURE_NO_WARNINGS"
		}
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
