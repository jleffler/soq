(
set -x
./shm-master -H
./shm-master -ax
./shm-master -dx
./shm-master -da
./shm-master -dax
ipcs -m | grep -v '^0x00000000 '
./shm-master -x
ipcs -m | grep -v '^0x00000000 '
./shm-master -d
ipcs -m | grep -v '^0x00000000 '
./shm-master -f $PWD/shm-master -a
./shm-master -f $PWD/shm-master -d
./shm-master -f $PWD/shm-master -x
./shm-master -f $PWD/shm-master -d
./shm-master -f $PWD/shm-master -x
shmid=$(./shm-master -f $PWD/shm-master -a | sed -n '/ShmID: /s///p')
ipcs -m | grep -i $shmid | detab -e8
./shm-master -f $PWD/shm-master -d
) 2>&1 | stb | sed -e 's%/usr/local/google%%' -e 's/^++*/$/' | so
