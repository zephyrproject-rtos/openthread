if(CONFIG_OPENTHREAD_SOURCES)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# OpenThread options
set(OT_BUILD_EXECUTABLES OFF CACHE BOOL "Disable OpenThread samples")
set(OT_BUILTIN_MBEDTLS_MANAGEMENT OFF CACHE BOOL "Use Zephyr's mbedTLS heap")
set(OT_PLATFORM "zephyr" CACHE STRING "Zephyr as a target platform")
set(OT_THREAD_VERSION ${CONFIG_OPENTHREAD_THREAD_VERSION} CACHE STRING "User selected Thread stack version")
set(OT_CLI_TRANSPORT "CONSOLE" CACHE STRING "Set CLI to use console interpreter")

string(REPLACE " " ";" OT_MBEDTLS_LIB_LIST " ${CONFIG_OPENTHREAD_MBEDTLS_LIB_NAME}")

set(
    OT_EXTERNAL_MBEDTLS
    ${OT_MBEDTLS_LIB_LIST}
    CACHE STRING
    "Specify external mbedtls library"
)

if(CONFIG_OPENTHREAD_BACKBONE_ROUTER)
  set(OT_BACKBONE_ROUTER ON CACHE BOOL "Enable backbone router functionality")
endif()

if(CONFIG_OPENTHREAD_BORDER_AGENT)
  set(OT_BORDER_AGENT ON CACHE BOOL "Enable Border Agent")
endif()

if(CONFIG_OPENTHREAD_BORDER_ROUTER)
  set(OT_BORDER_ROUTER ON CACHE BOOL "Enable Border Router")
endif()

if(CONFIG_OPENTHREAD_COAP)
  set(OT_COAP ON CACHE BOOL "Enable CoAP API")
endif()

if(CONFIG_OPENTHREAD_COAPS)
  set(OT_COAPS ON CACHE BOOL "Enable secure CoAP API support")
endif()

if(CONFIG_OPENTHREAD_COAP_BLOCK)
  set(OT_COAP_BLOCK ON CACHE BOOL "Enable CoAP Block-wise option support")
endif()

if(CONFIG_OPENTHREAD_COAP_OBSERVE)
  set(OT_COAP_OBSERVE ON CACHE BOOL "Enable CoAP Observe option support")
endif()

if(CONFIG_OPENTHREAD_COMMISSIONER)
  set(OT_COMMISSIONER ON CACHE BOOL "Enable Commissioner")
endif()

if(CONFIG_OPENTHREAD_CHANNEL_MANAGER)
  set(OT_CHANNEL_MANAGER ON CACHE BOOL "Enable channel manager support")
endif()

if(CONFIG_OPENTHREAD_CHANNEL_MONITOR)
  set(OT_CHANNEL_MONITOR ON CACHE BOOL "Enable channel monitor support")
endif()

if(CONFIG_OPENTHREAD_CHILD_SUPERVISION)
  set(OT_CHILD_SUPERVISION ON CACHE BOOL "Enable child supervision support")
endif()

if(CONFIG_OPENTHREAD_CSL_RECEIVER)
  set(OT_CSL_RECEIVER ON CACHE BOOL "Enable CSL receiver feature for Thread 1.2")
endif()

if(CONFIG_OPENTHREAD_CSL_DEBUG)
  set(OT_CSL_DEBUG ON CACHE BOOL "Enable CSL debug")
endif()

if(CONFIG_OPENTHREAD_DATSET_UPDATER)
  set(OT_DATASET_UPDATER ON CACHE BOOL "Enable Dataset updater")
endif()

if(CONFIG_OPENTHREAD_DHCP6_CLIENT)
  set(OT_DHCP6_CLIENT ON CACHE BOOL "Enable DHCPv6 Client")
endif()

if(CONFIG_OPENTHREAD_DHCP6_SERVER)
  set(OT_DHCP6_SERVER ON CACHE BOOL "Enable DHCPv6 Server")
endif()

if(CONFIG_OPENTHREAD_DIAG)
  set(OT_DIAGNOSTIC ON CACHE BOOL "Enable Diagnostics support")
endif()

if(CONFIG_OPENTHREAD_DNS_CLIENT)
  set(OT_DNS_CLIENT ON CACHE BOOL "Enable DNS client support")
endif()

