# SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

set(QT_MIN_VERSION "6.8.0")
set(KF6_MIN_VERSION "6.0.0")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(hephaestus VERSION 0.10)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(FeatureSummary)
include(GenerateExportHeader)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMFindQmlModule)
include(KDEGitCommitHooks)
include(KDEClangFormat)

ecm_setup_version(${PROJECT_VERSION} VARIABLE_PREFIX HEPHAESTUS VERSION_HEADER
                  "${CMAKE_CURRENT_BINARY_DIR}/src/version-hephaestus.h")

set(QT_EXTRA_COMPONENTS)
list(APPEND QT_EXTRA_COMPONENTS Widgets)

find_package(
    Qt6 ${QT6_MIN_VERSION} REQUIRED COMPONENTS 
    Core
    Quick
    Gui
    Qml
    QuickControls2
    Svg
    DBus
    ${QT_EXTRA_COMPONENTS}
)

find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS
    Kirigami
    Config
    CoreAddons
    KCMUtils
    WidgetsAddons
    I18n
)

qt_policy(SET QTP0001 NEW)

ecm_find_qmlmodule(org.kde.kirigamiaddons.formcard 1.0)

add_subdirectory(src)

# i18n
# https://techbase.kde.org/Development/Tutorials/Localization/i18n_Build_Systems/Outside_KDE_repositories
add_subdirectory(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES
                         FATAL_ON_MISSING_REQUIRED_PACKAGES)

file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES src/*.cpp src/*.h)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)

ki18n_install(KF_SKIP_PO_PROCESSING po)
