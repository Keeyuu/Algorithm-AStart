add_rules("mode.debug", "mode.release")

target("xx")
    set_kind("binary")
    add_files("src/*.cpp")

