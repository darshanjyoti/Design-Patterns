/******************************************************************************
Composite design pattern:
Composite pattern lets you treat individual object and group of objects
in the same way.
It is useful when 
- you have tree like structuree
- you want to perform same operation on single object (leaf) as well as group of objects (composite)
examples:
- files and folder
- UI: buttons and panel
- Company hierarchy- employee and manager etc

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;


//Interface
class FileSystem{
public:
    virtual string getName() = 0;
    virtual int getSize() = 0;
    virtual void ls() = 0;
    virtual ~FileSystem() = default;
};

//Leaf - File 
class File : public FileSystem{
private:
    string _name;
    int _size;
public:
    File(const string& name, int size) : _name(name), _size(size){}
    
    string getName() override{
        return _name;
    }
    
    int getSize() override{
        return _size;
    }
    
    void ls() override{
        cout<<getName()<<endl;
    }
};

//Composite - Folder
class Folder : public FileSystem{
private:
    string _name;
    vector<FileSystem*> child;
public:
    Folder(const string& name) : _name(name){}
    
    ~Folder(){
        for(auto& c : child){
            delete c;
        }
    }
    
    void add(FileSystem* item){
        child.push_back(item);
    }
    
    void ls() override{
         cout<<_name<<"-"<<endl;;
         
        for(auto& c: child){
               c->ls();
            }
    }
    
    string getName() override{
        return _name;
    }
    
    int getSize() override{
        int total = 0;
        for(auto& c: child){
            total += c->getSize();
        }
        return total;
    }
    
};

int main()
{
    Folder* root = new Folder("root");
    root->ls();
    cout<<root->getName()<<endl;
    cout<<root->getSize()<<endl;
    File* f1 = new File("file1", 5);
    f1->ls();
    cout<<f1->getSize()<<endl;
    //adding Files 
    root->add(f1);
    root->add(new File("file2", 10));
    root->ls();
    cout<<root->getSize()<<endl;
    
   Folder* img = new Folder("ImageFolder");
   img->add(new File("images", 10));
   img->add(new File("images2", 20));
   root->add(img);
   cout<<"------------"<<endl;
   root->ls();
   cout<<root->getSize()<<endl;
    
    

    return 0;
}
