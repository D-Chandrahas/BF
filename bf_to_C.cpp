#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argc,char **argv){
	bool compile = false;
	string input_file = "";
	string output_file = "a";
	
	for(int i=1;i<argc;i++){
		if(*(argv[i]) == '-'){
			if((*(argv[i]+1) == 'c') || (*(argv[i]+1) == 'C')){
				compile = true;
			}
			else if ((*(argv[i]+1) == 'o') || (*(argv[i]+1) == 'O')){
				output_file =  argv[i+1];
				i++;
			}
		}
		else{
			input_file = argv[i];
		}
	}
	
	ifstream ifile(input_file);
	if(!ifile.is_open()){ifile.close(); cout << "ERROR: " << input_file << ": No such file exists" << endl; return 0;}
	
	ofstream ofile(output_file + ".c");
	ofile << "#include <stdio.h>\n#include <stdlib.h>\n\nint main(){\nchar *arr = (char *)calloc(30000,sizeof(char));\nchar *head = arr;\n";
	
	char ch = 0;
	while((ch = ifile.get()) != -1){
		if(ch == '>'){ofile << "\nhead++;";}
		else if(ch == '<'){ofile << "\nhead--;";}
		else if(ch == '+'){ofile << "\n(*head)++;";}
		else if(ch == '-'){ofile << "\n(*head)--;";}
		else if(ch == '.'){ofile << "\nputchar(*head);";}
		else if(ch == ','){ofile << "\n*head = getchar();";}
		else if(ch == '['){ofile << "\nwhile(*head){";}
		else if(ch == ']'){ofile << "\n}";}
	}
	
	ofile << "\n\nfree(arr);\nreturn 0;\n}";
	ofile.close();
	
	if(!compile){return 0;}
	
	string command = "gcc " + output_file + ".c -o " + output_file;
	
	system(command.c_str());
	//remove((output_file + ".c").c_str());
	
	return 0;
}