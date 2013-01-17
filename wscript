def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  # This will tell the compiler to link our extension with the gtkmm and libnotifymm libraries.
  # conf.check_cfg(package='gtkmm-2.4', args='--cflags --libs', uselib_store='LIBGTKMM')
  # conf.check_cfg(package='libnotifymm-1.0', args='--cflags --libs', uselib_store='LIBNOTIFYMM')

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.cxxflags = ["-g", "-Wall"]
  # This is the name of our extension.
  obj.target = "rcswitch"
  obj.source = ["externals/rcswitch-pi/RCSwitch.cpp", "src/RCSwitchNode.cpp"]
  # obj.uselib = ['LIBGTKMM', 'LIBNOTIFYMM']
