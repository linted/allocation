
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/allocation.pdf
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/allocation.tex
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/allocation.tex ${CMAKE_CURRENT_SOURCE_DIR}/ieeeconf.cls ${CMAKE_CURRENT_SOURCE_DIR}/graphs ${CMAKE_CURRENT_BINARY_DIR}/ &&
        cd ${CMAKE_CURRENT_BINARY_DIR}/ && pdflatex allocation.tex 1>/dev/null && pdflatex allocation.tex 1>/dev/null && pdflatex allocation.tex 1>/dev/null
)

add_custom_target(paper ALL 
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/allocation.pdf
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/allocation.pdf ${CMAKE_SOURCE_DIR}
)