if(NOT EXISTS "C:/MAMP/htdocs/ProjetPOO/ProjetCIR2-1/out/build/x64-Debug/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: C:/MAMP/htdocs/ProjetPOO/ProjetCIR2-1/out/build/x64-Debug/install_manifest.txt")
endif()

file(READ "C:/MAMP/htdocs/ProjetPOO/ProjetCIR2-1/out/build/x64-Debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif()
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif()
endforeach()
