
# Find all the packages needed by this code
find_package(wxWidgets REQUIRED COMPONENTS core base)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Create the version information code
configure_file(version.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/version.cpp @ONLY)

#
# The PsxLoc Program
#
# A utility program for converting between scanner location and 
#	scale position
#

if(WIN32)
    # Include a RC file for windows
	set(resource_files
#  		./Resources/[filename].ico
  		./Resources/psxloc.rc
	)

#	source_group("Resources" FILES
#		${resource_files} )

elseif(APPLE)

    # Add an icon for the apple .app file
#	set(resource_files
#  		Resources/[filename].icns )

endif()

add_executable(psxloc WIN32 MACOSX_BUNDLE)

set_target_properties(psxloc PROPERTIES LANGUAGE CXX)

target_compile_features(psxloc PRIVATE cxx_std_17)

target_sources(psxloc
PRIVATE
	MainFrame.hpp
	MainFrame.cpp

	psxloc.cpp
	
	${resource_files}
)

include(${wxWidgets_USE_FILE})

#target_include_directories(psxloc PRIVATE ${LIBSSNX_INCLUDE_DIR} ${CMAKE_INSTALL_PREFIX}/include)


#
# Setting MSVC_STATIC_RUNTIME determines which MSVC runtime to use...
#
if (MSVC_STATIC_RUNTIME)
	# To use MultiThreaded (-MT) and MultiThreadedDebug (-MTd)
	set_property(TARGET psxloc PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
	# To use MultiThreadedDLL (-MD) and MultiThreadedDebugDLL (-MDd)
	set_property(TARGET psxloc PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()


if(APPLE)
    set_target_properties(psxloc PROPERTIES
        RESOURCE "./Resources/AltusNR3.icns"
        MACOSX_BUNDLE_ICON_FILE AltusNR3.icns
        MACOSX_BUNDLE_COPYRIGHT "Copyright University of Illinois"
        MACOSX_BUNDLE_GUI_IDENTIFIER "edu.illinois.ripe"
        )
endif()


target_link_libraries(psxloc PRIVATE psx_utils_static)
target_link_libraries(psxloc PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(psxloc PRIVATE ${wxWidgets_LIBRARIES})

set_target_properties(psxloc PROPERTIES FOLDER "Tools")


#
# Install the PsxLoc executable
#

install(TARGETS psxloc
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