if(CONFIG_OPENTHREAD_DNSSD_SERVER)
  set(OT_DNSSD_SERVER ON CACHE BOOL "Enable DNS-SD server support")
endif()

if(CONFIG_OPENTHREAD_DUA)
  set(OT_DUA ON CACHE BOOL "Enable Domain Unicast Address feature for Thread 1.2")
endif()

if(CONFIG_OPENTHREAD_ECDSA)
  set(OT_ECDSA ON CACHE BOOL "Enable ECDSA support")
endif()

if(CONFIG_OPENTHREAD_ENABLE_SERVICE)
  set(OT_SERVICE ON CACHE BOOL "Enable Service entries in Thread Network Data")
endif()

if(CONFIG_OPENTHREAD_EXTERNAL_HEAP)
  set(OT_EXTERNAL_HEAP ON CACHE BOOL "Enable external heap support")
endif()

if(CONFIG_OPENTHREAD_IP6_FRAGM)
  set(OT_IP6_FRAGM ON CACHE BOOL "Enable IPv6 fragmentation support")
endif()

if(CONFIG_OPENTHREAD_JAM_DETECTION)
  set(OT_JAM_DETECTION ON CACHE BOOL "Enable Jam Detection")
endif()

if(CONFIG_OPENTHREAD_JOINER)
  set(OT_JOINER ON CACHE BOOL "Enable Joiner")
endif()

if(CONFIG_OPENTHREAD_LEGACY)
  set(OT_LEGACY ON CACHE BOOL "Enable legacy network support")
endif()

if(CONFIG_OPENTHREAD_LINK_METRICS)
  set(OT_LINK_METRICS ON CACHE BOOL "Enable Link Metrics feature for Thread 1.2")
endif()

if(CONFIG_OPENTHREAD_LOG_LEVEL_DYNAMIC)
  set(OT_LOG_LEVEL_DYNAMIC ON CACHE BOOL "Enable dynamic log level control")
endif()

if(CONFIG_OPENTHREAD_MAC_FILTER)
  set(OT_MAC_FILTER ON CACHE BOOL "Enable MAC filter support")
endif()

if(CONFIG_OPENTHREAD_MLE_LONG_ROUTES)
  set(OT_MLE_LONG_ROUTES ON CACHE BOOL "Enable MLE long routes support (Experimental)")
endif()

if(CONFIG_OPENTHREAD_MLR)
  set(OT_MLR ON CACHE BOOL "Enable Multicast Listener Registration feature for Thread 1.2")
endif()

if(CONFIG_OPENTHREAD_MTD_NETDIAG)
  set(OT_MTD_NETDIAG ON CACHE BOOL "Enable TMF network diagnostics on MTDs")
endif()

if(CONFIG_OPENTHREAD_MULTIPLE_INSTANCE)
  set(OT_MULTIPLE_INSTANCE ON CACHE BOOL "Enable multiple instances")
endif()

if(CONFIG_OPENTHREAD_PLATFORM_NETIF)
  set(OT_PLATFORM_NETIF ON CACHE BOOL "Enable platform netif support")
endif()

if(CONFIG_OPENTHREAD_PLATFORM_UDP)
  set(OT_PLATFORM_UDP ON CACHE BOOL "Enable platform UDP support")
endif()

if(CONFIG_OPENTHREAD_RAW)
  set(OT_LINK_RAW ON CACHE BOOL "Enable Link Raw")
endif()

if(CONFIG_OPENTHREAD_REFERENCE_DEVICE)
  set(OT_REFERENCE_DEVICE ON CACHE BOOL "Enable Thread Certification Reference Device")
endif()

if(CONFIG_OPENTHREAD_SETTINGS_RAM)
  set(OT_SETTINGS_RAM ON CACHE BOOL "Enable volatile-only storage of settings")
endif()

if(CONFIG_OPENTHREAD_SLAAC)
  set(OT_SLAAC ON CACHE BOOL "Enable SLAAC")
endif()

if(CONFIG_OPENTHREAD_SNTP_CLIENT)
  set(OT_SNTP_CLIENT ON CACHE BOOL "Enable SNTP Client support")
endif()

if(CONFIG_OPENTHREAD_SRP_CLIENT)
  set(OT_SRP_CLIENT ON CACHE BOOL "Enable SRP Client support")
endif()

if(CONFIG_OPENTHREAD_SRP_SERVER)
  set(OT_SRP_SERVER ON CACHE BOOL "Enable SRP Server support")
