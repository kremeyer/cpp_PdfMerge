make: main.cpp
	g++ -I ${{env.GITHUB_WORKSPACE}} main.cpp -o PdfMerge
