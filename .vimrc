"######[http://www.alexeyshmalko.com/2014/using-vim-as-c-cpp-ide/]########

set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

"####set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

"#By default, Vim assumes all .h files to be C++ files. 
"#However, I work with pure C and want filetype to be c. Since project 
"#also comes with doxygen documentation, I want to set subtype to doxygen to 
"#enable very nice doxygen highlighting.

augroup project
    autocmd!
    autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END



"#By default, Vim searches file in working directory. 
"#However, most projects have separated directory for include files. 
"#Thus, you should set Vim’s path option to contain a comma-separated 
"#list of directories to look for the file.

let &path.="src/include,/usr/include/AL,"
