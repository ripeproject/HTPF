
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Create the version information code
configure_file(version.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/version.cpp @ONLY)

#
# The Phenospex Experiment Planner
#

if(WIN32)
    # Include a RC file for windows
	set(resource_files
  		./Resources/psx_planner.ico
  		./Resources/psx_planner.rc
	)

#	source_group("Resources" FILES
#		${resource_files}
#)

elseif(APPLE)

    # Add an icon for the apple .app file
	set(resource_files
  		Resources/psx_planner.icns
	)

endif()

add_executable(PsxPlanner WIN32 MACOSX_BUNDLE)

set_target_properties(PsxPlanner PROPERTIES LANGUAGE CXX)

target_compile_features(PsxPlanner PRIVATE cxx_std_17)

target_sources(PsxPlanner
PRIVATE

	${resource_files}
)

include(${wxWidgets_USE_FILE})


#
# Setting MSVC_STATIC_RUNTIME determines which MSVC runtime to use...
if (MSVC_STATIC_RUNTIME)
	# To use MultiThreaded (-MT) and MultiThreadedDebug (-MTd)
	set_property(TARGET PsxPlanner PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
	# To use MultiThreadedDLL (-MD) and MultiThreadedDebugDLL (-MDd)
	set_property(TARGET PsxPlanner PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()


if(APPLE)
    set_target_properties(PsxPlanner PROPERTIES
        RESOURCE "./Resources/AltusNR3.icns"
        MACOSX_BUNDLE_ICON_FILE AltusNR3.icns
        MACOSX_BUNDLE_COPYRIGHT "Copyright University of Illinois"
        MACOSX_BUNDLE_GUI_IDENTIFIER "edu.illinois.ripe"
        )
endif()


target_link_libraries(PsxPlanner PRIVATE ${wxWidgets_LIBRARIES})

message(STATUS "CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")


#
# Install the PsxPlanner executable
#
#install(TARGETS PsxPlanner

install(TARGETS PsxPlanner
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


