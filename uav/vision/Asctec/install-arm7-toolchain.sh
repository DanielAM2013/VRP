#!/bin/bash

apt-get install libx11-6 libx11-dev libncurses5-dev libncursesw5-dbg libncursesw5-dev libncurses5 libncurses5-dbg libncursesw5  libnewlib-dev libnewlib-dev newlib-source  zlibc texinfo flex bison gdb

export PATH=$PATH:/usr/local/arm7/bin
echo 'export PATH=$PATH:/usr/local/arm7/bin' >> ~/.bashrc

tar -C / -xjf arm7-gcc-2012-03-28.tar.bz2 

#cd /usr/local/arm7/bin

#for i in * 
#do
#   echo "$i"
#   ln -s $i /usr/bin/
#   chmod a+x $i
#done


