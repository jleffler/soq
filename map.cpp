#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    map<string, int> zip_map;
    string text;
    while (cin >> text)
    {
        if (text == "zip:")
        {
            string zip;
            if (cin >> zip)
                zip_map[zip]++;
        }
    }
    //sort(zip_map.begin(), zip_map.end());
    //for (auto it = zip_map.begin(); it != zip_map.end(); ++it)
    //    cout << *it.first() << ": " << zip_map[*it.first()] << "\n";
    return 0;
}
