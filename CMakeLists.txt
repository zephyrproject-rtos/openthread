if (CONFIG_NET_L2_OPENTHREAD)

# Invoke OpenThread's external autoconf-based build system.
include(ExternalProject)

# Construct a list of commands to give to ExternalProject_Add()
#
# See https://cmake.org/cmake/help/latest/module/ExternalProject.html
# for documentation on ExternalProject_Add
set(cmd "")

set(ot_name ot)
list(APPEND cmd
  ${ot_name}
  )

set(ot_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/Install/${ot_name})

#--Configure step-------------
if(EXTERNAL_PROJECT_PATH_OPENTHREAD)
  set(ot_SOURCE_DIR ${EXTERNAL_PROJECT_PATH_OPENTHREAD})
else()
  execute_process(
      COMMAND
      ${WEST} list -f {posixpath} openthread
      OUTPUT_VARIABLE ot_SOURCE_DIR
      )

  # Trim a trailing whitespace.
  string(STRIP ${ot_SOURCE_DIR} ot_SOURCE_DIR)
endif()

list(APPEND cmd
  SOURCE_DIR ${ot_SOURCE_DIR}
  )

# TODO: Can we omit this, does OpenThread need to use install?
# TODO: Move this to host-tools?
find_program(INSTALL install)

# It looks like OpenThread requires a *nix system to build for
# embedded.
#
# https://github.com/openthread/openthread/blob/master/examples/drivers/windows/README.md

# TODO: Use different includes for C and CXX
zephyr_get_include_directories_for_lang_as_string(       C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)
zephyr_get_compile_definitions_for_lang_as_string(       C definitions)

zephyr_get_compile_options_for_lang_as_string(C   c_options)
zephyr_get_compile_options_for_lang_as_string(CXX cxx_options)

# TODO: What happens if a CFLAG is added after this build script has
# been run?

# TODO: Does OpenThread need all flags, or just some? Should we
# whitelist, or blacklist flags?


# TODO: What is all this? $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

set(exec_prefix zephyr)

# For zephyr-mbedtls-config.h
set(ot_port_path "$ENV{ZEPHYR_BASE}/subsys/net/lib/openthread")

set(commoncflags "-DOPENTHREAD_CONFIG_LOG_LEVEL=${CONFIG_OPENTHREAD_LOG_LEVEL}")
set(commoncflags "${commoncflags} -DOPENTHREAD_PROJECT_CORE_CONFIG_FILE=\\\"openthread-core-zephyr-config.h\\\"")
set(commoncflags "${commoncflags} -I${ot_port_path}/platform")

get_property(RULE_LAUNCH_COMPILE GLOBAL PROPERTY RULE_LAUNCH_COMPILE)

set(configure_flags
  "INSTALL=${INSTALL} -p"
  "CPP=${CMAKE_C_COMPILER} -E"                 # TODO: Find CPP in toolchain-gcc.cmake and use that instead?
  "CC=${RULE_LAUNCH_COMPILE} ${CMAKE_C_COMPILER}"
  "CXX=${RULE_LAUNCH_COMPILE} ${CMAKE_CXX_COMPILER}"
  OBJC=""                      # TODO: Omit this?
  "OBJCXX=${OBJCXX}"           # TODO: Omit this?
  "AR=${CMAKE_AR}"
  "RANLIB=${CMAKE_RANLILB}"
  "NM=${CROSS_COMPILE}nm"      # TODO: Find NM in toolchain-gcc.cmake and use that instead?
  "STRIP=${CMAKE_STRIP}"
  "CPPFLAGS=${definitions} ${commoncflags} ${includes} ${system_includes}"
  "CFLAGS=${c_options}     ${commoncflags} ${includes} ${system_includes}"
  "CXXFLAGS=${cxx_options} ${commoncflags} ${includes} ${system_includes}" # TODO: Do we need includes here?
  LDFLAGS="" # TODO: What does a networking stack need to use the linker for?

  --host=arm-none-eabi
  --prefix=/
  --exec-prefix=/${exec_prefix}
  --target=arm-none-eabi # TODO: Is Kconfig expressing that OT is ARM-only?
  --enable-no-executables-hack
  --disable-docs
  --with-platform-info=zephyr
  --enable-builtin-mbedtls=no
)

# TODO: Simplify
set(ZEPHYR_MBEDTLS_CPPFLAGS "${ZEPHYR_MBEDTLS_CPPFLAGS} -DMBEDTLS_CONFIG_FILE='\"${CONFIG_MBEDTLS_CFG_FILE}\"'")
set(ZEPHYR_MBEDTLS_CPPFLAGS "${ZEPHYR_MBEDTLS_CPPFLAGS} -I$ENV{ZEPHYR_BASE}/../modules/crypto/mbedtls/include")
set(ZEPHYR_MBEDTLS_CPPFLAGS "${ZEPHYR_MBEDTLS_CPPFLAGS} -I$ENV{ZEPHYR_BASE}/../modules/crypto/mbedtls/configs")

