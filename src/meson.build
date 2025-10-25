project(
  'kindle_balatro',
  'c',
  version: '1.0.0',
  default_options: ['c_std=c23'],
  meson_version: '>=1.1'
)

# GTK dependency
gtk_dep = dependency('gtk+-2.0')

# Source files
sources = files(
  './main.c'
)

# Include directories
include_dirs = include_directories('./include')

# Build executable
executable(
  'balatro',
  sources,
  include_directories: include_dirs,
  dependencies: [gtk_dep],
  c_args: '-static-libgcc',         # optional: request static build
  link_args: '-static-libgcc'       # optional: request static linking
)
