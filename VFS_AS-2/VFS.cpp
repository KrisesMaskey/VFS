#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<ctime>
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"
#include "Qu.h"
using namespace std;

//Function that prints the available commands
void command_help(){
	cout<<"\nList of available Commands:"<<endl
		<<"pwd                : Display the the path of current inode"<<endl
		<<"realpath           : Display the the full path of a given file"<<endl
		<<"ls                 : Display the children of the current inode"<<endl
		<<"mkdir              : Creates a folder under the current folder"<<endl
		<<"touch              : Creates a file under the current inode location"<<endl
		<<"cd                 : Change Directory"<<endl
		<<"find               : Returns the path of the file"<<endl	
		<<"mv                 : Moves a file located under the current inode location, to the specified folder path"<<endl
		<<"rm                 : Removes the specified folder or file"<<endl
		<<"size               : Returns the total size of the folder"<<endl
		<<"emptybin           : Empties the bin"<<endl
		<<"showbin            : Display the oldest inode of the bin"<<endl
		<<"recover            : Reinstates the oldest inode back from the bin to its original position in the tree"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}

//Class Inode
class Inode{
public:
	bool isFolder;
	string name;
	int size;
	string date;
	Inode* parent;

public:
	Vector<Inode*> v;
	Inode();
	Inode(int s, string n, bool f, Inode* node, string d);
};

//Constructor for root
Inode::Inode (){
	parent = NULL;
	time_t t = time(NULL);
	tm* tPtr = localtime(&t);
	isFolder = true;
	name = "/";
	size = 0;
	date = to_string(tPtr->tm_mday) +"-"+ to_string(tPtr->tm_mon + 1) +"-"+ to_string(tPtr->tm_year + 1900);
}
//Constructor with parameters
Inode::Inode (int s, string n, bool f, Inode* node, string d = string()){ 
	parent = node; 
	time_t t = time(NULL); 	 
	tm* tPtr = localtime(&t); 
	isFolder = f; name = n; 
	size = s; 
	string day, month; 
	if(stoi(to_string(tPtr->tm_mday))>-1 && stoi(to_string(tPtr->tm_mday))<10){day = "0" + to_string(tPtr->tm_mday);}
	if(stoi(to_string(tPtr->tm_mon + 1)) > -1 && stoi(to_string(tPtr->tm_mon + 1)) < 10){month = "0" + to_string(tPtr->tm_mon + 1);}
	if(d == ""){date = day +"-"+ month +"-"+ to_string((tPtr->tm_year + 1900)%100);}
	else{date = d;}
}
//======================================================================================================================================

//Vector vec stores all the ancestors of a current inode
Vector<Inode*> vec;

//Function split string seperates the path of a folder based on "/" and stores it in a vector
void split_string(string& s, Vector<string>& array){
	int pos = 0; string token; string delimiter = "/";
	if (s.substr(0, 1) == "/"){s.erase(0,1);}
	while ((pos = s.find(delimiter)) != string::npos) {
	    token = s.substr(0, pos);
	    array.push_back(token);
	    s.erase(0, pos + delimiter.length());
	}
	array.push_back(s);
}

//Function get_size returns the size of a folder/file by splitting the string
string get_size(string& str){
	return str.substr(str.find(" "), str.length());
}

//Function get_name returns the name of a folder/file by splitting the string
string get_name(string& str){
	return str.substr(0, str.find(" "));
}

//Function check_duplicate checks if a inode name is already present or not inside the children list of an inode
bool check_duplicate(Inode* node, Inode* val){
	for (int i = 0; i < node->v.size(); ++i){
		if(node->v.get(i)->name == val->name){
			return true;
	}}
	return false;
}

//Function load_vector loads the data fron file "VFS.dat" to a Vector
void load_vector(Vector<string>& path, Vector<string>& data){
	string temp, file = "VFS.dat", dt;
	ifstream fin(file); 
	if (fin.is_open()){
		while(getline(fin, temp)){
			dt = temp.substr(temp.find(",")+1);
			path.push_back(temp.substr(0, temp.find(",")));	
			data.push_back(dt);
		}}
	fin.close();
}

