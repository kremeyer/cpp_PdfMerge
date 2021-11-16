BOOST_ROOT := ${{ steps.install-boost.outputs.BOOST_ROOT }}

make: main.cpp
	pwd
	ls
	ls $(BOOST_ROOT)
	g++ main.cpp -I$(BOOST_ROOT) -o PdfMerge
