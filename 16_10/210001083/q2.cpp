#include <bits/stdc++.h>
using namespace std;

//Farthest in Future Algorithm
int FIF(int frames, int pages[], int n){
    // Declatation of Variables
    int page_faults = 0;
    // s: Set Representing the Elements in the Frame
    unordered_set<int> s;
    // indexes: Map storing the last time a page was used

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
        }
        // If all frames are utilized
        else{
            // If required page is not in frame
            if(s.find(pages[i]) == s.end()){
                // Find Page Occuring Farthest in the Future
                unordered_map<int, int> indexes;
                // For Each Page in Frame
                for(auto it=s.begin(); it!=s.end(); it++){
                    // Assume Page Never Occurs in the Future
                    indexes[*it] = INT_MAX;
                    // Search for Page in Future
                    for(int j = i + 1; j < n; j++){
                        // Found Page in Future
                        if(*it == pages[j]){
                            indexes[*it] = j;
                            break;
                        }
                    }
                }
                // Find Page Farthest in Future
                int fif = INT_MIN, val;
                for(auto it=s.begin(); it!=s.end(); it++){
                    if(indexes[*it] > fif){
                        fif = indexes[*it];
                        val = *it;
                    }
                }
                // Remove farthest in future page
                s.erase(val);
                // Add in new Page
                s.insert(pages[i]);
                // Page Fault
                page_faults++;
            }
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
    FIF(f, pages, n);
    return 0;
}