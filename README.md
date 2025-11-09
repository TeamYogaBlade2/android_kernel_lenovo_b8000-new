WHAT IS THIS?
=============

Linux Kernel source code for the device Lenovo YOGA Tablet 10 based on bq Aquaris 5

BUILD INSTRUCTIONS?
===================

Specific sources are separated by branches and each version is tagged with it's corresponding number. First, you should
clone the project:

	$ git clone --filter=blob:none https://github.com/TeamYogaBlade2/android_kernel_lenovo_b8000-new

(or `--depht=1`)

Build the kernel:

	$ ./makeMtk -t blade10 n k
