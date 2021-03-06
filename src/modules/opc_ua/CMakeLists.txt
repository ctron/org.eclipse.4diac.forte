#*******************************************************************************
# * Copyright (c) 2015-2016 Florian Froschermeier <florian.froschermeier@tum.de>,
# *                         fortiss GmbH
# * All rights reserved. This program and the accompanying materials
# * are made available under the terms of the Eclipse Public License v1.0
# * which accompanies this distribution, and is available at
# * http://www.eclipse.org/legal/epl-v10.html
# *
# * Contributors:
# *    Florian Froschermeier
# *      - initial integration of OPC Unified Architecture into FORTE
# *    Stefan Profanter
# *      - refactoring and adaption to new concept
# ******************************************************************************/

#############################################################################
# OPC Unified Architecture (UA) integration.
# For integration the open-source OPC-UA communication stack/library
# from (open62541 - http://open62541.org/) was used.
#############################################################################

# option to enable OPC UA with cmake
forte_add_network_layer(OPC_UA OFF "opc_ua" COPC_UA_Layer opcua_layer "Enable OPC UA communication layer")

forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (FORTE_COM_OPC_UA)

    SET(FORTE_COM_OPC_UA_PORT "4840" CACHE NUMBER "Port where the OPC_UA server will listen")
    SET(FORTE_COM_OPC_UA_MULTICAST OFF CACHE BOOLEAN "Enable multicast support for OPC UA and registering with LDS")
    SET(FORTE_COM_OPC_UA_INCLUDE_DIR "" CACHE PATH "ABSOLUTE path to open62541.h file in the OPC UA project")
    SET(FORTE_COM_OPC_UA_LIB_DIR "" CACHE PATH "ABSOLUTE path to OPC UA folder with object library FORTE_COM_OPC_UA_LIB")
    SET(FORTE_COM_OPC_UA_CUSTOM_HOSTNAME CACHE STRING "Custom hostname which is used for the OPC UA app name and app uri")

    # OPEN62541 library to be linked to forte
    IF ("${FORTE_ARCHITECTURE}" STREQUAL "Posix")
        SET(FORTE_COM_OPC_UA_LIB "libopen62541.so" CACHE STRING "OPC_UA Library file in FORTE_COM_OPC_UA_DIR to be linked to forte (normally with name libopen62541 and a extension according to the type and OS)")
    ELSEIF ("${FORTE_ARCHITECTURE}" STREQUAL "Win32")
        SET(FORTE_COM_OPC_UA_LIB "open62541.lib" CACHE STRING "OPC_UA Library file in FORTE_COM_OPC_UA_DIR to be linked to forte (normally with name libopen62541 and a extension according to the type and OS)")
    ELSE ()
        SET(FORTE_COM_OPC_UA_LIB "libopen62541.a" CACHE STRING "OPC_UA Library file in FORTE_COM_OPC_UA_DIR to be linked to forte (normally with name libopen62541 and a extension according to the type and OS)")
    ENDIF ("${FORTE_ARCHITECTURE}" STREQUAL "Posix")
    forte_add_include_system_directories(${FORTE_COM_OPC_UA_INCLUDE_DIR})
    forte_add_link_directories(${FORTE_COM_OPC_UA_LIB_DIR})
    forte_add_link_library_beginning(${FORTE_COM_OPC_UA_LIB})

    forte_add_sourcefile_hcpp(opcua_layer opcua_handler opcua_helper)
    if (NOT EXISTS ${FORTE_COM_OPC_UA_INCLUDE_DIR})
        message(SEND_ERROR "FORTE_COM_OPC_UA_INCLUDE_DIR not set or does not exist")
    endif (NOT EXISTS ${FORTE_COM_OPC_UA_INCLUDE_DIR})

    file(TO_CMAKE_PATH "${FORTE_COM_OPC_UA_LIB_DIR}/${FORTE_COM_OPC_UA_LIB}" FORTE_COM_OPC_UA_LIB_PATH)
    if (NOT EXISTS ${FORTE_COM_OPC_UA_LIB} AND NOT EXISTS ${FORTE_COM_OPC_UA_LIB_PATH})
        message(SEND_ERROR "OPC UA library not found '${FORTE_COM_OPC_UA_LIB}'. Check the value of FORTE_COM_OPC_UA_LIB_DIR and optionally define an absolute path for FORTE_COM_OPC_UA_LIB.")
    endif()

    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/forte_config_opc_ua.h.in ${CMAKE_BINARY_DIR}/forte_config_opc_ua.new.h)
    forte_replacefile_if_changed(${CMAKE_BINARY_DIR}/forte_config_opc_ua.new.h ${CMAKE_BINARY_DIR}/forte_config_opc_ua.h)
    file(REMOVE ${CMAKE_BINARY_DIR}/forte_config_opc_ua.new.h)

endif (FORTE_COM_OPC_UA)


