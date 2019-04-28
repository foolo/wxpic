env = Environment()
src = [
	'wxpic.cpp',
	'MainWindow.cpp',
	'MainWindowLayout.cpp',
	'wxCustomButton.cpp',
]
env.ParseConfig('wx-config --cflags --libs')
env.Program(target = 'wxpic', source = src)

