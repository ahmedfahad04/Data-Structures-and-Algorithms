#include <bits/stdc++.h>
using namespace std;

//global variables
map<char,long int> freq;
set <char> letters;
map<char, string> prefix_code;
string encoded_message;
string decoded_message;
string characters;
int n, bits , total=0, new_bits=0, new_total=0;

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

    
        if(root->data == ' '){
            cout << " " << "Space" << "     | " << freq[root->data]  << "           | " << code <<endl;
            prefix_code[root->data] = code;
            new_bits += freq[root->data]*(code.size());
        }

        else if(root->data == '\n'){
            cout << " " << "New Line" << "  | " << freq[root->data]  << "            | " << code <<endl;
            prefix_code[root->data] = code;
            new_bits += freq[root->data]*(code.size());
        }

        else{
            cout << " " << root->data << "         | " << freq[root->data]  << "            | " << code <<endl;
            prefix_code[root->data] = code;
            new_bits += freq[root->data]*(code.size());
        }
        
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

    cout << "\nLetters    | Frequency    | Prefix Code\n";
    cout << "-----------------------------------------------\n";
    prefix_code_generator(Q[1],"");

    return extract_min(Q);

}

void encode(string data){

    for(int i = 0; i<data.size();i++){
        encoded_message += prefix_code[characters[i]];
    }

}

void decode(node * root, string data, int index){

    if(index == data.size()+1) return;

    if(root -> left == NULL && root -> right == NULL){
        decoded_message += root->data;
        //cout << root->data ;
        root = Q[1];
    }

    if(data[index++] == '0') decode(root->left, data, index);
    else decode(root->right, data, index);

}

void size_comparasion(){

    // Before huffman coding
    bits = ceil(log2(characters.size()));
    total = bits*characters.size();
    cout << "Before Compression: " << total << " bits" <<endl;

    // After encoding
    new_total = new_bits*characters.size();
    cout << "After Compression: " << new_bits << " bits" << endl;
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

    //string input_message; //enter your message to encode it
    encode(characters);
    cout << "\nEncoded Message: " << endl;
    cout << encoded_message << endl;

    //string message; //enter binary representation of your message to decode it
    decode(ptr,encoded_message, 0);
    cout << "\nDecoded Message: " << endl;
    cout << decoded_message << endl;

    cout << "\nComparison between data Size: " << endl;
    size_comparasion();
    puts("");


}
