make: main.cpp
	g++ -I ${{ steps.install-boost.outputs.BOOST_ROOT }} main.cpp -o PdfMerge
