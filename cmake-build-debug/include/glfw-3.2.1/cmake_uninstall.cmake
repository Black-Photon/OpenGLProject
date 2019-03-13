
if (NOT EXISTS "/run/media/u1800015/USB-ALPHA/C++/OpenGLProject/cmake-build-debug/include/glfw-3.2.1/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/run/media/u1800015/USB-ALPHA/C++/OpenGLProject/cmake-build-debug/include/glfw-3.2.1/install_manifest.txt\"")
endif()

file(READ "/run/media/u1800015/USB-ALPHA/C++/OpenGLProject/cmake-build-debug/include/glfw-3.2.1/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/run/media/u1800015/USB-ALPHA/clion-2018.3.4/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/run/media/u1800015/USB-ALPHA/clion-2018.3.4/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

