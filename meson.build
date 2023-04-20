project('danxe',
  'cpp',
  license: 'MIT',
  version: '0.0.0',
  default_options: [
    'c_std=11',
    'cpp_std=c++20',
    'warning_level=1',
  ])

sources = files(
  'src/main.cc',
  'src/utils.cc',
  'src/vm/Value.cc',
)

# additional compiler flags
cxx = meson.get_compiler('cpp')
cxx_flags = []

if cxx.get_id() == 'gcc'
  cxx_flags +=  ['-Wimplicit-fallthrough']
endif

if cxx.get_id() == 'clang'
  cxx_flags +=  ['-Wimplicit-fallthrough']
endif

add_project_arguments(cxx_flags, language: 'cpp')

# dependencies
fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')

executable('danxe', sources,
  include_directories: [
    './src',
  ],
  dependencies: [
    fmt_dep,
  ])
