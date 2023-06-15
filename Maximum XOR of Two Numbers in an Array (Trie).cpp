//https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/description/

class Solution {
public:
    
    struct Trie{

        struct Trie* next[2];
        
        Trie(){
            this->next[0]=NULL;
            this->next[1]=NULL;
        }
    };
    
    string bin(int n){
        
        string s;
        
        while(n>0){
            
            if(n%2==0)
                s+='0';
            else
                s+='1';
            n/=2;
        }
        
        while(s.size()<32)
            s+='0';
        
        reverse(s.begin(),s.end());
        
        return s;
    }
    
    int findMaximumXOR(vector<int>& nums) {
        
        Trie* node = new Trie;
        int n=nums.size(),i,j;
        
        for(i=0;i<n;i++){
            
            string binary=bin(nums[i]);
            Trie* temp = node;
            
            for(j=0;j<binary.size();j++){
                
                int ind=binary[j]-'0';
                if(temp->next[ind]==NULL){
                    
                    temp->next[ind]=new Trie;
                }
                temp=temp->next[ind];
            }
        }
        
        int ans=0;
        
        for(i=0;i<n;i++){
            
            string binary=bin(nums[i]);
            Trie* temp = node;
            int curr=0;
            
            for(j=0;j<binary.size();j++){
                
                int ind=binary[j]-'0';
                if(temp->next[(ind^1)]==NULL){
                    
                    if(temp!=NULL)
                        temp=temp->next[ind];
                }
                else{
                    
                    curr+=(1<<(31-j));
                    if(temp!=NULL)
                        temp=temp->next[(ind^1)];
                }
            }
            
            ans=max(ans,curr);
        }
        
        return ans;
    }
};;