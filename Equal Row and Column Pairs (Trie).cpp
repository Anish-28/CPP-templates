// https://leetcode.com/problems/equal-row-and-column-pairs/description/

class Trie{
    int cnt;
    unordered_map<int,Trie*> child;

    public:

    Trie(){
        cnt=1;
    }

    void add(vector<int> &v, Trie* node){
        int n=v.size(),i;

        for(i=0;i<n;i++){
            if(node->child[v[i]]==NULL)
                node->child[v[i]] = new Trie;
            else
                node->child[v[i]]->cnt++;
            node = node->child[v[i]];
        }
    }

    int occurances(vector<int> &v, Trie* node){
        int n=v.size(),i;

        for(i=0;i<n;i++){
            if(node->child[v[i]]==NULL)
                return 0;
            node = node->child[v[i]];
        }

        return node->cnt;
    }
};

class Solution {

public:

    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size(),i,j,k,ans=0;
        Trie* node = new Trie,*root;
        root = node;

        for(i=0;i<n;i++){
            node->add(grid[i],node);
        }

        for(i=0;i<n;i++){
            vector<int> temp;
            for(j=0;j<n;j++){
                temp.push_back(grid[j][i]);
            }

            ans+=node->occurances(temp,node);
        }

        return ans;
    }
};