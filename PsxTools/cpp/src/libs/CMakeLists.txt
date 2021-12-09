

# Interfaces files for the phenospex utility libraries
set(PSX_UTILS_INTERFACE_FILES 

  phenospex_utils.hpp
)


# Source files for the phenospex utility libraries
set(PSX_UTILS_PRIVATE_FILES 

  ${PSX_UTILS_INTERFACE_FILES}
  phenospex_utils.cpp
)


#
# The Phenospex Utilities Static Library
#

# The static utilities library (.lib/.a) for processing Phenospex data

add_library(psx_utils_static STATIC)

set_target_properties(psx_utils_static PROPERTIES LANGUAGE CXX)

target_compile_features(psx_utils_static PRIVATE cxx_std_17)

if (MSVC)
	# Add the "lib" prefix for generated .lib outputs.
	set_target_properties(psx_utils_static PROPERTIES OUTPUT_NAME "libPsxUtils")
else ()
	set_target_properties(psx_utils_static PROPERTIES OUTPUT_NAME "PsxUtils")
endif (MSVC)

set_target_properties(psx_utils_static PROPERTIES PUBLIC_HEADER ${PSX_UTILS_INTERFACE_FILES})

target_sources(psx_utils_static
PRIVATE
  ${PSX_UTILS_PRIVATE_FILES}
)

if (WIN32)
  #
  # Setting MSVC_STATIC_RUNTIME determines which MSVC runtime to use...
  #
  if (MSVC_STATIC_RUNTIME)
    # To use MultiThreaded (-MT) and MultiThreadedDebug (-MTd)
    message("The PsxUtils static library is using the static runtime libraries.")

    set_property(TARGET psx_utils_static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  else()
    # To use MultiThreadedDLL (-MD) and MultiThreadedDebugDLL (-MDd)
    message("The PsxUtils static library is using the dynamic runtime libraries.")

    set_property(TARGET psx_utils_static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  endif()
endif(WIN32)

#
# The Phenospex Utilities Shared Library
#

# The shared utilities library (.dll/.so/.dylib) for processing Phenospex data

add_library(psx_utils_shared SHARED)

#set_target_properties(psx_utils_shared PROPERTIES
#	VERSION ${SSNX_VERSION}
#	SOVERSION ${SSNX_SOVERSION}
#)

set_target_properties(psx_utils_shared PROPERTIES OUTPUT_NAME "PsxUtils")

set_target_properties(psx_utils_shared PROPERTIES LANGUAGE CXX)

target_compile_features(psx_utils_shared PRIVATE cxx_std_17)

set_target_properties(psx_utils_shared PROPERTIES PUBLIC_HEADER ${PSX_UTILS_INTERFACE_FILES})

target_sources(psx_utils_shared
PRIVATE
	${PSX_UTILS_PRIVATE_FILES}
)

#
# Shared libraries (DLLs) in Windows should always use MSVC dynamic runtime libraries
# Force use MultiThreadedDLL (-MD) and MultiThreadedDebugDLL (-MDd)
#
set_property(TARGET psx_utils_shared PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

#
# IDE Grouping
#

set_target_properties(psx_utils_static psx_utils_shared PROPERTIES FOLDER "Libraries")

#
# Install the Phenospex Utility libraries
#

install(TARGETS psx_utils_static psx_utils_shared
	EXPORT ${PROJECT_NAME}-config
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}-config
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)


#install(DIRECTORY ${LIBSSNX_INCLUDE_DIR}/${PROJECT_NAME}/
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