//checks if a string is aplhanumeric
bool check_name(string key){
	bool val = true;
	for (int count = 0;count<key.size();count++){
		int asc = key[count];
		if((asc>=48 && asc<=58)|| (asc>=65 && asc<=90) || (asc>=97 && asc<=122) || asc==46){	
			bool val = true;
		}
		else val = false;
	}
	return val;
}
//=========================================================================================================================================

//Tree Data Structure
class Tree{
private:
	Inode* root;	//points to the root inode
	Inode* position; //points to the current position
public:
	Tree();  											//Constructor
	~Tree(); 											//Destructor
	Inode* get_root(); 									//returns root pointer
	bool check_node(Inode* node, string& value);   		//Checks if a given node exists or not
	void set_Inode(Inode* path);				  		//Create a new Inode 
	void dislpay_Ipath();						 		//Displays Inode path when pwd is entered
	void display_Rpath(string path);					//Displays real path of a file
	void display_children();							//Displays all the children of current inode
	void find_path(string& path, Vector<Inode*>& v);	//returns a vector of inode* with matching input name
	void move(string& path, Inode* node, bool& flag);	//Moves a folder/file in another directory
	void remove(string& node, queue<Inode*>& q);		//Deletes a folder/file
	void size(Inode* node, int& path);					//returns the size of a folder/file
	void Traverse(string& name, Stack<Inode*>& stk);	//Traverses the tree 
	void display_fpath(Vector<Inode*>& v);				//Displays the path of a node if found
	void show_bin(queue<Inode*>& q);					//Displays first element of the Bin
	void remove_bin(queue<Inode*>& q);					//Empties the Bin
	void recover(queue<Inode*>& q, Stack<Inode*>& s);	//Recovers the first element inside the Bin if Path still exists
	void sort();										//Sorts the children according to size	
	void Dump_VFS(Inode* n);							//Dumps Data into the file after program terminates
	void Load_VFS(Vector<string>& v, Vector<string>& d);//Loads Data into the tree at the begining	
};

//Constructor
Tree::Tree(){
	Inode* node = new Inode();
	root = node;
	position = root;
}

//Destructor
Tree::~Tree(){
	delete root;
	delete position;
}

//Method returns root
Inode* Tree::get_root(){
	return root;
}

//Method returns if a node exists or not
bool Tree::check_node(Inode* node, string& value){
	if (node->name == value)
    	return true;
	for (int i =0; i<node->v.size();i++) {
		if (check_node(node->v.get(i), value))
		  return true;
	}
	return false;
}

//Method sets a new Inode
void Tree::set_Inode(Inode* node){
	if(position->isFolder == true && check_duplicate(position, node)==false)
		position->v.push_back(node);
	else
		cout<<"Error: Duplicate Name Found"<<endl;
}

//Method displays the path of a children
void Tree::dislpay_Ipath(){
	string path;
	if(position==root){
		cout<<"/"<<endl; return;
	}

	for(int i =1; i<vec.size();i++){
		if(vec.get(i)->isFolder == true)
			path += "/" + vec.get(i)->name;
	}
	cout<<path;
}

//Method displays path of a file
void Tree::display_Rpath(string name){
	for(int i = 0; i<position->v.size();i++){
		if(position->v.get(i)->name == name){
			dislpay_Ipath();
			cout<<"/" + name<<endl;
			return;
		}
	}
	cout<<"Error: File not found"<<endl;
}

//Method displays all the children of the current Inode
void Tree::display_children(){
	for (int i = 0; i < position->v.size(); ++i){
		string str = position->v.get(i)->date; str.erase(str.find_last_not_of(" \n\r\t")+1);
		if(position->v.get(i)->isFolder == true){
			cout<<"dir " + position->v.get(i)->name + " " + str + " " + to_string(position->v.get(i)->size) + "-bytes"<<endl;
		}else{
			cout<<"file " + position->v.get(i)->name + " " + str + " " + to_string(position->v.get(i)->size) + "-bytes"<<endl;
	}}
	cout<<endl;
}

