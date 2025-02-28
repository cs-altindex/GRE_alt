//
// Created by yyx on 23-11-7.
//

#ifndef GRE_SALI_H
#define GRE_SALI_H
#include"./src/src/core/sali.h"
#include"../indexInterface.h"

template<class KEY_TYPE, class PAYLOAD_TYPE>
class SALIInterface : public indexInterface<KEY_TYPE, PAYLOAD_TYPE> {
public:
    void init(Param *param = nullptr) {}

    void bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num, Param *param = nullptr);

    bool get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param = nullptr);

    bool put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param = nullptr);

    bool update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param = nullptr);

    bool remove(KEY_TYPE key, Param *param = nullptr);

    size_t scan(KEY_TYPE key_low_bound, size_t key_num, std::pair <KEY_TYPE, PAYLOAD_TYPE> *result,
                Param *param = nullptr);

    long long memory_consumption() { return sali.total_size(); }

    void print(Param *param = nullptr){ sali.print_depth();}

    long adjust_num(){
        return sali.adjust_num();
    }

    std::tuple<long,double,long> depth(){
        return sali.depth();
    }

    long long get_model_nums() { return 0;}

private:
    sali::SALI<KEY_TYPE, PAYLOAD_TYPE> sali;
};

template<class KEY_TYPE, class PAYLOAD_TYPE>
void SALIInterface<KEY_TYPE, PAYLOAD_TYPE>::bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num,
                                                      Param *param) {
    sali.bulk_load(key_value, static_cast<int>(num));
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool SALIInterface<KEY_TYPE, PAYLOAD_TYPE>::get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param) {
    return sali.at(key, val);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool SALIInterface<KEY_TYPE, PAYLOAD_TYPE>::put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
    sali.insert(key, value);
    return true;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool SALIInterface<KEY_TYPE, PAYLOAD_TYPE>::update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
    return sali.update(key, value);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool SALIInterface<KEY_TYPE, PAYLOAD_TYPE>::remove(KEY_TYPE key, Param *param) {
    return sali.remove(key);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
size_t SALIInterface<KEY_TYPE, PAYLOAD_TYPE>::scan(KEY_TYPE key_low_bound, size_t key_num,
                                                   std::pair <KEY_TYPE, PAYLOAD_TYPE> *result,
                                                   Param *param) {
    if(!result) {
        result = new std::pair <KEY_TYPE, PAYLOAD_TYPE>[key_num];
    }
    return sali.range_query_len(result, key_low_bound, key_num);
    //return 0;
}
#endif //GRE_SALI_H
