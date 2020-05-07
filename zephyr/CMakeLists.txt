if(CONFIG_NET_L2_OPENTHREAD)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# OpenThread options
set(OT_BUILD_EXECUTABLES OFF CACHE BOOL "Disable OpenThread samples")
set(OT_EXTERNAL_MBEDTLS "mbedTLS" CACHE STRING "Specify external mbedtls library")
set(OT_BUILTIN_MBEDTLS_MANAGEMENT OFF CACHE BOOL "Use Zephyr's mbedTLS heap")
set(OT_PLATFORM "zephyr" CACHE STRING "Zephyr as a target platform")

if(CONFIG_OPENTHREAD_COMMISSIONER)
  set(OT_COMMISSIONER ON CACHE BOOL "Enable Commissioner")
endif()

if(CONFIG_OPENTHREAD_JAM_DETECTION)
  set(OT_JAM_DETECTION ON CACHE BOOL "Enable Jam Detection")
endif()

if(CONFIG_OPENTHREAD_JOINER)
  set(OT_JOINER ON CACHE BOOL "Enable Joiner")
endif()

if(CONFIG_OPENTHREAD_SLAAC)
  set(OT_SLAAC ON CACHE BOOL "Enable SLAAC")
endif()

if(CONFIG_OPENTHREAD_DHCP6_CLIENT)
  set(OT_DHCP6_CLIENT ON CACHE BOOL "Enable DHCPv6 Client")
endif()

if(CONFIG_OPENTHREAD_DHCP6_SERVER)
  set(OT_DHCP6_SERVER ON CACHE BOOL "Enable DHCPv6 Server")
endif()

if(CONFIG_OPENTHREAD_DIAG)
  set(OT_DIAGNOSTIC ON CACHE BOOL "Enable Diagnostics")
endif()

if(CONFIG_OPENTHREAD_RAW)
  set(OT_LINK_RAW ON CACHE BOOL "Enable Link Raw")
endif()

if(CONFIG_OPENTHREAD_ENABLE_SERVICE)
  set(OT_SERVICE ON CACHE BOOL "Enable Service entries in Thread Network Data")
endif()

if(CONFIG_OPENTHREAD_BORDER_AGENT)
  set(OT_BORDER_AGENT ON CACHE BOOL "Enable Border Agent")
endif()

if(CONFIG_OPENTHREAD_BORDER_ROUTER)
  set(OT_BORDER_ROUTER ON CACHE BOOL "Enable Border Router")
endif()

if(CONFIG_OPENTHREAD_NCP)
  set(OT_NCP ON CACHE BOOL "Enable Network Co-Processor NCP")
endif()

if(CONFIG_OPENTHREAD_RCP)
  set(OT_RCP ON CACHE BOOL "Enable Network Co-Processor RCP")
endif()

if(CONFIG_OPENTHREAD_UDP_FORWARD)
  set(OT_UDP_FORWARD ON CACHE BOOL "Enable UDP Forward")
endif()

if(CONFIG_OPENTHREAD_COAP)
  set(OT_COAP ON CACHE BOOL "Enable CoAP api")
endif()

# Zephyr compiler options
zephyr_get_compile_options_for_lang_as_string(C   c_options)
zephyr_get_compile_options_for_lang_as_string(CXX cxx_options)

set(c_options   "${c_options} -fno-builtin")
set(cxx_options "${cxx_options} -fno-builtin")

zephyr_get_include_directories_for_lang_as_string(       C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)

set(CMAKE_C_FLAGS   "${c_options} ${includes} ${system_includes}")
set(CMAKE_CXX_FLAGS "${cxx_options} ${includes} ${system_includes}")
set(CMAKE_ASM_FLAGS "${c_options} ${includes} ${system_includes}")

# Other options
add_definitions(
    -DOPENTHREAD_CONFIG_LOG_LEVEL=${CONFIG_OPENTHREAD_LOG_LEVEL}
    -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE="openthread-core-zephyr-config.h"
)

list(APPEND OT_PRIVATE_INCLUDES $ENV{ZEPHYR_BASE}/subsys/net/lib/openthread/platform)

# Need to specify build directory as well
add_subdirectory(.. build)

# Include OpenThread headers
zephyr_system_include_directories(../include)
zephyr_system_include_directories(../examples/platforms)

# Determine which libs should be linked in
set(ot_libs "")

if(CONFIG_OPENTHREAD_FTD)
set(cli_lib openthread-cli-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
set(cli_lib openthread-cli-mtd)
endif()

if(CONFIG_OPENTHREAD_SHELL)
list(APPEND ot_libs ${cli_lib})
endif()

if(CONFIG_OPENTHREAD_NCP)
if(CONFIG_OPENTHREAD_FTD)
list(APPEND ot_libs openthread-ncp-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
list(APPEND ot_libs openthread-ncp-mtd)
endif()
endif()

if(CONFIG_OPENTHREAD_FTD)
list(APPEND ot_libs openthread-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
list(APPEND ot_libs openthread-mtd)
endif()

zephyr_link_libraries(${ot_libs} -lc)

endif()