//Method sorts the childrens according to Size (Bubble Sort)
void Tree::sort(){
	for (int i = 0; i < position->v.size(); ++i){
		for (int j = 0; j < position->v.size() - 1; ++j){
			if(position->v.get(j)->size < position->v.get(j + 1)->size){
				Inode* inode = position->v.get(j);
				position->v.insert(j, position->v.get(j + 1));
				position->v.insert(j + 1, inode);}
	}}
	cout<<endl;
}

//Method finds path of a given Inode
void Tree::find_path(string& path, Vector<Inode*>& found){
	Queue<Inode *> q;  
    q.push(root); 
    //Level Order Traversal
    while (!q.empty())
    {
        int n = q.size();
        while (n > 0)
        {
            Inode * p = q.front();
            q.pop();
            if(p->name == path)
            	found.push_back(p);
           	for (int i=0; i<p->v.size(); i++)
                q.push(p->v.get(i));
            n--;
    }}  
}

//Method displays path of a given Inode if found
void Tree::display_fpath(Vector<Inode*>& v){
	if(v.empty()){
		cout<<"Error: Directory/File not found"<<endl; return;
	}
	for (int i = 0; i < v.size(); ++i){	
		string path, temp;
		while(v.get(i) != root){
			temp = "";
			temp += "/" + v.get(i)->name;
			path.insert(0, temp);
			v.get(i) = v.get(i)->parent;
		}
		cout<<path<<endl;
	}
}

//Method returns the total size of a Directory
void Tree::size(Inode* node, int& total){
	//Postorder Traversal
  	for (int i=0; i<node->v.size(); i++) {
  		total += node->v.get(i)->size;
    	size(node->v.get(i), total);
  	}
}

//Method which Traverses the tree according to user input
void Tree::Traverse(string& name, Stack<Inode*>& prev)
{	bool flag = false;
	//Traverses to Parent Inode
    if (name == ".." && position!=root){
    	if(!prev.empty()){prev.pop();} prev.push(position);
    	position = position->parent;
    	vec.pop_back(); return;
    }else if (name == ""){	//Traverses to root
    	if(!prev.empty()){prev.pop();} prev.push(position);
    	int s = vec.size();
    	while(s>1){
    		if(vec.back()!=prev.top()){prev.push(vec.back());} vec.pop_back(); s--;
    	}
    	position = root; return;
    }else if (name == "-" && position==root){ //Traverses to previous directory from root
    	while(!prev.empty()){
    		vec.push_back(prev.top()); prev.pop();
    	}
    	position = vec.back(); prev.push(root); return;
    }else if (name == "-"){	//Traverses to previous directory from current position
    	Inode* temp_node = prev.top();
    	if(!prev.empty()){prev.pop();} prev.push(position);
    	if(position->parent == temp_node){
    		vec.pop_back();
    	}else if(temp_node->parent == position){
    		vec.push_back(temp_node);
    	}
    	position = temp_node; return;
    }else if (position == root){ //Update vec
    	int s = vec.size();
    	while(s>1){vec.pop_back(); s--;}
    }

    Stack<string> arr;
    Vector<string> array;
	split_string(name, array);  
	//Checl if given directory exists or not
	for (int i = array.size() -1; i > -1; i--){
		if(check_node(root, array.get(i))==false){ 
			cout<<"Error: Directory not found"<<endl;
			flag = true;
		}else if(array.get(i).find(".")!= string::npos){cout<<"Error: Directory cannot be changed to a File"<<endl; flag= true;}
		arr.push(array.get(i));
	}
	if(flag){return;}
	//Traversal if input directly points to a directory (eg: /Desktop/Assignment/DS)
    Queue<Inode*> q;  
    q.push(position); 
    while (!q.empty())
    {
        int n = q.size();	
        while (n > 0){
            Inode* p = q.front();
            q.pop();
            if(arr.size()>0 && p->name == arr.top() && p->isFolder == true && position->name!=arr.top()){
            	if(!prev.empty()){prev.pop();} prev.push(position);
            	vec.push_back(p); 
            	arr.pop();
            }else if (arr.size()>0 && p->name == arr.top() && p->isFolder == false){
            	cout<<"Error: Directory cannot be changed to a File"<<endl;}
            
            for (int i=0; i<p->v.size(); i++)
                q.push(p->v.get(i));
            n--;
        }}
    //Update Position
    position = vec.back();
}

