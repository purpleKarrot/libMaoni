##########################################################################
# Copyright (C) 2011 Daniel Pfeifer <daniel@pfeifer-mail.de>             #
#                                                                        #
# Distributed under the Boost Software License, Version 1.0.             #
# See accompanying file LICENSE_1_0.txt or copy at                       #
#   http://www.boost.org/LICENSE_1_0.txt                                 #
##########################################################################

set(Maoni_INCLUDE_DIRS "/usr/include")

include("${CMAKE_CURRENT_LIST_DIR}/Maoni.cmake")

set(MAONI_LIBRARIES Maoni MaoniMain)
set(MAONI_EQ_LIBRARIES MaoniEq MaoniMain)
set(MAONI_ICET_LIBRARIES MaoniIceT MaoniMain)