endif()

if(CONFIG_OPENTHREAD_TIME_SYNC)
  set(OT_TIME_SYNC ON CACHE BOOL "Enable the time synchronization service feature")
endif()

if(CONFIG_OPENTHREAD_UDP_FORWARD)
  set(OT_UDP_FORWARD ON CACHE BOOL "Enable UDP forward feature")
endif()

if(CONFIG_OPENTHREAD_OTNS)
  set(OT_OTNS ON CACHE BOOL "Enable OTNS support")
endif()

if(CONFIG_OPENTHREAD_FULL_LOGS)
  set(OT_FULL_LOGS ON CACHE BOOL "Enable full logs")
endif()

if(CONFIG_OPENTHREAD_COPROCESSOR_VENDOR_HOOK_SOURCE)
  set(OT_NCP_VENDOR_HOOK_SOURCE ${CONFIG_OPENTHREAD_COPROCESSOR_VENDOR_HOOK_SOURCE} CACHE STRING "NCP vendor hook source file name")
endif()

string(REPLACE " " ";" OT_PARAM_LIST " ${CONFIG_OPENTHREAD_CUSTOM_PARAMETERS}")
list(APPEND OT_PRIVATE_DEFINES ${OT_PARAM_LIST})

# Zephyr logging options

if(CONFIG_LOG_BACKEND_SPINEL)
  add_definitions(
      -DOPENTHREAD_CONFIG_LOG_OUTPUT=OPENTHREAD_CONFIG_LOG_OUTPUT_APP
  )
endif()

# Other options
add_definitions(
    -DOPENTHREAD_CONFIG_LOG_LEVEL=${CONFIG_OPENTHREAD_LOG_LEVEL}
    -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE="openthread-core-zephyr-config.h"
)

list(APPEND OT_PRIVATE_INCLUDES ${ZEPHYR_BASE}/subsys/net/lib/openthread/platform)

# Need to specify build directory as well
add_subdirectory(.. build)

zephyr_get_targets(${CMAKE_CURRENT_LIST_DIR}/../ "STATIC_LIBRARY;OBJECT_LIBRARY" ALL_TARGETS)
foreach(target ${ALL_TARGETS})
  # We don't want to build all openthread libraries per default.
  # Setting EXCLUDE_FROM_ALL ensures that only libraries that are linked
  # into Zephyr will be built due to dependencies.
  set_property(TARGET ${target} PROPERTY EXCLUDE_FROM_ALL TRUE)
endforeach()

# Zephyr compiler options
target_include_directories(ot-config INTERFACE
    $<TARGET_PROPERTY:zephyr_interface,INTERFACE_INCLUDE_DIRECTORIES>
)

target_include_directories(ot-config SYSTEM INTERFACE
    $<TARGET_PROPERTY:zephyr_interface,INTERFACE_SYSTEM_INCLUDE_DIRECTORIES>
)

target_compile_definitions(ot-config INTERFACE
    $<TARGET_PROPERTY:zephyr_interface,INTERFACE_COMPILE_DEFINITIONS>
)

target_compile_options(ot-config INTERFACE
    $<TARGET_PROPERTY:zephyr_interface,INTERFACE_COMPILE_OPTIONS> -fno-builtin
)

# Openthread depends on errno.h, which includes errno_private.h in minimal libc.
# errno_private.h is generated as part of ${SYSCALL_LIST_H_TARGET} target.
add_dependencies(ot-config ${SYSCALL_LIST_H_TARGET})

# Make sure C library is linked after OpenThread libraries (to prevent linker
# errors)
target_link_libraries(ot-config INTERFACE -lc)

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

if(CONFIG_OPENTHREAD_COPROCESSOR_RCP)
list(APPEND ot_libs openthread-rcp)
endif()

if(CONFIG_OPENTHREAD_COPROCESSOR_NCP)
if(CONFIG_OPENTHREAD_FTD)
list(APPEND ot_libs openthread-ncp-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
list(APPEND ot_libs openthread-ncp-mtd)
endif()
endif()

if(NOT CONFIG_OPENTHREAD_COPROCESSOR_RCP)
if(CONFIG_OPENTHREAD_FTD)
list(APPEND ot_libs openthread-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
list(APPEND ot_libs openthread-mtd)
endif()
endif()

zephyr_link_libraries(${ot_libs})

endif()
