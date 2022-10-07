function(package_cpack root)
  set(SOURCE_IGNORE_FILES
    ${root}/.git
    ${root}/.cache
    ${root}/.vscode
    ${root}/.github
    ${root}/.gitignore
    ${root}/.gitmodules
    ${root}/.gitattributes
    ${PROJECT_BINARY_DIR}
  )
  include(InstallRequiredSystemLibraries)
  set(CPACK_SOURCE_IGNORE_FILES ${SOURCE_IGNORE_FILES})
  set(CPACK_RESOURCE_FILE_LICENSE ${root}/LICENSE.txt)
  set(CPACK_RESOURCE_FILE_README ${root}/README.md)
  set(CPACK_SOURCE_GENERATOR ZIP)
  set(CPACK_GENERATOR ZIP)
  include(CPack)
endfunction()
