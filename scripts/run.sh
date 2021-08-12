#!/bin/bash
#
#SBATCH --job-name=test_job
#SBATCH --output=./results/result.%j.txt
#
#SBATCH --mail-type=ALL
#SBATCH --mail-user=joonho0320@gmail.com
#
#SBATCH --ntasks=1
#SBATCH --array=0-6

ARGS=(1 4 8 16 32 64 128)
PTW_CNT=${ARGS[${SLURM_ARRAY_TASK_ID}]}
OUT_DIR="stats-${PTW_CNT}"

srun echo "================== running experiment : ${SLURM_ARRAY_TASK_ID} ========================="
srun ./macsim --out=${OUT_DIR} --ptw_cnt=${PTW_CNT} --pts_entry=${PTW_CNT} --prmb_cnt=0
srun mkdir ${OUT_DIR}

srun echo "=============================  IOMMU SIM CONFIGURATION ================================="
srun cat "./${OUT_DIR}/configs.out"

srun echo "=================================  IOMMU SIM STATS ====================================="
srun cat "./${OUT_DIR}/iommu-stats.txt"

srun echo "============================  macsim SIM CONFIGURATION ================================="
srun cat "./${OUT_DIR}/params.out"

srun echo "============================  macsim SIM STATS ================================="
srun cat ./${OUT_DIR}/general.stat.out
srun cat ./${OUT_DIR}/core.stat.out
srun cat ./${OUT_DIR}/memory.stat.out
srun cat ./${OUT_DIR}/inst.stat.out
