add_custom_command(
    OUTPUT allocation.pdf
    DEPENDS allocation.tex
    COMMAND pdflatex allocation.tex
    COMMAND pdflatex allocation.tex
    COMMAND pdflatex allocation.tex
    )