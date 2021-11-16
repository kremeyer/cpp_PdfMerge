make: main.cpp
	g++ main.cpp -L ${{env.GITHUB_WORKSPACE}} -l boost -o PdfMerge