list(APPEND configure_flags
  "MBEDTLS_CPPFLAGS=${ZEPHYR_MBEDTLS_CPPFLAGS}"
  )

if(CONFIG_OPENTHREAD_FTD)
  list(APPEND configure_flags
    --enable-ftd
    )
elseif(CONFIG_OPENTHREAD_MTD)
  list(APPEND configure_flags
    --enable-mtd
    )
endif()

if(CONFIG_OPENTHREAD_COMMISSIONER)
  list(APPEND configure_flags
    --enable-commissioner
    )
endif()

if(CONFIG_OPENTHREAD_JAM_DETECTION)
  list(APPEND configure_flags
    --enable-jam-detection
    )
endif()

if(CONFIG_OPENTHREAD_JOINER)
  list(APPEND configure_flags
    --enable-joiner
    )
endif()

if(CONFIG_OPENTHREAD_DHCP6_CLIENT)
  list(APPEND configure_flags
    --enable-dhcp6-client
    )
endif()

if(CONFIG_OPENTHREAD_DHCP6_SERVER)
  list(APPEND configure_flags
    --enable-dhcp6-server
    )
endif()

if(CONFIG_OPENTHREAD_SHELL)
  list(APPEND configure_flags
    --enable-cli
    )
endif()

if(CONFIG_OPENTHREAD_DIAG)
  list(APPEND configure_flags
    --enable-diag
    )
endif()

list(APPEND cmd
  CONFIGURE_COMMAND ${ot_SOURCE_DIR}/configure ${configure_flags}
)

#--Build step-----------------

# Invoke OpenThread's build system from the root of it's source
# directory
# TODO: Support out-of-source builds
set(ot_BINARY_DIR  ${CMAKE_CURRENT_BINARY_DIR}/build)
list(APPEND cmd
  BINARY_DIR  ${ot_BINARY_DIR}
  INSTALL_DIR ${ot_INSTALL_DIR}
  )

set(make_flags
  -j99 # TODO: Why 99?
  --no-print-directory
  )

list(APPEND cmd
  BUILD_COMMAND   make ${make_flags}                           all
  INSTALL_COMMAND make ${make_flags} DESTDIR=${ot_INSTALL_DIR} install
  )

# TODO: Find out how to make this work.
set(ot_include_dir ${ot_SOURCE_DIR}/include)
set(ot_generated_dir ${ot_BINARY_DIR}/include)
# For platform.h
set(ot_platforms_dir ${ot_SOURCE_DIR}/examples/platforms)

# TODO: Is this only needed by alarm.c?
zephyr_system_include_directories(${ot_include_dir})
zephyr_system_include_directories(${ot_generated_dir})
zephyr_system_include_directories(${ot_platforms_dir})

# TODO: Why doesn't app get this path from the above function call?
target_include_directories(app SYSTEM PRIVATE ${ot_include_dir})
target_include_directories(app SYSTEM PRIVATE ${ot_generated_dir})
target_include_directories(app SYSTEM PRIVATE ${ot_platforms_dir})

#set_target_properties(ot_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${ot_include_dir})
zephyr_include_directories(${ot_include_dir})
zephyr_include_directories(${ot_generated_dir})
zephyr_include_directories(${ot_platforms_dir})

# Determine which libs should be linked in
set(ot_libs
  openthread-platform-utils
  )

if(CONFIG_OPENTHREAD_FTD)
  list(APPEND ot_libs openthread-ftd)
  set(cli_lib         openthread-cli-ftd)
elseif(CONFIG_OPENTHREAD_MTD)
  list(APPEND ot_libs openthread-mtd)
  set(cli_lib         openthread-cli-mtd)
endif()

if(CONFIG_OPENTHREAD_SHELL)
  list(APPEND ot_libs ${cli_lib})
endif()

foreach(ot_lib ${ot_libs})
  set(build_byproducts ${build_byproducts} ${ot_INSTALL_DIR}/${exec_prefix}/lib/lib${ot_lib}.a)
endforeach()

list(APPEND cmd
  BUILD_BYPRODUCTS ${build_byproducts}
  )

ExternalProject_Add(${cmd})

ExternalProject_Add_Step(
  ${ot_name} bootstrap # Names of project and custom step
  COMMAND ./bootstrap     # Command line invoked by this step
  COMMENT "bootstrapping..." # Text printed when step executes
  DEPENDEES download        # Steps on which this step depends
  DEPENDERS configure     # Steps that depend on this step
  WORKING_DIRECTORY ${ot_SOURCE_DIR}
  )

# Create wrapper CMake libraries
foreach(ot_lib ${ot_libs})
  zephyr_library_import(${ot_lib}
    ${ot_INSTALL_DIR}/${exec_prefix}/lib/lib${ot_lib}.a
    )
endforeach()

endif()
