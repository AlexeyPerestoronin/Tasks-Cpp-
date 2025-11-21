# brief: filters files in VS-solution by theirs self directory
# param: i_baseDiretory - common part of path for all files
# param: i_listOfFiles - target list of files to filtering
function(ComposeFileBySourceGroup i_baseDirectory i_listOfFiles)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    foreach(fileFullPath ${i_listOfFiles}) 
        # Get the directory of the source file
        get_filename_component(fileDir "${fileFullPath}" DIRECTORY)

        # Remove common directory prefix to make the group
        string(REPLACE "${i_baseDirectory}" "" fileGroup "${fileDir}")

        # place the target source file in detected group
        source_group("${fileGroup}" FILES "${fileFullPath}")
    endforeach()
endfunction(ComposeFileBySourceGroup)
