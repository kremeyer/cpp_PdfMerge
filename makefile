make: main.cpp
	pwd
	ls
	ls $(BOOST_ROOT)
	g++ main.cpp -I$(BOOST_ROOT) -o PdfMerge
