# add the include directory of the filter
include_directories(../include)
# declare our filter
set(FILTER_NAME user_SituationDetection)

adtf_add_filter(${FILTER_NAME}
    stdafx.h
    cSituationDetection.h
    cSituationDetection.cpp
)
# Folder for the storage with using Visual Studio
adtf_set_folder(${FILTER_NAME} SituationDetection) 

# Specify where it should be installed to
adtf_install_plugin(${FILTER_NAME} ${CMAKE_INSTALL_BINARY})
