function(deploy_dll LIB_NAME DLL_PATH TARGET)
    add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL_PATH}/${LIB_NAME}.dll"
            $<TARGET_FILE_DIR:${TARGET}>
        COMMENT "Deploying ${LIB_NAME}.dll to ${TARGET} output directory"
    )
endfunction()
