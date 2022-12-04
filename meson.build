project('wxpic', 'cpp', default_options : ['cpp_std=c++17'])

src = [
	'src/wxpic.cpp',
	'src/MainWindow.cpp',
	'src/MainWindowLayout.cpp',
	'src/ImagePanel.cpp',
	'src/ImageStack.cpp',
	'src/LoadedFile.cpp',
	'src/ShapeTool.cpp',
	'src/DrawTool.cpp',
	'src/Util.cpp',
]

wx_dep = dependency('wxWidgets', version: '>=3.0.0')

executable('wxpic', src, dependencies: wx_dep, install : true)
