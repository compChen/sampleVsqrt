cmake_minimum_required(VERSION 2.8)

project(neonVsqrt)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
	set(ARM 1)
endif()

if (ARM)
	message(STATUS "detected ARM architecture")
	if (UNIX)
		add_compile_options("-mfpu=neon-fp16")
	endif()
endif()


add_executable(vsqrtTest main.cpp)
