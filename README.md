# ISOMORPH

OVERVIEW: 
This project was originally created as an independent final project for the
course Comp 15 at Tufts University. Since its original submission, I have 
continued to develop the program. 
This project utilizes Graph Theory to create a new encryption scheme with a brute force decryption time complexity of N(!). The program reads in a file and converts its bits into an adjacency matrix. It can encrypt the file and generate a key, or it can decrypt the file using a key. The key represents a permutation done to the adjacency matrix (of plaintext) to create an isomorphic graph (ciphertext).

****************************************************************************

May 18, 2017 UPDATE:
-Updated bruteforce encryption to account for new encryption process
-Implemented Heap's Algorithm to efficiently generate all permutations
-Bruteforce process now appears to work - stops when finds correct
key/ permutation. 


May 17, 2017 UPDATE:
-Created Compressor class to handle compression of padding and permutation
information in key file. 
-Binary numbers and decimal numbers are both compressed by being converted
to base 128 digits represented by characters. 
-Binary compression is implemented and seems to be functional. Reduces key 
file size by approx 1/4. 
-Decimal compression also added - now seems to be working - filesizes reduces by about 1/2 in conjunction with pad compression


May 16, 2017 UPDATE:
Updated permutation scheme - now has true n! time complexity
-Encryption randomly scrambles list of labels to create permutation
	-does num_label swaps, moving through array
-Encryption permutes graph by treating permutation as pairs and swapping pairs
in forward order. 
-Outputs permutation list in key.txt instead of listing pairs swapped
-Decryption reads in permutation and permutes by treating permutation as 
pairs and swapping in reverse order (it is the transpose)
-NodePair struct no longer needed in any class

Summary: 
Twice as many swaps are now done when encrypting, decrypting, which
trivially adds to runtime. Likewise, the process of creating the 
permutation takes twice as long, which is trivial. 
Time complexity has greatly increased from the obscene (n!!) to the absurd 
(n!). Though more swaps are done, file size of key is same, since complete permutation is interpreted as series of swaps by encryption, decryption processes.

Goals for next update: 
-Reduce file size of key (without sacrificing security)
	-Compress padding
		- Trivial: 
			-Groups of 8 bits can be printed as chars, to be
			interpreted by decryption class properly later.
			What to do if 8 does not divide pad length?
		- Other ideas: 
			-Represent binary in new base (using ascii values)
				-Base that most effectively compresses!!??
				-Can exceed decimal, hex (using chars). 
			-Represent as prime factorization, some other math 
				-Seems slow!
	-Compress permutation information
		- Possible to represent permutation without added 
		  whitespace delimeters?
		- Can use same base approach as above?
			- Print ints as char instead of string?!!
			- Allows to avoid adding whitespace delims as well!!

********************************************


ORIGINAL README TEXT WITH PROJECT SUBMISSION: 	

COMP15 INEPENDENT PROJECT README - ISOMORPH
Design & Implementation by Sebastian Coates 
Last Updated: April 16, 2017


Algorithms:
Graph permutation - this algorithm takes two labels and switches the values
in the row and column of the graph adjacency matrix corresponding to the two
labels. 

Read plaintext - this algorithm in the graph class buffers the contents of a 
file as a stringstream and then stores the string contained in the 
stringstream. This allows to read the entire file in one go, which preserves
formatting and helps avoid a pesky bug (encrypted chars become whitespace). 

File to bits - this algorithm takes the ascii value of each char in base 10 and
converts to binary so that it can populate the graph with the correct data. 

Graph to string - This reads 8 bits at a time from the graph and converts them
to a character. After appending all these chars in a string, the string is 
returned. 

Random label pairing - this algorithm populates a vector with all the labels in 
a graph. It chooses indices two at a time to pair up labels. The indices of
these labels are randomly generated. Once a label is chosen, it is removed from
the vector. Each pair of numbers is outputted to the key.txt file so that 
the key allows for easy decryption. 

Read key - this first checks if the graph has a non-square number of bits, so
it knows whether or not the key contains padding to add to the back of the 
ciphertext graph. It then reads in two ints as a time, and permutes the graph,
treating the two ints as labels. This essentially reverses all the permutations
done in the encryption process, which decrypts the file. 


