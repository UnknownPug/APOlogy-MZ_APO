#!/bin/bash

ssh-add ~/.ssh/mzapo-root-key

ssh-add -l

scp -i ~/.ssh/mzapo-root-key /path/to/local/project/folder/*  root@MZAPO_IP:~/path/to/MZ_APO_FOLDER

ssh -i /opt/zynq/ssh-connect/mzapo-root-key root@MZAPO_IP <<END
cd ~/path/to/MZ_APO_FOLDER
make clean
make
./apology
END
echo "RUN COMPLETED"