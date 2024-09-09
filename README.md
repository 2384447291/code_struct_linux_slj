# code_struct_linux_slj
rm -rf ./*
sudo gedit
sudo  find / -name  libstdc++.so.6*
strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX
ls /dev | grep ttyUSB
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DCMAKE_BUILD_TYPE=Release ..
ulimit -c unlimited
pwd