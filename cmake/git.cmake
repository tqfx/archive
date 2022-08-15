find_package(Git)

if(GIT_FOUND)
  function(git_command output)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} ${ARGN}
      OUTPUT_STRIP_TRAILING_WHITESPACE
      OUTPUT_VARIABLE ${output}
      ERROR_QUIET
    )
    set(${output} ${${output}} PARENT_SCOPE)
  endfunction()

  git_command(GIT_BRANCH branch --show-current)
  git_command(GIT_COMMIT log -1 --pretty=format:%h)
  git_command(GIT_COMMIT_LONG log -1 --pretty=format:%H)
  git_command(GIT_COMMIT_DATE log -1 --pretty=format:%cd --date=format:%Y%m%d%H%M)
endif()

if(GIT_COMMIT_DATE)
  set(PROJECT_VERSION_TWEAK ${GIT_COMMIT_DATE})
else()
  string(TIMESTAMP PROJECT_VERSION_TWEAK %Y%m%d%H%M)
endif()
