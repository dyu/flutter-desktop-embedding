## Build via GN
1. `git clone --depth 1 --single-branch -b cpp14 https://github.com/dyu/gn-build`

2. `echo 'buildconfig = "//gn-build/config/BUILDCONFIG.gn"' > .gn`

3. `gn gen gn-out --args='gcc_cc="gcc" gcc_cxx="g++" symbol_level=0 is_debug=false is_clang=false is_official_build=true'`

4. `ninja -C gn-out`
