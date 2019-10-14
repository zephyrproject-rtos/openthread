if(CONFIG_NET_L2_OPENTHREAD)

# OpenThread options
set(OT_BUILD_EXECUTABLES OFF CACHE BOOL "Disable OpenThread samples")
set(OT_BUILTIN_MBEDTLS OFF CACHE BOOL "Use Zephry's mbedTLS")
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

if(CONFIG_OPENTHREAD_DHCP6_CLIENT)
  set(OT_DHCP6_CLIENT ON CACHE BOOL "Enable DHCPv6 Client")
endif()

if(CONFIG_OPENTHREAD_DHCP6_SERVER)
  set(OT_DHCP6_SERVER ON CACHE BOOL "Enable DHCPv6 Server")
endif()

if(CONFIG_OPENTHREAD_DIAG)
  set(OT_DIAGNOSTIC ON CACHE BOOL "Enable Diagnostics")
endif()

# Zephyr libc capabilies
set(HAVE_STRLCPY OFF CACHE BOOL "Zephyr's minimal libc does not provide strlcpy")
set(HAVE_STRLCAT OFF CACHE BOOL "Zephyr's minimal libc does not provide strlcat")

# Zephyr compiler options
zephyr_get_compile_options_for_lang_as_string(C   c_options)
zephyr_get_compile_options_for_lang_as_string(CXX cxx_options)

set(c_options   "${c_options} -fno-builtin")
set(cxx_options "${cxx_options} -fno-builtin")

zephyr_get_include_directories_for_lang_as_string(       C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)
zephyr_get_compile_definitions_for_lang_as_string(       C definitions)

set(CMAKE_C_FLAGS   "${definitions} ${c_options} ${includes} ${system_includes}")
set(CMAKE_CXX_FLAGS "${definitions} ${cxx_options} ${includes} ${system_includes}")
set(CMAKE_ASM_FLAGS "${definitions} ${c_options} ${includes} ${system_includes}")

# Other options
add_definitions(
    -DOPENTHREAD_CONFIG_LOG_LEVEL=${CONFIG_OPENTHREAD_LOG_LEVEL}
    -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE="openthread-core-zephyr-config.h"
)

list(APPEND OT_PRIVATE_INCLUDES $ENV{ZEPHYR_BASE}/subsys/net/lib/openthread/platform)

# mbedTLS

# Obtain Zephyr mbedTLS path
execute_process(
COMMAND
${WEST} list -f {posixpath} mbedtls
OUTPUT_VARIABLE mbedtls_root_dir
)

# Trim trailing whitespace.
string(STRIP ${mbedtls_root_dir} mbedtls_root_dir)

list(APPEND OT_PRIVATE_INCLUDES ${mbedtls_root_dir}/configs)
list(APPEND OT_PRIVATE_INCLUDES ${mbedtls_root_dir}/include)

add_definitions(
    -DMBEDTLS_CONFIG_FILE="${CONFIG_MBEDTLS_CFG_FILE}"
)

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

if(CONFIG_OPENTHREAD_FTD)
list(APPEND ot_libs openthread-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
list(APPEND ot_libs openthread-mtd)
endif()

zephyr_link_libraries(${ot_libs})

endif()
