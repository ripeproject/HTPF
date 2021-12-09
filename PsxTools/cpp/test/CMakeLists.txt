
find_package(Catch2 REQUIRED)

add_executable(verification_tests)

target_compile_features(verification_tests
PUBLIC
    cxx_noexcept
    cxx_std_17
)

#
# Setting MSVC_STATIC_RUNTIME determines which MSVC runtime to use...
#
if (MSVC_STATIC_RUNTIME)
	set_property(TARGET verification_tests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
	set_property(TARGET verification_tests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

target_sources(verification_tests
PRIVATE
  verification_tests.cpp
)

target_link_libraries(verification_tests
PRIVATE
    Catch2::Catch2WithMain
    psx_utils_static
)

include(CTest)
include(Catch)
catch_discover_tests(verification_tests)

#
# IDE Grouping
#

set_target_properties(verification_tests PROPERTIES FOLDER "Tests")
