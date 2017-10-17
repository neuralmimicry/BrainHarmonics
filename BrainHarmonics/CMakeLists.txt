cmake_minimum_required(VERSION 2.8)
 
# General build settings
IF (NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Possible build types: None Debug Release RelWithDebInfo MinSizeRel")
ENDIF()

PROJECT(BrainHarmonics)
SET(PROJECT_VERSION_MAJOR 0)
SET(PROJECT_VERSION_MINOR 1)
SET(PROJECT_VERSION_PATCH 0)
SET(PROJECT_VERSION_NOREV ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
IF (NOT PROJECT_REVISION)
	# EXECUTE_PROCESS(COMMAND svnversion OUTPUT_VARIABLE PROJECT_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE)
	EXECUTE_PROCESS(COMMAND git rev-parse HEAD OUTPUT_VARIABLE PROJECT_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDIF()
SET(PROJECT_VERSION ${PROJECT_VERSION_NOREV}-r${PROJECT_REVISION})

# Define installation paths.
SET(CMAKE_MODULE_PATH "~/Developer/BrainHarmonics/BrainHarmonics/" ${CMAKE_MODULE_PATH})
INCLUDE(GNUInstallDirs)

# Set compiler info
SET(CC_CLANG FALSE)
SET(CC_GCC FALSE)
SET(CC_ICC FALSE)
SET(CC_MSVC FALSE)

IF ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	SET(CC_CLANG TRUE)
ELSEIF ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
	SET(CC_GCC TRUE)
ELSEIF ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
	SET(CC_ICC TRUE)
ELSEIF ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
	SET(CC_MSVC TRUE)
ENDIF()

# Set operating system info
SET(OS_UNIX FALSE)
SET(OS_LINUX FALSE)
SET(OS_MACOSX FALSE)
SET(OS_WINDOWS FALSE)

IF (UNIX)
	SET(OS_UNIX TRUE)
	ADD_DEFINITIONS(-DOS_UNIX=1)
ENDIF()

IF (UNIX AND "${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	SET(OS_LINUX TRUE)
	ADD_DEFINITIONS(-DOS_LINUX=1)
ENDIF()

IF (UNIX AND APPLE AND "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
	SET(OS_MACOSX TRUE)
	ADD_DEFINITIONS(-DOS_MACOSX=1)
ENDIF()

IF (WIN32 AND "${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
	SET(OS_WINDOWS TRUE)
	ADD_DEFINITIONS(-DOS_WINDOWS=1)
ENDIF()

# Check GCC compiler version, 4.9 is needed at least for atomics support.
IF (CC_GCC)
	IF (${CMAKE_C_COMPILER_VERSION} VERSION_LESS "4.9.0")
		MESSAGE(FATAL_ERROR "GCC version found is ${CMAKE_C_COMPILER_VERSION}. Required >= 4.9.0.")
	ENDIF()
ENDIF()

# Check Clang compiler version, 3.6 is needed at least for atomics support.
IF (CC_CLANG)
	IF (${CMAKE_C_COMPILER_VERSION} VERSION_LESS "3.6.0")
		MESSAGE(FATAL_ERROR "Clang version found is ${CMAKE_C_COMPILER_VERSION}. Required >= 3.6.0.")
	ENDIF()
ENDIF()

# Test if we are on a big-endian architecture
INCLUDE(TestBigEndian)
TEST_BIG_ENDIAN(SYSTEM_BIGENDIAN)

# Check size of various types
INCLUDE(CheckTypeSize)
CHECK_TYPE_SIZE("size_t" SIZEOF_SIZE_T)
CHECK_TYPE_SIZE("void *" SIZEOF_VOID_PTR)

IF (NOT "${SIZEOF_VOID_PTR}" STREQUAL "${SIZEOF_SIZE_T}")
	MESSAGE(SEND_ERROR "Size of void * and size_t must be the same!")
ENDIF()

# Check threads support (almost nobody implements C11 threads yet!)
FIND_PACKAGE(Threads)
SET(HAVE_PTHREADS FALSE)
SET(HAVE_WIN32_THREADS FALSE)

IF (DEFINED "CMAKE_USE_PTHREADS_INIT")
	IF (${CMAKE_USE_PTHREADS_INIT})
		SET(HAVE_PTHREADS TRUE)
		ADD_DEFINITIONS(-DHAVE_PTHREADS=1)
	ENDIF()
ENDIF()

IF (DEFINED "CMAKE_USE_WIN32_THREADS_INIT")
	IF (${CMAKE_USE_WIN32_THREADS_INIT})
		SET(HAVE_WIN32_THREADS TRUE)
		ADD_DEFINITIONS(-DHAVE_WIN32_THREADS=1)
	ENDIF()
ENDIF()

# Add system defines for header features
IF (OS_UNIX AND HAVE_PTHREADS)
	# POSIX system (Unix, Linux, MacOS X)
	ADD_DEFINITIONS(-D_XOPEN_SOURCE=700)
	ADD_DEFINITIONS(-D_DEFAULT_SOURCE=1)

	IF (OS_MACOSX)
		ADD_DEFINITIONS(-D_DARWIN_C_SOURCE=1)
	ENDIF()
ENDIF()

IF (OS_WINDOWS AND (CC_GCC OR CC_CLANG))
	ADD_DEFINITIONS(-D__USE_MINGW_ANSI_STDIO=1)
ENDIF()

# C11 standard needed (atomics, threads)
IF (CC_GCC OR CC_CLANG)
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

# Enable all warnings for GCC / Clang
IF (CC_GCC OR CC_CLANG)
	SET(WARN_COMMON_FLAGS "-pedantic -Wall -Wextra")
	SET(WARN_C_FLAGS "")
	SET(WARN_CXX_FLAGS "")

	IF (CC_GCC)
		# Enable all useful warnings in GCC one-by-one.
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wunused -Wundef -Wformat=2 -Winit-self -Wuninitialized")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wredundant-decls -Wmissing-declarations -Wstack-protector")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wshadow -Wfloat-equal -Wconversion -Wstrict-overflow=5")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wdouble-promotion")

		SET(WARN_C_FLAGS "${WARN_C_FLAGS} -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs")
		SET(WARN_C_FLAGS "${WARN_C_FLAGS} -Wbad-function-cast -Wjump-misses-init -Wunsuffixed-float-constants")
	ENDIF()

	IF (CC_CLANG)
		# Enable all warnings in Clang, then turn off useless ones.
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Weverything -Wno-packed -Wno-padded -Wno-unreachable-code-break")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wno-disabled-macro-expansion -Wno-reserved-id-macro -Wno-vla")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wno-parentheses-equality -Wno-covered-switch-default")
		SET(WARN_COMMON_FLAGS "${WARN_COMMON_FLAGS} -Wno-used-but-marked-unused -Wno-cast-align")

		SET(WARN_CXX_FLAGS "${WARN_CXX_FLAGS} -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-old-style-cast")
	ENDIF()

	# Apply all flags.
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARN_COMMON_FLAGS} ${WARN_C_FLAGS}")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_COMMON_FLAGS} ${WARN_CXX_FLAGS}")
ENDIF()

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Search for external libraries with pkg-config.
INCLUDE(FindPkgConfig)

# Basic USB device support
PKG_CHECK_MODULES(LIBUSB1 REQUIRED libusb-1.0>=1.0.17)
# Check OpenCV support
PKG_CHECK_MODULES(OPENCV REQUIRED opencv>=3.0)
# LibCAER Dynapse support
PKG_CHECK_MODULES(LIBCAER REQUIRED libcaer>=2.0)
# LibPCAP support
find_package(PCAP)
# VTK Graphics library
find_package(VTK REQUIRED NO_MODULE)
include(${VTK_USE_FILE})
# Python locator
find_package(PythonInterp)
find_package(PythonLibs 2.7 REQUIRED)
find_package(NumPy REQUIRED)
# Override Python path if not detecting v2 correctly.
#SET(PYTHON_ROOT "/opt/local/Library/Frameworks/Python.framework/Versions/2.7")
#SET(PYTHON_LIBRARY "${PYTHON_ROOT}/lib")
#SET(PYTHON_INCLUDE_DIR "${PYTHON_ROOT}/include/python2.7")
#SET(NUMPY_LIBRARY_DIRS "${PYTHON_ROOT}/lib/python2.7/site-packages/numpy/lib")
#SET(NUMPY_INCLUDE_DIR "${PYTHON_ROOT}/lib/python2.7/site-packages/numpy/core/include")

SET(BRAINHARMONICS_INCDIRS ${PYTHON_INCLUDE_DIRS} ${PYTHON_NUMPY_INCLUDE_DIR} ${VTK_INCLUDE_DIRS} ${PCAP_INCLUDE_DIRS} ${LIBCAER_INCLUDE_DIRS} ${LIBUSB1_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})
SET(BRAINHARMONICS_LIBDIRS ${PYTHON_LIBRARY_DIRS} ${VTK_LIBRARY_DIRS} ${PCAP_LIBRARY_DIRS} ${LIBCAER_LIBRARY_DIRS} ${LIBUSB1_LIBRARY_DIRS} ${OPENCV_LIBDIR})
SET(BRAINHARMONICS_LIBS ${PYTHON_LIBRARIES} ${VTK_LIBRARIES} ${PCAP_LIBRARY} ${LIBCAER_LIBRARIES} ${LIBUSB1_LIBRARIES} ${OPENCV_LIBRARIES})
 
# Threads support
SET(LIBCAER_LIBS ${LIBCAER_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# Add local directory to include paths
SET(LIBCAER_INCDIRS ${LIBCAER_INCDIRS} ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE BRAINHARMONICS_SOURCES "*.cc")
file(GLOB_RECURSE BRAINHARMONICS_HEADERS "*.h")

foreach (_headerFile ${BRAINHARMONICS_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND BRAINHARMONICS_INCDIRS ${_dir})
endforeach()
LIST(REMOVE_DUPLICATES BRAINHARMONICS_INCDIRS)

INCLUDE_DIRECTORIES(${BRAINHARMONICS_INCDIRS})
LINK_DIRECTORIES(${BRAINHARMONICS_LIBDIRS})

SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed")

# Set full RPATH
SET(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
IF (OS_MACOSX)
	SET(CMAKE_MACOSX_RPATH TRUE)
ENDIF()

# Subdirectories
#ADD_SUBDIRECTORY(include)
#ADD_SUBDIRECTORY(includecpp)
#ADD_SUBDIRECTORY(~/Developer/BrainHarmonics/BrainHarmonics)

file(GLOB MY_SRC
    "*.h"
    "*.cc"
)

# Generate pkg-config file
FOREACH (LIB ${CMAKE_THREAD_LIBS_INIT})
	SET(PRIVATE_LIBS "${LIB} ${PRIVATE_LIBS}")
ENDFOREACH()

add_executable(BrainHarmonics ${MY_SRC})
 
target_link_libraries(BrainHarmonics ${BRAINHARMONICS_LIBS})

INSTALL(FILES ${CMAKE_BINARY_DIR}/brainharmonics.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# Automatic documentation generation support
FIND_PACKAGE(Doxygen)

IF (DOXYGEN_FOUND)
#	ADD_SUBDIRECTORY(docs)
add_custom_target (docs ALL
                     ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
                     )
ENDIF()

# Print info summary for debug purposes
MESSAGE(STATUS "Project version is: ${PROJECT_VERSION}")
MESSAGE(STATUS "Compiler is Clang: ${CC_CLANG}")
MESSAGE(STATUS "Compiler is GCC: ${CC_GCC}")
MESSAGE(STATUS "Compiler is IntelCC: ${CC_ICC}")
MESSAGE(STATUS "Compiler is MS VisualC: ${CC_MSVC}")
MESSAGE(STATUS "OS is Unix: ${OS_UNIX}")
MESSAGE(STATUS "OS is Linux: ${OS_LINUX}")
MESSAGE(STATUS "OS is MacOS X: ${OS_MACOSX}")
MESSAGE(STATUS "OS is Windows: ${OS_WINDOWS}")
MESSAGE(STATUS "System is big-endian: ${SYSTEM_BIGENDIAN}")
MESSAGE(STATUS "Thread support is PThreads: ${HAVE_PTHREADS}")
MESSAGE(STATUS "Thread support is Win32 Threads: ${HAVE_WIN32_THREADS}")
MESSAGE(STATUS "C flags are: ${CMAKE_C_FLAGS}")
MESSAGE(STATUS "CXX flags are: ${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "Include directories are: ${BRAINHARMONICS_INCDIRS}")
MESSAGE(STATUS "Library directories are: ${BRAINHARMONICS_LIBDIRS}")
MESSAGE(STATUS "Linked libraries are: ${BRAINHARMONICS_LIBS}")
MESSAGE(STATUS "Compiled source files are: ${BRAINHARMONICS_SRC_FILES}")
MESSAGE(STATUS "Final install libdir is: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
MESSAGE(STATUS "Final install includedir is: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}")

