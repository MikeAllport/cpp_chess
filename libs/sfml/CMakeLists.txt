message(STATUS "Fetching SFML...")

# No need to build audio and network modules
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(BUILD_SHARED_LIBS TRUE)
set(SFML_STATIC_LIBRARIES OFF)

FetchContent_MakeAvailable(sfml)