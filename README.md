# cipherv2
made this since I was bored during quarantine, as a way to apply what I learned during that time.
Uses caesar cipher, and beaufort to make text files unreadable
note that this takes a while for large files exceeding 50Mb, taking up to 150Mb of RAM as well.
currently, XOR does not work as intended for decrypting text files. don't use it.

Use to encrypt a text file: (make sure the txt file is in the same directory as the code)
test.encryptTxt_test("txtfilename", "resultfilename", key);

Decrypt a file:
test.decryptTxt_test("txtfilename", "outputfilename", key);

