
# add all .cpp files to project (stored in "raidmonitor_SRCS" variable")

# and finally an resource file
set(_SRCS
	main.cpp
	)


include_directories(
			${GENSOLVER_INCLUDE_DIR}
			${FLEXPARS_INCLUDE_DIR}	
			#${CMAKE_CURRENT_BINARY_DIR}
			)

ADD_EXECUTABLE( char-solver ${_SRCS} )


target_link_libraries( char-solver
			${GENSOLVER_LIBRARY}
			${FLEXPARS_LIBRARY}
			)

install(TARGETS char-solver DESTINATION bin)
