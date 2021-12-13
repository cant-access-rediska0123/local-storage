#include "my_storage.h"
#include <iostream>

using namespace std;

MyStorage::MyStorage(const std::string &storage_filepath) {
    ifstream in(storage_filepath);
    Key key;
    Value value;
    while (in >> key >> value)
        _st[key] = value;
    _storage_filepath = storage_filepath;
}

std::unordered_map<Key, Value>::const_iterator MyStorage::find(const Key &key) const { return _st.find(key); }

std::unordered_map<Key, Value>::const_iterator MyStorage::end() const { return _st.end(); }

void MyStorage::set(const Key &key, const Value &value) {
    ofstream out;
    out.open(_storage_filepath, ios_base::app);
    _st[key] = value;
    out << key << " " << value << endl;
    out.close();
}