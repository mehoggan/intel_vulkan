let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Devel/github/mehoggan/intel_vulkan
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess+=aoO
badd +73 include/intel_vulkan/Tutorial02.h
badd +1193 src/Tutorial02.cpp
badd +1 term://~/Devel/github/mehoggan/intel_vulkan//1628653:/bin/bash
badd +2791 /usr/include/vulkan/vulkan_core.h
badd +0 NvimTree_1
argglobal
%argdel
edit src/Tutorial02.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 116 + 64) / 129)
exe 'vert 1resize ' . ((&columns * 169 + 254) / 509)
exe '2resize ' . ((&lines * 116 + 64) / 129)
exe 'vert 2resize ' . ((&columns * 169 + 254) / 509)
exe '3resize ' . ((&lines * 116 + 64) / 129)
exe 'vert 3resize ' . ((&columns * 169 + 254) / 509)
exe '4resize ' . ((&lines * 10 + 64) / 129)
argglobal
balt include/intel_vulkan/Tutorial02.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 157 - ((102 * winheight(0) + 58) / 116)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 157
normal! 09|
wincmd w
argglobal
if bufexists(fnamemodify("src/Tutorial02.cpp", ":p")) | buffer src/Tutorial02.cpp | else | edit src/Tutorial02.cpp | endif
if &buftype ==# 'terminal'
  silent file src/Tutorial02.cpp
endif
balt include/intel_vulkan/Tutorial02.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1193 - ((60 * winheight(0) + 58) / 116)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1193
normal! 045|
wincmd w
argglobal
if bufexists(fnamemodify("term://~/Devel/github/mehoggan/intel_vulkan//1628653:/bin/bash", ":p")) | buffer term://~/Devel/github/mehoggan/intel_vulkan//1628653:/bin/bash | else | edit term://~/Devel/github/mehoggan/intel_vulkan//1628653:/bin/bash | endif
if &buftype ==# 'terminal'
  silent file term://~/Devel/github/mehoggan/intel_vulkan//1628653:/bin/bash
endif
balt src/Tutorial02.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
let s:l = 116 - ((115 * winheight(0) + 58) / 116)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 116
normal! 0
wincmd w
argglobal
enew
balt src/Tutorial02.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
wincmd w
2wincmd w
exe '1resize ' . ((&lines * 116 + 64) / 129)
exe 'vert 1resize ' . ((&columns * 169 + 254) / 509)
exe '2resize ' . ((&lines * 116 + 64) / 129)
exe 'vert 2resize ' . ((&columns * 169 + 254) / 509)
exe '3resize ' . ((&lines * 116 + 64) / 129)
exe 'vert 3resize ' . ((&columns * 169 + 254) / 509)
exe '4resize ' . ((&lines * 10 + 64) / 129)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
