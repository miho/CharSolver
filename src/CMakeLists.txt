
# add all .cpp files to project (stored in "raidmonitor_SRCS" variable")

# and finally an resource file
set(_CHARSOLVER_SRCS
	charsolver.cpp
	)

set(_IMG_CONVERT_SRCS
	img-convert.cpp
	)


QT4_WRAP_UI(_UIS_H ${_UIS})


include_directories(
			${CMAKE_CURRENT_BINARY_DIR}
			${QT_INCLUDE_DIR}
			${QT_QTGUI_INCLUDE_DIR}
			${QT_QTGUI_TOOLS_INCLUDE_DIR}

			${FLEXPARS_INCLUDE_DIR}
			${GENSOLVER_INCLUDE_DIR}
	      	 	)

ADD_EXECUTABLE( charsolver ${_CHARSOLVER_SRCS} )

# CMAKE WARNING SUGGESTS:
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


ADD_EXECUTABLE( charsolver-convert 
  ${_IMG_CONVERT_SRCS}
  ${_UIS_H}
  ${_MOC_SRCS})


target_link_libraries( charsolver
			${GENSOLVER_LIBRARY}
			${FLEXPARS_LIBRARY}
			)

target_link_libraries(charsolver-convert
				${QT_LIBRARIES}
				${QT_QTGUI_TOOLS_LIBRARIES}
				${QT_QT_GUI_LIBRARIES}

				${FLEXPARS_LIBRARY}
				)

install(TARGETS charsolver DESTINATION bin)
install(TARGETS charsolver-convert DESTINATION bin)
