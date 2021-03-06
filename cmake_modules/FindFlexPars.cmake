FIND_PATH(FLEXPARS_INCLUDE_DIR DoubleField.h /usr/include/flexpars /usr/local/include/flexpars)

FIND_LIBRARY(FLEXPARS_LIBRARY NAMES flexpars PATHS /usr/lib64 /usr/local/lib64 /usr/lib64/flexpars /usr/local/lib64/flexpars /usr/lib /usr/local/lib /usr/lib/flexpars /usr/local/lib/flexpars ) 

IF (FLEXPARS_INCLUDE_DIR AND FLEXPARS_LIBRARY)
   SET(FLEXPARS_FOUND TRUE)
ENDIF (FLEXPARS_INCLUDE_DIR AND FLEXPARS_LIBRARY)


IF (FLEXPARS_FOUND)
   IF (NOT FlexPars_FIND_QUIETLY)
      MESSAGE(STATUS "Found Flexpars: ${FLEXPARS_LIBRARY}")
   ENDIF (NOT FlexPars_FIND_QUIETLY)
ELSE (FLEXPARS_FOUND)
   IF (FlexPars_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find FlexPars")
   ENDIF (FlexPars_FIND_REQUIRED)
ENDIF (FLEXPARS_FOUND)
