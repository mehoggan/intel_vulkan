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
badd +1233 src/Tutorial02.cpp
badd +97 src/Tutorial01.cpp
badd +3 include/intel_vulkan/Tutorial01.h
badd +26 include/intel_vulkan/Tutorial02.h
argglobal
%argdel
edit src/Tutorial02.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
4wincmd h
wincmd w
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
exe 'vert 1resize ' . ((&columns * 30 + 254) / 509)
exe 'vert 2resize ' . ((&columns * 119 + 254) / 509)
exe 'vert 3resize ' . ((&columns * 119 + 254) / 509)
exe 'vert 4resize ' . ((&columns * 119 + 254) / 509)
exe 'vert 5resize ' . ((&columns * 118 + 254) / 509)
argglobal
enew
file NvimTree_1
balt src/Tutorial02.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal nofoldenable
lcd ~/Devel/github/mehoggan/intel_vulkan
wincmd w
argglobal
balt ~/Devel/github/mehoggan/intel_vulkan/src/Tutorial02.cpp
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
let s:l = 189 - ((72 * winheight(0) + 62) / 124)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 189
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial02.h", ":p")) | buffer ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial02.h | else | edit ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial02.h | endif
if &buftype ==# 'terminal'
  silent file ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial02.h
endif
balt ~/Devel/github/mehoggan/intel_vulkan/src/Tutorial01.cpp
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
let s:l = 114 - ((68 * winheight(0) + 62) / 124)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 114
normal! 039|
wincmd w
argglobal
if bufexists(fnamemodify("~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial01.h", ":p")) | buffer ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial01.h | else | edit ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial01.h | endif
if &buftype ==# 'terminal'
  silent file ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial01.h
endif
balt ~/Devel/github/mehoggan/intel_vulkan/src/Tutorial01.cpp
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
let s:l = 27 - ((26 * winheight(0) + 62) / 124)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Devel/github/mehoggan/intel_vulkan/src/Tutorial01.cpp", ":p")) | buffer ~/Devel/github/mehoggan/intel_vulkan/src/Tutorial01.cpp | else | edit ~/Devel/github/mehoggan/intel_vulkan/src/Tutorial01.cpp | endif
if &buftype ==# 'terminal'
  silent file ~/Devel/github/mehoggan/intel_vulkan/src/Tutorial01.cpp
endif
balt ~/Devel/github/mehoggan/intel_vulkan/include/intel_vulkan/Tutorial01.h
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
let s:l = 139 - ((91 * winheight(0) + 62) / 124)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 139
normal! 013|
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 30 + 254) / 509)
exe 'vert 2resize ' . ((&columns * 119 + 254) / 509)
exe 'vert 3resize ' . ((&columns * 119 + 254) / 509)
exe 'vert 4resize ' . ((&columns * 119 + 254) / 509)
exe 'vert 5resize ' . ((&columns * 118 + 254) / 509)
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
