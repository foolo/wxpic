env = Environment()
src = [
	'wxpic.cpp',
	'MainWindow.cpp',
	'MainWindowLayout.cpp',
	'ImagePanel.cpp',
	'ImageStack.cpp',
	'ShapeTool.cpp',
]

env.ParseConfig('wx-config --cflags --libs')
env.Append(CCFLAGS = '-g')
env.Program(target = 'wxpic', source = src)

