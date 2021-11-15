#include "main.h"
#include <iostream>
#include <getopt.h>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

// tex code to include pdf
string tex_pdf(const string& fname, const string& pages){
    return "\\includepdf[pages=" + pages + "]{" + fname + "}";
}

// tex code to include image
string tex_image(const string& fname){
    return R"(\newpage\null\vfill\includegraphics[width=\textwidth,height=\textheight,keepaspectratio]{)" + fname + R"(}\vfill\null)";
}

// check if string ends with certain string
bool endswith (string const &fullString, string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool is_image(const string& fname){
    string fname_lower = fname;
    boost::algorithm::to_lower(fname_lower);
    if(endswith(fname_lower, ".png")){
        return true;
    }
    if(endswith(fname_lower, ".jpg")){
        return true;
    }
    if(endswith(fname_lower, ".jpeg")){
        return true;
    }
    return false;
}

bool is_pdf(const string& fname){
    string fname_lower = fname;
    boost::algorithm::to_lower(fname_lower);
    return endswith(fname_lower, ".pdf");
}


int main(int argc, char *argv[]) {

    // set default parameters
    int arg_offset = 1;
    bool verbose = false;
    string output_name = "merge.pdf";

    // check for command line arguments
    switch (getopt(argc, argv, "v")) {
        case 'v':
            verbose = true;
            arg_offset++;
        case -1:
            break;
    }

    // check if pdflatex is installed
    int pdflatex_version_ret;
    pdflatex_version_ret = system("pdflatex --version >nul 2>nul");
    if (pdflatex_version_ret != 0) {
        cout << "pdflatex not found, exiting...\n";
        return 0;
    }
    if (verbose) {
        cout << "USING PDFLATEX VERSION:" << "\n";
        cout << "--------------------------------------------\n";
        system("pdflatex --version");
        cout << "--------------------------------------------\n\n";
    }


    //check number of input files
    int n_files;
    n_files = argc - arg_offset;

    //print input files
    if (n_files > 0) {
        cout << n_files << " files to merge:\n";
        copy(argv + arg_offset, argv + argc, ostream_iterator<const char *>(cout, "\n"));
    } else {
        cout << "list files to merge as command line arguments\n";
    }

    //read files into array
    string files[n_files];
    for (int i = 0; i < n_files; i++) {
        files[i] = argv[i + arg_offset];
    }

    //create string containing acting as the tex document
    string texcode = tex_header;
    string pages = "-";
    bool pages_specified = false;

    for (int i = 0; i < n_files; i++) {
        if(is_pdf(files[i])) {
            if (i + 1 <= n_files){
                if (files[i+1][0] == '{'){
                    pages = files[i+1];
                    pages_specified = true;
                }
            }
            texcode += tex_pdf(files[i], pages);
            if (pages_specified){
                pages = "-";
                i++;
            }
            continue;
        }
        if(is_image(files[i])){
            texcode += tex_image(files[i]);
            continue;
        }
        cout << "could not merge file: " + files[i] + " unsupported format\n";
    }
    texcode += tex_footer;

    if (verbose) {
        cout << "ASSEMBLED TEX FILE:" << "\n";
        cout << "--------------------------------------------\n";
        cout << texcode << "\n";
        cout << "--------------------------------------------\n\n";
    }

    string pdflatex_command = ("pdflatex \"" + texcode + "\"");
    if (verbose) {
        system(pdflatex_command.c_str());
    } else {
        pdflatex_command += " >nul 2>nul";
        system(pdflatex_command.c_str());
    }

    // cleanup pdftex outpus
    rename("texput.pdf", output_name.c_str());
    remove("texput.aux");
    remove("texput.log");
    remove("nul");

    return 0;
}
