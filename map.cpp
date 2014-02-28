#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef pair<string, int> zip_cnt;

static bool cmp_second(const zip_cnt &v1, const zip_cnt &v2)
{
    return v1.second <  v2.second ||
          (v1.second == v2.second && v1.first < v2.first);
}

int main()
{
    map<string, int> zip_map;

    string text;
    while (cin >> text)
    {
        //cout << "Got: " << text << "\n";
        if (text == "zip:")
        {
            string zip;
            if (cin >> zip)
            {
                //cout << "Zip: " << zip << "\n";
                zip_map[zip]++;
            }
        }
    }

    // NB: Sorted in key order
    cout << "Raw:\n";
    for (auto it = zip_map.begin(); it != zip_map.end(); ++it)
        cout << it->first << ": " << zip_map[it->first] << "\n";

    // To sort: convert to vector of pairs, sort vector, print data.
    vector<zip_cnt> zip_vec;
    zip_vec.reserve(zip_map.size());
    for (auto it = zip_map.begin(); it != zip_map.end(); ++it)
        zip_vec.push_back(*it);

    sort(zip_vec.begin(), zip_vec.end(), cmp_second);
    cout << "Sorted (increasing count):\n";
    for (auto it = zip_vec.begin(); it != zip_vec.end(); ++it)
        cout << it->first << ": " << it->second << "\n";

    sort(zip_vec.begin(), zip_vec.end());
    cout << "Sorted (increasing zip code):\n";
    for (auto it = zip_vec.begin(); it != zip_vec.end(); ++it)
        cout << it->first << ": " << it->second << "\n";

    return 0;
}