Data Structures:
Graph - I implemented a graph data structure in order to facilitate the 
encryption / decryption process. Obviously, it was essential for using graph
isomorphism as an encryption scheme. To imlpement the graph, I used a 2D 
dynamic array, which allows for easy permutation. This particular graph 
structure takes a file and creates a graph that represents all the bits of the 
file (read right-left top-down). If a file does not have a square number of 
bits, extra zeros are added to the end of the graph matrix. 


Decisions and Layout of Project: 
The choice of using a graph as my primary data structure should be obvious,
given the integral role of graph isomorphism in the encryption scheme. I chose
to represent the graph using its adjacency matrix for the ease of relabeling,
simply swapping rows and columns. It also allows for the very easy printing of
the graph as an n by n grid. This was incredibly useful in the debugging 
process to spot issues in the code. 
I chose to represent the pairs of labels in two ways. In the main project,
I used the simple NodePair struct, because it was a very easy way of 
abstracting the label pairs as a distinct unit. In the bruteforce decryption
algorithm, I choose to represent the label pairing as a vector of integers
where adjacent entries (like (0,1) (2,3) ... (n, n+1)) are the label pairs. 
This was much more useful for the process of generating all of the possible 
label pairs, as it facilitated lexographic comparisons. This allowed for an 
easy, systematic way of generating all the possible pairs without repeats.
This made it a better method of implementation than the struct for the 
bruteforce process. 
I think it made sense to separate the normal encryption/decryption process from
the bruteforce decryption process, which is why I have them implemented in 
two separate mains. The bruteforce process is really only interesting as a way
of verifying the strength of encryption, but it is not a practical tool. The 
encryption/decryption using the key are both practical and make sense to be 
combined, as I want someone who uses the program to be able to do both easily.
They are designated by either -encrypt or -decrypt at the command line. 
The graph structure made sense to abstract as a class; and I think this is an
obvious choice. Like a vector or a queue or a stack, it has private data as 
well as public functions. It can be utilized in many programs and is utilized
in both the encryption, decryption, and bruteforce decryption processes. 
The choice of separating the encryption process and the decryption process
into two separate classes was a less trivial decision, as they serve similar
purposes and have a similar general structure. From an abstraction 
perspective, I think it made sense to keep them separate as they do represent
distinct albeit similar processes. Also, in thinking about the program in a 
broader, conceptual sense, the driver serves two functions: to encrypt or to
decrypt. It was conceptually easy to implement this two function driver by 
having its two functions abstracted by two separate classes.


Significant Changes?:
I made no real significant changes to the program from the original 
specification. What was not clear from the spec was how I would handle 
non-square numbers of bits and how many permutations I would do during
encryption to guarentee security. To fix the non-square cases I pad the end
of the graphs with zeros, and I include the permuted pad in the key. To do
an appropriate number of permutations, I pair every label with another label
randomly and swap them. 


Time Spent on Project:
Project Proposal / Spec / Figuring out encryption scheme: 8 hours
Weekend April 9-10: 10 Hours - Initial implementation, functional w odd bug
Monday - Wednesday: 7 Hours - Project fully functional, commented (bug found)
Weekend April 14-15: 5 Hours - README finished & work on Bruteforce extension.
Project presentation created.

Total Hour Tally: 30 hours


Credit: 
Moon Duchin - for indroducing me to the Graph Isomorphism problem and graph
theory. Also, for responding to a late-night email incredibly quickly about
the time complexity of my encryption scheme. 
David LeCount - for introducing me to Number Theory and RSA encryption in 
high school.
Mark Sheldon - for facilitating student interest in individual projects and 
allowing this program to exist. 
Julie Jiang, Winnona DeSombre, and Erica Schwartz - for being so helpful 
throughout the entire independent project process. 
John Tag - for helpful discussion about the encryption scheme and debugging
process. 
COMP 11 Staff - for providing the termfuncs.h and termfuncs.cpp files (with
the comp 11 final project last semester), which make the output of the 
Bruteforce decryption process easier to read and a bit more visually appealing.


Future Improvement in Independent Projects:
For this project, I spent a lot of time planning the project through the 
proposal and specification. This made the process of implementation much 
smoother than it has been for other independent work I've done. I'll take this
as a learning experience to plan thoroughly before going to code. 
I also spent a lot of time talking to others - TAs, Moon, John, other friends -
which helped me in all stages of the process. I'll make sure to speak with 
others when working on future projects so I can get helpful input and make the 
implementation process smooth. 
