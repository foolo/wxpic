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
	'src/imagwebp.cpp',
]

wx_dep = dependency('wxWidgets', version: '>=3.0.0')
libwebp_dev = dependency('libwebp', static: true)
libwebpdemux = dependency('libwebpdemux', static: true)

executable('wxpic', src, dependencies: [wx_dep, libwebp_dev, libwebpdemux], install : true,  cpp_args : '-DNDEBUG')
