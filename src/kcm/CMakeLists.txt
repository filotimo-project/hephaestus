# SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
# SPDX-License-Identifier: BSD-3-Clause

kcmutils_add_qml_kcm(kcm_hephaestus)
target_sources(kcm_hephaestus PRIVATE
   hephaestussettings.cpp
   hephaestussettings.h
)

target_link_libraries(kcm_hephaestus PRIVATE
    KF6::I18n
    KF6::ConfigGui
    KF6::KCMUtilsQuick
    HephaestusCommon
)
