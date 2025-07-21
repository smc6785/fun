# The first parameter would be the path for the disk
LFS_DISK = "$1"

# commands for fdisk
sudo fdisk "$LFS_DISK" << EOF
o
n
p
1


+100M
a
n
p
2


p
w
q
EOF

# boot partition
sudo mkfs -t ext2 -f "${LFS_DISK}1"
# kernel partition
sudo mkfs -t ext2 -f "${LFS_DISK}2"
