# SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
# SPDX-License-Identifier: BSD-3-Clause

set(HephaestusCommon_SRCS)
qt_add_dbus_interface(HephaestusCommon_SRCS org.projectatomic.rpmostree1.xml RpmOstreeDbusInterfaces)

add_library(HephaestusCommon STATIC)

target_sources(HephaestusCommon PRIVATE
    DeveloperOptions.h
    DeveloperOptions.cpp
    RpmOstreeInterface.cpp
    RpmOstreeInterface.h
    RpmOstreeInterfaceTypes.h
    ${HephaestusCommon_SRCS}
)

target_include_directories(HephaestusCommon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(HephaestusCommon PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(HephaestusCommon PUBLIC
    Qt6::Core
    Qt6::DBus
    KF6::I18n
    KF6::WidgetsAddons
)
