#include"./src/include/alt_index.h"
#include"../indexInterface.h"

template<class KEY_TYPE, class PAYLOAD_TYPE>
class altInterface : public indexInterface<KEY_TYPE, PAYLOAD_TYPE> {
public:
    void init(Param *param = nullptr) {}

    void bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num, Param *param = nullptr);

    bool get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param = nullptr);

    bool put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param = nullptr);

    bool update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param = nullptr);

    bool remove(KEY_TYPE key, Param *param = nullptr);

    size_t scan(KEY_TYPE key_low_bound, size_t key_num, std::pair <KEY_TYPE, PAYLOAD_TYPE> *result,
                Param *param = nullptr);

    long long memory_consumption() { return alt.memoryConsumption(); }

    long long get_model_nums();

private:
    alt_index::AltIndex <KEY_TYPE, PAYLOAD_TYPE> alt;
};

template<class KEY_TYPE, class PAYLOAD_TYPE>
void altInterface<KEY_TYPE, PAYLOAD_TYPE>::bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num,
                                                      Param *param) {


//    auto start = std::chrono::high_resolution_clock::now();
    alt.bulkLoad(key_value, static_cast<int>(num));
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    std::cout << "ALT-index bulkload time:" << duration.count() << "us" << std::endl;
//     std::cout << "buffer data number:" << alt.buffer_num << std::endl;
     alt.printFastPointer();
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool altInterface<KEY_TYPE, PAYLOAD_TYPE>::get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param) {
    bool exist = false;
    val = alt.find(key, exist);
    return exist;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool altInterface<KEY_TYPE, PAYLOAD_TYPE>::put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
    bool ok;
    ok = alt.insert(key, value);
    return ok;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool altInterface<KEY_TYPE, PAYLOAD_TYPE>::update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
    bool ok;
    ok = alt.update(key, value);
    return ok;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool altInterface<KEY_TYPE, PAYLOAD_TYPE>::remove(KEY_TYPE key, Param *param) {
    bool ok;
    ok = alt.remove(key);
    return ok;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
size_t altInterface<KEY_TYPE, PAYLOAD_TYPE>::scan(KEY_TYPE key_low_bound, size_t key_num,
                                                   std::pair <KEY_TYPE, PAYLOAD_TYPE> *result,
                                                   Param *param) {
    int scan_size = alt.rangeQuery(result, key_low_bound, key_num);
    return scan_size;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
long long altInterface<KEY_TYPE, PAYLOAD_TYPE>::get_model_nums() {
    return alt.node_keys_num;
}
