# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/fortuneserver_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/fortuneserver_autogen.dir/ParseCache.txt"
  "fortuneserver_autogen"
  )
endif()
