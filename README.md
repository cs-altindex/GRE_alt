# GRE
GRE is a benchmark suite for learned indexes and traditional indexes to measure throughput and latency with custom workload (read / write ratio) and any dataset. GRE quantifies datasets using local and global hardness, and includes a synthetic data generator to generate data with various hardness.

See details in our VLDB 2022 paper below. If you use our work, please cite:
```
Chaichon Wongkham, Baotong Lu, Chris Liu, Zhicong Zhong, Eric Lo, and Tianzheng Wang. Are Updatable Learned Indexes Ready?. PVLDB, 15(11): 3004 - 3017, 2022.
```

## Requirements
- gcc 8.3.0+
- cmake 3.12.0+

## Dependencies
- intel-mkl 2025.0.1.46
```bash
# download install script
wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/dfc4a434-838c-4450-a6fe-2fa903b75aa7/intel-oneapi-base-toolkit-2025.0.1.46_offline.sh

# install intel oneapi
sudo sh ./intel-oneapi-base-toolkit-2025.0.1.46_offline.sh -a --silent --cli --eula accept

# then the intel oneapi is installed in /opt/intel/oneapi by default
# set varaibles in CMakeLists.txt
set(MKL_INCLUDE_DIRS "/opt/intel/oneapi/mkl/2025.0/include")
```
- intel-tbb
- jemalloc
```bash
sudo apt install libtbb-dev libjemalloc-dev
```
## Build
```bash
git submodule update --init # only for the first time
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && make

# download datasets
cd datasets && sudo chmod 755 ./download.sh && ./download.sh
```
Additional datasets can be found at:

- [Longlat (200M 8-byte floats)](https://drive.google.com/file/d/1mH-y_PcLQ6p8kgAz9SB7ME4KeYAfRfmR/view?usp=sharing)
- [YCSB (200M 8-byte unsigned ints)](https://drive.google.com/file/d/1Q89-v4FJLEwIKL3YY3oCeOEs0VUuv5bD/view?usp=sharing)

## Basic usage
To calculate throughput:
```bash
./build/microbench \
--keys_file=./data/dataset \
--keys_file_type={binary,text} \
--read=0.5 --insert=0.5 \
--operations_num=800000000 \
--table_size=-1 \
--init_table_ratio=0.5 \
--thread_num=24 \
--index=index_name \
```
table_size=-1 is to infer from the first line of the file.
init_table_ratio is to specify the proportion of the dataset to bulkload.

For additional features, add additional flags:
- Latency
```
--latency_sample --latency_sample_ratio=0.01
```
- Range query (eg. range = 100)
```
--scan_ratio=1 --scan_num=100
```
- To use Zipfian distribution for lookup
```
--sample_distribution=zipf
```
- To perform data-shift experiment. Note that the key file needs to be generated like so (changing from one dataset to another). This flag just simply prevent the keys be shuffled and preserving the order in the key file
```
--data_shift
```
- Calculate data hardness (PLA-metric) with specified model error bound of the input dataset
```
--dataset_statistic --error_bound=32
```
- If the index implement memory consumption interface
```
--memory
```
All the result will be output to the csv file specified in --output_path flag.

## Use test script

```bash
./test.sh
```
