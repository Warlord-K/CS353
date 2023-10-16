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
    cout << "Pages Left: ";
    for(auto it=s.begin(); it!=s.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    cout << "Page Faults: "<< page_faults << endl;
    return page_faults;
}



int main(){
    int n, f;
    cout << "Enter Number of Frames: \n";
    cin >> f;
    cout << "Enter Number of Pages: \n";
    cin >> n;
    int pages[n];
    cout << "Enter Page Reference Numbers space seperated: \n";
    for(int i = 0; i < n; i++){
        cin >> pages[i];
    }
    LRU(f, pages, n);
    return 0;
}