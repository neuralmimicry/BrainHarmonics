# - Try to find libcaer include dirs and libraries
#
# Usage of this module as follows:
#
#     find_package(CAER)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  CAER_ROOT_DIR             Set this variable to the root installation of
#                            libcaer if the module has problems finding the
#                            proper installation path.
#
# Variables defined by this module:
#
#  CAER_FOUND                System has libcaer, include and library dirs found
#  CAER_INCLUDE_DIR          The libcaer include directories.
#  CAER_LIBRARY              The libcaer library (possibly includes a thread
#                            library e.g. required by pf_ring's libcaer)
#  HAVE_PF_RING              If a found version of libcaer supports PF_RING

find_path(CAER_ROOT_DIR
    NAMES include/caer.h
)

find_path(CAER_INCLUDE_DIR
    NAMES caer.h
    HINTS ${CAER_ROOT_DIR}/include
)

find_library(CAER_LIBRARY
    NAMES caer
    HINTS ${CAER_ROOT_DIR}/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CAER DEFAULT_MSG
    CAER_LIBRARY
    CAER_INCLUDE_DIR
)

include(CheckCSourceCompiles)
set(CMAKE_REQUIRED_LIBRARIES ${CAER_LIBRARY})
check_c_source_compiles("int main() { return 0; }" CAER_LINKS_SOLO)
set(CMAKE_REQUIRED_LIBRARIES)

# check if linking against libcaer also needs to link against a thread library
if (NOT CAER_LINKS_SOLO)
    find_package(Threads)
    if (THREADS_FOUND)
        set(CMAKE_REQUIRED_LIBRARIES ${CAER_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
        check_c_source_compiles("int main() { return 0; }" CAER_NEEDS_THREADS)
        set(CMAKE_REQUIRED_LIBRARIES)
    endif ()
    if (THREADS_FOUND AND CAER_NEEDS_THREADS)
        set(_tmp ${CAER_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
        list(REMOVE_DUPLICATES _tmp)
        set(CAER_LIBRARY ${_tmp}
            CACHE STRING "Libraries needed to link against libcaer" FORCE)
    else ()
        message(FATAL_ERROR "Couldn't determine how to link against libcaer")
    endif ()
endif ()

include(CheckFunctionExists)
set(CMAKE_REQUIRED_LIBRARIES ${CAER_LIBRARY})
check_function_exists(caer_get_pfring_id HAVE_PF_RING)
set(CMAKE_REQUIRED_LIBRARIES)

mark_as_advanced(
    CAER_ROOT_DIR
    CAER_INCLUDE_DIR
    CAER_LIBRARY
)
