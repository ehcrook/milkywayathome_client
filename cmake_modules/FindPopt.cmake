# Copyright 2010 Matthew Arsenault, Travis Desell, Dave Przybylo,
# Nathan Cole, Boleslaw Szymanski, Heidi Newberg, Carlos Varela, Malik
# Magdon-Ismail and Rensselaer Polytechnic Institute.

# This file is part of Milkway@Home.

# Milkyway@Home is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# Milkyway@Home is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with Milkyway@Home.  If not, see <http://www.gnu.org/licenses/>.
#


find_path(POPT_INCLUDE_DIR popt.h)

if(POPT_USE_STATIC)
  set(__old_cmake_find_lib_suffixes ${CMAKE_FIND_LIBRARY_SUFFIXES})
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_STATIC_LIBRARY_SUFFIX})
endif()

find_library(POPT_LIBRARY popt)
if(POPT_USE_STATIC)
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${__old_cmake_find_lib_suffixes})
endif()

if(POPT_INCLUDE_DIR AND POPT_LIBRARY)
   set(POPT_FOUND TRUE)
endif()

if(POPT_FOUND)
   if(NOT Popt_FIND_QUIETLY)
      message(STATUS "Found POPT Library: ${POPT_LIBRARY}")
   endif()
else()
   if(Popt_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find POPT Library")
   endif()
endif()

