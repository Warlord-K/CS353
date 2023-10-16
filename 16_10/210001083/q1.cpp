#include <bits/stdc++.h>
using namespace std;

// Least Recenty Used Algorithm
int LRU(int frames, int pages[], int n){
    // Declatation of Variables
    int page_faults = 0;
    // s: Set Representing the Elements in the Frame
    unordered_set<int> s;
    // indexes: Map storing the last time a page was used
    unordered_map<int, int> indexes;

    // Start Iterating over the pages
    for(int i=0; i<n; i++){
        // If all frames are not utilized
        if(s.size() < frames){
            // If required page is not in frame
            if(s.find(pages[i]) == s.end()){
                // Add Page
                s.insert(pages[i]);
                // Page Fault
                page_faults++;
            }
            // Change the page's last occured index
            indexes[pages[i]] = i;
        }
        // If all frames are utilized
        else{
            // If required page is not in frame
            if(s.find(pages[i]) == s.end()){
                // Find Least Recently Used Page using th indexes
                int lru = INT_MAX, val;
                for(auto it=s.begin(); it!=s.end(); it++){
                    if(indexes[*it] < lru){
                        lru = indexes[*it];
                        val = *it;
                    }
                }
                // Remove least recently used page
                s.erase(val);
                // Add in new Page
                s.insert(pages[i]);
                // Page Fault
                page_faults++;
            }
            // Change the page's last occured index
            indexes[pages[i]] = i;
        }
    }
    return page_faults;
}



int main(){
    int pages[] = {1,2,3,4,2,1,5,3};
    cout << LRU(3, pages, 8) << endl;
    return 0;
}