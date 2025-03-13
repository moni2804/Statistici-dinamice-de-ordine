/*
 * Complexitatea lui create_bst este de O(n), deoarece construirea arborelui echilibrat are nevoie doar de o trecere pentru a crea nodurile.
 * Complexitatea lui os_select este de O(lg n) pentru un arbore echilibrat.
 * Complexitatea lui os_delete este de O(lg n) pentru un arbore echilibrat, dar poate ajunge la O(n) in cel mai rau caz, care este arborele dezechilibrat.
 *
 */
#include <iostream>
#include "Profiler.h"
using namespace std;
Profiler profiler;
//suficient sa fie crescator, nu trebuie sa fie consecutiv

struct BST{
    int key;
    int size;
    BST* left;
    BST *right;
};

//BST *root; //radacina arborelui
BST *create_node(int key,int size){ //initializarea crearea si nodului
    BST* node=new BST;
    node->key=key;
    node->size=size;
    node->left= nullptr;
    node->right= nullptr;

    return node;
}

BST* create_bst(int left,int right,int a[],Operation &op){ //BUILD_TREE(n)
    op.count();
    if(right<left)
        return nullptr;

    op.count();
    int mid=(left+right)/2;

    op.count();
    BST* node=create_node(a[mid],right-left+1);

    op.count();
    node->left=create_bst(left,mid-1,a,op);

    op.count();
    node->right= create_bst(mid+1,right,a,op);

    return node;
}

void pretty_print(BST *node,int tabs){ ///afisez arborele culcat spre stanga, nodul si in paranteze rangul lui
    if(node){
        pretty_print(node->right,tabs+5);
        for(int i=0;i<tabs;i++){
            cout<<" ";
        }
        cout<<node->key<<"("<<node->size<<")"<<endl;
        pretty_print(node->left,tabs+5);
    }
}

BST* os_select(BST* node,int i,Operation &op){
    op.count();
    if(node == nullptr){
        ///cout<<"Nod null sau nu este in arbore "<<endl;
        return nullptr;
    }

    int r;

    if (node->left) {
        r = node->left->size + 1;
    } else{
        r=1;
    }
    op.count(2); //comparatie si atribuire

    op.count();
    if(i+1==r){ //indexarea incepe de la 0 si numararea nodurilor de la 1
        return node;
    } else if(i+1<r){
        op.count();
        return os_select(node->left,i,op);
    }else{
        return os_select(node->right,i-r,op);
    }
}

BST* succesor(BST* node){
    while(node && node->left){
        node=node->left;
    }
    return node;
}

BST* os_delete(BST *&node,int i,Operation &op){
    op.count();
    if(!node){
        ///cout<<"Nod null sau nu se afla in arbore"<<endl;
        return nullptr;
    }

    int rank;
    op.count(2);
    if(node->left){
        rank=node->left->size + 1;
    }else{
        rank=1;
    }

    if (i + 1 == rank) {
        op.count();
        if (!node->left) { //daca nu are copii stanga returneaza copilul din dreapta si daca acesta este null, il sterge ca pe un nod frunza
            BST* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) { //daca are copil stanga si nu are copil dreapta
            BST* temp = node->left;
            delete node;
            return temp;
        }

        //daca are ambi copii il inlocuim cu succesorul
        BST* succ = succesor(node->right);
        node->key = succ->key;
        op.count();
        node->right = os_delete(node->right, 0,op);  // Ștergerea succesorului.
    } else if (i + 1 < rank) { //daca n-am gasit nodul
        node->left = os_delete(node->left, i,op);
    } else {
        node->right = os_delete(node->right, i - rank,op);
    }

    //Actualizam size-ul nodurilor
    op.count();
    node->size=1;
    op.count();
    if(node->left){
        node->size+=node->left->size;
    }
    op.count();
    if(node->right){
        node->size+=node->right->size;
    }

    return node;

}
void demo(){
    int a[]={1,2,3,4,5,6,7,8,9,10,11};
    int n=sizeof(a)/sizeof(a[0]);
    Operation op=profiler.createOperation("Operatii demo",n);

    ///1
    cout<<"Afisarea arborelui initial"<<endl;

    BST* root= create_bst(0,n-1,a,op); //crearea arborelui

    pretty_print(root,0); //afisarea arborelui

    cout<<"--------------------------------"<<endl;
    cout<<"Cautarile:"<<endl;

    ///2
    pretty_print(root,0);

    BST* node=os_select(root,6,op); //a 6-a cheie
    if(node){
        cout<<node->key<<endl;
    } else{
        cout<<"Nodul nu se afla in arbore"<<endl;
    }

    node=os_select(root,10,op);
    if(node){
        cout<<node->key<<endl;
    } else{
        cout<<"Nodul nu se afla in arbore"<<endl;
    }

    node= os_select(root,12,op);
    if(node){
        cout<<node->key<<endl;
    } else{
        cout<<"Nodul nu se afla in arbore"<<endl;
    }

    cout<<"--------------------------------"<<endl;
    cout<<"Arborele initial:"<<endl;

    ///3

    pretty_print(root,0);

    cout<<"--------------------------------"<<endl;

    node=os_select(root,8,op);
    if(node){
        cout<<node->key<<endl;
        os_delete(root,8,op);
    } else{
        cout<<"Nodul nu se afla in arbore"<<endl;
    }
    pretty_print(root,0);

    cout<<"--------------------------------"<<endl<<endl;

    node=os_select(root,6,op);
    if(node){
        cout<<node->key<<endl;
        os_delete(root,6,op);
    } else{
        cout<<"Nodul nu se afla in arbore"<<endl;
    }
    pretty_print(root,0);

    cout<<"--------------------------------"<<endl<<endl;

    node=os_select(root,12,op);
    if(node){
        cout<<node->key<<endl;
        os_delete(root,12,op);
    } else{
        cout<<"Nodul nu se afla in arbore"<<endl;
    }
    pretty_print(root,0);

}
void perf(){
    for(int n=100;n<=10000;n+=100){
        for(int test=0;test<5;test++){
            int a[n];
            FillRandomArray(a,n,1,n*10000,true,ASCENDING);
            Operation op_create=profiler.createOperation("Operatii_create",n);
            Operation op_select=profiler.createOperation("Operatii_select",n);
            Operation op_delete=profiler.createOperation("Operatii_delete",n);

            BST* root= create_bst(0,n-1,a,op_create);

            for(int i=0;i<n;i++){
                int index=rand()%(n-i);

                BST* node=os_select(root,index,op_select);
                root= os_delete(root,index,op_delete);
            }
        }
    }

    profiler.divideValues("Operatii_create",5);
    profiler.divideValues("Operatii_select",5);
    profiler.divideValues("Operatii_delete",5);
    profiler.createGroup("Operatii totale","Operatii_create","Operatii_select","Operatii_delete");

    profiler.showReport();
}


int main() {
    demo();
    //perf();
    return 0;
}
