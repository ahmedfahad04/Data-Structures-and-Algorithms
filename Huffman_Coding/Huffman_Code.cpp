#include <bits/stdc++.h>
using namespace std;

map<char,long int> freq;
set <char> letters;
map<char, string> prefix_code;
string binary_message;
string characters;
int n;

struct node{
    char data;
    int frequencey;
    node *left, *right;
};

struct node *Q[100];

struct node *newnode(char info, long int freq, node *leftnode, node *rightnode){

    struct node * ptr = new node();

    ptr -> data = info;
    ptr -> frequencey = freq;
    ptr -> left = leftnode;
    ptr -> right = rightnode;

    return ptr;
}

void Min_heapify(node * ar[], int i){
    //int smallest = i , left , right;
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;


    if(left < n && ar[smallest]->frequencey > ar[left]->frequencey)
        smallest = left;

    if(right < n && ar[smallest]->frequencey > ar[right]->frequencey)
        smallest = right;


    if(smallest != i){
        swap(ar[smallest],ar[i]);
        Min_heapify(ar, smallest);
    }
}

void min_heap_insert(node * array[], node * z){
    int index,parent;

    index = ++n;
    parent = index/2;
  
    array[index] = z;
    
    while(index>1){
       parent = index/2;
        if(array[parent]->frequencey > array[index]->frequencey){
            swap(array[index/2],array[index]);
            index = parent;  
        }
        else return ;
    }
}

node * extract_min(node * arr[]){
    node *min;
    min = arr[1];
    arr[1] = arr[n];
    n--;

    Min_heapify(arr, 1);

    return min;
}

void prefix_code_generator(node * root, string code){

    if(root -> left == NULL && root -> right == NULL){
        
        cout << "  " << root->data << "        | CODE: " << code << endl;
        prefix_code[root->data] = code;
        return;
    }

    prefix_code_generator(root->left, code+"0");
    prefix_code_generator(root->right, code+"1");
}

node * huffman_code(){
    int i=0;

    for(auto x: letters){;
        node *temp = newnode(x,freq[x],NULL,NULL);
        min_heap_insert(Q,temp);              
    }

    while(n!=1){
    
        node *first = extract_min(Q);
        node *second = extract_min(Q);
       
        node *z = newnode('\0', first -> frequencey + second -> frequencey, first, second);

        min_heap_insert(Q, z);
    }

    cout << "Letters    |Prefix Code     \n";
    cout << "---------------------------------\n";
    prefix_code_generator(Q[1],"");

    return extract_min(Q);

}

string encode(string data){

    for(int i = 0; i<data.size();i++){
        binary_message += prefix_code[characters[i]];
    }

    return binary_message;
}

void decode(node * root, string data, int index){
        
    if(index == data.size()+1) return;
    
    if(root -> left == NULL && root -> right == NULL){
        cout << root->data ;
        root = Q[1];
    }

    if(data[index++] == '0') decode(root->left, data, index);
    else decode(root->right, data, index);
    
}

int main(){

    FILE *file;
    char x;
    file = fopen("data.txt", "r");
 
    while((x = fgetc(file))!=EOF){
        characters += x;
        freq[x]++;
        letters.insert(x);
    }

    node *ptr;
    ptr = huffman_code();
    
          
    cout << "\nEncoded Message: " << endl;
    cout << encode(characters) << endl;
    
    string message = "11101111001111110011100001010010111";
    
    cout << "\nDecoded Message: " << endl;
    decode(ptr,message, 0);
    puts("");

   
}
