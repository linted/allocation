

add_custom_command(
    OUTPUT allocation.pdf
    # DEPENDS allocation.tex
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/allocation.tex ${CMAKE_CURRENT_SOURCE_DIR}/ieeeconf.cls ${CMAKE_CURRENT_BINARY_DIR}/ &&
        cd ${CMAKE_CURRENT_BINARY_DIR}/ && pdflatex allocation.tex 1>/dev/null && pdflatex allocation.tex 1>/dev/null && pdflatex allocation.tex 1>/dev/null
    )

add_custom_target(paper ALL DEPENDS allocation.pdf)