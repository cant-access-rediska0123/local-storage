#ifndef LOCAL_STORAGE_MY_STORAGE_H
#define LOCAL_STORAGE_MY_STORAGE_H

#include <unordered_map>
#include <cstring>
#include <pthread.h>
#include <fstream>

typedef std::string Key;
typedef uint64_t Value;

const std::string DEFAULT_STORAGE_FILEPATH1 = "storage1.txt";
const std::string DEFAULT_STORAGE_FILEPATH2 = "storage2.txt";

class MyStorage {
public:
    explicit MyStorage();

    std::unordered_map<Key, Value>::const_iterator find(const Key &key) const;

    std::unordered_map<Key, Value>::const_iterator end() const;

    void set(const Key &key, const Value &value);

private:
    std::unordered_map<Key, Value> _st;
};

#endif //LOCAL_STORAGE_MY_STORAGE_H
