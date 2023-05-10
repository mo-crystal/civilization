add_rules("mode.debug", "mode.release")

target("mocvcore")
  set_kind("static")
  add_files("src/core/*.cc")

target("mocvserver")
  set_kind("binary")
  add_files("src/core/*.cc")
  add_files("src/utils/*.cc")
  add_files("src/server/*.cc")

target("mocvclient")
    add_rules("qt.widgetapp")
    add_headerfiles("src/client/*.h")
    add_files("src/client/*.cc")
    add_files("src/client/mainwindow.ui")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("src/client/mainwindow.h")