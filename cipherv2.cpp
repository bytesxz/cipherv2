/*

- simple cipher alg
- randomly generates key
- this will BREAK any semblance of formatting


*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>

using namespace std;

class algs {
private:
	//nothing to add here for now

public:

	string cscipher(int key, string text) {
		string result = "";

		// traverse text
		for (int i = 0; i < text.length(); i++)
		{
			// apply transformation to each character
			// Encrypt Uppercase letters
			if (isupper(text[i]))
				result += char(int(text[i] + key - 65) % 26 + 65);

			// Encrypt Lowercase letters
			else
				result += char(int(text[i] + key - 97) % 26 + 97);
		}

		// Return the resulting string
		return result;
	}

	string beaufort(string text, string key, string charset) { // beaufort cipher
		string cipher;
		string alphabet = charset;
		for (int i = 0; i < text.size(); i++) {
			char c0 = text[i];
			char c1 = key[i % key.size()];
			int start = 0;
			for (int j = 0; j < 26; j++) {
				if (alphabet[j] == toupper(c0)) {
					start = j;
					break;
				}
			}
			int offset = 0;
			for (int j = start; j < start + 26; j++) {
				int letter = j % 26;
				if (alphabet[letter] == toupper(c1)) {
					break;
				}
				offset++;
			}
			cipher += alphabet[offset];
		}
		return cipher;
	}

	string XOR_base(string key, string phrase) {
		string output = phrase;

		for (int i = 0; i < phrase.size(); i++) {
			int j = 0;
			output[i] = phrase[i] ^ key[j];
			if (j < key.size()) {
				j++;
			}
			else {
				j = 0;
			}
		}

		return output;
	}

	string keymake(int M_iter, int Mkey) { // generates the key for encryption, does not account for the other type. might make this one user supplied.
		string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		string output = "";
		string k1 = "";
		int k2;
		int keylength = rand() % Mkey;
		keylength = keylength = 10;
		int times = (rand() + 1) % M_iter;
		output += to_string(times + 1);
		output += '-';

		for (int i = 0; i <= keylength; i++) {
			int temp = rand() % 25;
			k1 += alphabet[temp];
		}
		output += k1;
		output += '-';

		int t = (rand() % 25);
		k2 = t + 1;
		output += to_string(k2);
		output += '-';
		return output;
	}
};

class encrypt { // i might make a different keygen.
private:
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int key_length = 0;
	int key1 = 0; // gets len
	int key2 = 0;
	int key3 = 0;
	int k1_loc = 0;
	int k2_loc = 0;
	int k3_loc = 0;
	string temp = "";
	string pass1, pass2;

	void reset() {
		key_length = 0;
		key1 = 0;
		key2 = 0;
		key3 = 0;
		k1_loc = 0;
		k2_loc = 0;
		k3_loc = 0;
		temp = "";
		pass1 = "";
		pass2 = "";
	}

public:

	void show_values() {
		cout << "key1_len: " << key1 << endl;
		cout << "key2_len: " << key2 << endl;
		cout << "key3_len: " << key3 << endl;

		cout << "key1_loc: " << k1_loc << endl;
		cout << "key2_loc: " << k2_loc << endl;
		cout << "key3_loc: " << k3_loc << endl;
	}

	string enc(string key, string raw_text) {
		reset(); // idk if deconstructing would be an alternative to this
		string output;
		//get key separation

		//get key sep + ;loc:
		for (int i = 0; i < key.length(); i++) { // get k1 len
			if (key[i] != '-') {
				key1++;
			}
			else if (key[i] == '-') {
				key_length = i;
				k2_loc = (i + 1);
				//cout << key1 << endl;
				break;
			}
		}
		key_length = key_length + 1;
		for (int j = key_length; j < key.length(); j++) { // get k2 len
			if (key[j] != '-') {
				key2++;
			}
			else if (key[j] == '-') {
				key_length = (j + 1);
				k3_loc = (j + 1);
				break;
			}
		}
		for (int k = key_length; k < key.length(); k++) {
			if (key[k] != '-') {
				key3++;
			}
			else if (key[k] == '-') {
				break;
			}
		}
		// get rand char amt
		string temp = "";
		for (int o = 0; o <= 1; o++) {
			temp += key[o];
		}

		// get beau phrase
		string Pphrase;
		for (int m = k2_loc; m <= (key2 + 2); m++) {
			Pphrase += key[m];
		}

		// get ciph key
		string ckey = "";
		for (int n = (k3_loc); n < (key.length() - 1); n++) {
			ckey += key[n];
		}

		//start encryption
		int n_char = stoi(temp);
		for (int l = 0; l < n_char; l++) {
			int choice = (rand() % 25);
			output += alphabet[choice];
		}

		// get alg instances:

		algs inst;

		// passphrase is known, pass through function, store to temp var
		string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		string first_pass = inst.beaufort(raw_text, Pphrase, charset);

		// pass through ciph:
		int ciph_key = stoi(ckey); // pass ckey string to stoi, get number
		string second_pass = inst.cscipher(ciph_key, first_pass); // encrypt

		// append to output string:
		output += second_pass;
		return output;
	}

	string decr(string key, string raw_text) {
		reset();
		string output;

		for (int i = 0; i < key.length(); i++) { // get k1 len
			if (key[i] != '-') {
				key1++;
			}
			else if (key[i] == '-') {
				key_length = i;
				k2_loc = (i + 1);
				//cout << key1 << endl;
				break;
			}
		}
		key_length = key_length + 1;
		for (int j = key_length; j < key.length(); j++) { // get k2 len
			if (key[j] != '-') {
				key2++;
			}
			else if (key[j] == '-') {
				key_length = (j + 1);
				k3_loc = (j + 1);
				break;
			}
		}
		for (int k = key_length; k < key.length(); k++) {
			if (key[k] != '-') {
				key3++;
			}
			else if (key[k] == '-') {
				break;
			}
		}

		// get keys

		for (int o = 0; o <= 2; o++) {
			temp += key[o];
		}

		int n_char = stoi(temp);

		//use first key to remove chars from string
		//cout << "char_n: " << n_char << endl;
		for (int l = n_char; l < raw_text.length(); l++) { // use this to remove chars
			output += raw_text[l];
		}

		// get beau phrase;
		string Pphrase;
		for (int m = k2_loc; m <= (key2 + 2); m++) {
			Pphrase += key[m];
		}

		// get ciph key
		string ckey = "";
		for (int n = (k3_loc); n < (key.length() - 1); n++) {
			ckey += key[n];
		}
		// get alg instance:
		algs decrypt;
		//decode everything, pray it works
		int caes_key = stoi(ckey);
		pass1 = decrypt.beaufort(output, Pphrase, alphabet);

		pass2 = decrypt.cscipher(caes_key, pass1);
		output = pass2;

		//return
		return output;
	}
};

class file_handler {
private:
	string filename;
	ofstream outfile;
	string outName = filename;
	vector<string> text;

public:
	file_handler(string f_name, int NorOl = 0) { // constructor
		filename = f_name;
		outName = filename;
		if (NorOl == 0) {
			outName += ".txt"; // save as txt file
		}
	}

	void makefile() {
		outfile.open(outName);

		if (outfile.is_open()) {
			outfile.close();
			cout << "txt file generated" << endl;
		}
		else {
			cout << "could not create file: " << outName << ". Check permissions" << endl;
		}
	}

	void writefile(string data) {
		int open_state = 0;
		outfile.open(outName, ios::app); // iostream app = append to list of characters.

		if (outfile.is_open()) {
			open_state = 1;
			cout << "file opened!" << endl;
		}
		else {
			open_state = 0;
			cout << "File open error." << endl;
		}
		cout << "writing to a file: " << data << endl;

		outfile << data << endl;

		outfile.close();
	}

	void readfile() { // reading line by line is... cancer.
		string infilen = outName;
		string output;
		ifstream infile;
		string line;
		infile.open(outName);
		if (infile.is_open()) {
			cout << "file opened: " << outName << endl;

			while (!infile.eof()) {
				getline(infile, line);
				cout << line << endl;
				text.push_back(line);
			}
		}
		else {
			cout << "file open error: " << outName << endl;
		}
	}

	vector<string> getvals() {
		return text;
	}
};

class assemblers {
private:

public:

	string run_test(string phrase, int x = 0) {
		algs alg;
		string yes = alg.keymake(100, 20);

		encrypt st;
		string nooo = st.enc(yes, "jiajia");

		if (x == 0) {
			;
		}
		else if (x == 1) {
			st.show_values();
		}

		cout << "key: " << yes << endl;
		cout << "encrypted: " << nooo << endl;

		string asdf = st.decr(yes, nooo);
		cout << "decrypted: " << asdf << endl;

		return asdf;
	}

	void test_consistency(int amt, string phrase) {
		for (int i = 0; i < amt; i++) {
			string decr = run_test(phrase);
		}
	}

	void testFileHandling() {
		file_handler hopeitworks("testtesttest", 0);
		hopeitworks.writefile("1");
		hopeitworks.writefile("2");
		hopeitworks.writefile("3");
		hopeitworks.writefile("4");

		hopeitworks.readfile();

		file_handler testopen("research", 0);
		testopen.readfile();
	}

	void encryptTxt_test(string inputfile, string outputfile, string key) {
		// variables
		vector<string> input_txt;

		// get instances for encryption
		file_handler getfile(inputfile);
		getfile.readfile();
		input_txt = getfile.getvals();

		// make a file that will be outputted to
		file_handler encryptedfile(outputfile);
		encryptedfile.makefile();

		//we now have the values, encrypt
		encrypt file;
		string temp = "";
		for (int i = 0; i < input_txt.size(); i++) {
			temp = file.enc(key, input_txt[i]);
			encryptedfile.writefile(temp);
			cout << "line: " << temp << endl;
		}
	}

	void decryptTxt_test(string inputfile, string outputfile, string key) {
		// variables
		vector<string> input_txt;

		// get instances for encryption
		file_handler fileget(inputfile);
		fileget.readfile();
		input_txt = fileget.getvals();

		// make a file that will be outputted to
		file_handler encryptedfile(outputfile);
		encryptedfile.makefile();

		//we now have the values, encrypt
		encrypt file;
		string temp = "";
		for (int i = 0; i < input_txt.size(); i++) {
			temp = file.decr(key, input_txt[i]);
			encryptedfile.writefile(temp);
			cout << "line: " << temp << endl;
		}
	}

};

int main() {
	srand(time(0)); // makes n a lot more random. (don't remove this)

	algs getkey;
	string key = getkey.keymake(100, 20);
	string key2 = "thisisakeyyes";

	assemblers test;
	test.encryptTxt_test("research", "resencrypted", key);

	test.decryptTxt_test("resencrypted", "resdecrypted", key);

	return 0;
}