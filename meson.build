project('wxpic', 'cpp', default_options : ['cpp_std=c++17'])

src = [
	'src/wxpic.cpp',
	'src/MainWindow.cpp',
	'src/MainWindowLayout.cpp',
	'src/ImagePanel.cpp',
	'src/ImageStack.cpp',
	'src/Types.cpp',
	'src/ShapeTool.cpp',
	'src/CropTool.cpp',
	'src/DrawTool.cpp',
	'src/Util.cpp',
	'src/Version.cpp',
	'src/imagwebp.cpp',
]

wx_dep = dependency('wxWidgets', version: '>=3.0.0')
libwebp_dev = dependency('libwebp', static: true)
libwebpdemux = dependency('libwebpdemux', static: true)

version_gen_h = custom_target(
	command : ['version.sh', 'version_gen.h'],
	build_always_stale: true,
   output: 'version_gen.h')

executable('wxpic', src, version_gen_h, dependencies: [wx_dep, libwebp_dev, libwebpdemux], install : true,  cpp_args : '-DNDEBUG')
