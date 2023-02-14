add_subdirectory(datastructure)

add_library(cppmodernity STATIC ${ALL_OBJECT_FILES})

set(CM_LIBS
      cm_ds
      )

target_link_libraries(
  cppmodernity
  ${CM_LIBS}
)

target_include_directories(
  cppmodernity PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
