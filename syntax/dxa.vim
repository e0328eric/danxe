" NOTE: Code stolen from Tsoding's bm
" Addr: https://github.com/tsoding/bm/blob/master/tools/basm.vim

" Vim syntax file
" Language: dxa

" Usage Instructions
" Put this file in .vim/syntax/dxa.vim
" and add in your .vimrc file the next line:
" autocmd BufRead,BufNewFile *.dxa set filetype=dxa

if exists("b:current_syntax")
  finish
endif

" Language keywords
syntax keyword dxaKeywords nop pop dup halt
syntax keyword dxaKeywords push pusht pushf push0 push1 pushn1
syntax keyword dxaKeywords pushu0 pushu1 pushf0 pushf1 pushfn1
syntax keyword dxaKeywords jmp jt jf je jne
syntax keyword dxaKeywords jg jge jl jle
syntax keyword dxaKeywords rjmp rjt rjf rje rjne
syntax keyword dxaKeywords rjg rjge rjl rjle
syntax keyword dxaKeywords call ret swap sswap rot
syntax keyword dxaKeywords and or xor not shl shr
syntax keyword dxaKeywords andb orb xorb notb
syntax keyword dxaKeywords add sub mul div neg
syntax keyword dxaKeywords eq neq lt lte gt gte
syntax keyword dxaKeywords inc dec store load
syntax keyword dxaKeywords alloc realloc free
syntax keyword dxaKeywords readi writei scani
syntax keyword dxaKeywords readu writeu scanu
syntax keyword dxaKeywords readf writef scanf
syntax keyword dxaKeywords readc writec scanc
syntax keyword dxaKeywords readb writeb scanb
syntax keyword dxaKeywords read scans
syntax keyword dxaKeywords print println prints printsln
syntax keyword dxaKeywords i2u u2i u2b b2u
syntax keyword dxaKeywords i2f f2i i2b b2i n2b

syntax keyword dxaLoopKeywords from to do

" Comments
syntax region dxaCommentLine start="//" end="$"   contains=dxaTodos
syntax region dxaDirective start="%" end=" "

syntax match dxaLabel		"\v\<([a-zA-Z0-9]|_|-|\?)*\>\n"he=e-1

" Numbers
syntax match dxaDecInt display "\<[0-9][0-9_]*\%([u]*\)"
syntax match dxaHexInt display "\<0[xX][0-9a-fA-F][0-9_a-fA-F]*"
syntax match dxaFloat  display "\<[0-9][0-9_]*\%(\.[0-9][0-9_]*\)"

" Strings
syntax region dxaString start=/\v"/ skip=/\v\\./ end=/\v"/
syntax region dxaString start=/\v'/ skip=/\v\\./ end=/\v'/

" Set highlights
highlight default link dxaTodos Todo
highlight default link dxaKeywords Identifier
highlight default link dxaCommentLine Comment
highlight default link dxaDirective PreProc
highlight default link dxaLoopKeywords PreProc
highlight default link dxaDecInt Number
highlight default link dxaHexInt Number
highlight default link dxaFloat Float
highlight default link dxaString String
highlight default link dxaLabel Label

let b:current_syntax = "dxa"
