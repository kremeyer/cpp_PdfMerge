#include "string"

#ifndef PDF_MERGER_MAIN_H
#define PDF_MERGER_MAIN_H

using namespace std;

string tex_header = "\\documentclass[12pt, a4]{article}"
                    "\\usepackage{geometry}"
                    "\\geometry{"
                    "bindingoffset=0cm,"
                    "left=1cm,"
                    "right=1cm,"
                    "top=1cm,"
                    "bottom=1cm,"
                    "showframe=false,"
                    "}"
                    "\\usepackage{pdfpages}"
                    "\\pagestyle{empty}"
                    "\\setlength{\\parindent}{0cm}"
                    "\\begin{document}";

string tex_footer = "\\end{document}";

#endif //PDF_MERGER_MAIN_H
