project('lab1', 'cpp')

executable(
	'main',
	sources: [
		'src/main.cpp',
		'src/Publication.cpp',
		'src/Book.cpp',
	],
	include_directories: [
		'src',
	],
	cpp_args: [
		'-Wall',
		'-Wextra',
		'-Wpedantic',
	],
	override_options: {
		'cpp_std': 'c++20',
	}
)