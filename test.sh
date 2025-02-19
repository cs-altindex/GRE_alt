#!/bin/bash
set -o errexit

set -o nounset


#if [ -f "../results/1.csv" ]; then
#    # Program is in PATH.
#    rm ../results/1.csv
#fi

#keys_files=( "books" "covid" "fb" "genome" "history" "libio" "osm" "stack" "wise" "ycsb" "longlat" "longitudes")
#keys_files=( "books" "covid" "genome" "history"  "osm"  "wise" "ycsb" )
keys_files=(  "fb" "libio" "osm")
#keys_files=( "libio" "osm" "longlat" "longitudes")
# keys_files=("ycsb")
#keys_files=( "genome" "history" "libio" "osm" "stack" "wise")
#keys_files=( "genome" "history" "libio" "osm" "stack" "wise")
#keys_files=("covid" "libio" "planet" "stack" "wise")
keys_file_types=("binary" "text")
reads=("0.1" "0.2" "0.3" "0.4" "0.5" "0.6" "0.7" "0.8" "0.9")
inserts=("0.1" "0.2" "0.3" "0.4" "0.5" "0.6" "0.7" "0.8" "0.9")
operations_nums=("1000000" "10000000" "100000000")
table_sizes=("2000000" "20000000" "200000000")
thread_nums=( "1" "32")
init_table_ratios=("0.1" "0.3" "0.5" "0.7" "0.9")
zipfian_thetas=("0.99" "0.9" "0.8" "0.7" "0.6" "0.5")
scan_numbers=("100")


for keys_file in ${keys_files[@]}; do
#     for zipfian_theta in ${zipfian_thetas[@]}; do
         for scan_num in ${scan_numbers[@]}; do
#            for table_size in ${table_sizes[@]}; do
#                for thread_num in ${thread_nums[@]}; do
#                    for init_table_ratio in ${init_table_ratios[@]}; do
                      ./build/microbench \
                      --keys_file=./datasets/${keys_file} \
                      --keys_file_type=binary \
                      --read=0.5 --insert=0.5 --scan=0 --update=0 \
                      --operations_num=1000000 \
                      --table_size=2000000 \
                      --init_table_ratio=0.5 \
                      --thread_num=8 \
                      --index=alt,finedex\
                      --sample_distribution=uniform \
                      --output_path=./results/final_read_write.csv \
                      --latency_sample=1 \
                      --data_statistic=1 \
                      --memory=1 \
                      --error_bound=32 \
                      --scan_num=${scan_num} \
                      --seed=114514
#                    done
#                done
#            done
         done
#     done
done