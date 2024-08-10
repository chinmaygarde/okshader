ok_executable(ok_test
  unittests.cc
)

target_link_libraries(ok_test
  gtest_main
  ok
)

gtest_discover_tests(ok_test)
