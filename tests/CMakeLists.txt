include(FetchContent)

# Grab GoogleTest (no system install needed)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For MSVC: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(rle_tests rle_tests.cpp)
target_link_libraries(rle_tests PRIVATE rle GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(rle_tests)
