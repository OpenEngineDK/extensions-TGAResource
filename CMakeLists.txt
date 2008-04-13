SET( EXTENSION_NAME "Extensions_TGAResource")

ADD_LIBRARY( ${EXTENSION_NAME}
  Resources/TGAResource.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  OpenEngine_Core
)
