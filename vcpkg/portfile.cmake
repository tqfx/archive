vcpkg_from_git(OUT_SOURCE_PATH SOURCE_PATH
  REF f573fbe629a0a48402b9ab72ee82e0288c56917a
  URL https://github.com/tqfx/${PORT}.git
  HEAD_REF master
)

vcpkg_check_features(OUT_FEATURE_OPTIONS FEATURE_OPTIONS
  FEATURES ipo ENABLE_IPO
)

vcpkg_configure_cmake(SOURCE_PATH ${SOURCE_PATH}
  OPTIONS_RELEASE ${FEATURE_OPTIONS}
  OPTIONS -DBUILD_TESTING=OFF
)

vcpkg_install_cmake()

vcpkg_copy_pdbs()

vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/${PORT})

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(INSTALL ${SOURCE_PATH}/LICENSE.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
