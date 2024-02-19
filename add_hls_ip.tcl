proc tool_add_xact {file_component_xml} {
    puts "\n=> add_xact: $file_component_xml"

    global current_xml_name
    global current_xml_vlnv


    if {! [file exists $file_component_xml]} {
        puts "ERROR: file doesn't exist: $file_component_xml"
        exit 1;
    }

    if {! [regexp {component\.xml$} $file_component_xml tmp]} {
        puts "ERROR: wrong file name ($file). This proc only reads component.xml files created by IP Packager."
        exit 1;                 
    }

    set xml_dir  [file dirname $file_component_xml]
    set cfs      [current_fileset]
    set old_path [get_property ip_repo_paths $cfs]
    set new_path [concat $old_path $xml_dir]

    puts "    xml_dir: ($xml_dir)"
    puts "    add_repo:($new_path)"
    set_property ip_repo_paths $new_path $cfs

    puts "    update_ip_catalog"
    update_ip_catalog

    puts "    open_core"        
    set core [ipx::open_core -set_current false $file_component_xml]

    set vlnv    [get_property vlnv $core]
    set tidbits [split $vlnv ":"]
    puts "    vlnv: $vlnv"

    puts "    close_core"        
    ipx::unload_core $core

    set current_xml_name  [lindex $tidbits 2]
    set current_xml_vlnv  $vlnv
}