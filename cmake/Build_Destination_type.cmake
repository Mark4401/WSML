# Function to create a build path variable with config suffix
# cfg_path_type: Just a descriptive name (not used internally)
# prefix_variable_name: The name of the variable to set
# destination_directory: Base directory
function(cfg_path_type prefix_variable_name destination_directory)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(config_subdir "Debug")
    else()
        set(config_subdir "Release")
    endif()
    
    # Construct the full path
    set(full_path "${destination_directory}/${config_subdir}")
    
    # Set the variable in parent scope
    set(${prefix_variable_name} "${full_path}" PARENT_SCOPE)
endfunction()


