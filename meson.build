project('lab1', 'cpp')

executable(
	'main',
	sources: [
		'src/main.cpp',
		'src/Publication.cpp',
		'src/Book.cpp',
		'src/book/Fiction.cpp',
		'src/book/Novel.cpp',
		'src/book/Poem.cpp',
		'src/attrs/FullName.cpp',
		'src/attrs/Lifespan.cpp',
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