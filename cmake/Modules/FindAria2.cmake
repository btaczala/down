#  ARIA2_FOUND
#  ARIA2_INCLUDE_DIRS
#  ARIA2_LIBRARIES
#  ARIA2_DEFINITIONS

find_path(ARIA2_INCLUDE_DIR aria2/aria2.h
          PATH_SUFFIXES aria2 )

find_library(ARIA2_LIBRARY NAMES aria2)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set ARIA2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LibAria2  DEFAULT_MSG
                                  ARIA2_LIBRARY ARIA2_INCLUDE_DIR)

mark_as_advanced(ARIA2_INCLUDE_DIR ARIA2_LIBRARY )

set(ARIA2_LIBRARIES ${ARIA2_LIBRARY})
set(ARIA2_INCLUDE_DIRS ${ARIA2_INCLUDE_DIR})

if(ARIA2_LIBRARIES AND ARIA2_INCLUDE_DIRS)
    set(ARIA2_FOUND ON)
endif()