//Method which moves a folder/file to another directory
void Tree::move(string& path, Inode* node, bool& flag){
	string str =  path.substr(path.find(" ") + 1);
	for (int i = 0; i < position->v.size(); ++i){
		if(position->v.get(i)->name == str){
			position->v.get(i)->v.push_back(node); flag=true;
			node->parent = position->v.get(i); return;
		}
	}
	flag = false;
	cout<<"Error: Directory not found"<<endl;
}

//Method which removes a folder/file 
void Tree::remove(string& key, queue<Inode*>& q){
	for (int i = 0; i < position->v.size(); ++i){
		if(position->v.get(i)->name == key){
			Inode* temp = new Inode();
			temp = position->v.get(i);
			if(!q.isFull())
				q.push(temp);
			position->v.erase(i); 
			return;
	}
}cout<<"Error: Directory/File not found"<<endl;}

//Method shows the first element of the BIN
void Tree::show_bin(queue<Inode*>& q){
	if(q.empty()){
		cout<<"The bin is empty"<<endl; return;
	}
	cout<<"Next Element to remove: ";
	Inode* node = q.Front();
	string path, temp;
	while(node != root){ 
		temp = "";
		temp += node->name + "/";
		path.insert(0, temp);
		node = node->parent;
	}
	cout<<"/" + path + " (" + to_string(q.Front()->size) + " bytes, " + q.Front()->date +  ")"<<endl;; 
}

//Method empties the BIN
void Tree::remove_bin(queue<Inode*>& q){
	while(!q.empty()){
		q.pop();
	}
}

//Method reinstates the deleted inode if Path exists
void Tree::recover(queue<Inode*>& q, Stack<Inode*>& stk){
	bool flag = false;
	if(q.empty()){
		cout<<"The bin is empty"<<endl; flag==true; 
		return;
	}
	
	if(flag == false){
		Inode* node = q.Front(); if(node!=root){node = node->parent;}
		string path = string(), temp;
		while(node != root){ 
			if(check_node(root, node->name) == false){
				cout<<"Error: The inode couldn't be recovered (Path not found)"<<endl; return;
			}
			temp = string();
			temp += "/" + node->name;
			path.insert(0, temp);
			node = node->parent;
		}
		Inode* curr = position;
		position = root;
		Traverse(path, stk);
		set_Inode(q.Front());
		position = curr;
		q.pop();
	}
}

//Method loads data from the file to the tree
void Tree::Load_VFS(Vector<string>& path, Vector<string>& data){
	bool type_flag = false;
	for (int i = 0; i < data.size(); ++i){
		if(i==0){
			root->date = data.get(0).substr(data.get(0).find(",") + 1); continue;
		}
		position = root;
		vec.push_back(root);
		string fpath = path.get(i);
		Vector<string> temp;
		split_string(fpath, temp);
		for(int j=0; j<temp.size(); j++){
			string val = temp.get(j);
			if(check_node(position, val)==false){
				int file_size = stoi(data.get(i).substr(0 , data.get(i).find(","))); string temp_date = data.get(i).substr(data.get(i).find(",") + 1);
				temp_date.erase(temp_date.find_last_not_of(" \n\r\t")+1);
				if(val.find(".")!=string::npos){type_flag = false;}else{type_flag = true;}
				Inode* node = new Inode(file_size, val, type_flag, vec.back(), temp_date); 
				set_Inode(node);   
			}else{
				Vector<Inode*> inode; find_path(val, inode);
				position = inode.back(); vec.push_back(position);
			}
		}
		while(!vec.empty()){
			vec.pop_back();
		}
	}
	position = root;
}

