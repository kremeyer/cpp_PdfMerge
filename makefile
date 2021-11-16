make: main.cpp
	pwd
	ls --all
	ls $(BOOST_ROOT)
	g++ main.cpp -I$(BOOST_ROOT) -o PdfMerge
