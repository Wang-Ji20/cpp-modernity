add_library(
  cm_ds
  OBJECT
  Vector.cc
)

set(
  ALL_OBJECT_FILES
  ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:cm_ds>
  PARENT_SCOPE
)
