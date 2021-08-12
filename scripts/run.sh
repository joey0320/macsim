#!/bin/bash
#
#SBATCH --job-name=macsim
#SBATCH --output=./results/result.%j.txt
#
#SBATCH --mail-type=ALL
#SBATCH --mail-user=joonho0320@gmail.com
#
#SBATCH --ntasks=8

IOMMU_EN_LIST=(0 1)
PTW_CNT_LIST=(1 4 8 16 32 64 128)

for PTW_CNT in 1 4 8 16 32
do
  srun -N1 -n1 -c1 --exclusive mkdir --out=saxpy-${PTW_CNT}
  srun -N1 -n1 -c1 --exclusive ./macsim --out=saxpy-${PTW_CNT} --ptw_cnt=${PTW_CNT} --pts_entry=${PTW_CNT} --prmb_cnt=${PTW_CNT}
done
wait