//Method dumps data from the Tree to the file
void Tree::Dump_VFS(Inode* pos){
	Inode* node = pos; 
	string path = "", temp, spec = string(); if(node==root){path="/";}
	spec = "," + to_string(node->size) + "," + node->date; 
	while(node != root){ 
		temp = string();
		temp += "/" + node->name; 
		path.insert(0, temp);
		node = node->parent;
	}
	ofstream fout;
	fout.open("VFS.dat", ios::app);
	if(fout.is_open()){
		fout<<path+spec<<endl;}
	fout.close();
	for(int i= 0; i< pos->v.size(); i++){
		Dump_VFS(pos->v.get(i));
	}
}
//================================================================================================================================

//Main Function
int main(){
	Vector<string> file_path; Vector<string> file_data;
	load_vector(file_path, file_data);
	string input, command, key;
	//Bin initialized
	queue<Inode*> BIN;
	//stack initialized for cd-
	Stack<Inode*> prev;
	Tree tree;
	
	//Load Data
	tree.Load_VFS(file_path, file_data);
	//Root pushed
	vec.push_back(tree.get_root());

	command_help();
	//Loop until exit is entered
	while(input!="exit"){
		cout<<">";
		getline(cin,input);
		command = input.substr(0,input.find(" "));
		key = input.substr(input.find(" ")+1);

		if (command == "pwd"){
			tree.dislpay_Ipath();
			cout<<endl;
		}else if (command == "realpath"){
			tree.display_Rpath(key);
		}else if (command == "ls"){
			if(key == "sort"){
				tree.sort(); 
			}
			tree.display_children();
		}else if (command == "mkdir"){
			Inode* node = new Inode(10, key, true, vec.back(), "");
			tree.set_Inode(node);
		}else if (command == "touch"){
			try{
				stoi(get_size(key));
			}catch(exception e){
				cout<<"Please enter valid size for the file"<<endl; continue;
			}
			if(check_name(get_name(key))==true){
				Inode* node = new Inode(stoi(get_size(key)), get_name(key), false, vec.back());
				tree.set_Inode(node);
			}else{
				cout<<"File name is not alphanumeric"<<endl;
			}
		}else if (command == "cd"){
			tree.Traverse(key, prev);
		}else if (command == "find"){
			Vector<Inode*> list;
			tree.find_path(key, list);
			tree.display_fpath(list);
		}else if (command == "size"){

			Vector<Inode*> v; int t = 0; Vector<string> path; bool flag = true;
			if(key!="/"){
				split_string(key, path);
				for (int i = path.size() -1; i > -1; i--){
					if(tree.check_node(tree.get_root(), path.get(i))==false){
						cout<<"Error: Directory not found"<<endl; flag=false; break;}}}
			else{path.push_back("/");}
			if(flag==true){
				string p = path.back();
				tree.find_path(p, v);
				t = v.back()->size;
				tree.size(v.back(), t);
				cout<<to_string(t) + " bytes"<<endl;}

		}else if (command == "mv"){
			Vector<Inode*> v; bool flag;
			string temp =  key.substr(0, key.find(" "));
			tree.find_path(temp, v);
			tree.move(key, v.back(), flag);
			if(flag==true){
				tree.remove(temp, BIN);
			}
		}else if (command == "rm"){
			if(key=="/"){cout<<"Root node cannot be deleted"<<endl; continue;}
			tree.remove(key, BIN);
		}else if (command == "showbin"){
			tree.show_bin(BIN);
		}else if (command == "emptybin"){
			tree.remove_bin(BIN);
		}else if (command == "recover"){
			tree.recover(BIN, prev);
		}else if (command == "help"){
			command_help();
		}else{
			if(key!="exit"){cout<<"Invalid Command"<<endl;}
		}
	}
	//Data dumped
	ofstream f;
	f.open("VFS.dat", ios::trunc); f.close();
	tree.Dump_VFS(tree.get_root());
}