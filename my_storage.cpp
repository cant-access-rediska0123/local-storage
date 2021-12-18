#include "my_storage.h"
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <chrono>
#include <thread>

using namespace std;

pthread_mutex_t updater_lock = PTHREAD_MUTEX_INITIALIZER;

std::string current_storage_filepath;

void read_from_file(unordered_map<Key, Value> &st, const string &storage_filepath) {
    ifstream in(storage_filepath);
    Key key;
    Value value;
    while (in >> key >> value)
        st[key] = value;
}

void update() {
    cout << "Update map" << endl;
    unordered_map<Key, Value> st;
    read_from_file(st, DEFAULT_STORAGE_FILEPATH1);
    read_from_file(st, DEFAULT_STORAGE_FILEPATH2);
    ofstream out;
    string new_storage_filepath;
    if (current_storage_filepath == DEFAULT_STORAGE_FILEPATH1)
        new_storage_filepath = DEFAULT_STORAGE_FILEPATH2;
    else
        new_storage_filepath = DEFAULT_STORAGE_FILEPATH1;
    out.open(new_storage_filepath);
    for (const pair<Key, Value> p: st)
        out << p.first << " " << p.second << endl;
    out.close();
    string old_storage_filepath = current_storage_filepath;
    current_storage_filepath = new_storage_filepath;

    // clear old file
    ofstream old_out;
    old_out.open(old_storage_filepath, ofstream::out | ofstream::trunc);
    old_out.close();
}

void updater_thread_routine() {
    chrono::milliseconds sleep_time(10000);
    while (true) {
        assert(!pthread_mutex_lock(&loupdater_lockck));
        update();
        assert(!pthread_mutex_unlock(&updater_lock));
        this_thread::sleep_for(sleep_time);
    }
}

MyStorage::MyStorage() {
    read_from_file(_st, DEFAULT_STORAGE_FILEPATH1);
    read_from_file(_st, DEFAULT_STORAGE_FILEPATH2);
    current_storage_filepath = DEFAULT_STORAGE_FILEPATH2;
    update();
    thread thr(updater_thread_routine);
    thr.detach();
}

std::unordered_map<Key, Value>::const_iterator MyStorage::find(const Key &key) const { return _st.find(key); }

std::unordered_map<Key, Value>::const_iterator MyStorage::end() const { return _st.end(); }

void MyStorage::set(const Key &key, const Value &value) {
    assert(!pthread_mutex_lock(&loupdater_lockck));
    ofstream out;
    out.open(current_storage_filepath, ios_base::app);
    _st[key] = value;
    out << key << " " << value << endl;
    out.close();
    assert(!pthread_mutex_unlock(&updater_lock));
}