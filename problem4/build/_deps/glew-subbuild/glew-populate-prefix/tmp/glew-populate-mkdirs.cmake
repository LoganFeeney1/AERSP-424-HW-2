# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-src"
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-build"
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix"
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix/tmp"
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp"
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix/src"
  "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/AERSP 424/424 Homework 2/problem4/build/_deps/glew-subbuild/glew-populate-prefix/src/glew-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
