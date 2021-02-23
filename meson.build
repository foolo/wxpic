project('wxpic', 'cpp', default_options : ['cpp_std=c++17'])

src = [
	'wxpic.cpp',
	'MainWindow.cpp',
	'MainWindowLayout.cpp',
	'ImagePanel.cpp',
	'ImageStack.cpp',
	'ShapeTool.cpp',
	'DrawTool.cpp',
	'Util.cpp',
]

wx_dep = dependency('wxWidgets', version: '>=3.0.0')

executable('wxpic', src, dependencies: wx_dep)
