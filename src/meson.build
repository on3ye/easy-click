src = [
  'main.c',
  'activate.c',
  'gui.c',
  'signals.c',
  'autoclick.c'
] 

executable('final', src,
  include_directories: include_directories('..', '../include'),
  dependencies: [gtk4_dep, x11_dep, xtst_dep],
  install: true)
