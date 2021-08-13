#!/bin/bash
#
#SBATCH --job-name=macsim
#SBATCH --output=./results/result.%j.txt
#
#SBATCH --mail-type=ALL
#SBATCH --mail-user=joonho0320@gmail.com
#
#SBATCH --ntasks=1
#SBATCH --array=0-13

IOMMU_EN_LIST=(0 1)
PTW_CNT_LIST=(1 4 8 16 32 64 128)

IOMMU_EN_ID=$((${SLURM_ARRAY_TASK_ID}%2))
PTW_CNT_ID=$((${SLURM_ARRAY_TASK_ID}%7))

IOMMU_EN=${IOMMU_EN_LIST[${IOMMU_EN_ID}]}
PTW_CNT=${PTW_CNT_LIST[${PTW_CNT_ID}]}

OUT_DIR="saxpy-${PTW_CNT}-${IOMMU_EN}"

srun mkdir ${OUT_DIR}
srun ./macsim --out=${OUT_DIR} --ptw_cnt=${PTW_CNT} --pts_entry=${PTW_CNT} --prmb_cnt=0
