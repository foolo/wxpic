project('wxpic', 'cpp')

src = [
	'wxpic.cpp',
	'MainWindow.cpp',
	'MainWindowLayout.cpp',
	'ImagePanel.cpp',
	'ImageStack.cpp',
	'ShapeTool.cpp',
]

wx_dep = dependency('wxWidgets', version: '>=3.0.0')

executable('wxpic', src, dependencies: wx_dep)
