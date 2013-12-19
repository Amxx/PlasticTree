
find_package(GLUT)
find_package(OpenGL)

add_executable(PlasticTree
	geometry/vec3.cc
  geometry/base3.cc
  geometry/bbox.cc
	objects/tree.cc
  main.cc
)
target_link_libraries(PlasticTree
	glut
	GL
	GLU
)

install(
	TARGETS
		PlasticTree
	DESTINATION
		bin/
)
