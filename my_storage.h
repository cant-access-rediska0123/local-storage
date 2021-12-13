#ifndef LOCAL_STORAGE_MY_STORAGE_H
#define LOCAL_STORAGE_MY_STORAGE_H

#include <unordered_map>
#include <cstring>
#include <fstream>

typedef std::string Key;
typedef uint64_t Value;

const std::string DEFAULT_STORAGE_FILEPATH = "storage.txt";

class MyStorage {
public:
    explicit MyStorage(const std::string &storage_filepath = DEFAULT_STORAGE_FILEPATH);

    std::unordered_map<Key, Value>::const_iterator find(const Key &key) const;

    std::unordered_map<Key, Value>::const_iterator end() const;

    void set(const Key &key, const Value &value);

private:
    std::unordered_map<Key, Value> _st;
    std::ofstream _out;
    std::string _storage_filepath;
};

#endif //LOCAL_STORAGE_MY_STORAGE_H
