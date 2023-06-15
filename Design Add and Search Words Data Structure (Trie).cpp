//https://leetcode.com/problems/design-add-and-search-words-data-structure/description/

class WordDictionary {
public:
    
    struct Trie{
        
        Trie* child[26];
        bool isPossible;
        
        Trie(){
            
            isPossible=false;
            for(int i=0;i<26;i++)
                child[i]=NULL;
        }
    };
    
    Trie* root;
    
    WordDictionary() {
        
        root = new Trie;
    }
    
    void addWord(string word) {
        
        int n=word.size(),i;
        Trie* curr = root;
        
        for(i=0;i<n;i++){
            
            int ind=word[i]-'a';
            
            if(curr->child[ind]==NULL)
                curr->child[ind] = new Trie;
            
            curr = curr->child[ind];
        }
        
        curr->isPossible=true;
    }
    
    bool fun(Trie* node,int pos,string word){
        
        if(pos==word.size()){
            
            if(node->isPossible)
                return true;
            
            return false;
        }
        
        if(word[pos]!='.'){
            
            int ind=word[pos]-'a';
            
            if(node->child[ind]==NULL)
                return false;
            
            return fun(node->child[ind],pos+1,word);
        }
        else{
            
            int ind=word[pos]-'a';
            bool ans=false;
            
            for(int i=0;i<26;i++){
                
                if(node->child[i]!=NULL)
                    ans|=fun(node->child[i],pos+1,word);    
            }
            
            return ans;
        }
    }
    
    bool search(string word) {
        
        int n=word.size(),i;
        Trie* curr = root;
        
        return fun(curr,0,word);
    }
};