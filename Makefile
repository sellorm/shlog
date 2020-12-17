shlog: shlog.c
	gcc shlog.c -o shlog

test: test.sh shlog
	./test.sh
	SHLOG_JSON=true ./test.sh

README.md: README.Rmd 
	-rm README.html
	-[ ! -d docs ] && mkdir docs
	R -q -e "rmarkdown::render('README.Rmd', output_format = 'prettydoc::html_pretty', output_file = 'README.html', clean = TRUE)"
	mv README.html docs/index.html
	R -q -e "rmarkdown::render('README.Rmd', output_format = 'github_document', clean = TRUE, output_file = 'README.md')"
	-rm README.html

build:
	./build.sh

clean:
	-rm README.md
	-rm docs/index.html

.PHONY: test clean build
