#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

void run_bf_loop(string &whole_loop,int &start,char **head_ptr){
	string loop = "";
	int counter=0;
	char ch;
	
	while((ch = whole_loop[start]) != ']' or counter != 0){
		if(ch == '['){counter++;}
		else if(ch == ']'){counter--;}
		loop += ch;
		start++;
	}
	
	while(**head_ptr){
		for(int i=0;loop[i] != '\0';i++){
			if(loop[i] == '>'){(*head_ptr)++;}
			else if(loop[i] == '<'){(*head_ptr)--;}
			else if(loop[i] == '+'){(**head_ptr)++;}
			else if(loop[i] == '-'){(**head_ptr)--;}
			else if(loop[i] == '.'){putchar(**head_ptr);}
			else if(loop[i] == ','){**head_ptr = getchar();cin.ignore(100,'\n');}
			else if(loop[i] == '['){i++;run_bf_loop(loop,i,head_ptr);}
		}
	}
	return;
}

void run_bf_loop(ifstream &ifile,char **head_ptr){
	string loop = "";
	int counter=0;
	char ch;
	
	while((ch = ifile.get()) != ']' or counter != 0){
		if(ch == '['){counter++;}
		else if(ch == ']'){counter--;}
		loop += ch;
	}
	
	while(**head_ptr){
		for(int i=0;loop[i] != '\0';i++){
			if(loop[i] == '>'){(*head_ptr)++;}
			else if(loop[i] == '<'){(*head_ptr)--;}
			else if(loop[i] == '+'){(**head_ptr)++;}
			else if(loop[i] == '-'){(**head_ptr)--;}
			else if(loop[i] == '.'){putchar(**head_ptr);}
			else if(loop[i] == ','){**head_ptr = getchar();cin.ignore(100,'\n');}
			else if(loop[i] == '['){i++;run_bf_loop(loop,i,head_ptr);}
		}
	}
	return;
}

int main(int argc,char **argv){
	char *arr = (char *)calloc(30000,sizeof(char));
	char *head = arr;
	
	if(argc == 1){
		system("cls");
		string input = "";
		
		cout << "\n>>> ";
		getline(cin,input);
		
		while(input != "exit"){
			for(int i=0;input[i] != '\0';i++){
				if(input[i] == '>'){(head)++;}
				else if(input[i] == '<'){(head)--;}
				else if(input[i] == '+'){(*head)++;}
				else if(input[i] == '-'){(*head)--;}
				else if(input[i] == '.'){putchar(*head);}
				else if(input[i] == ','){*head = getchar();cin.ignore(100,'\n');}
				else if(input[i] == '['){i++;run_bf_loop(input,i,&head);}
			}
			cout << "\n>>> ";
			getline(cin,input);
		}
		system("cls");
		return 0;
	}
	
	
	string input_file = argv[1];
	
	ifstream ifile(input_file);
	if(!ifile.is_open()){ifile.close(); cout << "ERROR: " << input_file << ": No such file exists" << endl; return 0;}
	
	char ch = 0;
	
	while((ch = ifile.get()) != -1){
		if(ch == '>'){head++;}
		else if(ch == '<'){head--;}
		else if(ch == '+'){(*head)++;}
		else if(ch == '-'){(*head)--;}
		else if(ch == '.'){putchar(*head);}
		else if(ch == ','){*head = getchar();cin.ignore(100,'\n');}
		else if(ch == '['){run_bf_loop(ifile,&head);}
	}
	
	free(arr);
	return 0;
}