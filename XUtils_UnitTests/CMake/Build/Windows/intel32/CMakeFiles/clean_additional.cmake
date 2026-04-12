# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "E:\\Projects\\GEN_FrameWork\\Tests\\XUtils_UnitTests\\CMake\\Common\\Docker\\dockerfile_prod_xutils_unittests"
  )
endif()
