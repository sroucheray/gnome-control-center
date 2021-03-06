panels_list += cappletname
desktop = 'gnome-@0@-panel.desktop'.format(cappletname)

desktop_in = configure_file(
  input: desktop + '.in.in',
  output: desktop + '.in',
  configuration: desktop_conf
)

i18n.merge_file(
  desktop,
  type: 'desktop',
  input: desktop_in,
  output: desktop,
  po_dir: po_dir,
  install: true,
  install_dir: control_center_desktopdir
)

install_data(
  'slideshow-symbolic.svg',
  install_dir: join_paths(control_center_icondir, 'hicolor', 'scalable', 'categories')
)

install_data(
  'slideshow-emblem.svg',
  install_dir: join_paths(control_center_icondir, 'hicolor', 'scalable', 'emblems')
)

install_data(
  'noise-texture-light.png',
  install_dir: join_paths(control_center_pkgdatadir, 'pixmaps')
)

common_sources = []

enums = 'gdesktop-enums-types'
enums_header = files(
  gsettings_desktop_dep.get_pkgconfig_variable('prefix') + '/include/gsettings-desktop-schemas/gdesktop-enums.h',
  'cc-background-item.h'
)

common_sources += gnome.mkenums(
  enums + '.h',
  sources: enums_header,
  fhead: '#ifndef __GDESKTOP_ENUMS_TYPES_H__\n#define __GDESKTOP_ENUMS_TYPES_H__\n\n#include <glib-object.h>\n\nG_BEGIN_DECLS\n',
  fprod: '/* enumerations from "@filename@" */\n',
  vhead: 'GType @enum_name@_get_type (void) G_GNUC_CONST;\n#define G_DESKTOP_TYPE_@ENUMSHORT@ (@enum_name@_get_type())\n',
  ftail: 'G_END_DECLS\n\n#endif /* __GDESKTOP_ENUMS_TYPES_H__ */'
)

common_sources += gnome.mkenums(
  enums + '.c',
  sources: enums_header,
  fhead: '#include <gdesktop-enums.h>\n#include "gdesktop-enums-types.h"\n#include "cc-background-item.h"',
  fprod: '\n/* enumerations from "@filename@" */',
  vhead: 'GType\n@enum_name@_get_type (void)\n{\n  static GType etype = 0;\n  if (etype == 0) {\n    static const G@Type@Value values[] = {',
  vprod: '      { @VALUENAME@, "@VALUENAME@", "@valuenick@" },',
  vtail: '      { 0, NULL, NULL }\n    };\n    etype = g_@type@_register_static ("@EnumName@", values);\n  }\n  return etype;\n}\n'
)

resource_data = files('background.ui')

common_sources += gnome.compile_resources(
  'cc-@0@-resources'.format(cappletname),
  cappletname + '.gresource.xml',
  c_name: 'cc_' + cappletname,
  dependencies: resource_data,
  export: true
)

sources = common_sources + files(
  'bg-colors-source.c',
  'bg-pictures-source.c',
  'bg-source.c',
  'bg-wallpapers-source.c',
  'cc-background-chooser-dialog.c',
  'cc-background-grilo-miner.c',
  'cc-background-item.c',
  'cc-background-xml.c'
)

deps = common_deps + [
  gdk_pixbuf_dep,
  gnome_desktop_dep,
  goa_dep,
  libxml_dep,
  dependency('cairo-gobject'),
  dependency('grilo-0.3', version: '>= 0.3.0')
]

cflags += [
  '-DGNOMELOCALEDIR="@0@"'.format(control_center_localedir),
  '-DDATADIR="@0@"'.format(control_center_datadir),
  '-DGNOME_DESKTOP_USE_UNSTABLE_API'
]

libbackground_chooser = static_library(
  cappletname + '-chooser',
  sources: sources,
  include_directories: top_inc,
  dependencies: deps,
  c_args: cflags
)

sources = common_sources + files('cc-background-panel.c')

panels_libs += static_library(
  cappletname,
  sources: sources,
  include_directories: top_inc,
  dependencies: deps,
  c_args: cflags,
  link_with: libbackground_chooser
)

test_name = 'test-chooser-dialog'

executable(
  test_name,
  test_name + '.c',
  include_directories: top_inc,
  dependencies: deps,
  c_args: cflags,
  link_with: libbackground_chooser
)
