workspace 'Wabisabi'

architecture 'x86' 
configurations
{
	'Debug',
	'Release',
}
outputdir = '%{cfg.buildcfg}-%{cfg.architecture}'

include 'Wabisabi/vendor/GLFW'
include 'Wabisabi/vendor/Glad'
include 'Wabisabi/vendor/imgui'

libtype = 'static'
if(libtype == 'static') then
	libdefine = 'WB_STATIC_LINK'
	wabibuild = 'WB_BUILD_LIB'
	switch = 'on'
	copycomand = ''
elseif(libtype == 'dynamic') then 
	libdefine = 'WB_DYNAMIC_LINK'
	wabibuild = 'WB_BUILD_DLL'
	switch = 'off'
	copycomand = '{COPY} %{cfg.buildtarget.relpath} ../bin/' .. outputdir .. '/Sandbox'
end
project 'Wabisabi'
	location 'Wabisabi'
	kind 'StaticLib'
	language 'C++'
	staticruntime(switch)
	targetdir('bin/'.. outputdir .. '/%{prj.name}')
	objdir('bin-int/'.. outputdir .. '/%{prj.name}')
	pchheader 'wbpch.h'
	pchsource 'Wabisabi/src/wbpch.cpp'
	linkedProject = '%{prj.name}'
	files
	{
		'%{prj.name}/src/**.h',
		'%{prj.name}/src/**.cpp',
		'%{prj.name}/vendor/stb/stb/stb_image.cpp', -- добавл€ю stb в проект
		'%{prj.name}/vendor/stb/stb/stb_image.h',
	}
	includedirs
	{
	 '%{prj.name}/vendor/GLFW/include',
	 '%{prj.name}/src',
	 '%{prj.name}/vendor/spdlog/include',
	 '%{prj.name}/vendor/Glad/include',
	 '%{prj.name}/vendor/imgui',
	 '%{prj.name}/vendor/stb',
	 '%{prj.name}/vendor/glm/',
	}
	links
	{
		'Glad',
		'GLFW',
		'opengl32.lib',
		'ImGui',
	}
	filter 'system:windows'
		cppdialect 'C++17'
		
		systemversion 'latest'
		defines
		{
			libdefine,
			wabibuild,
			"GLFW_INCLUDE_NONE",
		}
		postbuildcommands
		{
			copycomand,
		--	('{COPY} %{cfg.buildtarget.relpath} ../bin/' .. outputdir .. '/Sandbox')
		}
	filter 'configurations:Debug'
		defines 'WB_DEBUG'
		symbols 'On'
	filter 'configurations:Release'
		defines 'WB_RELEASE'
		optimize 'On'
project 'Sandbox'

location 'Sandbox'
	kind 'ConsoleApp'
	language 'C++'
	cppdialect 'C++17'
	staticruntime(switch)
	targetdir('bin/'.. outputdir .. '/%{prj.name}')
	objdir('bin-int/'.. outputdir .. '/%{prj.name}')

	files
	{
		'%{prj.name}/src/**.h',
		'%{prj.name}/src/**.cpp'
		'%{prj.name}/shaders/**.vert'
		'%{prj.name}/shaders/**.frag'
		'%{prj.name}/shaders/**.glsl'
		'%{prj.name}/shaders/**.geom'
	}
	includedirs
	{
		'Wabisabi/src',
		'Wabisabi/vendor/spdlog/include',
		'Wabisabi/vendor/glm/',
	}
	links
	{
		'Wabisabi'
	}
	filter 'system:windows'

		systemversion 'latest'
		defines
		{
			libdefine,
		}
		filter 'configurations:Debug'
			defines 'APP_DEBUG'
			symbols 'On'
		filter 'configurations:Release'
			defines 'APP_RELEASE'
			optimize 'On'