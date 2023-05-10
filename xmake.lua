add_rules("mode.debug", "mode.release")

target("mocvserver")
  set_kind("binary")
  add_files("src/core/*.cc")
  add_files("src/utils/*.cc")
  add_files("src/server/*.cc")

target("mocvclient")
  set_kind("binary")
  add_files("src/core/*.cc")
  add_files("src/utils/*.cc")
  add_files("src/client/*.cc")