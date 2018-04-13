## Fetch deps
```sh
./deps.sh
```

## Build via GN
1. `git clone --depth 1 --single-branch -b cpp14 https://github.com/dyu/gn-build`

2. `echo 'buildconfig = "//gn-build/config/BUILDCONFIG.gn"' > .gn`

3. `gn gen gn-out --args='gcc_cc="gcc" gcc_cxx="g++" symbol_level=0 is_debug=false is_clang=false is_official_build=true'`

4. `ninja -C gn-out`

See https://github.com/flutter/flutter/issues/14438 if you have problems building the flutter engine

## Install fonts
```sh
sudo apt-get install fonts-roboto

# or link the bundled fonts
sudo ln -s $PWD/fonts/truetype/roboto /usr/share/fonts/truetype/roboto
```

## Link and build the app
```sh
ln -s example_flutter app
./build.sh
```

### Memory usage of the app: `example_flutter`
Ubuntu 14.04 x64
```
 Private  +   Shared  =  RAM used	Program

 98.7 MiB +   1.4 MiB = 100.1 MiB	run
---------------------------------
                        100.1 MiB
=================================
```

Ubuntu 16.04 x64
```
 Private  +   Shared  =  RAM used	Program

115.4 MiB +   3.0 MiB = 118.3 MiB	run
---------------------------------
                        118.3 MiB
=================================
```

Note: the binaries are built in release mode `host_release`

### Download and run the prebuilt binary (17.4mb) to test on your system
```sh
wget -O fde-linux-x64.tar.gz 'https://onedrive.live.com/download?cid=73A9A646B31A141F&resid=73A9A646B31A141F%21469&authkey=AKdY45YMew02dZg'
tar -xzf fde-linux-x64.tar.gz
cd fde-linux-x64
./target/run
```

Make sure the font `roboto` is already installed for the app to run properly (`sudo apt-get install fonts-roboto`)

