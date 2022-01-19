#include <iostream>
#include <vector>
#include <fstream>
#include <string>


std::string commands;

int8_t mem[1000] = { 0 };

int memptr = 0; 
int codeptr = 0; 



std::string parseCode() {

	std::ifstream file;

	std::string temp; 

	file.open("temp.txt");

	std::string line;

	while (std::getline(file, line)) {
		temp += line;
	}
	file.close();



	line.clear(); 

	while (!temp.empty()) {
		if (temp[0] == '.' || temp[0] == ',' || temp[0] == '<' || temp[0] == '>' || temp[0] == '+' || temp[0] == '-' || temp[0] == '[' || temp[0] == ']') {
			line += temp[0]; 
		}
		temp.erase(0, 1); 
	}
	std::cout << line << std::endl << std::endl << std::endl << std::endl;
	return line; 
}

int findMatching(int ptr, int step) {
	int counter = 1;

	while (counter != 0) {
		ptr += step;
		if (commands[ptr] == '[') {
			counter += step; 
		}

		if (commands[ptr] == ']') {
			counter -= step; 
		}
	}
	return step == -1 ? ptr : ptr + step; 
}


int main() {

	commands = parseCode(); 

	std::ofstream code("Code.cpp"); 

	code << "#include <iostream>\n\nint main(){\n"; 
	code << "int mem[30000] = {0}; \n int memptr = 50; \nchar temp;\n";

	int count = 0; 
	while (count < commands.length()) {
		if (commands[count] == '+') {
			code << "mem[memptr]++;\n "; 
		}

		if (commands[count] == '-') {
			code << "mem[memptr]--;\n ";
		}

		if (commands[count] == '.') {
			code << "std::cout << (char)mem[memptr]; \n";
		}

		if (commands[count] == ',') {
			code << "temp = ' '; std::cin >> temp; mem[memptr] = (int)temp; \n";
		}

		if (commands[count] == '>') {
			code << "memptr++; \n";
		}		
		
		if (commands[count] == '<') {
			code << "memptr--; \n";
		}

		if (commands[count] == '[') {
			code << "while (mem[memptr] != 0){\n";
		}

		if (commands[count] == ']') {
			code << "}\n";
		}

		count++; 
	}

	code << "\n\nreturn 0;\n}"; 

	code.close(); 

	system("g++ -o output Code.cpp");
	system("output.exe"); 


	int a; 
	std::cin >> a; 
	return 0;
}


/*
]++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.




++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.+++++++++++++++++++++++++++++.+++++++..+++.-------------------------------------------------------------------.------------.+++++++++++++++++++++++++++++++++++++++++++++++++++++++.++++++++++++++++++++++++.+++.------.--------.-------------------------------------------------------------------.






++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++>++++++++++++++++>>+<<[>>>>++++++++++<<[->+>-[>+>>]>[+[-<+>]>+>>]<<<<<<]>[<+>-]>[-]>>>++++++++++<[->-[>+>>]>[+[-<+>]>+>>]<<<<<]>[-]>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]<[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]<<<++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<<<<<<.>.>>[>>+<<-]>[>+<<+>-]>[<+>-]<<<-]<<++...
*/