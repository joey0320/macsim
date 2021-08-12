import os
import sys
import argparse
import functools
import pandas as pd

nullstr = ' '
nanstr = 'NAN'

parser = argparse.ArgumentParser(description='Extract Stats')
parser.add_argument('--results', dest='result_path', type=str, 
                    default='./results', help='path to slurm results')
parser.add_argument('--outfile', dest='outfile_path', type=str, default='./out.csv', 
                    help='path to slurm results')
args = parser.parse_args()

iommu_knob_list = [
    'ptw_cnt'
    ]

iommu_stat_list = [
    'total_sim_cycles',
    'tlb_hit_count',
    'tlb_miss_count',
    'tlb_blocked_cycles',
    'pts_hit_count',
    'prmb_merged_count',
    'ptw_full_cycles',
    'number_of_page_table_walks',
    'pgd_register_hit_count',
    'pgd_register_miss_count',
    'pud_register_hit_count',
    'pud_register_miss_count',
    'pmd_register_hit_count',
    'pmd_register_miss_count'
    ]

macsim_knob_list = [
    'num_sim_cores',
    'enable_physical_mapping'
    ]

macsim_stat_list = [
    'CYC_COUNT_TOT',
    'INST_COUNT_TOT',
    'TLB_HIT',
    'TLB_MISS'
    ]

def cmd(command):
  fail = os.system(command)
  if fail:
    print(f'[*] ERROR : could not execute {command}')
    sys.exit(1)

def get_candidate_lines(key, file_path):
  file = open(file_path, 'r')
  lines = file.readlines()
  cand_list = []

  for line in lines:
    if key in line:
      cand_list.append(line)
  return cand_list

def get_word(line, index):
  words = line.split()
  try:
    ret = float(words[index])
  except:
    ret = nanstr
  return ret

def get_val(key, file_path, index=-1):
  line_list = get_candidate_lines(key, file_path)
  for line in line_list:
    val = get_word(line, index)
    if val != nanstr:
      return val
  return nanstr

def get_val_list(key_list, file_path, index=-1):
  val_list = []
  for key in key_list:
    val = get_val(key, file_path, index)
    val_list.append(val)
  return list(zip(key_list, val_list))

def process_file(file_path):
  iommu_config = get_val_list(iommu_knob_list, file_path)
  iommu_stats = get_val_list(iommu_stat_list, file_path)

  macsim_config = get_val_list(macsim_knob_list, file_path)
  macsim_stats = get_val_list(macsim_stat_list, file_path, 1)

  configs = iommu_config + macsim_config
  stats = iommu_stats + macsim_stats
  data = configs + stats
  return data

# [(k1, v1), (k2, v2)...] -> key_name | k1, k2, ...
#                            val_name | v1, v2, ...
def keyval_list_to_df(keyval_list):
    unzip_obj = zip(*keyval_list)
    unzip_list = list(unzip_obj)
    (key_list, val_list) = unzip_list
    return pd.DataFrame(val_list, index=key_list).transpose()

def export_to_csv(df, outfile_path):
  df.to_csv(outfile_path)

def concat_dflist(df_list):
  return pd.concat(df_list)

def main():
  cwd = os.getcwd()
  result_path = os.path.join(cwd, args.result_path)
  out_path = os.path.join(cwd, args.outfile_path)
  df_list = []

  for file_name in os.listdir(result_path):
    # skip directories
    if os.path.isdir(os.path.join(result_path, file_name)):
        continue

    file_path = os.path.join(result_path, file_name)
    data = process_file(file_path)
    df = keyval_list_to_df(data)
    df_list.append(df)

  df = concat_dflist(df_list)
  export_to_csv(df, out_path)

  print('[*] data processing finished')


if __name__=="__main__":
  main()
